#!/usr/bin/env python
# coding: utf-8

# In[1]:


def get_rand_word():
    import urllib.request
    import random
    word_url = "http://svnweb.freebsd.org/csrg/share/dict/words?view=co&content-type=text/plain"
    response = urllib.request.urlopen(word_url)
    long_txt = response.read().decode()
    words = long_txt.splitlines()
    x = random.randint(1,10000)
    word = words[x]
    return word


# In[2]:


def board(word):
    line = ''
    for char in word:
        line = line + ' _'
    return line


# In[3]:


def tries_print(tries):
    man = ""
    if tries == 0:
        return ''
    if tries == 1:
        man = "   \n|  |"
    if tries == 2:
        man = "  __\n |__|"
    if tries == 3:
        man = " __\n|__|\n  |"
    if tries == 4:
        man = " __\n|__|\n  |\n  |"
    if tries == 5:
        man = " __\n|__|\n _|__ \n  |"
    if tries == 6:
        man = " __\n|__|\n\_|__/\n  |"
    if tries == 7:
        man = " __\n|__|\n\_|__/\n  |\n /"
    if tries == 8:
        man = " __\n|__|\n\_|__/\n  |\n /\n/"
    if tries == 9:
        print(" __\n|__|\n\_|__/\n  |\n /\ \n/  ")
    if tries == 10:
        print(" __\n|__|\n\_|__/\n  |\n /\ \n/  \ ")
    if tries == 11:
        print(" __\n|`_`|\n\_|__/\n  |\n /\ \n/  \ ")
    if tries == 12:
        print("  __\nL|`_`| LLLLLLLLLLLL\n \_|__/\n   |\n  /\ \n /  \ ")
    return man


# In[4]:


def hangman():
    failed_tries = 0
    failed_lets = []
    word = get_rand_word()
    line = board(word)
    guessed_board = ' '*len(word)
    print(line)
    word_in_list = list(word)
    word = ' '.join(word_in_list)
    length = len(word_in_list)
    guessed_board_list = list(guessed_board)
    while failed_tries < 12 and guessed_board_list != word_in_list:
        guessing = input('What letters do you want to guess?')
        x = 0
        guessed = 0   
        while x < len(word_in_list):
            if guessing == word_in_list[x]:
                guessed_board_list[x] = word_in_list[x]
                x += 1
                guessed += 1
            else:
                x += 1
        if guessed == 0:
            failed_tries += 1
            failed_lets.extend([guessing])
        guessed_board = ' ' + ' '.join(guessed_board_list) 
        print(guessed_board)
        print(line)
        print('Wrong letters:' + '  '.join(failed_lets))
        print(tries_print(failed_tries))
    if failed_tries == 12:
        print('You lose')
        print(word)
    elif guessed_board_list == word_in_list:
        print('You win')
        print(word)
    else:
        print('Error 404')


# In[5]:


get_rand_word()


# In[6]:


board('word')


# In[7]:


tries_print(11)


# In[ ]:


hangman()


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:




