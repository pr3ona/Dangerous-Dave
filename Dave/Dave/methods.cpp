#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>




void Dave::InitDave(Dave &man, int x, int y, int Movespeed, int bx, int by)
{
	man.x = x;
	man.y = y;
	man.ID = PLAYER;
	man.boundy = by;
	man.lives = 3;
	man.score = 0;
	man.boundx = bx;
	man.speed = Movespeed;
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
	man.score += 100;
	if (man.score = 1000)
		man.lives = +1;
		
		return man.score;
}



void Level::displayFont(const int &WIDTH, const int &HEIGHT, int &countFPS) //Display Top and Bottom Text
{
	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	ALLEGRO_FONT *font18 = al_load_font("AGENCYR.TTF", 18, 0);

	al_draw_text(font24, al_map_rgb(0, 255, 0), 5, 5, 0, "Level:000000000000000000 ");	
	/*al_draw_text(font24, al_map_rgb(0, 255, 0), 10, HEIGHT - 50, 0, "JetPack");
	al_draw_text(font24, al_map_rgb(0, 255, 0), 810, HEIGHT - 50, 0, "Gun");
	al_draw_text(font24, al_map_rgb(0, 255, 0), WIDTH / 2, HEIGHT - 50, ALLEGRO_ALIGN_CENTER, "!!Go Thru The Door!!");
	al_draw_textf(font18, al_map_rgb(0, 255, 0), WIDTH, 5, ALLEGRO_ALIGN_RIGHT, "FPS: %i"); count fps needs to be added

	//al_flip_display();??????????*/
}


/*										
void Dave:: MoveLeft(Dave &man)
{
	man.x -= man.speed;
	if (man.x < 0)
		man.x = 0;

}

void Dave:: MoveUp(Dave &man, bool &jump, const int gravity, const int HEIGHT)
{
	//man.vely = -man.jumpspeed;
	//jump = false;
	
	man.y -= man.jumpspeed;
	jump = true;

	if (man.y < 0)
		man.y = 50;
}
void Dave:: MoveDown(Dave &man)
{
	man.y += man.speed;
	if (man.y > 700)
		man.y = 700;

}
void Dave:: MoveRight(Dave &man)
{
	man.x += man.speed;
	if (man.x > 1200)
		man.x = 1200;
}

void Dave::JumpUp(Dave &man, bool &jump, const int gravity, const int HEIGHT)
{

	if (jump)
	{
		man.y += gravity;
	}
	else
	{
		vely = 0;
	}

	man.y += man.vely;

	jump = man.y + 75 >= 560;

	if (jump)
		man.y = HEIGHT - 75;
}
*/
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
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 2 ,al_map_rgb(255, 255, 255));
	}
}
void Bullet::FireBullet(Bullet bullet[], int size, int x, int y)
{
	
	for (int i = 0; i < size; i++)
	{
	
		if (!bullet[i].live)
		{
			bullet[i].x = x + 17;
			bullet[i].y = y - 50;
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

void Bullet::collideBullets(Bullet bullets[], int BSize, Enemies enemy[], int ESize, Dave &man)
{
	for (int i = 0; i < BSize; i++)
	{
		if (bullets[i].live)
		{
			for (int j = 0; j < ESize; j++)
			{
				if (enemy[j].live)
				{
					if (bullets[i].x >(enemy[j].x - enemy[j].boundx) &&
						bullets[i].x < (enemy[j].x + enemy[j].boundx) &&
						bullets[i].y >(enemy[j].y - enemy[j].boundy) &&
						bullets[i].y < (enemy[j].y + enemy[j].boundy))
					{
						bullets[i].live = false;
						enemy[j].live = false;
						man.score++;
					}
				}
			}
		}
	}

}


void Enemies::InitEnemy(Enemies enemy[], int size)
{
	for (int i = 0; i < size; i++)
	{

		enemy[i].ID = ENEMY;
		enemy[i].live = false;
		enemy[i].speed = 5;
		enemy[i].boundx = 18;
		enemy[i].boundy = 18;
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