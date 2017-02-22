/**
* Title: racing_car.c
* Abstract: This program implements a race car game which has two levels.
*			The player should be able to speed up or down using the keys 0, 1, 2, 3, and 4.
*			Initially, the car’s speed is zero. The second level will contain enemies
*			if you collide with them your speed will drop to 0. Reach the end of the second level
*			for the game to end.
* Author: Eduardo Trejo
* Date: 11/16/2014
*/

#include <time.h>
#include <allegro.h>
#include "mappyal.h"

#define MODE GFX_SAFE
#define WIDTH 640
#define HEIGHT 480
#define RED makecol(255, 0, 0)
#define WHITE makecol(255,255,255)
#define BOTTOM 12000 - HEIGHT

BITMAP *buffer;
BITMAP *player;
BITMAP *enemy;

MIDI *music;
SAMPLE *splash[1];

int level, yoffset = BOTTOM, gear;
int speed, zerogear, firstgear, secondgear, thirdgear, fourthgear;
int n, gameover;
int pitch, volume, pan;

gameover = 0;
volume = 128;
pan = 128;
pitch = 1000;

// Starting speed.
speed = 0;

// Gears.
zerogear = 1;
firstgear = 0;
secondgear = 0;
thirdgear = 0;
fourthgear = 0;

// Define myCar structure.
struct tagCar
{
	int x, y;
	int width, height;
} myCar;

struct tagEnemy
{
	int x, y;
	int width, height;
	int xspeed, yspeed;
}enemyCar[5];

// Car boundary.
void carBound()
{
	// Check boundary collision.
	if (myCar.x < 90)
	{
		myCar.x = 90;
	}
	if (myCar.x > SCREEN_W - 145)
	{
		myCar.x = SCREEN_W - 145;
	}
}

// Key input.
void keyInput()
{
	if (key[KEY_ESC])
	{
		gameover = 1;
	}
	if (key[KEY_LEFT] && speed != 0)
	{
		myCar.x -= 1;
	}
	if (key[KEY_RIGHT] && speed != 0)
	{
		myCar.x += 1;
	}
	if (key[KEY_0] && firstgear)
	{
		speed = 0;
		gear = 0;
		zerogear = 1;
		firstgear = 0;
		secondgear = 0;
		thirdgear = 0;
		fourthgear = 0;
	}
	if (key[KEY_1] && zerogear || key[KEY_1] && secondgear)
	{
		speed = 1;
		firstgear = 1;
		zerogear = 0;
		secondgear = 0;
		thirdgear = 0;
		fourthgear = 0;
		gear = 1;
	}
	if (key[KEY_2] && firstgear || key[KEY_2] && thirdgear)
	{
		speed = 2;
		firstgear = 0;
		zerogear = 0;
		secondgear = 1;
		thirdgear = 0;
		fourthgear = 0;
		gear = 2;
	}
	if (key[KEY_3] && secondgear || key[KEY_3] && fourthgear)
	{
		speed = 3;
		zerogear = 0;
		firstgear = 0;
		secondgear = 0;
		thirdgear = 1;
		fourthgear = 0;
		gear = 3;
	}
	if (key[KEY_4] && thirdgear)
	{
		speed = 5;
		fourthgear = 1;
		thirdgear = 0;
		gear = 4;
	}
	yoffset -= speed;
}

// Draw car.
void drawMyCar()
{
	draw_sprite(buffer, player, myCar.x, myCar.y);
}

// Loads enemies.
void loadEnemies()
{
	// Sets them up.
	for (n = 0; n < 5; n++)
	{
		enemyCar[n].x = (rand() % (500 + 1 - 90)) + 90;
		enemyCar[n].y = (rand() % SCREEN_H) - 500;
		enemyCar[n].width = 42;
		enemyCar[n].height = 55;
		enemyCar[n].xspeed = 2;
		enemyCar[n].yspeed = 1;
	}
}

// Updates the enemies and check boundary collision.
void updateEnemyCar()
{
	for (n = 0; n < 5; n++)
	{
		enemyCar[n].y += enemyCar[n].yspeed;
		enemyCar[n].x += enemyCar[n].xspeed;
	
		if (enemyCar[n].x > SCREEN_W - 145)
		{
			enemyCar[n].x = SCREEN_W - 145;
		}
		if (enemyCar[n].x == SCREEN_W - 145)
		{
			enemyCar[n].xspeed -= 2;
		}
		if (enemyCar[n].x < 90)
		{
			enemyCar[n].x = 90;
		}
		if (enemyCar[n].x == 90)
		{
			enemyCar[n].xspeed += 2;
		}
		if (enemyCar[n].y > SCREEN_H)
		{
			enemyCar[n].x = (rand() % (500 + 1 - 90)) + 90;
			enemyCar[n].y = (rand() % SCREEN_H) - 500;
		}
		draw_sprite(buffer, enemy, enemyCar[n].x, enemyCar[n].y);
	}	
}

