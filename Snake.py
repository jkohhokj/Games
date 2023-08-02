#working uses dictionaries
#copied bascis from http://programarcadegames.com/python_examples/f.php?file=snake.py
import pygame
import random 


# Call this function so the Pygame library can initialize itself
pygame.init()
 
# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Set the width and height of each snake segment
segment_width = 15
segment_height = 15

# Margin between each segment
segment_margin = 3
 
# Set initial speed
x_change = segment_width + segment_margin
y_change = 0


screen_w = int(input('What do you want the screen width to be?'))
screen_w = round(screen_w/(segment_width+segment_margin)) * (segment_width+segment_margin)
screen_h = int(input('What do you want the screen height to be?'))
screen_h = round(screen_h/(segment_height+segment_margin)) * (segment_height+segment_margin)
print(screen_w,screen_h)

grid_height = 0
grid_height = int(screen_h/(segment_height+segment_margin))

grid_width = 0
grid_width = int(screen_w/(segment_width+segment_margin))
screen = pygame.display.set_mode([screen_w, screen_h]) #set the display   

#define class Apple
class Apple(pygame.sprite.Sprite):
    def __init__(self,x,y):
        # Call the parent's constructor
        super().__init__()        
        # Set height, width
        self.image = pygame.Surface([segment_width, segment_height])
        self.image.fill((255,0,0))
        # Make our top-left corner the passed-in location.
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y

#define call Segment
class Segment(pygame.sprite.Sprite):
    """ Class to represent one segment of the snake. """
    # -- Methods
    # Constructor function
    def __init__(self, x, y):
        # Call the parent's constructor
        super().__init__()
 
        # Set height, width
        self.image = pygame.Surface([segment_width, segment_height])
        self.image.fill(WHITE)
        # Make our top-left corner the passed-in location.
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y

determined = False # for apple later
eaten = True # for apple later

# Set the title of the window
pygame.display.set_caption('Snake Example')
 
allspriteslist = pygame.sprite.Group() #create group
 
# Create an initial snake
#create initial list
snake_segments = []
snake_segments_pos = []

for i in range(10):
    x = 146 - (segment_width + segment_margin) * i
    y = 20
    segment = Segment(x, y)
    snake_segments.append(segment)
    snake_segments_pos.append((segment.rect.x,segment.rect.y))
    allspriteslist.add(segment)


clock = pygame.time.Clock()
done = False
#running 
while not done:
    if eaten == True:
        determined = False # reset it for next apple
        #setting up apple coords
        apple_coordx = 0
        apple_coordy = 0
        t = []
        for x in range(0,grid_width*grid_height):
            for i in range(0,grid_width):
                t.append((x,i))
        griddict = dict(zip(range(grid_width*grid_height),t))

        
        while determined == False:
            try:
                pick = (random.randint(0,grid_width*grid_height))
                pick = griddict.pop(pick)
                apple_coordx = pick[1] * (segment_width+segment_margin) + 2 #margin of error change to segment_margin-1 ?
                apple_coordy = pick[0] * (segment_width+segment_margin) + 2 # notice not [0] is x and [1] is not y change axis?
                

            except KeyError:
                pass
                
            if len(griddict) == 1: #0?
                running = False
                determined = True
            if tuple((apple_coordx,apple_coordy)) not in snake_segments_pos:
                determined = True
        #removing old apple
        if len(allspriteslist) > 11:
            allspriteslist.remove(apple)
        #giving apple coords
        apple = Apple(apple_coordx,apple_coordy) 
        allspriteslist.add(apple)
        eaten = False # set back to default ending of apple
        
        #detecting input
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
            
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                done = True
                
            if event.key == pygame.K_LEFT and x_change != segment_width + segment_margin:
                x_change = (segment_width + segment_margin) * -1
                y_change = 0
                
            if event.key == pygame.K_RIGHT and x_change != (segment_width + segment_margin) * -1:
                x_change = (segment_width + segment_margin)
                y_change = 0
                
            if event.key == pygame.K_UP and y_change != segment_width + segment_margin:
                x_change = 0
                y_change = (segment_height + segment_margin) * -1
                
            if event.key == pygame.K_DOWN and y_change != (segment_width + segment_margin) * -1:
                x_change = 0
                y_change = (segment_height + segment_margin)
            if event.key == pygame.K_p:
                wait = True
                while wait:
                    for event in pygame.event.get():
                        if event.type == pygame.KEYDOWN:
                            if event.key == pygame.K_p:
                                wait = False
                                break
                
            if event.key == pygame.K_a:
                print(snake_segments_pos)
                print(apple_coordx,apple_coordy)
                print(allspriteslist)
                
    #check if apple got
    if snake_segments_pos[0] == tuple((apple_coordx,apple_coordy)):
        eaten = True
    if eaten == True:
        snake_segments.append(Segment(x, y))
        snake_segments_pos.append((x,y))
    
    #changing pos list
    for a in (range(len(snake_segments)-1)):
        snake_segments_pos[-a-1] = snake_segments_pos[-a-2]
        
    #deleting old 
    old_segment = snake_segments.pop()
    allspriteslist.remove(old_segment)
    
    #changing head
    x = snake_segments[0].rect.x + x_change
    y = snake_segments[0].rect.y + y_change
    snake_segments_pos[0] = (x,y)
    segment = Segment(x, y)
        
    #self-collision
    if snake_segments_pos[0] in snake_segments_pos[1:]:
        done = True
        
    #wall-collision
    if snake_segments_pos[0][0] > screen_w - 1:
        done = True
    if snake_segments_pos[0][0] < 0: 
        done = True
    if snake_segments_pos[0][1] < 0:
        done = True
    if snake_segments_pos[0][1] > screen_h - 1:
        done = True
        
    # Insert new segment into the list
    snake_segments.insert(-1*len(allspriteslist), segment)
    allspriteslist.add(segment)
    
    # Clear screen
    screen.fill(BLACK)

    for x in range(grid_width):
        pygame.draw.line(screen,(25,25,25),(x*(segment_width+segment_margin),0),(x*(segment_width+segment_margin),screen_h),3)
    for x in range(grid_height):    
        pygame.draw.line(screen,(25,25,25),(0,x*(segment_height+segment_margin)),(screen_w,x*(segment_height+segment_margin)),3) 
    allspriteslist.draw(screen)

    # Flip screen
    pygame.display.flip()
  
    # Pause
    clock.tick(5)
#end of game
screen.fill(BLACK)
if len(griddict) == 0:
    print(f'You win! You got {(len(allspriteslist)-11)} apples.')
else:
    print(f'You lose! You got {(len(allspriteslist)-11)} apples.')

pygame.quit()
