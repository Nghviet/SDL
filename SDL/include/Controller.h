#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include<SDL.h>
#include<math.h>

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

		void render();

	private:
		const int POINT = 1;
		const int GROUP = 2;
		int x1, y1 ;  
		int x2, y2 ;  
		int xt, yt;  
		int mode;
};

class Keybroad
{

};

#endif // !CONTROLLER_H_
