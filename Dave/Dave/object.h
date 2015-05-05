//Object IDs
enum IDS{ PLAYER, BULLET, ENEMY };

//Key ID
enum KEYS{ UP, DOWN, LEFT, RIGHT, LCTRL };

//Our Player
class Dave
{

	friend class Bullet; //Bullet class receives the x and y position of the player to make it appear to the user
						//that the bullet is firing from the user

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
	

public:
	//prototypes
	void InitDave(Dave &man, int, int, int);
	void DrawDave(Dave &man, int, int);
	void MoveLeft(Dave &man);
	void MoveUp(Dave &man, bool&, const int, const int);
	void MoveDown(Dave &man);
	void MoveRight(Dave &man);
	void JumpUp(Dave &man, bool&, const int, const int);
};

class Level
{

public:
	void displayFont(const int&, const int&, int&); //display font at the top and bottom of the screen
	void walls(const int&, const int&); //display the walls of the screen
	
};

class Bullet
{

private:
	int ID;
	int x;
	int y;
	bool live;
	int speed;

public:
	void InitBullet(Bullet bullet[], int);
	void DrawBullet(Bullet bullet[], int);
	void FireBullet(Bullet bullet[], int, Dave &man);
	void UpdateBullet(Bullet bullet[], int, int);

};

