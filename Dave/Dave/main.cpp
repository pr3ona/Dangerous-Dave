#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "object.h"
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "mappy_A5.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <iostream>

//GLOBAL VARIABLES
const int WIDTH = 1200;
const int HEIGHT = 650;
const int FPS = 60;
const int num_bullets = 3;
const int num_enemies = 3;
const int gravity = 1;
int Lives = 3;
int Score = 0;

void changeState(int &state, int newState, int, int, int, int, int);

//object variables
Dave man;
Level lvl; // object to display text on top and bottom of screen 
Bullet bull;
Enemies enem;

///////Animate the enemy
const int maxFrame = 2;
int curFrame = 0;
int frameCount = 0;
int frameDelay = 5;
/////////

Bullet bullets[num_bullets];
Enemies enemy[num_enemies];
ALLEGRO_BITMAP *iDave = NULL;
ALLEGRO_BITMAP *en[maxFrame];
ALLEGRO_BITMAP *enf[maxFrame];

int main(void)
{

	//primitive variable
	int countFPS = 0;
	int DaveWidth = 0;
	int DaveHeight = 0;
	int EnemyWidth = 0;
	int EnemyHeight = 0;

	bool done = false;
	bool keys[] = { false, false, false, false, false, false };
	bool redraw = true;
	bool jump = false;
	//bool isGameOver = false;
	bool collision = false;
	bool collisiont = false;
	bool liveGem1 = true;
	bool liveGem2 = true;
	bool liveGem3 = true;
	bool liveGem4 = true;
	bool liveGem5 = true;
	bool liveGem6 = true;
	bool liveGem7 = true;
	bool liveGem8 = true;
	bool level1 = true;
	bool level2 = false;
	bool liveTrophy = true;
	bool flipenemy = false;

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

	/////////STATE////////////////TITLE/////PLAYING///GAMEOVER
	int state = -1;
	///////////////

	///////Enemy movement
	int degree = 0;
	/////////////

	

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	
	ALLEGRO_BITMAP *Door = NULL;
	ALLEGRO_BITMAP *Trophy = NULL;
	ALLEGRO_BITMAP *redGem1 = NULL;
	ALLEGRO_BITMAP *redGem2 = NULL;
	ALLEGRO_BITMAP *redGem3 = NULL;
	ALLEGRO_BITMAP *redGem4 = NULL;

	ALLEGRO_BITMAP *blueGem1 = NULL;
	ALLEGRO_BITMAP *blueGem2= NULL;
	ALLEGRO_BITMAP *blueGem3 = NULL;
	ALLEGRO_BITMAP *blueGem4 = NULL;

	ALLEGRO_BITMAP *fire = NULL;
	
	ALLEGRO_BITMAP *title = NULL;
	ALLEGRO_BITMAP *lost = NULL;

	ALLEGRO_SAMPLE *backgroundMusic = NULL;
	ALLEGRO_SAMPLE_INSTANCE *walking = NULL;
	ALLEGRO_SAMPLE_INSTANCE *shooting = NULL;
	ALLEGRO_SAMPLE_INSTANCE *collectGem = NULL;
	ALLEGRO_SAMPLE_INSTANCE *jumptime = NULL;
	ALLEGRO_SAMPLE_INSTANCE *gothruthedoor = NULL;
	ALLEGRO_SAMPLE_INSTANCE *exitdoor = NULL;
	ALLEGRO_SAMPLE_INSTANCE *newlife = NULL;
	ALLEGRO_SAMPLE_INSTANCE *gameover = NULL;
	ALLEGRO_SAMPLE_INSTANCE *death = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//Initialization of addons
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_image_addon(); //mappy
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);		//creates channels ...(number of channels)... and a *default mixer which 
								//converts many sounds being played simultaneously 
								//together, to output to a signle channel since speakers are only single channel
	backgroundMusic = al_load_sample("AnimalsRemix.ogg"); //allegro can't play mp3s
	walking = al_create_sample_instance(al_load_sample("Walking.wav"));
	shooting = al_create_sample_instance(al_load_sample("Shooting.wav"));
	collectGem = al_create_sample_instance(al_load_sample("Gem.wav"));
	jumptime = al_create_sample_instance(al_load_sample("Jump.wav"));
	gothruthedoor = al_create_sample_instance(al_load_sample("Gothruthedoor.wav"));
	exitdoor = al_create_sample_instance(al_load_sample("Exitdoor.wav"));
	newlife = al_create_sample_instance(al_load_sample("Newlife.wav"));
	gameover = al_create_sample_instance(al_load_sample("Gameover.wav"));
	death = al_create_sample_instance(al_load_sample("Death.wav"));

	/*To hear each sound effect individually we use the sample instance to mixer method,
	recall that each sound effect = 1 channel, therefore, we have 10 channels in our game,
	but our speaker is only a 1 channel*/

	al_attach_sample_instance_to_mixer(walking, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(shooting, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(collectGem, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(jumptime, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(gothruthedoor, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(exitdoor, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(newlife, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(gameover, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(death, al_get_default_mixer());
	///////////////

	title = al_load_bitmap("Dave_title.png");
	lost = al_load_bitmap("Dave_end.png");

	
	//mappy
	if (MapLoad("game.fmp", 1))
		return -5;
	//-------------

	///Load pictures
	iDave = al_load_bitmap("man.png");
	
	en[0] = al_load_bitmap("en0.bmp");
	en[1] = al_load_bitmap("en1.bmp");
	enf[0] = al_load_bitmap("en0f.bmp");
	enf[1] = al_load_bitmap("en1f.bmp");

	for (int i = 0; i < 2; i++)
	{
		al_convert_mask_to_alpha(en[i], al_map_rgb(255, 0, 255));
		al_convert_mask_to_alpha(enf[i], al_map_rgb(255, 0, 255));
	}

	

	Trophy = al_load_bitmap("trophy.png");
	Door = al_load_bitmap("door.png");
	//red gems
	redGem1 = al_load_bitmap("redGem.png");
	redGem2 = al_load_bitmap("redGem.png");
	redGem3 = al_load_bitmap("redGem.png");
	redGem4 = al_load_bitmap("redGem.png");

	//blue gems
	blueGem1 = al_load_bitmap("blueGem.png");
	blueGem2 = al_load_bitmap("blueGem.png");
	blueGem3 = al_load_bitmap("blueGem.png");
	blueGem4 = al_load_bitmap("blueGem.png");
	
	
	//fire = al_load_bitmap(fire.png");
	////////

	//Bounds for collision
	DaveWidth = al_get_bitmap_width(iDave);
	DaveHeight = al_get_bitmap_height(iDave);
	EnemyWidth = al_get_bitmap_width(en[0]);
	EnemyHeight = al_get_bitmap_height(en[0]);

	int redGemWidth = al_get_bitmap_width(redGem1);
	int redGemHeight = al_get_bitmap_width(redGem1);


	int redGem2Width = al_get_bitmap_width(redGem2);
	int redGem2Height = al_get_bitmap_width(redGem2);
	int RG2x = 250;
	int RG2y = HEIGHT-300;

	int redGem3Width = al_get_bitmap_width(redGem3);
	int redGem3Height = al_get_bitmap_width(redGem3);
	int RG3x = 300;
	int RG3y = HEIGHT-400;

	int redGem4Width = al_get_bitmap_width(redGem4);
	int redGem4Height = al_get_bitmap_width(redGem4);
	int RG4x = 400;
	int RG4y = HEIGHT - 400;


	int blueGem1Width = al_get_bitmap_width(blueGem1);
	int blueGem1Height = al_get_bitmap_width(blueGem1);
	int BG1x = 600;
	int BG1y = HEIGHT - 300;

	int blueGem2Width = al_get_bitmap_width(blueGem2);
	int blueGem2Height = al_get_bitmap_width(blueGem2);
	int BG2x = 850;
	int BG2y = HEIGHT - 300;

	int blueGem3Width = al_get_bitmap_width(blueGem3);
	int blueGem3Height = al_get_bitmap_width(blueGem3);
	int BG3x = 50;
	int BG3y = HEIGHT - 500;

	int blueGem4Width = al_get_bitmap_width(blueGem4);
	int blueGem4Height = al_get_bitmap_width(blueGem4);
	int BG4x = 1100;
	int BG4y = HEIGHT - 450;








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


	changeState(state, TITLE, Davex, Davey, Movespeed, Dbx, Dby);

	//Initialise characters
	man.InitDave(man, Davex, Davey, Movespeed, Dbx, Dby, iDave);
	bull.InitBullet(bullets, num_bullets);
	//enem.InitEnemy(enemy, num_enemies, en[]);

	//Register/ Load sources to event queue 
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_play_sample(backgroundMusic, 0.2, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

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
				keys[ESCAPE] = true;
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
				al_play_sample_instance(shooting);
				break;

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				if (state == TITLE)
					changeState(state, PLAYING, Davex, Davey, Movespeed, Dbx, Dby);
				else if (state == GAMEOVER)
					changeState(state, PLAYING, Davex, Davey, Movespeed, Dbx, Dby);
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
				keys[ESCAPE] = false;
				break;

			case ALLEGRO_KEY_LCTRL:
				keys[LCTRL] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
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
				al_play_sample_instance(jumptime);
				jump = false;
			}

			/*if (keys[DOWN])			//Not needed anymore, delete if necessary
			man.MoveDown(man);*/

			if (keys[LEFT])
			{

				//man.MoveLeft(man);
				velx = -Movespeed;
				//al_play_sample_instance(walking);
			}

			if (keys[RIGHT])
			{

				//man.MoveRight(man);
				velx = Movespeed;
				//al_play_sample_instance(walking);
				
			}
			
			if (state == TITLE)
			{ 
				
			}

			if (state == PLAYING)
			{
				bull.UpdateBullet(bullets, num_bullets, WIDTH);
				bull.collideBullets(bullets, num_bullets, enemy, num_enemies, man);
				enem.StartEnemy(enemy, num_enemies, WIDTH, HEIGHT);
				enem.UpdateEnemy(enemy, num_enemies);

				//Collision  enemy
				if (Davex + Dbx > xE - Ebx && Davex - Dbx < xE + Ebx && Davey + Dby > yE - Eby &&	Davey - Dby < yE + Eby)
				{
					//collision = true;

					man.DecreaseLife(man); // Lives -= 1;
					Davex = 100;
					Davey = 150;
					al_draw_bitmap(iDave, Davex, Davey - DaveHeight / 2, 0);
					al_play_sample_instance(death);
				}

				//collision detection gem
				if (liveGem1 && Davex + Dbx > RGx - RGBx && Davex - Dbx < RGx + RGBx && Davey + Dby > RGy - RGBy &&	Davey - Dby < RGy + RGBy)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem1 = false;
				}
				
				//collision detection gem
				if (liveGem2 && Davex + Dbx > RG2x - redGem2Width / 2 && Davex - Dbx < RG2x + redGem2Width / 2 && Davey + Dby > RG2y - redGem2Height / 2 && Davey - Dby < RG2y + redGem2Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score+=100;
					liveGem2 = false;
				}

				//collision detection gem
				if (liveGem2 && Davex + Dbx > RG2x - redGem2Width / 2 && Davex - Dbx < RG2x + redGem2Width / 2 && Davey + Dby > RG2y - redGem2Height / 2 && Davey - Dby < RG2y + redGem2Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score+=100;
					liveGem2 = false;
					
				}

				//collision detection gem
				if (liveGem3&&Davex + Dbx > RG3x - redGem3Width / 2 && Davex - Dbx < RG3x + redGem3Width / 2 && Davey + Dby > RG3y - redGem3Height / 2 && Davey - Dby < RG3y + redGem3Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem3 = false;
				}

				//collision detection gem
				if (liveGem4&&Davex + Dbx > RG4x - redGem4Width / 2 && Davex - Dbx < RG4x + redGem4Width / 2 && Davey + Dby > RG4y - redGem4Height / 2 && Davey - Dby < RG4y + redGem4Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem4 = false;
				}

				//collision detection gem
				if (liveGem5&&Davex + Dbx > BG1x - blueGem1Width / 2 && Davex - Dbx < BG1x + blueGem1Width / 2 && Davey + Dby > BG1y - blueGem1Height / 2 && Davey - Dby < BG1y + blueGem1Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem5 = false;
				}

				//collision detection gem
				if (liveGem6&&Davex + Dbx > BG2x - blueGem2Width / 2 && Davex - Dbx < BG2x + blueGem1Width / 2 && Davey + Dby > BG2y - blueGem2Height / 2 && Davey - Dby < BG2y + blueGem2Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem6 = false;
				}

				//collision detection gem
				if (liveGem7&&Davex + Dbx > BG3x - blueGem3Width / 2 && Davex - Dbx < BG3x + blueGem3Width / 2 && Davey + Dby > BG3y - blueGem3Height / 2 && Davey - Dby < BG3y + blueGem3Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem7 = false;
				}

				//collision detection gem
				if (liveGem8&&Davex + Dbx > BG4x - blueGem4Width / 2 && Davex - Dbx < BG4x + blueGem4Width / 2 && Davey + Dby > BG4y - blueGem4Height / 2 && Davey - Dby < BG4y + blueGem4Height / 2)
				{
					man.increaseScore(man);
					al_play_sample_instance(collectGem);
					//Score += 100;
					liveGem8 = false;
				}

				//collision detection trophy
				if (liveTrophy&&Davex + Dbx > Tx - TBx && Davex - Dbx < Tx + TBx && Davey + Dby > Ty - TBy &&	Davey - Dby < Ty + TBy)
				{ 
					man.increaseScore(man);
					al_play_sample_instance(gothruthedoor);
					//Score += 1000;
					liveTrophy = false;	
				}

				//trophy collision 
				if (!liveTrophy)
				{
					int txtposx = 480;	//text position x
					al_draw_text(font24, al_map_rgb(0, 255, 0), txtposx, HEIGHT - 38, 0, "!!!Go Thru the door!!!");
					al_draw_bitmap(Trophy, txtposx + 250 , HEIGHT - 42, 0);
					al_draw_bitmap(Trophy, txtposx - 50, HEIGHT - 42, 0);
				}


				if (man.displayLives(man) <= 0)
				{
					changeState(state, GAMEOVER, Davex, Davey, Movespeed, Dbx, Dby);
					al_play_sample_instance(gameover);
				}
						
					//man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;
			}

			else if (state == GAMEOVER)
			{

			}
	
			if (state == TITLE)
			{
				if (keys[SPACE])
					state = PLAYING;
			}
			else if (state == PLAYING)
			{
				if (keys[ESCAPE])
					state = GAMEOVER;

			}
			else if (state == GAMEOVER)
			{
				if (keys[SPACE])
					done = true;
			}

	}

		///////Redraw
		if (redraw && al_is_event_queue_empty(event_queue))
		{

			redraw = false;

			if (state == TITLE)
			{
				//al_flip_display();
				//al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(title, 0, 0, 0);
			
			}
		
			else if (state == PLAYING)
			{

			/*	if (state == TITLE)
				{
					al_draw_text(font24, al_map_rgb(0, 255, 0), WIDTH/ 2, HEIGHT /2, ALLEGRO_ALIGN_CENTER, "Press SPACEBAR to play.");
				}
				else if (state == PLAYING)
				{
					al_draw_text(font24, al_map_rgb(0, 255, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press SPACE to end.");

				}
				else if (state == GAMEOVER)
				{

					al_draw_text(font24, al_map_rgb(0, 255, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Press SPACE to exit the game.");
				}*/


				MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT); //mappy

				int posx = 200;
				
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx, 60, 0, "Score: %i", man.displayScore(man));
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx + 300, 60, 0, "Level:%i", lvl.displayLevel(lvl));
				al_draw_textf(font24, al_map_rgb(0, 255, 0), posx + 600, 60, 0, "Daves:%i", man.displayLives(man));
				al_draw_text(font24, al_map_rgb(0, 255, 0), 938, HEIGHT - 38, 0, "Press LCNTRL to shoot.");
				al_draw_text(font24, al_map_rgb(0, 255, 0), 25, HEIGHT - 38, 0, "Use arrow keys to move.");

				if (!jump)
					vely += gravity;

				else
					vely = 0;
				Davex += velx;
				Davey += vely;

				jump = (Davey + DaveHeight / 2 >= HEIGHT - 105);

				if (Davex>0 && Davex<205 && Davey<HEIGHT - 115 && Davey> HEIGHT-200)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 155);

				if (Davex>105 && Davex<305 && Davey<HEIGHT - 215 && Davey>330)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex>205 && Davex < 455 && Davey < HEIGHT - 315 && Davey> HEIGHT-420)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 355);

				if (Davex > 455 && Davex< 660 && Davey < HEIGHT - 210&& Davey>HEIGHT-315)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex > 500 && Davex< 850 && Davey < HEIGHT - 385 && Davey>HEIGHT-470)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 450);

				if (Davex > 900 && Davex< 1200 && Davey < HEIGHT - 310&& Davey>HEIGHT-415)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 410);

				if (Davex > 700 && Davex< 855 && Davey < HEIGHT - 210 && Davey> HEIGHT - 260)
					jump = (Davey + DaveHeight / 2 >= HEIGHT - 255);

				if (Davex > 855 && Davex < 1200 && Davey < HEIGHT - 150 && Davey> HEIGHT - 210)
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
					liveGem1 = false;
				}
				

				//If trophy collision is detected execute this code
				if (collisiont)
				{
					man.increaseScore(man);
					//al_draw_bitmap(redGem, 600, 100, 0);
					liveGem1 = false;
				}
				////////Draw to screen
				
				if (liveGem1)
				{
					al_draw_bitmap(redGem1, RGx, RGy, 0);
				}
				
				if (liveGem2)
				{
					al_draw_bitmap(redGem2, RG2x, RG2y, 0);
				}

				if (liveGem3)
				{
					al_draw_bitmap(redGem3, RG3x, RG3y, 0);
				}
				
				if (liveGem4)
				{
					al_draw_bitmap(redGem4, RG4x, RG4y, 0);
				}
				if (liveGem5)
				{
					al_draw_bitmap(blueGem1, BG1x, BG1y, 0);
				}
				if (liveGem6)
				{
					al_draw_bitmap(blueGem2, BG2x, BG2y, 0);
				}
				if (liveGem7)
				{
					al_draw_bitmap(blueGem3, BG3x, BG3y, 0);
				}
				if (liveGem8)
				{
					al_draw_bitmap(blueGem4, BG4x, BG4y, 0);
				}

				if (!liveTrophy && Davex > 1090 && Davey<HEIGHT - 100 && Davey>HEIGHT - 200)
				{
					//al_play_sample(win, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					al_draw_text(font24, al_map_rgb(255, 168, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Congratulations you passed Level 1");
					al_play_sample_instance(exitdoor);
					al_flip_display();
					al_rest(8);
				//	changeState(state, GAMEOVER, Davex, Davey, Movespeed, Dbx, Dby);
					//done = true;
					//goto END;
				}



				al_draw_bitmap(iDave, Davex, Davey - DaveHeight / 2, 0);

				//////enemy one level 1
				if (xE >= 875 && a > 0)
				{
					a *= -1;
					flipenemy = false;
				
				}
					
				if (xE < 750 && a < 0)
				{
					a *= -1;
					flipenemy = true;
				
				}

				////////////

			
					if (++frameCount >= frameDelay)
					{
						if (++curFrame >= maxFrame)
							curFrame = 0;

						frameCount = 0;
					}
					
					if (flipenemy)
					{
						al_draw_bitmap(enf[curFrame], xE += a * 3, 350, 0);
					}
			
					if (!flipenemy)
					{
						al_draw_bitmap(en[curFrame], xE += a * 3, 350, 0);		//draw enemy to map
					}

				bull.DrawBullet(bullets, num_bullets);
				
				al_draw_bitmap(Door, 1150, HEIGHT - 150, 0);
				
				if (liveTrophy)
				{
					al_draw_bitmap(Trophy, Tx, Ty, 0);
				}
				
				if (man.displayLives(man) <= 0)
				{
					changeState(state, GAMEOVER, Davex, Davey, Movespeed, Dbx, Dby);
					al_play_sample_instance(gameover);
				}
				//man.gameOver(man, isGameOver); //checks if man.lives < = 0, if it is then >> isGameOver = true;

				
			//
				//enem.DrawEnemy(enemy, num_enemies);
				//lvl.displayFont(WIDTH, HEIGHT, countFPS);
				//lvl.walls(WIDTH, HEIGHT);
				//lvl.displayFont(WIDTH, HEIGHT, countFPS);
				//man.displayScoreLives(man);
			}
			
					else if (state == GAMEOVER)
					{
						al_draw_bitmap(lost, 0, 0, 0);
						al_draw_textf(font24, al_map_rgb(0, 255, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Final score: %i", man.displayScore(man));
				
					}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	

	////Destroy objects from memory
	al_destroy_bitmap(title);
	al_destroy_bitmap(lost);
	al_destroy_sample(backgroundMusic);
	al_destroy_sample_instance(walking);
	al_destroy_sample_instance(shooting);
	al_destroy_sample_instance(collectGem);
	al_destroy_sample_instance(jumptime);
	al_destroy_sample_instance(gothruthedoor);
	al_destroy_sample_instance(exitdoor);
	al_destroy_sample_instance(newlife);
	al_destroy_sample_instance(gameover);
	al_destroy_sample_instance(death);
	al_destroy_bitmap(iDave);
	 
	for (int i = 0; i < 2; i++)
	{

		al_destroy_bitmap(en[i]);
		al_destroy_bitmap(enf[i]);
	}
		
	al_destroy_bitmap(blueGem1);
	al_destroy_bitmap(blueGem2);
	al_destroy_bitmap(blueGem3);
	al_destroy_bitmap(blueGem4);
	al_destroy_bitmap(redGem1);
	al_destroy_bitmap(redGem2);
	al_destroy_bitmap(redGem3);
	al_destroy_bitmap(redGem4);
	al_destroy_bitmap(fire);
	al_destroy_bitmap(Door);
	al_destroy_bitmap(Trophy);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	

	return 0;
	}


	void changeState(int &state, int newState, int Davex, int Davey, int Movespeed, int Dbx, int Dby)
	{
		if (state == TITLE)
		{
		}
		else if (state == PLAYING)
		{
		}
		else if (state == GAMEOVER)
		{
		}

		state = newState;

		if (state == TITLE)
		{

		}
		else if (state == PLAYING)
		{
			//Initialise again..... no ideawhy
			man.InitDave(man, Davex, Davey, Movespeed, Dbx, Dby, iDave);
			//bull.InitBullet(bullets, num_bullets);
		//	enem.InitEnemy(enemy, num_enemies, en);
			
		}
		else if (state == GAMEOVER)
		{

		}


	}

