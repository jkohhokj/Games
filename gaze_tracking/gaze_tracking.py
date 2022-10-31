from __future__ import division
import os
import cv2
import dlib
from .eye import Eye
from .calibration import Calibration
import time
import keyboard

class GazeTracking(object):
    """
    This class tracks the user's gaze.
    It provides useful information like the position of the eyes
    and pupils and allows to know if the eyes are open or closed
    """

    def __init__(self):
        self.frame = None
        self.eye_left = None
        self.eye_right = None
        self.coeff = 1.4
        self.calibration = Calibration()

        # _face_detector is used to detect faces
        self._face_detector = dlib.get_frontal_face_detector()

        # _predictor is used to get facial landmarks of a given face
        cwd = os.path.abspath(os.path.dirname(__file__))
        model_path = os.path.abspath(os.path.join(cwd, "trained_models/shape_predictor_68_face_landmarks.dat"))
        self._predictor = dlib.shape_predictor(model_path)

    @property
    def pupils_located(self):
        """Check that the pupils have been located"""
        try:
            int(self.eye_left.pupil.x)
            int(self.eye_left.pupil.y)
            int(self.eye_right.pupil.x)
            int(self.eye_right.pupil.y)
            return True
        except Exception:
            return False

    def _analyze(self):
        """Detects the face and initialize Eye objects"""
        frame = cv2.cvtColor(self.frame, cv2.COLOR_BGR2GRAY)
        faces = self._face_detector(frame)

        try:
            landmarks = self._predictor(frame, faces[0])
            self.eye_left = Eye(frame, landmarks, 0, self.calibration)
            self.eye_right = Eye(frame, landmarks, 1, self.calibration)

        except IndexError:
            self.eye_left = None
            self.eye_right = None

    def refresh(self, frame):
        """Refreshes the frame and analyzes it.

        Arguments:
            frame (numpy.ndarray): The frame to analyze
        """
        self.frame = frame
        self._analyze()

    def pupil_left_coords(self):
        """Returns the coordinates of the left pupil"""
        if self.pupils_located:
            x = self.eye_left.origin[0] + self.eye_left.pupil.x
            y = self.eye_left.origin[1] + self.eye_left.pupil.y
            return (x, y)

    def pupil_right_coords(self):
        """Returns the coordinates of the right pupil"""
        if self.pupils_located:
            x = self.eye_right.origin[0] + self.eye_right.pupil.x
            y = self.eye_right.origin[1] + self.eye_right.pupil.y
            return (x, y)

    def horizontal_ratio(self):
        """Returns a number between 0.0 and 1.0 that indicates the
        horizontal direction of the gaze. The extreme right is 0.0,
        the center is 0.5 and the extreme left is 1.0
        """
        if self.pupils_located:
            pupil_left = self.eye_left.pupil.x / (self.eye_left.center[0] * 2)# - 10)
            pupil_right = self.eye_right.pupil.x / (self.eye_right.center[0] * 2)# - 10)
            return ((pupil_left + pupil_right) / 2 - .5) * self.coeff + .5

    def vertical_ratio(self):
        """Returns a number between 0.0 and 1.0 that indicates the
        vertical direction of the gaze. The extreme top is 0.0,
        the center is 0.5 and the extreme bottom is 1.0
        """
        if self.pupils_located:
            pupil_left = self.eye_left.pupil.y / (self.eye_left.center[1] * 2)# - 10)
            pupil_right = self.eye_right.pupil.y / (self.eye_right.center[1] * 2)# - 10)
            return ((pupil_left + pupil_right) / 2 - .5) * self.coeff + .5

    def is_right(self):
        """Returns true if the user is looking to the right"""
        if self.pupils_located:
            return self.horizontal_ratio() <= 0.35

    def is_left(self):
        """Returns true if the user is looking to the left"""
        if self.pupils_located:
            return self.horizontal_ratio() >= 0.65

    def is_center(self):
        """Returns true if the user is looking to the center"""
        if self.pupils_located:
            return self.is_right() is not True and self.is_left() is not True

    def is_blinking(self):
        """Returns true if the user closes his eyes"""
        if self.pupils_located:
            blinking_ratio = (self.eye_left.blinking + self.eye_right.blinking) / 2
            return blinking_ratio > 3.8

    def annotated_frame(self):
        """Returns the main frame with pupils highlighted"""
        frame = self.frame.copy()

        if self.pupils_located:
            color = (0, 255, 0)
            x_left, y_left = self.pupil_left_coords()
            x_right, y_right = self.pupil_right_coords()
            cv2.line(frame, (x_left - 5, y_left), (x_left + 5, y_left), color)
            cv2.line(frame, (x_left, y_left - 5), (x_left, y_left + 5), color)
            cv2.line(frame, (x_right - 5, y_right), (x_right + 5, y_right), color)
            cv2.line(frame, (x_right, y_right - 5), (x_right, y_right + 5), color)

        return frame


class Timer(object):

    def __init__(self):
        self.stopped = True
        self.times = []
        self.start_time = 0
        self.stop_time = 0
        self.refresh_limit = 10
        self.refresh_timer = 0
        self.text = ""
        self.reaction = 0
        self.live = False
        keyboard.add_hotkey('q',self.set_stim, args=("LOOK RIGHT",.4))
        keyboard.add_hotkey('w',self.set_stim, args=("LOOK LEFT",.6))

    def start_clock(self):
        self.start_time = time.time()
        self.live = True
    def stop_clock(self):
        self.stop_time = time.time()
        self.times.append(self.stop_time-self.start_time)
        self.live = False
        print(self.stop_time, self.start_time)
    def set_stim(self,text="LOOK RIGHT",reaction=.4):
        self.text = text
        self.reaction = reaction
        self.start_clock()
    def run(self):
        gaze = GazeTracking()
        webcam = cv2.VideoCapture(0)
        self.stopped = False
        #
        #
        #
        #self.set_stim()
        while not self.stopped:
            # We get a new frame from the webcam
            _, frame = webcam.read()

            # We send this frame to GazeTracking to analyze it
            gaze.refresh(frame)

            frame = gaze.annotated_frame()

            cv2.putText(frame, self.text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

            left_pupil = gaze.pupil_left_coords()
            right_pupil = gaze.pupil_right_coords()
            vertical_ratio = gaze.vertical_ratio()
            horizontal_ratio = gaze.horizontal_ratio()
            #cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            #cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            cv2.putText(frame, "Ratios: " + str(vertical_ratio)[:4] + " " + str(horizontal_ratio)[:4], (90, 210), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            cv2.putText(frame, "Times: " + str([str(ti)[:3] for ti in self.times]), (90, 150), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            if self.live:
                cv2.putText(frame, "Current Timer: " + str(round(time.time()-self.start_time,3)), (90, 120), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            else:
                cv2.putText(frame, "Current Timer: ", (90, 120), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            cv2.imshow("Demo", frame)

            self.refresh_timer += 1
            if cv2.waitKey(1) == 27:
                self.stopped = True
            if horizontal_ratio != None and self.refresh_timer >= self.refresh_limit:
                self.refresh_timer = 0
                if self.reaction > .5:
                    if horizontal_ratio > self.reaction and self.live:
                        self.stop_clock()
                        self.text = ""
                if self.reaction < .5:
                    if horizontal_ratio < self.reaction and self.live:
                        self.stop_clock()
                        self.text = ""
        webcam.release()
        cv2.destroyAllWindows()