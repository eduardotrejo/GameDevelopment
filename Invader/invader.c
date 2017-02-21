/**
* Title: invader.c
* Abstract: This program acts as an invader game. In the game, there are two invaders 
*			at the level 1 and three invaders at the level 2. And also, there’s one
*			barricade to protect the defender.	
* Author: Eduardo Trejo
* ID: 6787
* Date: 10/24/2014
*/

#include "allegro.h"

// Define some game constants.
#define MODE GFX_SAFE
#define WIDTH 640
#define HEIGHT 480
#define WHITE makecol(255, 255, 255)
#define BULLETSPEED 10
#define BLACK makecol(0,0,0)

// Bitmaps.
BITMAP *barricade;
BITMAP *myTank_bmp;
BITMAP *enemyTank;
BITMAP *buffer;
BITMAP *bullet;
BITMAP *explode_bmp;

MIDI *music;

SAMPLE *boom[1];

// Variables used.
int score, level, barricadeX, barricadeY, fire, gameover, lost, win, level2once, blownUp;
int enemyShot, enemyShot2, enemyShot3, active, active2, active3, i, detroyed, once, once2, once3;
int pitch, volume, pan;
score = 0;
level = 1;
fire = 0;
gameover = 0;
lost = 0;
win = 0;
enemyShot = 0;
enemyShot2 = 0;
enemyShot3 = 0;
active = 1;
active2 = 1;
active3 = 1;
destroyed = 0;
once = 0;
once2 = 0;
once3 = 0;
level2once = 0;
blownUp = 0;
volume = 128;
pan = 128;
pitch = 1000;

// Define myTank structure.
struct tagTank
{
	int x, y;
	int speed;
	int score;
} myTank;

// Define enemyTanks structure.
struct tagEnemyTank
{
	int x, y;
	int speed;
}enemyTanks[3];

// Define bullets structure.
struct tagBullet
{
	int x, y;
	int alive;
	int xspd, yspd;

} bullets[3];

// Define bullets structure.
struct tagEnemyBullet
{
	int x, y;
	int alive;
	int xspd, yspd;

} enemyBullets[3];

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
void status(score, level)
{
	textprintf_ex(buffer, font, 20, 20, WHITE, 0, "Score: %d", score);
	textprintf_ex(buffer, font, 550, 20, WHITE, 0, "Level: %d", level);
	rectfill(buffer, 0, 40, WIDTH, 45, WHITE);
}

// Draws the barricade if it was not destroyed.
void drawBarricade()
{
	if (!destroyed)
	{
		barricadeX = SCREEN_W / 2 - barricade->w / 2;
		barricadeY = (SCREEN_H - 80) - barricade->h / 2;
		blit(barricade, buffer, 0, 0, barricadeX, barricadeY, barricade->w, barricade->h);
	}	
}

// Draws the enemies depending on the level and if active.
void drawEnemyTank(int level)
{
	if (level == 1)
	{
		if (active)
		{
			draw_sprite_v_flip(buffer, enemyTank, enemyTanks[0].x, enemyTanks[0].y);
		}
		if (active2)
		{
			draw_sprite_v_flip(buffer, enemyTank, enemyTanks[1].x, enemyTanks[1].y);
		}
		
	}
	else
	{
		if (active)
		{
			draw_sprite_v_flip(buffer, enemyTank, enemyTanks[0].x, enemyTanks[0].y);
		}
		if (active2)
		{
			draw_sprite_v_flip(buffer, enemyTank, enemyTanks[1].x, enemyTanks[1].y);
		}
		if (active3)
		{
			draw_sprite_v_flip(buffer, enemyTank, enemyTanks[2].x, enemyTanks[2].y);
		}	
	}
}

// Draws my tank.
void drawMyTank()
{
	draw_sprite(buffer, myTank_bmp, myTank.x, myTank.y);
}