// Check if there is collision with the enemy cars.
void collisionDetection()
{
	for (n = 0; n < 5; n++)
	{
		// Top left collision.
		if (enemyCar[n].x > myCar.x && enemyCar[n].x < myCar.x + myCar.width
			&& enemyCar[n].y > myCar.y && enemyCar[n].y < myCar.y + myCar.height)
		{
			speed = 0;
			gear = 0;
			zerogear = 1;
			firstgear = 0;
			secondgear = 0;
			thirdgear = 0;
			fourthgear = 0;
			play_sample(splash[0], volume, pan, pitch, FALSE);
		}
		// Top right collision.
		if (enemyCar[n].x + enemyCar[n].width > myCar.x && enemyCar[n].x + enemyCar[n].width < myCar.x + myCar.width
			&& enemyCar[n].y > myCar.y && enemyCar[n].y < myCar.y + myCar.height)
		{
			speed = 0;
			gear = 0;
			zerogear = 1;
			firstgear = 0;
			secondgear = 0;
			thirdgear = 0;
			fourthgear = 0;
			play_sample(splash[0], volume, pan, pitch, FALSE);
		}
		// Botton left collision.,
		if (enemyCar[n].x > myCar.x && enemyCar[n].x < myCar.x + myCar.width
			&& enemyCar[n].y + enemyCar[n].height > myCar.y && enemyCar[n].y + enemyCar[n].height < myCar.y + myCar.height)
		{
			speed = 0;
			gear = 0;
			zerogear = 1;
			firstgear = 0;
			secondgear = 0;
			thirdgear = 0;
			fourthgear = 0;
			play_sample(splash[0], volume, pan, pitch, FALSE);
		}
		// Bottom right collision.
		if (enemyCar[n].x + enemyCar[n].width > myCar.x && enemyCar[n].x + enemyCar[n].width < myCar.x + myCar.width
			&& enemyCar[n].y + enemyCar[n].height > myCar.y && enemyCar[n].y + enemyCar[n].height < myCar.y + myCar.height)
		{
			speed = 0;
			gear = 0;
			zerogear = 1;
			firstgear = 0;
			secondgear = 0;
			thirdgear = 0;
			fourthgear = 0;
			play_sample(splash[0], volume, pan, pitch, FALSE);
		}
	}
}
int main()
{
	srand(time(NULL));
	allegro_init();
	install_timer();

	install_keyboard();
	set_color_depth(16);
	set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);

	//create the double buffer and clear it
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	clear(buffer);

	player = load_bitmap("car.bmp", NULL);
	enemy = load_bitmap("speedster.bmp", NULL);

	
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
	{
		allegro_message("Error initializing sound system\n%s\n", allegro_error);
		return 1;
	}

	// Load the midi file
	music = load_midi("MetroidRidley.mid");
	splash[0] = load_sample("splash.wav");
	if (!music)
	{
		allegro_message("Error loading Midi file");
		return 1;
	}
	if (play_midi(music, 1) != 0)
	{
		allegro_message("Error playing Midi\n%s", allegro_error);
		return 1;
	}
	// Load the Mappy file
	if (MapLoad("track1.fmp") != 0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Can't find track1.fmp");
	}

	// Set palette.
	MapSetPal8();

	level = 1;
	// Sets up my tank.
	myCar.x = 320 - 32;
	myCar.y = SCREEN_H - 80;
	myCar.width = 35;
	myCar.height = 69;
	
	loadEnemies();

	while (!gameover)
	{

		keyInput();
		
		// Make sure it doesn't scroll beyond map edge.
		if (yoffset < 0) yoffset = 0;
		if (yoffset > BOTTOM) yoffset = BOTTOM;

		// Draw map with single player.
		MapDrawBG(buffer, 0, yoffset, 0, 0, SCREEN_W - 1, SCREEN_H - 1);

		carBound();

		drawMyCar();
		if (level == 2)
		{
			if (yoffset == 0)
			{		
				gameover = 1;	
			}
			if (gameover == 0)
			{
				updateEnemyCar();
			}	
		}
		collisionDetection();
		
		textprintf_ex(buffer, font, 100, 460, RED, -1,
			"Gear: %d", gear);
		textprintf_ex(buffer, font, 170, 460, RED, -1,
			"Level: %d", level);
		// Blit the double buffer.
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, SCREEN_W - 1, SCREEN_H - 1);
		release_screen();

		if (yoffset == 0 && level == 1)
		{
			rest(2000);
			level = 2;
			yoffset = BOTTOM;
			speed = 0;
			gear = 0;
			zerogear = 1;

			
			if (MapLoad("track2.fmp") != 0)
			{
				set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
				allegro_message("Can't find track2.fmp");
			}
		}
		rest(10);
	}
	stop_midi();
	destroy_midi(music);
	destroy_bitmap(buffer);
	destroy_bitmap(player); 
	destroy_bitmap(enemy);
	MapFreeMem();

	remove_sound();
	allegro_exit();
	return 0;
}
END_OF_MAIN()
