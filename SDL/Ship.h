#pragma once
#ifndef SHIP_H_
#define SHIP_H_

#include<vector>
#include<string>

struct Vector2
{
	int x, y;
};

class shell
{
	int x, y, z;
	Vector2 dir;
	double pen;
	int damage;
	int fireChance;

	bool impact(section t);
};

struct plate
{
	int x
};


struct ship
{
	std::string name;
	std::vector<section> list;
	int TotalHP;
	int heal;
	int fireCount;
};

#endif // !SHIP_H_
