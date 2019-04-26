#pragma once
#ifndef UI_H_
#define UI_H_

#include<vector>
#include<memory>
#include<string>
#include<SDL.h>
#include<utility>
enum MODE
{
	LOADING,
	MAIN_MENU,
	OPTION,
	BATTLE,
	PAUSE
};

void mainUIControl();

void loading();

void main_menu();

void battle();

#endif // !UI_H_
