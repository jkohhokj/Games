import pygame
import numpy as np
import random as rand
import time
def reset_grid(dead_subpiece_place_list):
    grid = np.zeros((25,13),dtype='int32')
    grid[:,0] = True
    grid[:,-2] = True
    grid[-1,:] = True
    for i in range(25):
        if i < 4:
            grid[i,-1] = i
        else:
            grid[i,-1] = i-4
    for dead_subpiece_place in dead_subpiece_place_list:
        grid[dead_subpiece_place[1]][dead_subpiece_place[0]] = 1
    return grid
def test_grid_maker(dead_subpiece_place_list):
    test_grid = np.zeros((25,12),dtype='int32')
    test_grid[:,0] = True
    test_grid[:,-1] = True
    test_grid[-1,:] = True
    for dead_subpiece_place in dead_subpiece_place_list:
        grid[dead_subpiece_place[1]][dead_subpiece_place[0]] = 1
    return test_grid    #already occupied = 5

class Subpiece(pygame.sprite.Sprite): # class with sprite attribute
    def __init__(self,x=0,y=0,color=(255,255,255)):
        super().__init__()
        self.image = pygame.Surface([20,20])
        self.image.fill(color)
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
    def getxy(self):
        return (self.rect.x, self.rect.y)
    def getcenterxy(self):
        return (self.rect.x-10,self.rect.y-10)
    def setxy(self,x,y):
        self.rect.x = x
        self.rect.y = y
    def getcorners(self):
        return [[self.rect.x,self.rect.y],[self.rect.x+10,self.rect.y], [self.rect.x+10,self.rect.y+10],[self.rect.x,self.rect.y+10]]
    def setcenterxy(self,x,y):
        self.rect.x = x - 10
        self.rect.y = y - 10
    def getgridplace(self):
        return (int(self.rect.x/20)+1,int(self.rect.y/20)+4)

        
class Piece(pygame.sprite.Sprite): # class with group attribute of 4 subpieces with a shape
    def __init__(self,a,b,c,d,pointofrotation,color=(255,255,255)):
        super().__init__()
        self.Apiece = Subpiece(a[0],a[1],color)
        self.Bpiece = Subpiece(b[0],b[1],color)
        self.Cpiece = Subpiece(c[0],c[1],color)
        self.Dpiece = Subpiece(d[0],d[1],color)  
        self.group = pygame.sprite.Group(self.Apiece,self.Bpiece,self.Cpiece,self.Dpiece)
        self.por = pointofrotation
        self.rotation = 0
        self.shape = ''
    def getgridplace(self):
        self.gridplace = [subpiece.getgridplace() for subpiece in self.group]
        return self.gridplace
    def set_shape(self,a,b,c,d):
        self.Apiece = Subpiece(a[0],a[1])
        self.Bpiece = Subpiece(b[0],b[1])
        self.Cpiece = Subpiece(c[0],c[1])
        self.Dpiece = Subpiece(d[0],d[1])        
    def set_gravity(self):
        for subpiece in self.group:
            subpiece.rect.y += 20
        self.por[1] += 20
    def set_reverse_gravity(self):
        for subpiece in self.group:
            subpiece.rect.y -= 20
        self.por[1] -= 20
    def move_right(self):
        for subpiece in self.group:
            subpiece.rect.x += 20
        self.por[0] += 20
    def move_left(self):
        for subpiece in self.group:
            subpiece.rect.x -= 20
        self.por[0] -= 20
    def check_right(self):
        for subpiece in self.group:
    #         print(grid[piece_place[i][1]+5][piece_place[i][0]+2])
            if grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]+1] == 1:
                grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]+1] = 3
