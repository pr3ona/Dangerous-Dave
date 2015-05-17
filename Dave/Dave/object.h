//Object IDs
enum IDS{ PLAYER, BULLET, ENEMY };

//Key ID
enum KEYS{ UP, DOWN, LEFT, RIGHT, LCTRL, ESCAPE, SPACE };
enum STATE{TITLE, PLAYING, GAMEOVER};

//Our Player
class Dave
{

	friend class Bullet; //Bullet class receives the x and y position of the player to make it appear to the user
						//that the bullet is firing from the user
	friend class Level;


private:
	int ID;
	int x;
	int y;
	int lives;
	int boundx;
	int boundy;
	int score;
	int speed;
	int jumpspeed;
	int velx;
	int vely;

	ALLEGRO_BITMAP *iDave = NULL;
	

public:
	//prototypes
	void InitDave(Dave &man, int, int, int, int, int, ALLEGRO_BITMAP *image);
	void DrawDave(Dave &man, int, int,int);
	void MoveLeft(Dave &man);
	void MoveUp(Dave &man, bool&, const int, const int);
	void MoveDown(Dave &man);
	void MoveRight(Dave &man);
	void JumpUp(Dave &man, bool&, const int, const int);
	void gameOver(int, int, Dave &man,int);
	void gameOver(Dave &man, bool&);
	void displayScoreLives(Dave &man);
	void collideWall();
	int DecreaseLife(Dave &man);
	int displayScore(Dave &man);
	int displayLives(Dave &man);
	int increaseScore(Dave &man);
};

class Level
{
private:
	int ID;
	int x;
	int y;
	int boundx;
	int boundy;
	int stageNumber = 0;

public:
	void displayFont(const int&, const int&, int&); //display font at the top and bottom of the screen
	void walls(const int&, const int&); //display the walls of the screen
	int displayLevel(Level &lvl);
	void changeState(int &, int);
	
};

class Bullet
{
	friend class Enemies;

private:
	int ID;
	int x;
	int y;
	bool live;
	int speed;

public:
	void InitBullet(Bullet bullet[], int);
	void DrawBullet(Bullet bullet[], int);
	void FireBullet(Bullet bullet[], int, int, int);
	void UpdateBullet(Bullet bullet[], int, int);
	int collideBullets(Bullet bullet[], int, int, int, int, int, Dave &man, bool);

};


class Enemies
{
	friend class Bullet;

private:
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *iEnemy = NULL;
	ALLEGRO_BITMAP *iEnemy2 = NULL;

public:
	void InitEnemy(Enemies enemy[], int, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2);
	void DrawEnemy(Enemies enemy[], int);
	void StartEnemy(Enemies enemy[], int, int, int);
	void UpdateEnemy(Enemies enemy[], int);
	

};

class Gem
{
private:


public:




};