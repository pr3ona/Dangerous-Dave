#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

void Dave::InitDave(Dave &man, int x, int y, int Movespeed, int bx, int by, ALLEGRO_BITMAP *Dave)
{
	man.x = x;
	man.y = y;
	man.ID = PLAYER;
	man.boundy = by;
	man.lives = 3;
	man.score = 0;
	man.boundx = bx;
	man.speed = Movespeed;

	if (Dave != NULL) 
	      man.iDave = Dave;

}

void Dave::DrawDave(Dave &man, int x, int y, int imageRad)
{

	al_draw_filled_rectangle(imageRad, imageRad - 9, imageRad + 10, imageRad - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(imageRad, imageRad + 9, imageRad + 10, imageRad + 7, al_map_rgb(255, 0, 0));

	al_draw_filled_triangle(imageRad - 12, imageRad - 17, imageRad + 12, imageRad, imageRad - 12, imageRad + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(imageRad - 12, imageRad - 2, imageRad + 15, imageRad + 2, al_map_rgb(0, 0, 255));
}

void Dave::displayScoreLives(Dave &man)
{
	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	al_draw_textf(font24, al_map_rgb(0, 255, 0), 10, 5, 0, "Score: %i", man.score);
	al_draw_textf(font24, al_map_rgb(0, 255, 0), 810, 5, 0, "Daves: %i", man.lives);
}

void Dave::gameOver(Dave &man, bool &isGameover)
{

	if (man.lives <= 0)
		isGameover = true;
}

void Dave::gameOver(int WIDTH, int HEIGHT, Dave &man, int Score)
{

	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	al_draw_textf(font24, al_map_rgb(0, 255, 0), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "Game over. Final score: %i", Score);
}

int Dave::DecreaseLife(Dave &man)
{
	return man.lives--;
}
int Dave::displayScore(Dave &man)
{
	return man.score;
}

int Level::displayLevel(Level &lvl)
{
	return lvl.stageNumber +1;
}



int Dave::displayLives(Dave &man)
{
	return man.lives;
}

int Dave::increaseScore(Dave &man)
{
	man.score += 200;
	if (man.score % 1000 == 0)
	{
		man.lives++;
	}	
		return man.score;
}



void Level::displayFont(const int &WIDTH, const int &HEIGHT, int &countFPS) //Display Top and Bottom Text
{
	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	ALLEGRO_FONT *font18 = al_load_font("AGENCYR.TTF", 18, 0);

	al_draw_text(font24, al_map_rgb(0, 255, 0), 5, 5, 0, "Level:000000000000000000 ");
}

void Bullet::InitBullet(Bullet bullet[], int size)
{

	for (int i = 0; i < size; i++)
	{
	
		bullet[i].ID = BULLET;
		bullet[i].speed = 8;
		bullet[i].live = false;
	}

}
void Bullet::DrawBullet(Bullet bullet[], int size)
{

	for (int i = 0; i < size; i++)
	{
		if (bullet[i].live)
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 3 ,al_map_rgb(255, 255, 255));
	}
}
void Bullet::FireBullet(Bullet bullet[], int size, int Davex, int Davey)
{
	
	for (int i = 0; i < size; i++)
	{
	
		if (!bullet[i].live)
		{
			bullet[i].x = Davex + 17;
			bullet[i].y = Davey;
			bullet[i].live = true;
			break;
		}
	}

}
void Bullet::UpdateBullet(Bullet bullet[], int size, int WIDTH)
{

	for (int i = 0; i < size; i++)
	{
	
		if (bullet[i].live)
		{
		
			bullet[i].x += bullet[i].speed;
			if (bullet[i].x > WIDTH)
				bullet[i].live = false;
		}
	}
}

int Bullet::collideBullets(Bullet bullets[], int num_bullets, int Ebx, int EnemyWidth, int Eby, int EnemyHeight, Dave &man, bool shot)
{
	for (int i = 0; i < num_bullets; i++)
	{
		if (bullets[i].live)
		{
				if (!shot)
				{
					if (bullets[i].x > EnemyWidth - Ebx &&
						bullets[i].x < EnemyWidth + Ebx &&
						bullets[i].y > EnemyHeight - Eby &&
						bullets[i].y < EnemyHeight + Eby)
					{
						bullets[i].live = false;
						shot = false;
						man.score++;
					}
				}
			
		}
	}
	
	return shot;
}


void Enemies::InitEnemy(Enemies enemy[], int size, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2)
{
	for (int i = 0; i < size; i++)
	{

		enemy[i].ID = ENEMY;
		enemy[i].live = false;
		enemy[i].speed = 5;
		enemy[i].boundx = 18;
		enemy[i].boundy = 18;


		if (image != NULL)
			enemy[i].iEnemy = image;
		if (image2 != NULL)
			enemy[i].iEnemy2 = image2;
	}

	

}

void Enemies::DrawEnemy(Enemies enemy[], int size)
{

	for (int i = 0; i < size; i++)
	{

		if (enemy[i].live)
		{
			al_draw_filled_circle(enemy[i].x, enemy[i].y, 20, al_map_rgb(255, 0, 0));
		}
	}


}

void Enemies::StartEnemy(Enemies enemy[], int size, int WIDTH, int HEIGHT)
{

	for (int i = 0; i < size; i++)
	{

		if (!enemy[i].live)
		{

			if (rand() % 500 == 0)
			{

				enemy[i].live = true;
				enemy[i].x = 1000;
				enemy[i].y = 30 + rand() % (HEIGHT - 60);
				break;
			}
		}
	}

}

void Enemies::UpdateEnemy(Enemies enemy[], int size)
{

	//Code for where movement of enemies are added 

}