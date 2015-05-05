#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

void Dave::InitDave(Dave &man, int x, int y, int Movespeed)
{
	man.x = x;
	man.y = y;
	man.ID = PLAYER;
	man.boundy = 7;
	man.lives = 3;
	man.score = 0;
	man.boundx = 6;
	man.speed = Movespeed;
	

}

void Dave::DrawDave(Dave &man, int x, int y)
{

	/*al_draw_filled_rectangle(man.x, man.y - 90, man.x + 20, man.y - 70, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(man.x - 10, man.y - 70, man.x + 30, man.y - 50, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(man.x, man.y - 50, man.x + 5, man.y - 20, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(man.x + 20, man.y - 50, man.x + 15, man.y - 20, al_map_rgb(0, 0, 255));*/
	al_draw_filled_rectangle(x, y - 90, x + 20, y - 70, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(x - 10, y - 70, x + 30, y - 50, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(x, y - 50, x + 5, y - 20, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(x + 20, y - 50, x + 15, y - 20, al_map_rgb(0, 0, 255));

}


void Level::displayFont(const int &WIDTH, const int &HEIGHT, int &countFPS) //Display Top and Bottom Text
{

	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	ALLEGRO_FONT *font18 = al_load_font("AGENCYR.TTF", 18, 0);

	al_draw_text(font24, al_map_rgb(0, 255, 0), 10, 5, 0, "Score:");
	al_draw_text(font24, al_map_rgb(0, 255, 0), 410, 5, 0, "Level ");
	al_draw_text(font24, al_map_rgb(0, 255, 0), 810, 5, 0, "Daves:");
	al_draw_text(font24, al_map_rgb(0, 255, 0), 10, HEIGHT - 50, 0, "JetPack");
	al_draw_text(font24, al_map_rgb(0, 255, 0), 810, HEIGHT - 50, 0, "Gun");
	al_draw_text(font24, al_map_rgb(0, 255, 0), WIDTH / 2, HEIGHT - 50, ALLEGRO_ALIGN_CENTER, "!!Go Thru The Door!!");
	//al_draw_textf(font18, al_map_rgb(0, 255, 0), WIDTH, 5, ALLEGRO_ALIGN_RIGHT, "FPS: %i"); count fps needs to be added

	//al_flip_display();
}

void Level::walls(const int &WIDTH, const int &HEIGHT)
{

	al_draw_filled_rectangle(0, HEIGHT-50, 1200, HEIGHT-80, al_map_rgb(255, 0, 0));	//Top wall (x, y, length, height, colour)
	al_draw_filled_rectangle(100, HEIGHT-100, 200, HEIGHT-130, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(250, HEIGHT - 150, 350, HEIGHT - 180, al_map_rgb(255, 0, 255)); //Bottom Wall
	//al_draw_filled_rectangle(10, HEIGHT - 110, 1000, 100, al_map_rgb(255, 0, 0));
	//al_flip_display();
	//al_rest(10.0);
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