// Moves enemies all the way to the right, down for a bit, and then to the left. Depending on level.
void moveEnemy(int level)
{
	if (level == 1){
		if (enemyTanks[0].x < SCREEN_W - 35 && enemyTanks[0].y != SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].x += enemyTanks[0].speed;
		}
		if (enemyTanks[1].x < SCREEN_W - 35 && enemyTanks[1].y != SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].x += enemyTanks[1].speed;
		}
		if (enemyTanks[0].x > SCREEN_W - 35 && active)
		{
			enemyTanks[0].x = SCREEN_W - 35;
		}
		if (enemyTanks[1].x > SCREEN_W - 35 && active2)
		{
			enemyTanks[1].x = SCREEN_W - 35;
		}
		if (enemyTanks[0].x == SCREEN_W - 35 && active)
		{
			enemyTanks[0].y += enemyTanks[0].speed;
		}
		if (enemyTanks[1].x == SCREEN_W - 35 && active2)
		{
			enemyTanks[1].y += enemyTanks[1].speed;
		}
		if (enemyTanks[0].y > SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].y = SCREEN_H / 2 - 65;

		}
		if (enemyTanks[1].y > SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].y = SCREEN_H / 2 - 65;

		}
		if (enemyTanks[0].y == SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].x -= enemyTanks[0].speed;
		}
		if (enemyTanks[1].y == SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].x -= enemyTanks[1].speed;
		}
		if (enemyTanks[0].x < 0 && active)
		{
			gameover = 1;
			lost = 1;
		}
		if (enemyTanks[1].x < 0 && active2)
		{
			gameover = 1;
			lost = 1;
		}	
	}
	else
	{
		if (enemyTanks[0].x < SCREEN_W - 35 && enemyTanks[0].y != SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].x += enemyTanks[0].speed;
		}
		if (enemyTanks[1].x < SCREEN_W - 35 && enemyTanks[1].y != SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].x += enemyTanks[1].speed;
		}
		if (enemyTanks[2].x < SCREEN_W - 35 && enemyTanks[2].y != SCREEN_H / 2 - 65 && active3)
		{
			enemyTanks[2].x += enemyTanks[2].speed;
		}
		if (enemyTanks[0].x > SCREEN_W - 35 && active)
		{
			enemyTanks[0].x = SCREEN_W - 35;
		}
		if (enemyTanks[1].x > SCREEN_W - 35 && active2)
		{
			enemyTanks[1].x = SCREEN_W - 35;
		}
		if (enemyTanks[2].x > SCREEN_W - 35 && active3)
		{
			enemyTanks[2].x = SCREEN_W - 35;
		}
		if (enemyTanks[0].x == SCREEN_W - 35 && active)
		{
			enemyTanks[0].y += enemyTanks[0].speed;
		}
		if (enemyTanks[1].x == SCREEN_W - 35 && active2)
		{
			enemyTanks[1].y += enemyTanks[1].speed;
		}
		if (enemyTanks[2].x == SCREEN_W - 35 && active3)
		{
			enemyTanks[2].y += enemyTanks[2].speed;
		}
		if (enemyTanks[0].y > SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].y = SCREEN_H / 2 - 65;

		}
		if (enemyTanks[1].y > SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].y = SCREEN_H / 2 - 65;

		}
		if (enemyTanks[2].y > SCREEN_H / 2 - 65 && active3)
		{
			enemyTanks[2].y = SCREEN_H / 2 - 65;

		}
		if (enemyTanks[0].y == SCREEN_H / 2 - 65 && active)
		{
			enemyTanks[0].x -= enemyTanks[0].speed;
		}
		if (enemyTanks[1].y == SCREEN_H / 2 - 65 && active2)
		{
			enemyTanks[1].x -= enemyTanks[1].speed;
		}
		if (enemyTanks[2].y == SCREEN_H / 2 - 65 && active3)
		{
			enemyTanks[2].x -= enemyTanks[2].speed;
		}
		if (enemyTanks[0].x < 0 && active)
		{
			gameover = 1;
			lost = 1;
		}
		if (enemyTanks[1].x < 0 && active2)
		{
			gameover = 1;
			lost = 1;
		}
		if (enemyTanks[2].x < 0 && active3)
		{
			gameover = 1;
			lost = 1;
		}
	}
}

// Sets up bullet.
void draw_bullet(int num)
{
	int x = myTank.x;
	int y = myTank.y;

	// Ready to fire again?
	if (!bullets[num].alive)
	{
		bullets[num].alive = 1;
		bullets[num].x = x + 12;
		bullets[num].y = y - 18;
		bullets[num].yspd = -BULLETSPEED;
	}
	fire++;
}

// Updates bullet and draws.
void updatebullet(int num)
{

	int x = bullets[num].x;
	int y = bullets[num].y;

	if (bullets[num].alive)
	{
		// Move bullet.
		bullets[num].y += bullets[num].yspd;
		y = bullets[num].y;

		// Stay within the screen.
		if (y < 40)
		{
			bullets[num].alive = 0;
			return;
		}
		draw_sprite(buffer, bullet, bullets[num].x, bullets[num].y);
	}
}

// Sets up enemies bullet.
void enemy_bullet(int num)
{
	int x = enemyTanks[num].x;
	int y = enemyTanks[num].y;

	// Ready to fire again?
	if (!enemyBullets[num].alive)
	{
		enemyBullets[num].alive = 1;
		enemyBullets[num].x = x + 12;
		enemyBullets[num].y = y + 18;
		enemyBullets[num].yspd = +BULLETSPEED;
		if (num == 0)
		{
			enemyShot++;
		}
		if (num == 1)
		{
			enemyShot2++;
		}
		if (num == 2)
		{
			enemyShot3++;
		}
	}
}

