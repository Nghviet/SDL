#include"../include/Controller.h"
#include"../include/Variable.h"
#include"../include/Texture.h"
#include<iostream>
#include<fstream>
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

Ship::Ship( int _width, int _height, double _scale, double _angle, int _branch)
{
	width = _width;
	height = _height;
	scale = _scale;
	angle = _angle;
	branch = _branch;
	chosen = false;

	start = 0;
	current = 0;
	velocity = 0;
	rotation = 5;

	movex = 0;
	movey = 0;
	maxForwardSpeed = 50;
	maxBackwardSpeed = -5;
	acceleration = 5;
}

void Ship::init(int _x, int _y)
{
	cur.x = _x;
	cur.y = _y;
	movex = 0;
	movey = 0;
	velocity = 0;
	angle = 0;
	maxForwardSpeed = 50;
	maxBackwardSpeed = -5;
	acceleration = 5;
	rotation = 10;
	for (auto &i : turret)
	{
		i.start = SDL_GetTicks();
		i.fireT = 0;
		i.fired = 0;
		i.move = 1;
		i.xD = -1;
		i.yD = -1;
		i.rotate = 0;
	}
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
	if (distance) angle += movey * rotation * time * (float)velocity / maxForwardSpeed;

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

void Ship::resize(double newScale)
{
	scale = newScale;
}

void Ship::load(std::string text)
{
	std::ifstream in;
	in.open("txt/" + text);
	if (!in.good()) return;
	std::string path1, path2, path3;
	in >> path1  >> path3;
	{
		std::shared_ptr<Texture> tmp(new Texture);
		tmp->load(path1);
		hull = tmp; 
	}
	if (path3.size() > 1)
	{
		std::shared_ptr<Texture> tmp(new Texture);
		tmp->load(path3);
		cover = tmp;
	}
	scale = 1;
	width = hull->rWidth();
	height = hull->rHeight();
	angle = 0;
	branch = 0;
	
	cur.x = sWidth / 2;
	cur.y = sHeight / 2;

	int n;//number of turret

	std::vector< std::pair<int, double> > battery;

	in >> n;
	while (n--)
	{
		int dis;
		double angle;
		in >> dis >> angle;
		battery.push_back(std::pair<int, double>(dis, angle));
	}

	in >> n;
	while (n--)
	{
		int dis, angle, layer, cX, cY;
		std::string path;
		in >> dis >> angle >> layer >> path >> cX >> cY;
		std::cout << dis << " " << angle << " " << layer << " " << path << " " << cX << " " << cY << std::endl;
		turret.push_back(Turret(dis, angle, cX, cY, path,NULL,NULL,battery));
	}

	return;
}

void Ship::link()
{
	for (auto &i : turret)
	{
		i.sAngle = &angle;
		i.sScale = &scale;
	}
}

void Ship::update()
{
	if(1)
	for (auto &i : turret)
	{
		i.x = cur.x + i.dis*cos(angle *change)*scale;
		i.y = cur.y + i.dis*sin(angle *change)*scale;
		i.aim();
		if (left || i.fired) 
		{
//			std::cout << "Fired" << std::endl;

			i.fire();
		}
//		std::cout << i.fireT << std::endl;
	}

	if (0)
	{
		turret[1].x = cur.x + turret[1].dis*cos(angle *change)*scale;
		turret[1].y = cur.y + turret[1].dis*sin(angle *change)*scale;
		if (!turret[1].fired) turret[1].aim();
		if (left || turret[1].fired)
		{
			turret[1].fire();
		}
	}

}

void Ship::render()
{
	hull->render(cur.x, cur.y, NULL, scale, angle, NULL, SDL_FLIP_NONE);
	for (auto i : turret) i.render();
//	turret[1].render();
	if(cover!=NULL) cover->render(cur.x, cur.y, NULL, scale, angle, NULL, SDL_FLIP_NONE);
}

Turret::Turret()
{
	x = 0;
	y = 0;
	dis = 0;
	angle = 0;
	rotate = 0;
	limit = 150;
	cX = 0;
	cY = 0;
	speed = 30;
	mTexture = NULL;
	center = NULL;
	sScale = NULL;
	sAngle = NULL;
}

void Turret::aim()
{
	if (!fired)
	{
		double a = std::atan2(-(y - mousePos.y), -(x - mousePos.x));
		int cur = SDL_GetTicks();
		double time = (double)(cur - start) / 1000;
		a = a / change;
		a -= *sAngle + angle;
		while (a > 360) a -= 360;
		while (a < 0) a += 360;
		if (a > 180) a = a - 360;

		if (rotate > a) rotate -= time * speed;
		else rotate += time * speed;

		if (rotate > limit) rotate = limit;
		if (rotate < -limit) rotate = -limit;

		start = cur;
	}
	else
	{
		double a = std::atan2(-(y - yD), -(x - xD));
		int cur = SDL_GetTicks();
		double time = (double)(cur - start) / 1000;
		a = a / change;
		a -= *sAngle + angle;
		while (a > 360) a -= 360;
		while (a < 0) a += 360;
		if (a > 180) a = a - 360;

		if (rotate > a) rotate -= time * speed;
		else rotate += time * speed;

		if (rotate > limit) rotate = limit;
		if (rotate < -limit) rotate = -limit;

		start = cur;
	}
}

Turret::Turret(int _dis, double _angle,int _cX, int _cY,std::string path,double *_sAngle, double *_sScale, std::vector< std::pair<int, double> > _battery)
{
	dis = _dis;
	angle = _angle;
	rotate = 0;
	speed = 10;
	limit = 150;
	cX = _cX;
	cY = _cY;
	center = new SDL_Point{ cX,cY };
	std::shared_ptr<Texture> tmp(new Texture);
	tmp->load(path);
	layer = 1;
	mTexture = tmp;
	start = SDL_GetTicks();
	fireT = 0;
	fired = false;
	sAngle = _sAngle;
	sScale = _sScale;
	battery = _battery;
//	std::cout << *sAngle <<" "<<*sScale<<" "<<angle<< std::endl;
}

void Turret::render()
{
	int tX, tY;
	tX = cX * *sScale;
	tY = cY * *sScale;
	center->x = tX;
	center->y = tY;
	mTexture->render(x, y, NULL, *sScale, angle + *sAngle + rotate, center, SDL_FLIP_NONE);
	if (!fired)
	{
		double t = (angle + rotate + *sAngle)*change;
		double d = 1e9 + 7;
		if (cos(t) < 0)
		{
			if (-x < d*cos(t)) d = (double)-x / cos(t);
		}
		if (cos(t) > 0)
		{
			if ((sWidth - x) < d*cos(t)) d = (double)(sWidth - x) / cos(t);
		}
		if (sin(t) < 0)
		{
			if (-y < d*sin(t)) d = (double)-y / sin(t);
		}
		if (cos(t) > 0)
		{
			if ((sHeight - y) < d*sin(t)) d = (double)(sWidth - y) / sin(t);
		}

		double xT = x + d * cos(t);
		double yT = y + d * sin(t);

		t = (angle + rotate + *sAngle + 90)*change;

		for (int i = -0; i < 1; i++)
		{
			int xS = x + i * cos(t);
			int yS = y + i * sin(t);
			int xE = xT + i * cos(t);
			int yE = yT + i * sin(t);
			//	std::cout << xS << " " << yS << " " << xE << " " << yE << std::endl;
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
			SDL_RenderDrawLine(gRenderer, xS, yS, xE, yE);
		}
	}
	
}

void Turret::fire()
{
	double a = std::atan2(-(y - mousePos.y), -(x - mousePos.x));
	
	if (fireT > Flimit)
	{
		fireT = 0;
		start = SDL_GetTicks();
		fired = false;
		return;
	}

	if (!fired)
	{
		a = a / change;
		std::cout << a << " " << angle + rotate + *sAngle << std::endl;
		if (abs(a - (angle + rotate + *sAngle)) < 2 || abs(a + 360 - (angle + rotate + *sAngle)) < 2)
		{
			fired = true;
			firing = SDL_GetTicks();
			fireT = 0;
			a = angle + rotate + *sAngle; 
			double temp = a;
			
				double t = temp * change;
				double d = 1e9+7;
				if (cos(t) < 0)
				{
					if (-x < d*cos(t)) d = (double)-x / cos(t);
				}
				if (cos(t) > 0)
				{
					if ((sWidth - x) < d*cos(t)) d = (double)(sWidth - x) / cos(t);
				}
				if (sin(t) < 0)
				{
					if (-y < d*sin(t)) d = (double)-y / sin(t);
				}
				if (cos(t) > 0)
				{
					if ((sHeight - y) < d*sin(t)) d = (double)(sWidth - y) / sin(t);
				}
				


				xD = x + d * cos(t);
				yD = y + d * sin(t);
				std::cout << sin(t) << " " << cos(t) << " " << xD << " " << yD << std::endl;
			a = (a + 90)*change;
			for (auto j : battery)
			{
				int xB = x + j.first*cos((j.second + temp) * change) * *sScale;
				int yB = y + j.first*sin((j.second + temp) * change) * *sScale;

				double t = a * change;
				double dis = 0;


				std::cout << xB << " " << yB << std::endl;
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
				SDL_RenderDrawPoint(gRenderer, xB, yB);

				

				for (int i = -1; i < 1; i++)
				{
					int xS = xB + i * cos(a);
					int yS = yB + i * sin(a);
					int xE = xD + i * cos(a);
					int yE = yD + i * sin(a);
				//	std::cout << xS << " " << yS << " " << xE << " " << yE << std::endl;
					SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 0);
					SDL_RenderDrawLine(gRenderer, xS, yS, xE, yE);
				}
			}
		}
//		std::cout << "Fired " << firing << " " << fired << std::endl;
	}
	else
	{
		a = angle + rotate + *sAngle;
		int temp = a;
		a = (a + 90)*change;
		for (auto j : battery)
		{
			int xB = x + j.first*cos((j.second + temp) * change) * *sScale;
			int yB = y + j.first*sin((j.second + temp) * change) * *sScale;

			for (int i = -1; i < 1; i++)
			{
				
				int xS = xB + i * cos(a);
				int yS = yB + i * sin(a);
				int xE = xD + i * cos(a);
				int yE = yD + i * sin(a);
			//	std::cout << xS << " " << yS << " " << xE << " " << yE << std::endl;
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 0);
				SDL_RenderDrawLine(gRenderer, xS, yS, xE, yE);
			}
		}
		int cur = SDL_GetTicks();
		fireT += cur - firing;
		firing = cur;
	}
}

void Turret::testing()
{
	battery[0].first = 100;
	battery[0].second = -10;

	battery[1].first = 100;
	battery[1].second = 0;

	battery[2].first = 100;
	battery[2].second = 10;
}

Mouse::Mouse()
{
	x1 = 1;
	y1 = 1;
	x2 = 1;
	y2 = 1;
	mode = POINT;
}

void Mouse::update()
{
	Uint32 mouseState = SDL_GetMouseState(&xt, &yt);

	if(0)
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) leftclick = true;
	else leftclick = false;

	if(0)
	if (mouseState&SDL_BUTTON(SDL_BUTTON_RIGHT)) rightclick = true;
	else rightclick = false;

	mousePos = Point(xt, yt);
	return;
}

Point Mouse::getLocation()
{
	return Point(xt, yt);
}

void Mouse::left()
{
	leftclick = true;
}

void Mouse::right()
{
	rightclick = true;
}

bool Mouse::leftClick()
{
	return leftclick;
}

bool Mouse::rightClick()
{
	return rightclick;
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