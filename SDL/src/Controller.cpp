#include"../include/Controller.h"
#include"../include/Variable.h"

#include<iostream>

Point::Point()
{
	x = -1;
	y = -1;
}

Point::Point(double _x, double _y)
{
	x = _x;
	y = _y;
}

bool operator == (const Point&x, const Point &y)
{
	if (x.x == y.x&&x.y == y.y) return true;
	else return false;
}

Ship::Ship()
{
	cur = Point();
	des = Point();
	width = 0;
	height = 0;
	scale = 0;
	angle = 0;
	branch = -1;
	chosen = false;

	start = 0;
	current = 0;
	velocity = 0;
	rotation = 0;

	movex = 0;
	movey = 0;

	maxForwardSpeed = 20;
	maxBackwardSpeed = -5;
	acceleration = 1;
}

Ship::Ship(Point _cur, int _width, int _height, double _scale, double _angle, int _branch)
{
	cur = _cur;
	des = Point();
	width = _width;
	height = _height;
	scale = _scale;
	angle = _angle;
	branch = _branch;
	chosen = false;

	start = 0;
	current = 0;
	velocity = 0;
	rotation = 10;

	movex = 0;
	movey = 0;
	maxForwardSpeed = 50;
	maxBackwardSpeed = -5;
	acceleration = 5;
}

void Ship::setDestination(Point _des)
{
	des = _des;
}

void Ship::move()
{
	current = SDL_GetTicks();
	double time = (double)(current - start) / 1000;
	double distance = acceleration * acceleration*time / 2 + velocity * time;

	if (movey!=0)
	{
		maxForwardSpeed = 45;
		maxBackwardSpeed = -4;
	}
	else
	{
		maxForwardSpeed = 50;
		maxBackwardSpeed = -5;
	}

	switch (movex)
	{
		case -1:
		{
			if (velocity == maxBackwardSpeed) distance = velocity * time;
			velocity -= acceleration * time;
			if (velocity > maxBackwardSpeed) velocity = maxBackwardSpeed;
			break;
		}
		case 0:
		{
			if (velocity == 0)
			{
				distance = 0;
			}
			if (velocity < 0)
			{
				velocity += acceleration * time;
				if (velocity > 0) { velocity = 0; }
			}
			if (velocity > 0)
			{
				velocity -= acceleration * time;
				if (velocity < 0) 
				{ 
					velocity = 0; 
				}
			}
			break;
		}
		case 1:
		{
			if (velocity == maxForwardSpeed) distance = velocity * time;
			velocity += acceleration * time;
			if (velocity > maxForwardSpeed) velocity = maxForwardSpeed;
			break;
		}
	}
	
	/*
	switch (movex)
	{
		case -1:
		{
			cur.x -= velocity * time * cos(angle * M_PI / 180);
			cur.y -= velocity * time * sin(angle * M_PI / 180);
			break;
		}
		
		case 1:
		{
			cur.x += velocity * time * cos(angle * M_PI / 180);
			cur.y += velocity * time * sin(angle * M_PI / 180);
			break;
		}
	}
	*/

	cur.x += distance * cos(angle*M_PI / 180);
	cur.y += distance * sin(angle*M_PI / 180);
	if(distance) angle += movey * rotation * time;

//	std::cout << cur.x << " " << cur.y << std::endl;

	if (cur.x < 0) cur.x = 0;
	if (cur.x > sWidth) cur.x = sWidth;
	if (cur.y < 0) cur.y = 0;
	if (cur.y > sHeight) cur.y = sHeight;
	while (angle > 360) angle -= 360;
	while (angle < 0) angle += 360;
	start = current;
	return;
}

Mouse::Mouse()
{
	x1 = -1;
	y1 = -1;
	x2 = -1;
	y2 = -1;
	mode = POINT;
}

void Mouse::update()
{
	Uint32 mouseState = SDL_GetMouseState(&xt, &yt);
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) && 
		(x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0)  )
	{
		if (mode == POINT)
		{
			if (x1 != xt || y1 != yt)
			{
				x2 = xt;
				y2 = yt;
				mode = GROUP;
			}
			else
			{
				mode = POINT;
				x1 = xt;
				y1 = yt;
				x2 = xt;
				y2 = yt;
			}
		}
		else
		{
			x2 = xt;
			y2 = yt;
		}
	}
	else
	{
		mode = POINT;
		x1 = xt;
		y1 = yt;
		x2 = xt;
		y2 = yt;
	}

	if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{

	}
	return;
}

Point Mouse::getLocation()
{
	return Point(xt, yt);
}

void Mouse::render()
{
	if (mode == GROUP)
	{
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		drawRect(x1, y1, x2, y2);
	}
	return;
}