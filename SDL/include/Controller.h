#ifndef CONTROLLER_H_
#define CONTROLLER_H_

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

	Ship(Point _cur,
			 int _width, int _height,
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
};

class Mouse
{
	public:

		Mouse();

		void update();

		Point getLocation();

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