#                 print(grid)
                return False
        return True
    def check_left(self):
        for subpiece in self.group:
            if grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]-1] == 1:
                grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]-1] = 3
                return False
        return True            
    def check_bottom(self):
        for subpiece in self.group:
            if grid[subpiece.getgridplace()[1]+1][subpiece.getgridplace()[0]] == 1:
                grid[subpiece.getgridplace()[1]+1][subpiece.getgridplace()[0]] = 3    
                return False
        return True    
    def check_ccw_rotation(self):
        self.rotateccw()
        for subpiece in self.group:
            if grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] == 1:
                grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] = 3
                self.rotatecw()
                return False
        self.rotatecw()
        return True
    def check_cw_rotation(self):
        self.rotatecw()
        for subpiece in self.group:
            if grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] == 1:
                grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] = 3
                self.rotateccw()
                return False
        self.rotateccw()
        return True
    def rotateccw(self):
        if self.shape == 'I' or self.shape == 'Z' or self.shape == 'S': # Z,S, and I piece only have 2 positions
            if self.rotation >= 0:  
                for subpiece in self.group: 
                    #x,y -> y,-x
                    subpiece.setxy(subpiece.rect.y - self.por[1] + self.por[0],-1*(subpiece.rect.x - self.por[0])+self.por[1]-20)
                self.rotation -= 1
            else:
                self.rotatecw()
        else:
            for subpiece in self.group: 
                #x,y -> y,-x
                subpiece.setxy(subpiece.rect.y - self.por[1] + self.por[0],-1*(subpiece.rect.x - self.por[0])+self.por[1]-20)

    def rotatecw(self):
        if self.shape == 'I' or self.shape == 'Z' or self.shape == 'S': # Z,S, and I piece only have 2 positions
            if self.rotation <= 0:  
                for subpiece in self.group: 
                    #x,y -> -y,x
                    subpiece.setxy(-1*(subpiece.rect.y - self.por[1]) + self.por[0]-20,subpiece.rect.x - self.por[0]+self.por[1])
                self.rotation += 1
            else:
                self.rotateccw()    
        else:
            for subpiece in self.group: 
                #x,y -> -y,x
                subpiece.setxy(-1*(subpiece.rect.y - self.por[1]) + self.por[0]-20,subpiece.rect.x - self.por[0]+self.por[1])

def random_shape_gen(por): #starting point
    letters_list = ['L','J','I','O','Z','S','T']
    next_letter = rand.choice(letters_list)
    if next_letter == 'L':
        next_piece = Piece([por[0]-10, por[1]-30],[por[0]-10, por[1]-10],[por[0]-10, por[1]+10],[por[0]+10, por[1]+10],[por[0], por[1]],(3, 65, 174))
    elif next_letter == 'O':
        por[0]+=10
        por[1]+=10
        next_piece = Piece([por[0]-20,por[1]-20],[por[0],por[1]-20],[por[0],por[1]],[por[0]-20,por[1]],[por[0],por[1]],(255, 151, 28))
    elif next_letter == 'J':
        next_piece = Piece([por[0]-10, por[1]-30],[por[0]-10, por[1]-10],[por[0]-10, por[1]+10],[por[0]-30, por[1]+10],[por[0], por[1]],(255, 213, 0))
    elif next_letter == 'I':
        next_piece = Piece([por[0]-10, por[1]-30],[por[0]-10, por[1]-10],[por[0]-10, por[1]+10],[por[0]-10, por[1]+30],[por[0], por[1]],(146, 211, 202))
    elif next_letter == 'Z':
        por[0]+=10
        por[1]+=10
        next_piece = Piece([por[0]-20, por[1]-20],[por[0], por[1]-20],[por[0], por[1]],[por[0]+20, por[1]],[por[0]+10, por[1]+10],(255, 50, 19))
    elif next_letter == 'S':
        por[0]+=10
        por[1]+=10
        next_piece = Piece([por[0], por[1]-20],[por[0]-20, por[1]-20],[por[0]-20, por[1]],[por[0]-40, por[1]],[por[0]-10, por[1]-10],(114, 203, 59))
    elif next_letter == 'T':
        next_piece = Piece([por[0]-10, por[1]-30],[por[0]-10, por[1]-10],[por[0]-10, por[1]+10],[por[0]+10, por[1]-10],[por[0], por[1]],(255,0,255))
        
    next_piece.shape = next_letter
    return next_piece    
def gravity(speed, speed_counter): #,moved_down
    if speed_counter >= speed:
        if current_piece.check_bottom() == False:
            return 999999999999999999999999999999
        else:
            current_piece.set_gravity()
        speed_counter = 0            
    else:
        speed_counter += 1    

    return speed_counter
