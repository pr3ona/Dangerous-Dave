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

public:
	//prototypes
	void InitDave(Dave &man);
	void DrawDave(Dave &man);
	void MoveLeft(Dave &man);
	void MoveUp(Dave &man);
	void MoveDown(Dave &man);
	void MoveRight(Dave &man);
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
	void live();
	int speed;

public:

	void InitBullet(Bullet bullet[], int);
	void DrawBullet(Bullet bullet[], int);
	void FireBullet(Bullet bullet[], int, Dave &man);
	void UpdateBullet(Bullet bullet[], int, int);

};