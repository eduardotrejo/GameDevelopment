/**
* Title: tank_chaser.c
* Abstract: This program implements a tank game that the player tries to catch as
*			many enemy tanks as possible in the time constrain of 15 seconds.
*			In the game, the tanks can move only four directions (up/down/right/left).
* Author: Eduardo Trejo
* ID: 6787
* Date: 11/01/2014
*/

#include <stdlib.h>
#include <time.h> 
#include "allegro.h"

// Define some game constants.
#define MODE GFX_SAFE
#define WIDTH 640
#define HEIGHT 480
#define WHITE makecol(255, 255, 255)
#define RED makecol(255, 0, 0)

BITMAP *myTank_bmp;
BITMAP *buffer;
BITMAP *enemy_bmp;

SAMPLE *boom;

int times, score, gameover, limit, volume, pan, pitch, random, yPos;
int enemyBottom, enemyTop, enemyRight, enemyLeft;
float angle, eAngle;

// Timer variables.
clock_t start;
int counter;

times = 0;
scores = 0;
gameover = 0;
limit = 0;
volume = 128;
pan = 128;
pitch = 1000;
enemyTop = 70; 
enemyBottom = 440; 
enemyLeft = 70; 
enemyRight = 600; 

// Define myTank structure.
struct tagTank
{
	int x, y;
	int speed;
	int score;
} myTank;

struct tagEnemy
{
	int x, y;
	int speed;
} enemyTank;

// Sets the depth for magic pink and the screen.
void setupscreen()
{
	set_color_depth(16);
	int ret;
	ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0){
		allegro_message(allegro_error);
		return;
	}
}

// Prints out the status.
void status(counter, scores)
{
	// Depending on the counter print out will differ.
	if (counter >= 10)
	{
		textprintf_ex(buffer, font, 20, 20, WHITE, 0, "Time - 0:%d", counter);
	}
	else
	{
		textprintf_ex(buffer, font, 20, 20, WHITE, 0, "Time - 0:0%d", counter);
	}
	
	textprintf_ex(buffer, font, 550, 20, WHITE, 0, "Score: %d", scores);
	rectfill(buffer, 0, 40, WIDTH, 45, WHITE);
}

// Draws my tank.
void drawMyTank(float angle)
{
	// Rotates sprite depending on the angle passed in.
	rotate_sprite(buffer, myTank_bmp, myTank.x, myTank.y,  ftofix(angle));
}

void drawEnemyTank(float eAngle)
{
	rotate_sprite(buffer, enemy_bmp, enemyTank.x, enemyTank.y, ftofix(eAngle));
}

// Key input.
void keyInput()
{
	/*
		Normal degrees: 0, 90, 180, 27, 360.
		Allegro degrees: 0, 64, 128, 192, 256.
	*/
	if (keypressed())
	{
		if (key[KEY_ESC])
		{
			gameover = 1;
		}
		else if (key[KEY_LEFT])
		{
			myTank.x -= myTank.speed;
			angle = 192;
		}
		else if (key[KEY_RIGHT])
		{
			myTank.x += myTank.speed;
			angle = 64;
		}
		else if (key[KEY_UP])
		{
			myTank.y -= myTank.speed;
			angle = 0;
		}
		else if (key[KEY_DOWN])
		{
			myTank.y += myTank.speed;
			angle = 128;
		}
	}
}

// Player boundary.
void playerBoundary()
{
	if (myTank.x < 2)
	{
		myTank.x = 2;
	}
	if (myTank.x > SCREEN_W - myTank_bmp->w)
	{
		myTank.x = SCREEN_W - myTank_bmp->w;
	}
	if (myTank.y > SCREEN_H - myTank_bmp->h)
	{
		myTank.y = SCREEN_H - myTank_bmp->h;
	}
	if (myTank.y < 47)
	{
		myTank.y = 47;
	}
}

// Enemy boundary and movement.
void enemyBoundaryAndMove()
{
	yPos = enemyTank.y;

	// Enemy check right wall.
	if (enemyTank.x > enemyRight - enemy_bmp->w / 2)
	{
		enemyTank.x = enemyRight - enemy_bmp->w / 2;
		if (myTank.y > enemyTank.y)
		{
			enemyTank.y -= enemyTank.speed;
			eAngle = 0;
		}
		else
		{
			enemyTank.y += enemyTank.speed;
			eAngle = 128;
		}
	}
	// Enemy check left wall.
	if (enemyTank.x < enemyLeft - enemy_bmp->w / 2)
	{
		enemyTank.x = enemyLeft - enemy_bmp->w / 2;
		if (myTank.y > enemyTank.y)
		{
			enemyTank.y -= enemyTank.speed;
			eAngle = 0;
		}
		else
		{
			enemyTank.y += enemyTank.speed;
			eAngle = 128;
		}
	}
	// Enemy check top wall.
	if (enemyTank.y < enemyTop - enemy_bmp->h / 2)
	{
		enemyTank.y = enemyTop - enemy_bmp->h / 2;
		if (myTank.x > enemyTank.x)
		{
			enemyTank.x -= enemyTank.speed;
			eAngle = 192;
		}
		else
		{
			enemyTank.x += enemyTank.speed;
			eAngle = 64;
		}
	}
	// Enemy check bottom wall.
	if (enemyTank.y > enemyBottom - enemy_bmp->h / 2)
	{
		enemyTank.y = enemyBottom - enemy_bmp->h / 2;
		if (myTank.x > enemyTank.x)
		{
			enemyTank.x -= enemyTank.speed;
			eAngle = 0;
		}
		else
		{
			enemyTank.x += enemyTank.speed;
			eAngle = 64;
		}
	}

	// Running away from the player.
	if (myTank.x < enemyTank.x)
	{
		enemyTank.x += enemyTank.speed;
		eAngle = 64;
	}
	else if (myTank.x > enemyTank.x)
	{
		enemyTank.x -= enemyTank.speed;
		eAngle = 192;
	}
	else if (myTank.y < enemyTank.y)
	{
		enemyTank.y += enemyTank.speed;
	}
	else if (myTank.y > enemyTank.y)
	{
		enemyTank.y -= enemyTank.speed;
	}

	if (yPos > enemyTank.y)
	{ 
		eAngle = 0;
	}
	if (yPos < enemyTank.y)
	{
		eAngle = 128; 
	}
}

