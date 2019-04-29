#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include"Texture.h"
#include<SDL.h>
#include<math.h>
#include<vector>

struct Point
{
	double x, y;

	Point();

	Point(double _x, double _y);

};

bool operator == (const Point&x, const Point &y);

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

	std::shared_ptr<Texture> hull, turret;
	std::shared_ptr < Texture> covered;
	double angleTur[3];
	int disTur[3];
	void link(std::shared_ptr<Texture> _hull, std::shared_ptr<Texture>_turret,std::shared_ptr<Texture> _2nd);
	void render();
	void update();
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
