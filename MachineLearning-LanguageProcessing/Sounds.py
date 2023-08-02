import math as math  
import os 
import numpy as np 
import librosa, librosa.display
import matplotlib.pyplot as plt
# 1. Get the file path to an included audio example
# filename = librosa.example('nutcracker')


# 2. Load the audio as a waveform `y`
#    Store the sampling rate as `sr`
# y, sr = librosa.load(filename)

# 3. Run the default beat tracker
# tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)

# print('Estimated tempo: {:.2f} beats per minute'.format(tempo))

# 4. Convert the frame indices of beat events into timestamps
# beat_times = librosa.frames_to_time(beat_frames, sr=sr)
# print(y, y.__dir__, sr, sr.__dir__)
if __name__ == '__main__':
    filepath = 'C:/Users/jkohh/Desktop/ProjectUno/Test.wav'
    #waveform
    signal, sr = librosa.load(filepath, sr=22050)
    #librosa.display.waveplot(signal, sr=sr)
    #plt.xlabel("time")
    #plt.ylabel("amplitude")
    #plt.show()
    #fft = np.fft.fft(signal)

    #magnitude = np.abs(fft)
    #frequency = np.linspace(0, sr, len(magnitude))
    #plt.plot(frequency, magnitude)
    #plt.xlabel('frequency')
    #plt.ylabel('magnitude')
    #plt.show()
    #print(signal,sr)
    #tempo, beats = librosa.beat.beat_track(y=signal,sr=sr)
    #print('tempo: ', tempo)
    #previous = 0
    #for timestamp in beats:
    #    print(int(timestamp) - previous)
    #    previous = timestamp



    onset_env = librosa.onset.onset_strength(signal, sr=sr, aggregate=np.median)
    tempo, beats = librosa.beat.beat_track(onset_envelope=onset_env, sr=sr)
    hop_length = 512
    fig, ax = plt.subplots(nrows=2, sharex=True)
    print(type(fig),fig,type(ax),ax)

    times = librosa.times_like(onset_env, sr=sr, hop_length=hop_length)
    M = librosa.feature.melspectrogram(y=signal, sr=sr, hop_length=hop_length)
    librosa.display.specshow(librosa.power_to_db(M, ref=np.max),
                             y_axis='mel', x_axis='time', hop_length=hop_length,
                             ax=ax[0])
    ax[0].label_outer()
    ax[0].set(title='Mel spectrogram')
    ax[1].plot(times, librosa.util.normalize(onset_env),
             label='Onset strength')
    ax[1].vlines(times[beats], 0, 1, alpha=0.5, color='r',
               linestyle='--', label='Beats')
    ax[1].legend()
    print(M)
    plt.show()

    librosa.feature.mfcc(signal,sr=sr)
    fig, ax = plt.subplots()
    mfccs = librosa.feature.mfcc(y=signal, sr=sr, n_mfcc=40)
    img = librosa.display.specshow(mfccs, x_axis = 'time', ax=ax)
    fig.colorbar(img, ax=ax)
    ax.set(title='MFCC')
    print(mfccs)
    plt.show()
    
