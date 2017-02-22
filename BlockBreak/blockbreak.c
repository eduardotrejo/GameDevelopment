/**
 * Title: blockbreak.c
 * Abstract: This program is a simple blockbreak game. Uses two structs to create the paddle and
 *			 ball. If you lose all 3 balls it's gameover and if you destroy all 3 bricks you win.
 * Author: Eduardo Trejo
 * Date: 09/28/2014
 */
#include <allegro.h>

// Constant colors.
#define RED makecol(255, 0, 0)
#define WHITE makecol(255, 255, 255)
#define LIGHTBLUE makecol(128, 128, 255)

// Paddle.
struct tagPaddle
{
	int x, y;     
	int speed;  
	int color;  
} paddle; 

// Ball.
struct tagBall
{
	int x, y;
	int xSpeed, ySpeed;
	int color;
} squareBall;

// Variables used.
int ballsLeft = 3;
int score = 0;
int brick1Alive = 1, brick2Alive = 1, brick3Alive = 1;

// Sts up brick1, brick2, and birck3.
void brick1()
{
	rectfill(screen, 1, 40, 161, 60, LIGHTBLUE);
}

void brick2()
{
	rectfill(screen, 164, 40, 324, 60, LIGHTBLUE);
}

void brick3()
{
	rectfill(screen, 327, 40, 478, 60, LIGHTBLUE);
}

// Draw balls.
void drawBall()
{
	int x = squareBall.x;
	int y = squareBall.y;
	rectfill(screen, x, y, x + 20, y + 20, WHITE);
}

// Draw paddle.
void drawPaddle()
{
	int x = paddle.x;
	int y = paddle.y;
	rectfill(screen, x, y, x + 80, y + 20, paddle.color);
}

// Moves the ball and performs checks for the game.
void movingBall()
{	
	squareBall.x += squareBall.xSpeed;
	squareBall.y += squareBall.ySpeed;
		
	// Hit left.
	if(squareBall.x < 0)
	{
		squareBall.x = 1;
		squareBall.xSpeed = + 6;
	}
	// Hit right.
	if(squareBall.x > SCREEN_W - (20 - 1))
	{
		squareBall.x = SCREEN_W - (20- 1);
		squareBall.xSpeed = - 6;
	}
	// Hit top.
	if(squareBall.y < 20)
	{
		squareBall.y = 20;
		squareBall.ySpeed = + 6;
	}
	// Hit bottom.
	if(squareBall.y > SCREEN_H - (20 - 1))
	{
		ballsLeft--;	
		drawBall();
		squareBall.x = SCREEN_W / 2;
		squareBall.y = SCREEN_H / 2;
	}	
	// Hit paddle.
	if(getpixel(screen, squareBall.x, squareBall.y + 20) == RED)
	{
		squareBall.ySpeed = - 6;
	}
	if(getpixel(screen, squareBall.x + 10, squareBall.y + 20) == RED)
	{
		squareBall.ySpeed = - 6;
	}
	if(getpixel(screen, squareBall.x + 20, squareBall.y + 20) == RED)
	{
		squareBall.ySpeed = - 6;
	}
	// Checks collision with bricks.
	if(getpixel(screen, squareBall.x + 10, squareBall.y) == LIGHTBLUE)
	{
		squareBall.ySpeed = + 6;
		if(squareBall.x > 0 && squareBall.x < 161)
		{
			brick1Alive = 0;
			score++;
		}
	}
	
	if(getpixel(screen, squareBall.x + 10, squareBall.y) == LIGHTBLUE)
	{
		squareBall.ySpeed = + 6;
		if(squareBall.x > 163 && squareBall.x < 325)
		{
			brick2Alive = 0;
			score++;
		}
	}
	if(getpixel(screen, squareBall.x + 10, squareBall.y) == LIGHTBLUE)
	{
		squareBall.ySpeed = + 6;
		if(squareBall.x > 326 && squareBall.x < 479)
		{
			brick3Alive = 0;
			score++;
		}
	}
}
// Cleares the screen every so often.
void clearScreen(int s, int bl)
{
	rectfill(screen, 0, 0 , SCREEN_W, SCREEN_H, 0);
	textprintf_ex(screen, font, 10, 10, 15, -1, "Score: %d", s);
	textprintf_ex(screen, font, 385, 10, 15, -1, "%d Ball Left", bl);
}

int main()
{
	int ret;
	int gameover;
	gameover = 0;
	
	srand(time(NULL));

	//Initialize Allegro.
	allegro_init();

	//Initialize the keyboard.
	install_keyboard();

	//Initialize window mode to 480 x 260.
	ret = set_gfx_mode(GFX_SAFE, 480, 260, 0, 0);
	if(ret != 0){
		allegro_message(allegro_error);
		return -1;
	}
	
	// Sets x, y, color, and speed.
	paddle.x = 200;
	paddle.y = 237;
	paddle.color = RED; 
	paddle.speed = 10;
	
	// Sets x, y, color, xSpeed, and ySpeed.
	squareBall.x = SCREEN_W / 2;
	squareBall.y = SCREEN_H / 2;
	squareBall.color = WHITE;
	squareBall.xSpeed = 6;
	squareBall.ySpeed = 6;

	// While it's not gameover the game continues.
	while(!gameover)
	{
		// Control logic.
		if(keypressed())
		{
			if(key[KEY_ESC])
			{
                gameover = 1;  
			}
			if(key[KEY_LEFT])
			{
				paddle.x -= paddle.speed;
			}
			if(key[KEY_RIGHT])
			{
				paddle.x += paddle.speed;
			}
		}
		// Paddle collision detection.
		if(paddle.x < 0)
		{
			paddle.x = 0;
		}
		if(paddle.x > SCREEN_W - 80)
		{
			paddle.x = SCREEN_W - 80;
		}
		// No balls are left.
		if(ballsLeft == 0)
		{
			gameover = 1;
			clearScreen(score, ballsLeft);
			rectfill(screen, 0, 20, 480, 21, WHITE);
			textout_centre_ex(screen, font, "Game Over - You Lose",
                        SCREEN_W / 2, SCREEN_H / 2,
                        makecol(255, 0, 0), makecol(0, 0, 0));
			rest(2000);
		}
		// You broke all bricks.
		if(score == 3)
		{
			gameover = 1;
			clearScreen(score, ballsLeft);
			rectfill(screen, 0, 20, 480, 21, WHITE);
			textout_centre_ex(screen, font, "Game Over - You Win",
                        SCREEN_W / 2, SCREEN_H / 2,
                        WHITE, makecol(0, 0, 0));
			rest(2000);
		}
	
		// Drawing logic.		
		if(ballsLeft != 0 && score  < 3)
		{
			clearScreen(score, ballsLeft);
			rectfill(screen, 0, 20, 480, 21, WHITE);
			// Draws the bricks if they are alive.
			if(brick1Alive)
			{
				brick1();
			}
			if(brick2Alive)
			{
				brick2();
			}
			if(brick3Alive)
			{
				brick3();
			}
			drawBall();
			drawPaddle();
			movingBall();	
			rest(50);
		}	
	}
	allegro_exit();
	return 0;
}
END_OF_MAIN()

