import csv
def parse():
    f = open('D:\\voices\\dictionary.txt','r',encoding='utf8')
    buffer = open('D:\\voices\\new_dictionary.txt','w',encoding='utf8')
    for line in f:
        comma = False
        new_line = []
        line = list(line)
        no_space = False
        phoenetic = False
        kill = False
        for charIndex in range(len(line)):
            if line[charIndex] == ',':
                new_line.append('\n')
                break
            if line[charIndex] == ' ' or line[charIndex] == '\t' and comma == False:
                new_line.append(',')
                comma = True
            else:
                if line[charIndex] != '/':
                    new_line.append(line[charIndex])
        buffer.write(''.join(new_line))
    f.close()
    buffer.close()
d = {}
with open('D:\\voices\\new_dictionary.txt', newline='', encoding='utf8') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:
        d[row[0]] = row[1]

print(d['the'])