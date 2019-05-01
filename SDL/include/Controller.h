#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include"Texture.h"
#include<SDL.h>
#include<math.h>
#include<vector>

const double change = M_PI / 180;

struct Point
{
	double x, y;

	Point();

	Point(double _x, double _y);

};

bool operator == (const Point&x, const Point &y);

struct Turret
{
	int x, y;
	int dis;
	int layer;
	double angle;
	double rotate;
	double speed;
	double limit;
	int cX, cY;
	SDL_Point* center;
	std::shared_ptr<Texture> mTexture;

	unsigned int start;

	Turret();

	Turret(int _dis, double _angle, int _cX, int _cY, std::string path);
	void render(double sAngle,double scale);
	void aim(double sAngle);
};

struct Ship
{
	Point cur;
	Point des;
	int width, height;
	double scale;
	double angle;
	int branch;
	bool chosen;

	unsigned int start, current;
	double velocity,rotation;

	Ship();

	Ship( int _width, int _height,
			 double _scale, double _angle, int _branch);
	
	void init(int _x, int _y);

	void setDestination(Point _des);

	//Debug only
	//Erase before release

	int movex;
	int movey;
	void move();

	double maxForwardSpeed;
	double maxBackwardSpeed;
	double acceleration;

	double angleTur[10];
	int disTur[10];
	int cX, cY;

	std::vector<Turret> turret;
	std::shared_ptr<Texture> hull,cover;
	void init2();
	void update();
	void render();
	void resize(double newScale);
	
	void load(std::string text);

};


class Mouse
{
	public:

		Mouse();

		void update();

		Point getLocation();

		void left();

		void right();

		bool leftClick();

		bool rightClick();

		void render();

	private:
		const int POINT = 1;
		const int GROUP = 2;

		bool leftclick, rightclick;
		int x1, y1 ;  
		int x2, y2 ;  
		int xt, yt;  
		int mode;
};

class Terrain
{
public:

private:
	std::vector<Point> border;
};

class Map
{
public:

	Map();

	void load();

private:
//	std::vector<Point> start;
//	std::string name;
//	Texture* link;
};

#endif // !CONTROLLER_H_
