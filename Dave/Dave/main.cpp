#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "mappy_A5.h"


//GLOBAL VARIABLES
const int WIDTH = 1200;
const int HEIGHT = 650;
const int FPS = 60;
const int num_bullets = 3;
const int num_enemies = 3;
const int gravity = 1;
int Lives = 3;

int main(void)
{

	//primitive variable
	int countFPS = 0;
	int DaveWidth = 0;
	int DaveHeight = 0;
	int EnemyWidth = 0;
	int EnemyHeight = 0;

	bool done = false;
	bool keys[5] = { false, false, false, false, false };
	bool redraw = true;
	bool jump = false;
	bool isGameOver = false;
	bool collision = false;
	bool collisiont = false;
	bool liveGem = true;
	bool liveTrophy = true;
	Bullet bullets[num_bullets];
	Enemies enemy[num_enemies];

	//object variables
	Dave man;
	Level lvl; // object to display text on top and bottom of screen 
	Bullet bull;
	Enemies enem;

	//mappy-------
	int xOff = 0;
	int yOff = 0;
	//-----------
	
	//Dave init specs
	int Davex = 100; //allows us to change the players position from this class
	int Davey = 150; //allows us to change the players position from this class
	int Movespeed = 5; //allows us to change the players speed from this class
	int velx = 0;
	int vely = 0;
	int jumpSpeed = 13;
	///////////////////

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *Dave = NULL;
	ALLEGRO_BITMAP *Door = NULL;
	ALLEGRO_BITMAP *Trophy = NULL;
	ALLEGRO_BITMAP *redGem = NULL;
	ALLEGRO_BITMAP *blueGem = NULL;
	ALLEGRO_BITMAP *fire = NULL;
	ALLEGRO_BITMAP *en = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//Initialization
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_image_addon(); //mappy

	//mappy
	if (MapLoad("game.fmp", 1))
		return -5;
	//-------------

	///Load pictures
	Dave = al_load_bitmap("man.png");
	en = al_load_bitmap("enemy.png");
	Trophy = al_load_bitmap("trophy.png");
	Door = al_load_bitmap("door.png");
	redGem = al_load_bitmap("redGem.png");
	blueGem = al_load_bitmap("blueGem.png");
	//fire = al_load_bitmap(fire.png");
	////////

	//Bounds for collision
	DaveWidth = al_get_bitmap_width(Dave);
	DaveHeight = al_get_bitmap_height(Dave);
	EnemyWidth = al_get_bitmap_width(en);
	EnemyHeight = al_get_bitmap_height(en);
	int redGemWidth = al_get_bitmap_width(redGem);
	int redGemHeight = al_get_bitmap_width(redGem);
	int trophyGemWidth = al_get_bitmap_width(Trophy);
	int trophyGemHeight = al_get_bitmap_width(Trophy);

	int Dbx = DaveWidth / 2; //Dave bound x
	int Dby = DaveHeight / 2; //Dave bound y
	int Ebx = EnemyWidth / 2;
	int Eby = EnemyHeight / 2;
	int RGBx = redGemWidth / 2;
	int RGBy = redGemHeight / 2;
	int RGx = 600;
	int RGy = 500;
	int xE = 750;
	int yE = 350;
	int a = 1, b = 1;
	int Tx = 700;
	int Ty = 150;
	int TBx = trophyGemWidth / 2;
	int TBy = trophyGemHeight / 2;
	//////////////

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));

	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	ALLEGRO_FONT *font18 = al_load_font("AGENCYR.TTF", 18, 0);

	//Initialise characters
	man.InitDave(man, Davex, Davey, Movespeed, Dbx, Dby);
	bull.InitBullet(bullets, num_bullets);
	enem.InitEnemy(enemy, num_enemies);

	//Register/ Load sources to event queue 
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//////Main Game Loop
	al_start_timer(timer);
	while (!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		countFPS++;

		//enemy one level 1
		if (xE >= 900 && a>0)
			a *= -1;
		if (xE<750 && a<0)
			a *= -1;

		xE += a * 3;

		///////Key pressed
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //checks to see if a key is pressed
		{

			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;

				/*case ALLEGRO_KEY_DOWN:		//not needed anymore delete if necessary...
				keys[DOWN] = true;
				break;*/

			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;

			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = true;
				bull.FireBullet(bullets, num_bullets, Davex, Davey);
				break;
			}
		}

		////////Key released
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) //checks to see if a key is released
		{

			switch (ev.keyboard.keycode)
			{

			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;

				/*case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;*/

			case ALLEGRO_KEY_RIGHT:
				velx = 0;  //Stops moving Dave right when the key is not pressed, 
				//if we do not have this code, Dave will continue to move right.
				keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				velx = 0; //Stops moving Dave left when the key is not pressed,
				//if we do not have this code Dave will continue to move left.
				keys[LEFT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = false;
				break;
			}
		}

		/////Close screen
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		//////Timer Event
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			if (keys[UP] && jump) //Jump
			{

				//man.MoveUp(man, jump, gravity, HEIGHT);
				vely = -jumpSpeed;
				jump = false;
			}

			/*if (keys[DOWN])			//Not needed anymore, delete if necessary
			man.MoveDown(man);*/

			if (keys[LEFT])
			{

				//man.MoveLeft(man);
				velx = -Movespeed;
			}

			if (keys[RIGHT])
			{

				//man.MoveRight(man);
				velx = Movespeed;
			}

			if (!isGameOver)
			{
				bull.UpdateBullet(bullets, num_bullets, WIDTH);
				bull.collideBullets(bullets, num_bullets, enemy, num_enemies, man);
				enem.StartEnemy(enemy, num_enemies, WIDTH, HEIGHT);
				enem.UpdateEnemy(enemy, num_enemies);

				//Collision  enemy
				if (Davex + Dbx > xE - Ebx && Davex - Dbx < xE + Ebx && Davey + Dby > yE - Eby &&	Davey - Dby < yE + Eby)
				{
					//collision = true;

					Lives -= 1;
					Davex = 100;
					Davey = 150;
					al_draw_bitmap(Dave, Davex, Davey - DaveHeight / 2, 0);

				}

				//collision detection gem
				if (Davex + Dbx > RGx - RGBx && Davex - Dbx < RGx + RGBx && Davey + Dby > RGy - RGBy &&	Davey - Dby < RGy + RGBy)
				{
					liveGem = false;
					man.increaseScore(man);

				}

				//collision detection trophy
				if (Davex + Dbx > Tx - TBx && Davex - Dbx < Tx + TBx && Davey + Dby > Ty - TBy &&	Davey - Dby < Ty + TBy)
				{
					liveTrophy = false;
					man.increaseScore(man);

				}
				if (!liveTrophy)
				{
					al_draw_text(font24, al_map_rgb(0, 255, 0), 600, HEIGHT - 60, 0, "Go Thru the door");
				}

				if (Lives <= 0)
					isGameOver = true;
					
					
					//man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;
			}
		}

		///////Redraw
		if (redraw && al_is_event_queue_empty(event_queue))
		{

			redraw = false;

			if (!isGameOver)
			{

				MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT); //mappy

				int posx = 200;

				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx, 60, 0, "Score: %i", man.displayScore(man));
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx + 300, 60, 0, "Level:%i", lvl.displayLevel(lvl));
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx + 600, 60, 0, "Daves:%i", Lives);

				if (!jump)
					vely += gravity;

				else
					vely = 0;
				Davex += velx;
				Davey += vely;

				jump = (Davey + DaveHeight / 2 >= HEIGHT - 105);

				if (Davex>0 && Davex<205 && Davey<HEIGHT - 105)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 155);

				if (Davex>105 && Davex<305 && Davey<HEIGHT - 205 && Davey>275)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex>205 && Davex < 455 && Davey < HEIGHT - 305)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 355);

				if (Davex > 455 && Davex< 660 && Davey < HEIGHT - 200)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex > 500 && Davex< 850 && Davey < HEIGHT - 355)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 450);

				if (Davex > 900 && Davex< 1200 && Davey < HEIGHT - 300)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 400);

				if (Davex > 700 && Davex< 855 && Davey < HEIGHT - 200 && Davey> HEIGHT - 400)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex > 855 && Davex < 1200 && Davey < HEIGHT - 150 && Davey> HEIGHT - 250)
				{
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 205);
				}



				// frame restriction left
				if (Davex<50)
					Davex = 50;

				// frame restriction right
				if (Davex>1100)
					Davex = 1100;

				redraw = true;

				//If gem collision is detected execute this code
				if (collision)
				{
					man.increaseScore(man);
					//al_draw_bitmap(redGem, 600, 100, 0);
					liveGem = false;
				}
				

				//If trophy collision is detected execute this code
				if (collisiont)
				{
					man.increaseScore(man);
					//al_draw_bitmap(redGem, 600, 100, 0);
					liveGem = false;
				}
				////////Draw to screen
				
				if (liveGem)
				{
					al_draw_bitmap(redGem, RGx, RGy, 0);
				}
				
				
				
				al_draw_bitmap(Dave, Davex, Davey - DaveHeight / 2, 0);
				al_draw_bitmap(en, xE, 350, NULL);
				bull.DrawBullet(bullets, num_bullets);
				al_draw_bitmap(Door, 1150, HEIGHT - 150, 0);
				
				if (liveTrophy)
				{
					al_draw_bitmap(Trophy, Tx, Ty, 0);
				}
				

				man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;

				
			//
				//enem.DrawEnemy(enemy, num_enemies);
				//lvl.displayFont(WIDTH, HEIGHT, countFPS);
				//lvl.walls(WIDTH, HEIGHT);
				//lvl.displayFont(WIDTH, HEIGHT, countFPS);
				//man.displayScoreLives(man);
			}

			////If there is a game over
			else
			{
				man.gameOver(WIDTH, HEIGHT, man);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	////Destroy objects from memory
	al_destroy_bitmap(Dave);
	al_destroy_bitmap(en);
	al_destroy_bitmap(blueGem);
	al_destroy_bitmap(redGem);
	al_destroy_bitmap(fire);
	al_destroy_bitmap(Door);
	al_destroy_bitmap(Trophy);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}
///End of code