// Updates and draws enemies bullet.
void updateEnemybullet(int num)
{
	int x = enemyBullets[num].x;
	int y = enemyBullets[num].y;

	if (enemyBullets[num].alive)
	{
		// Move bullet.
		enemyBullets[num].y += enemyBullets[num].yspd;
		y = enemyBullets[num].y;

		// Stay within the screen.
		if (enemyBullets[num].y > HEIGHT)
		{
			enemyBullets[num].alive = 0;
			if (num == 0)
			{
				enemyShot = 0;
			}
			if (num == 1)
			{
				enemyShot2 = 0;
			}
			if (num == 2)
			{
				enemyShot3 = 0;
			}
			return;
		}
		draw_sprite(buffer, bullet, enemyBullets[num].x, enemyBullets[num].y);
	}
}

// Goes through a for loop to check if there is collision detection.
void collision_detection()
{
	for (i = 0; i < 3; i++)
	{
		if (bullets[i].x > enemyTanks[0].x && bullets[i].x < enemyTanks[0].x + 32)
		{
			if (bullets[i].y > enemyTanks[0].y && bullets[i].y < enemyTanks[0].y + 32)
			{
				active = 0;
				play_sample(boom[0], volume, pan, pitch, FALSE);
			}
		}

		if (bullets[i].x > enemyTanks[1].x && bullets[i].x < enemyTanks[1].x + 32)
		{
			if (bullets[i].y > enemyTanks[1].y && bullets[i].y < enemyTanks[1].y + 32)
			{
				active2 = 0;
				play_sample(boom[0], volume, pan, pitch, FALSE);
			}
		}

		if (bullets[i].x > enemyTanks[2].x && bullets[i].x < enemyTanks[2].x + 32)
		{
			if (bullets[i].y > enemyTanks[2].y && bullets[i].y < enemyTanks[2].y + 32)
			{
				active3 = 0;
				play_sample(boom[0], volume, pan, pitch, FALSE);
			}
		}
		if (enemyBullets[i].x > barricadeX && enemyBullets[i].x < barricadeX + 90 && !destroyed)
		{
			if (enemyBullets[i].y > barricadeY && enemyBullets[i].y < barricadeY + 90 && !destroyed)
			{
				enemyBullets[i].alive = 0;
				play_sample(boom[0], volume, pan, pitch, FALSE);
				destroyed = 1;
			}
		}
	}

	// Player can not destroy barricade. Won't be allowed to fire.
	for (i = 0; i < 3; i++)
	{
		if (bullets[i].x > barricadeX && bullets[i].x < barricadeX + 90 && !destroyed)
		{
			if (bullets[i].y > barricadeY && bullets[i].y < barricadeY + 90 && !destroyed)
			{
				bullets[i].alive = 0;
			}
		}
	}

	// Player got hit.
	for (i = 0; i < 3; i++)
	{
		if (enemyBullets[i].x > myTank.x && enemyBullets[i].x < myTank.x + 32)
		{
			if (enemyBullets[i].y > myTank.y && enemyBullets[i].y < myTank.y + 32)
			{
				enemyBullets[i].alive = 0;
				play_sample(boom[0], volume, pan, pitch, FALSE);
				blownUp = 1;
				gameover = 1;
			}
		}
	}
}

