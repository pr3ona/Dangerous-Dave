#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>



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
	bool done = false;
	bool keys[5] = { false, false, false, false, false };
	Bullet bullets[num_bullets];
	//Enemies enemy[num_enemies];
	bool redraw = true;
	bool jump = false;

	int Davex = 50; //allows us to change the players position from this class youll see why...
	int Davey = 600; //allows us to change the players position from this class youll see why...
	int Movespeed = 5; //allows us to change the players speed from this class youll see why...
	int velx = 0; //youll see why...
	int vely = 0; //youll see why...
	int jumpSpeed = 15; 
	//object variables
	Dave man;
	Level lvl; // text on top and bottom of screen 
	Bullet bull;
	//Enemies enem;



	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;



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

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();

	srand(time(NULL));
	man.InitDave(man, Davex, Davey, Movespeed);
	bull.InitBullet(bullets, num_bullets);
	//enem.InitEnemy(enemy, num_enemies);


	//Register/ Load sources to event queue 
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));



	



	al_start_timer(timer);
	while (!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//countFPS++;
		
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

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

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
				

			bull.UpdateBullet(bullets, num_bullets, WIDTH);
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{

			redraw = false;
			
			if (!jump)
				vely += gravity;
		
			else
				vely = 0;
			Davex += velx;
			Davey += vely;

			jump = (Davey + 32 >= 560);

			if (jump)
				Davey = 560 - 32;
			man.DrawDave(man, Davex, Davey);
			bull.DrawBullet(bullets, num_bullets);

			//lvl.displayFont(WIDTH, HEIGHT, countFPS);
			lvl.walls(WIDTH, HEIGHT);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
}

	//Destroying
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}
