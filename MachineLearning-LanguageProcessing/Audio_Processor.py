import math as math  
import os 
import numpy as np 
import librosa, librosa.display
import matplotlib.pyplot as plt
import time
def process(filepath,show_MEL=False,show_MFCC=False):
    signal, sr = librosa.load(filepath)
    onset_env = librosa.onset.onset_strength(signal, sr=sr, aggregate=np.median)
    tempo, beats = librosa.beat.beat_track(onset_envelope=onset_env, sr=sr)
    hop_length = 512


    times = librosa.times_like(onset_env, sr=sr, hop_length=hop_length)
    M = librosa.feature.melspectrogram(y=signal, sr=sr, hop_length=hop_length)

    if show_MEL:
        fig, ax = plt.subplots(nrows=2, sharex=True)
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
    mfccs = librosa.feature.mfcc(y=signal, sr=sr, n_mfcc=40)

    if show_MFCC:
        fig, ax = plt.subplots(nrows=2, sharex=True)
        librosa.display.specshow(librosa.power_to_db(M, ref=np.max),
                                    y_axis='mel', x_axis='time', hop_length=hop_length,
                                    ax=ax[0])
        fig, ax = plt.subplots()
        img = librosa.display.specshow(mfccs, x_axis = 'time', ax=ax)
        fig.colorbar(img, ax=ax)
        ax.set(title='MFCC')
        print(mfccs)
        plt.show()
    return M, mfccs

data = process('D:\\voices\\train-clean-100.tar\\LibriSpeech\\train-clean-100\\1-911\\19\\198\\19-198-0000.flac',True,True)
for vector in data[0]:
    print(len(vector))


def file_parse(root_file,function_to_run,new_directory):
    time_list = [time.time()]
    author_list = list(os.listdir(root_file))
    for a, author in enumerate(os.listdir(root_file),1):
        time.sleep(0.1)
        percent = float(a)/float(len(author_list)) * 100
        #print('author: ', author)
        for b, chapter in enumerate(os.listdir(root_file+'\\'+author)):
            print(f"transferring {author}'s {chapter}")
            old_directory = root_file + author +  '\\' + chapter
            function_to_run(old_directory,author,chapter,new_directory)
            #print('author,chapter: ', author, chapter )
        time_list.append(time.time())
        estimate_total_time = ((time_list[-1] - time_list[0])/percent * (100 / 60))
        eta = estimate_total_time *(1-percent)/100
        print(f'done with author: {author} which is {percent}% done, should be done in {eta} minutes')
        
            #print('chapter: ', chapter)
            #for section in chapter:
            #    print(author,'\t',chapter)
            #    if '.txt' in section:
            #        print('this is the transcipt for this chapter: ', section)



def transfer_chapter(chapter_directory,author,chapter,new_directory):
    transcript_path = chapter_directory+'\\'+author+'-'+chapter+'.trans.txt'
    transcript = open(transcript_path)

    for i, section in enumerate(os.listdir(chapter_directory)):
        if i < 10:
            i = '000'+str(i)
        elif i < 100:
            i = '00'+str(i)
        elif i < 1000:
            i = '0'+str(i)
        else:
            i = str(i)
        if '.txt' not in section: # get the transcript file out of here
            #print(f'transferring stuff from {old_file} to {new_directory}\\{author}-{chapter}-{i}.txt')
            current_line = transcript.readline()
            current_line_list = current_line.split(' ')
            del current_line_list[0]
            current_line = ' '.join(current_line_list)
            new_transcript = open(new_directory+'\\'+author+'-'+chapter+'-'+i+'.trans.txt','w')
            new_transcript.write(current_line)
            #print(f'transferring stuff from {transcript_path} ({current_line}) to {new_directory}\\{author}-{chapter}-{i}.trans.txt')

            # ^^parse the transcript
            
            audio_file = chapter_directory+'\\'+author+'-'+chapter+'-'+i+'.flac'
            MEL, MFCC = process(audio_file)
            # ^^ process the audio
            new_MEL = open(new_directory+'\\'+author+'-'+chapter+'-'+i+'.MEL.txt','w')
            new_MEL.write(str(MEL.tolist()))
            new_MFCC = open(new_directory+'\\'+author+'-'+chapter+'-'+i+'.MFCC.txt','w')
            new_MFCC.write(str(MFCC.tolist()))
            new_MEL.close()
            new_MFCC.close()
            new_transcript.close()
        #print('done with ',author,'-',chapter)
            # write the audio for one section
    transcript.close()

#file_parse('D:\\voices\\train-clean-100.tar\\LibriSpeech\\train-clean-100\\1-911\\',transfer_chapter,'D:\\voices\\data')
# transfer_chapter('D:\\voices\\train-clean-100.tar\\LibriSpeech\\train-clean-100\\19\\227','19','227','D:\\voices\\data')
#print(f.readline())
#print(f.readline())
#f.close()