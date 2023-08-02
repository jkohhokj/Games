import numpy as np
import cv2
from gaze_tracking import GazeTracking

class Timer(object):

    def __init__(self, eye_frame, threshold):
        self.iris_frame = None
        self.threshold = threshold
        self.x = None
        self.y = None
        self.stopped = True

        self.detect_iris(eye_frame)

    @staticmethod
    def run(self):
        gaze = GazeTracking()
        webcam = cv2.VideoCapture(0)
        self.stopped = False
        while not self.stopped:
            # We get a new frame from the webcam
            _, frame = webcam.read()

            # We send this frame to GazeTracking to analyze it
            gaze.refresh(frame)

            frame = gaze.annotated_frame()
            text = ""

            if gaze.is_blinking():
                text = "Blinking"
            elif gaze.is_right():
                text = "Looking right"
            elif gaze.is_left():
                text = "Looking left"
            elif gaze.is_center():
                text = "Looking center"

            cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

            left_pupil = gaze.pupil_left_coords()
            right_pupil = gaze.pupil_right_coords()
            vertical_ratio = gaze.vertical_ratio()
            horizontal_ratio = gaze.horizontal_ratio()
            cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
            cv2.putText(frame, "Ratios: " + str(vertical_ratio)[:4] + " " + str(horizontal_ratio)[:4], (90, 210), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

            cv2.imshow("Demo", frame)

            if cv2.waitKey(1) == 27:
                self.stopped = True
        webcam.release()
        cv2.destroyAllWindows()
