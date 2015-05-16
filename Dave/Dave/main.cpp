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

int main(void)
{

	//primitive variable
	int countFPS = 0;
	int DaveWidth = 0;
	int DaveHeight = 0;
	
	bool done = false;
	bool keys[5] = { false, false, false, false, false };
	bool redraw = true;
	bool jump = false;
	bool isGameOver = false;
	bool collision = false;
	
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
	Trophy = al_load_bitmap("trophy.png");
	Door = al_load_bitmap("door.png");
	redGem = al_load_bitmap("redGem.png");
	blueGem = al_load_bitmap("blueGem.png");
	//fire = al_load_bitmap(fire.png");
	////////

	//Bounds for collision
	DaveWidth = al_get_bitmap_width(Dave);
	DaveHeight = al_get_bitmap_height(Dave);
	int redGemWidth = al_get_bitmap_width(redGem);
	int redGemHeight = al_get_bitmap_width(redGem);

	int Dbx = DaveWidth / 2; //Dave bound x
	int Dby = DaveHeight / 2; //Dave bound y
	int RGBx = redGemWidth / 2;
	int RGBy = redGemHeight / 2;
	int RGx = 600;
	int RGy = 500;
	//////////////

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	srand(time(NULL));
	
	ALLEGRO_FONT *font24 = al_load_font("BAUHS93.TTF", 24, 0);
	ALLEGRO_FONT *font18 = al_load_font("AGENCYR.TTF", 18, 0);

	//Initialise characters
	man.InitDave(man, Davex, Davey, Movespeed, Dbx, Dby);
	bull.InitBullet(bullets, num_bullets);
	//enem.InitEnemy(enemy, num_enemies);
	
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
				//enem.StartEnemy(enemy, num_enemies, WIDTH, HEIGHT);
				//	enem.UpdateEnemy(enemy, num_enemies);

				//Collision detection
			if (Davex + Dbx > RGx - RGBx && Davex - Dbx < RGx + RGBx && Davey + Dby > RGy - RGBy &&	Davey - Dby < RGy + RGBy)
			{
				collision = true;
			}

			else
				collision = false;
				
			man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;
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
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx + 600, 60, 0, "Daves:%i", man.displayLives(man));

				if (!jump)
					vely += gravity;
		
				else
					vely = 0;
					Davex += velx;
					Davey += vely;

					jump = (Davey + DaveHeight / 2 >= HEIGHT-105);

				if (Davex>0 && Davex<205 && Davey<HEIGHT-105)
					jump = (Davey+DaveHeight/2>=HEIGHT-155);


				if (Davex>105 && Davex<305 && Davey<HEIGHT - 205)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex>205 && Davex < 455 && Davey < HEIGHT - 305)
				{

					jump = (Davey + DaveHeight / 2 >= HEIGHT - 355);
		
					if (Davex > 455 && Davey >HEIGHT - 355)
						Davey = HEIGHT - 250;
				}
				
				// frame restriction left
				if (Davex<1)
					Davex = 1;

				// frame restriction right
				if (Davex>1200 - 26)
					Davex = 1200 - 26;

				redraw = true;

				////////Draw to screen
				al_draw_bitmap(redGem, RGx, RGy, 0);
				al_draw_bitmap(Dave, Davex,Davey-DaveHeight/2, 0);
				bull.DrawBullet(bullets, num_bullets);
				al_draw_bitmap(Door, 1150, HEIGHT-150, 0);
				al_draw_bitmap(Trophy, 700, 150, 0);
			
				man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;
			
				//If collision is detected execute this code
				if (collision)
				{
					al_draw_bitmap(redGem, 600, 100, 0);
				
					man.DecreaseLife(man);
				}

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