int main()
{
	//Initialize Allegro.
	allegro_init();

	//Initialize the keyboard.
	install_keyboard();

	setupscreen();
	buffer = create_bitmap(WIDTH, HEIGHT);

	// Loads the images.
	barricade = load_bitmap("barricade.bmp", NULL);
	myTank_bmp = load_bitmap("tank2.bmp", NULL);
	enemyTank = load_bitmap("tank1.bmp", NULL);
	bullet = load_bitmap("bullet.bmp", NULL);
	explode_bmp = load_bitmap("explode.bmp", NULL);

	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
	{
		allegro_message("Error initializing sound system\n%s\n", allegro_error);
		return 1;
	}

	// Load the midi file
	music = load_midi("mach5.mid");
	boom[0] = load_sample("explode.wav");
	if (!music)
	{
		allegro_message("Error loading Midi file");
		return 1;
	}
	if (play_midi(music, 0) != 0)
	{
		allegro_message("Error playing Midi\n%s", allegro_error);
		return 1;
	}

	// Sets up my tank.
	myTank.x = SCREEN_W / 2 - myTank_bmp->w / 2;
	myTank.y = (SCREEN_H - 20) - myTank_bmp->h / 2;
	myTank.speed = 5;

	// Enemy Tank.Display (1, 2, 3).
	// 1.
	enemyTanks[0].x = 55 - enemyTank->w / 2;
	enemyTanks[0].y = 80 - enemyTank->h / 2;
	enemyTanks[0].speed = 5;

	// 2.
	enemyTanks[1].x = 85 - enemyTank->w / 2;
	enemyTanks[1].y = 80 - enemyTank->h / 2;
	enemyTanks[1].speed = 5;

	// 3.
	enemyTanks[2].x = 115 - enemyTank->w / 2;
	enemyTanks[2].y = 80 - enemyTank->h / 2;
	enemyTanks[2].speed = 5;

	while (!gameover){

			if (keypressed())
			{
				if (key[KEY_ESC])
				{
					gameover = 1;
				}
				if (key[KEY_LEFT])
				{
					myTank.x -= myTank.speed;
				}
				if (key[KEY_RIGHT])
				{
					myTank.x += myTank.speed;
				}
				if (key[KEY_SPACE])
				{
					if (fire < 3){
						draw_bullet(fire);
					}
				}
			}
			// Check boundary collision.
			if (myTank.x < 0)
			{
				myTank.x = 0;
			}
			if (myTank.x > SCREEN_W - 35)
			{
				myTank.x = SCREEN_W - 35;
			}

			if (enemyTanks[0].x == myTank.x && enemyShot < 1 && active)
			{
				enemy_bullet(0);
			}
			if (enemyTanks[1].x == myTank.x && enemyShot2 < 1 && active)
			{
				enemy_bullet(1);
			}

			collision_detection();
			status(score, level);

			drawBarricade();
			drawMyTank();
			drawEnemyTank(level);

			moveEnemy(level);

			// Update the bullets
			updatebullet(0);
			updatebullet(1);
			updatebullet(2);

			updateEnemybullet(0);
			updateEnemybullet(1);
			updateEnemybullet(2);
			if (fire == 3)
			{
				fire = 0;
			}
			if (active == 0 && !once)
			{
				score++;
				once = 1;
			}
			if (active2 == 0 && !once2)
			{
				score++;
				once2 = 1;
			}
			if (active3 == 0 && !once3)
			{
				score++;
				once3 = 1;
			}
		
		if (score == 2)
		{
			if (level2once == 0)
			{
				// Resets values for stuff.
				level = 2;
				for (i = 0; i < 3; i++)
				{
					enemyBullets[i].alive = 0;
				}

				active = 1;
				active2 = 1;
				active3 = 1;
				destroyed = 0;
				once = 0;
				once2 = 0;
				once3 = 0;
				enemyShot = 0;
				enemyShot2 = 0;
				enemyShot3 = 0;
				

				// Sets up my tank.
				myTank.x = SCREEN_W / 2 - myTank_bmp->w / 2;
				myTank.y = (SCREEN_H - 20) - myTank_bmp->h / 2;
				myTank.speed = 5;

				// Enemy Tank.Display (1, 2, 3).
				// 1.
				enemyTanks[0].x = 55 - enemyTank->w / 2;
				enemyTanks[0].y = 80 - enemyTank->h / 2;
				enemyTanks[0].speed = 5;

				// 2.
				enemyTanks[1].x = 85 - enemyTank->w / 2;
				enemyTanks[1].y = 80 - enemyTank->h / 2;
				enemyTanks[1].speed = 5;

				// 3.
				enemyTanks[2].x = 115 - enemyTank->w / 2;
				enemyTanks[2].y = 80 - enemyTank->h / 2;
				enemyTanks[2].speed = 5;

				level2once = 1;
			}		
		}
		if (score == 5)
		{
			// Makes sure it displays score 5.
			status(score, level);
			win = 1;
			gameover = 1;	
		}
		//Draw the buffer to the screen.
		blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);

		// Clear the contents of the buffer bitmap.
		clear_bitmap(buffer);
		rest(50);
	}
	rectfill(screen, 0, 45, WIDTH, HEIGHT, 0);
	if(lost)
	{
		stop_midi();
		textout_centre_ex(screen, font, "- Game Over - You Lose!!!",
			200, 20,
			WHITE, makecol(0, 0, 0));
		rest(2000);
	}
	if(win)
	{
		stop_midi();
		textout_centre_ex(screen, font, "- Game Over - You Win!!!",
			200, 20,
			WHITE, makecol(0, 0, 0));
		rest(2000);
	}
	if(blownUp)
	{
		stop_midi();
		textout_centre_ex(screen, font, "- Game Over - You Got Blowned Up!!!",
			200, 20,
			WHITE, makecol(0, 0, 0));
		rest(2000);
	}
	stop_midi();
	destroy_midi(music);
	destroy_bitmap(barricade);
	destroy_bitmap(myTank_bmp);
	destroy_bitmap(enemyTank);
	destroy_bitmap(bullet);
	destroy_bitmap(buffer);
	destroy_bitmap(explode_bmp);
	remove_sound();

	allegro_exit();
	return 0;
}
END_OF_MAIN()