def draw_it():
    for i in range(1,11):
        pygame.draw.line(screen,(255,255,255),(i*20,0),(i*20,400),1)
    for i in range(1,20):
        pygame.draw.line(screen,(255,255,255),(0,i*20),(200,i*20),1)

def kill_piece(current_dead_piece):
    dead_subpiece_group.add(current_dead_piece.Apiece,current_dead_piece.Bpiece,current_dead_piece.Cpiece,current_dead_piece.Dpiece)
    for subpiece_place in piece_place:
        dead_subpiece_place_list.append(subpiece_place)
    current_dead_piece.group = pygame.sprite.Group()
    next_piece = random_shape_gen([startingx+140,startingy+100])
    return next_piece
def check_line(grid):
    lines = []
    for line in grid[4:-1]:
        this_line = True
        for char in line[1:-2]:
            if char != 1:
                this_line = False
        if this_line == True:
            lines.append(line[-1])
    while len(lines) != 4:
        lines.append(False)
    return lines
def move_down_line_list(dead_line,dead_subpiece_place_list):
    new_dead_subpiece_place_list = []
    new_new_dead_subpiece_place_list = []
    for dead_subpiece in dead_subpiece_place_list:
        if dead_subpiece[1] != dead_line + 4: # accomodate for extra 4 on top
            new_dead_subpiece_place_list.append(dead_subpiece)
    for dead_subpiece in new_dead_subpiece_place_list:
        if dead_subpiece[1] < dead_line + 4:
            new_new_dead_subpiece_place_list.append((dead_subpiece[0],dead_subpiece[1]+1))
        else:
            new_new_dead_subpiece_place_list.append((dead_subpiece[0],dead_subpiece[1]))
    return new_new_dead_subpiece_place_list
def move_down_line_group(dead_line,dead_subpiece_group):
    new_dead_subpiece_group = pygame.sprite.Group()
    new_new_dead_subpiece_group = pygame.sprite.Group()
    for dead_subpiece in dead_subpiece_group:
        if dead_subpiece.getgridplace()[1] != dead_line + 4: # accomodate for extra 4 on top
            new_dead_subpiece_group.add(dead_subpiece)    
    for dead_subpiece in new_dead_subpiece_group:
        if dead_subpiece.getgridplace()[1] < dead_line + 4:
            dead_subpiece.setxy(dead_subpiece.getxy()[0],(dead_subpiece.getgridplace()[1]-3)*20)
            new_new_dead_subpiece_group.add(dead_subpiece)
        else:
            new_new_dead_subpiece_group.add(dead_subpiece)
    return new_new_dead_subpiece_group
def check_line_grouping(lines):
    lines.sort(reverse=True)
    line_group = []
    while lines != [False,False,False,False]:
        if lines[0] - 1 == lines[1]:
            if lines[1] - 1 == lines[2]:
                if lines[2] -1 == lines[3]:
                    line_group = [[lines[0],lines[1],lines[2],lines[3]]]
                    lines = [False,False,False,False]
                else:
                    line_group = [[lines[0],lines[1],lines[2]],[lines[3]]]
                    lines = [False,False,False,False]
            else:
                line_group.append([lines[0],lines[1]])
                lines.pop(0)
                lines.pop(0)
                lines.append(False)
                lines.append(False)
        else:
            line_group.append([lines[0]])
            lines.pop(0)
            lines.append(False)
    return line_group
def scoring(current_score,level,line_grouping):
    base_score = 0
    for line_set in line_grouping:
        if len(line_set) == 1:
            base_score += 40
        elif len(line_set) == 2:
            base_score += 100
        elif len(line_set) == 3:
            base_score += 300
        elif len(line_set) == 4:
            base_score += 1200
    return (level+1) * base_score + current_score
def check_level_up(total_lines,level):
    if level * 10 <= total_lines:
        return level + 1
    else:
        return level
def speed_check(level,initial_speed):
    if level < 9:
        speed = initial_speed - level * 5
    else:
        speed = initial_speed - 9 * 5 - 2
    if level > 9:
        speed -= 1
    if level > 12:
        speed -= 1
    if level > 15:
        speed -= 1
    if level > 18:
        speed -= 1
    if level > 28:
        speed -= 1
    return speed
        
