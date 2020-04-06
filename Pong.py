#can't make ball too fast because ball just glitches through bar also some weird glitchy thing near collision
#trying to increase frame rate becomes sluggish and other methods are hopeless
import pygame, math, random
screen = pygame.display.set_mode([400,400])
class Bar(pygame.sprite.Sprite):
    def __init__(self, x, y,bar_height,bar_width):
        # Call the parent's constructor
        super().__init__()

        # Set height, width
        self.image = pygame.Surface([bar_width,bar_height])
        self.image.fill((255,255,255))
        # Make our top-left corner the passed-in location.
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
class Ball(pygame.sprite.Sprite):
    def __init__(self,x,y):
        super().__init__()
        self.image = pygame.Surface([10,10])
        self.image.fill((255,255,255))
        # Make our top-left corner the passed-in location.
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y  

ball_speed = 1
    
bar_height = 40
bar_width = 100
loc1 = 50
loc2 = 50
bx_change = ball_speed
by_change = -1 * ball_speed


bar_speed = 10

ballx = 200
bally = 200
ball = Ball(ballx,bally)
player1 = Bar(-90,loc1,bar_height,bar_width)
player2 = Bar(390,loc2,bar_height,bar_width)
clock = pygame.time.Clock()
allspritesgroup1 = pygame.sprite.Group(player1)
allspritesgroup2 = pygame.sprite.Group(player2)
allspritesgroup3 = pygame.sprite.Group(ball)
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
            if event.key == pygame.K_w:
                loc1 -= bar_speed
            if event.key == pygame.K_s:
                loc1 += bar_speed
            if event.key == pygame.K_UP:
                loc2 -= bar_speed
            if event.key == pygame.K_DOWN:
                loc2 += bar_speed
            player1 = Bar(-90,loc1,bar_height,bar_width)
            allspritesgroup1 = pygame.sprite.Group(player1)
            player2 = Bar(390,loc2,bar_height,bar_width)
            allspritesgroup2 = pygame.sprite.Group(player2)

    if pygame.sprite.groupcollide(allspritesgroup1, allspritesgroup3, False, False):
        bx_change = ball_speed
        ball_speed += .25
    if pygame.sprite.groupcollide(allspritesgroup2, allspritesgroup3, False, False):
        bx_change = -1 * ball_speed
        ball_speed += .25
    
    #keep it in the screen
    if bally > 400:
        by_change = -1 * ball_speed
    if bally < 10:
        by_change = ball_speed
    if ballx < 0:
        print('Player 2 wins!!!')
        running = False
    if ballx > 400:
        print('Player 1 wins!!!')
        running = False

    #change of ball location

    bally += by_change
    ballx += bx_change
    
    ball = Ball(ballx,bally)
    allspritesgroup3 = pygame.sprite.Group(ball)
    screen.fill((0,0,0))
    allspritesgroup1.draw(screen)
    allspritesgroup2.draw(screen)
    allspritesgroup3.draw(screen)
    pygame.display.flip()
    clock.tick(100)
pygame.quit()