// Collision detection.
void collisionDetect()
{
	srand(time(NULL));

	// Top left detection.
	if (myTank.x > enemyTank.x && myTank.x < enemyTank.x + 32 && 
		myTank.y > enemyTank.y && myTank.y < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;
	}
	// Bottom left detection.
	if (myTank.x > enemyTank.x && myTank.x < enemyTank.x + 32 &&
		myTank.y + 32 > enemyTank.y && myTank.y + 32 < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;

	}
	// Top middle detection.
	if (myTank.x + 16 > enemyTank.x && myTank.x + 16 < enemyTank.x + 32 &&
		myTank.y > enemyTank.y && myTank.y < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;

	}
	// Bottom middle detection.
	if (myTank.x + 16 > enemyTank.x && myTank.x + 16 < enemyTank.x + 32 &&
		myTank.y + 32 > enemyTank.y && myTank.y + 32 < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;

	}
	// Top right detection.
	if (myTank.x + 32 > enemyTank.x && myTank.x + 32 < enemyTank.x + 32 && 
		myTank.y > enemyTank.y && myTank.y < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;
		
	}
	// Bottom right detection.
	if (myTank.x + 32 > enemyTank.x && myTank.x + 32 < enemyTank.x + 32 && 
		myTank.y + 32 > enemyTank.y && myTank.y + 32 < enemyTank.y + 32)
	{
		scores++;
		play_sample(boom, volume, pan, pitch, FALSE);
		enemyTank.x = rand() % 600 + 1;
		enemyTank.y = rand() % 440 + 1;
	}
}

// Timer. 
void timeCount()
{
	if (clock() > start + CLOCKS_PER_SEC)
	{
		counter--;
		if (counter == 0)
		{
			limit = 1;
			gameover = 1;
		}
		start = clock();
	}
}
	
int main()
{
	//Initialize Allegro.
	allegro_init();
	
	//Initialize the keyboard.
	install_keyboard();
	install_timer();

	setupscreen();
	buffer = create_bitmap(WIDTH, HEIGHT);

	// Loads the images.
	myTank_bmp = load_bitmap("tank2.bmp", NULL);
	enemy_bmp = load_bitmap("tank1.bmp", NULL);

	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
	{
		allegro_message("Error initializing sound system\n%s\n", allegro_error);
		return 1;
	}

	boom = load_sample("explode.wav");

	// Sets up my tank.
	myTank.x = SCREEN_W / 2 - myTank_bmp->w / 2;
	myTank.y = SCREEN_H / 2 - myTank_bmp->h / 2;
	myTank.speed = 10;

	// Sets up enemy tank.
	enemyTank.x = 500 - enemy_bmp->w / 2;
	enemyTank.y = 100 - enemy_bmp->h / 2;
	enemyTank.speed = 3;
	eAngle = 64;

	// Time limit.
	counter = 15;
	start = clock();

	while (!gameover){

		keyInput();
		
		// Check boundary collision.
		playerBoundary();	
		enemyBoundaryAndMove();
		
		timeCount();
		status(counter, scores);
		collisionDetect();

		drawMyTank(angle);
		drawEnemyTank(eAngle);

		//Draw the buffer to the screen.
		blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

		// Clear the contents of the buffer bitmap.
		clear_bitmap(buffer);
		rest(50);
	}
	
	if (limit)
	{
		rectfill(screen, 0, 45, WIDTH, HEIGHT, 0);
		textout_centre_ex(screen, font, "Game Over!!!",
			SCREEN_W / 2, SCREEN_H / 2,
			RED, makecol(0, 0, 0));
		rest(2000);
	}

	destroy_bitmap(myTank_bmp);
	destroy_bitmap(enemy_bmp);
	destroy_bitmap(buffer);
	destroy_sample(boom);
	remove_sound();

	allegro_exit();
	return 0;
}
END_OF_MAIN()