#YOU CAN CHANGE THESE
pygame.init()
screen = pygame.display.set_mode([300,400])
startingx = 90
startingy = -50
next_piece = random_shape_gen([startingx+140,startingy+100])
current_piece = random_shape_gen([startingx,startingy])
initial_speed = 60
drawings = True
cool_down = 4
level = 0

#DONT CHANGE THESE
score = 0
speed = initial_speed
total_lines = 0
cool_down_counter = 0
speed_counter = 0
dead_subpiece_place_list = []
dead_subpiece_group = pygame.sprite.Group()
clock = pygame.time.Clock()
running = True
while running:
    grid = reset_grid(dead_subpiece_place_list) #grid[y+4][x+1]
    #1 = border 2 = piece_place 3 = test
    piece_place = current_piece.getgridplace()
    for subpiece in current_piece.group:
        grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] = 2
    #kill tetris
    if pygame.event.get([pygame.QUIT]):
        running = False
    if pygame.key.get_pressed():
        if pygame.key.get_pressed()[pygame.K_ESCAPE]:
            running = False

    if cool_down_counter == cool_down:
        if pygame.key.get_pressed()[pygame.K_SPACE]:
            if current_piece.check_bottom():
                current_piece.set_gravity()
            else:
                next_piece_save = next_piece
                next_piece = kill_piece(current_piece)
                current_piece = next_piece_save
                for i in range(7):
                    current_piece.move_left()
                for i in range(4):
                    current_piece.set_reverse_gravity()
    
        if pygame.key.get_pressed()[pygame.K_RIGHT]:
            if current_piece.check_right():
                current_piece.move_right()
    #             np.where(grid == 1,grid+1,grid)
        elif pygame.key.get_pressed()[pygame.K_LEFT]:
            if current_piece.check_left():
                current_piece.move_left()
        elif pygame.key.get_pressed()[pygame.K_UP]:
            if current_piece.check_cw_rotation():
                current_piece.rotatecw()
        elif pygame.key.get_pressed()[pygame.K_DOWN]:
            if current_piece.check_ccw_rotation():
                current_piece.rotateccw()
        elif pygame.key.get_pressed()[pygame.K_m]:
            print(grid)
        elif pygame.key.get_pressed()[pygame.K_k]:
            for x in dead_subpiece_group:
                print(x)
        elif pygame.key.get_pressed()[pygame.K_s]:
            drawings = True
        elif pygame.key.get_pressed()[pygame.K_r]:
            current_piece.set_reverse_gravity()
        elif pygame.key.get_pressed()[pygame.K_q]:
            pass
        elif pygame.key.get_pressed()[pygame.K_p]:
            print(current_piece.getgridplace())
        cool_down_counter = 0
    else:
        cool_down_counter += 1
    grid = reset_grid(dead_subpiece_place_list) #grid[y+4][x+1]
    #1 = border 2 = piece_place 3 = test
    piece_place = current_piece.getgridplace()
    for subpiece in current_piece.group:
        grid[subpiece.getgridplace()[1]][subpiece.getgridplace()[0]] = 2
    # setting gravity
    speed_counter = gravity(speed,speed_counter) #,moved_down
    if speed_counter == 999999999999999999999999999999: # and killed == False
        next_piece_save = next_piece
        next_piece = kill_piece(current_piece)    
        current_piece = next_piece_save
        for i in range(7):
            current_piece.move_left()
        for i in range(5):
            current_piece.set_reverse_gravity()
    #update screen
    check = check_line(grid)
    if check != [False,False,False,False]:
        for dead_line in check:
            if dead_line != False:
                total_lines += 1
                dead_subpiece_place_list = move_down_line_list(dead_line,dead_subpiece_place_list)
                dead_subpiece_group = move_down_line_group(dead_line,dead_subpiece_group)
        grouping = check_line_grouping(check)
        score = scoring(score,1,grouping)
        print('this is the score',score)
        print('this is the total lines',total_lines)
        level = check_level_up(total_lines,level)
        speed = speed_check(level,initial_speed)
        print('level',level)

    if 1 in grid[0:4,1:-2]:
        running = False
    screen.fill((0,0,0))
    if drawings == True:
        draw_it()

    current_piece.group.draw(screen)
    next_piece.group.draw(screen)
    dead_subpiece_group.draw(screen)
    pygame.display.update()    
    clock.tick(60)
pygame.quit()