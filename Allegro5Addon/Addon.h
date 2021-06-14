#pragma once
#include <iostream>
#include <math.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/keyboard.h"
#include "allegro5/keycodes.h"

//The defined calls for the keys
#pragma region Alphabet

#define KS_AL_ADDON_KEY_A 0
#define KS_AL_ADDON_KEY_B 1
#define KS_AL_ADDON_KEY_C 2
#define KS_AL_ADDON_KEY_D 3
#define KS_AL_ADDON_KEY_E 4
#define KS_AL_ADDON_KEY_F 5
#define KS_AL_ADDON_KEY_G 6
#define KS_AL_ADDON_KEY_H 7
#define KS_AL_ADDON_KEY_I 8
#define KS_AL_ADDON_KEY_J 9
#define KS_AL_ADDON_KEY_K 10
#define KS_AL_ADDON_KEY_L 11
#define KS_AL_ADDON_KEY_M 12
#define KS_AL_ADDON_KEY_N 13
#define KS_AL_ADDON_KEY_O 14
#define KS_AL_ADDON_KEY_P 15
#define KS_AL_ADDON_KEY_Q 16
#define KS_AL_ADDON_KEY_R 17
#define KS_AL_ADDON_KEY_S 18
#define KS_AL_ADDON_KEY_T 19
#define KS_AL_ADDON_KEY_U 20
#define KS_AL_ADDON_KEY_V 21
#define KS_AL_ADDON_KEY_W 22
#define KS_AL_ADDON_KEY_X 23
#define KS_AL_ADDON_KEY_Y 24
#define KS_AL_ADDON_KEY_Z 25
#define KS_AL_ADDON_KEY_DOWN 26
#define KS_AL_ADDON_KEY_UP 27

#pragma endregion
bool key[28] = { false };

//A very curde hack to set keys back to false after getting pressed
void ResetKeys()
{
	for (int i = 0; i < 26; i++)
	{
		key[i] = false;
	}
}

//Used to easier calculate Distance between to Points
class Point
{
public:
	float dx, dy;
};

//Distance function
float Distance(float x1, float y1, float x2, float y2)
{
	return sqrt((pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

//Class to handle all Spritesheet animation related buisness
class Animation
{
	int currentTile;

public:
	Point position;
	int numberOfSprites;
	int dx, dy;
	ALLEGRO_BITMAP* animation;

	//Calculating pixel coordinates to show and drawing them
	void Show(int flag)
	{
		//Calculation of the middle of the sprite
		position.dx = dx + (al_get_bitmap_width(animation) / numberOfSprites) / 2;
		position.dy = dy + (al_get_bitmap_height(animation) / numberOfSprites) / 2;

		//Calculating and drawing the next part of the animation
		al_draw_bitmap_region(animation, (al_get_bitmap_width(animation) / numberOfSprites) * currentTile, 0, al_get_bitmap_width(animation) / numberOfSprites, al_get_bitmap_height(animation), dx, dy, flag);

		//Setting the index for the next sprite used
		if (currentTile == numberOfSprites - 1)
		{
			currentTile = 0;
		}
		else
		{
			currentTile++;
		}
	}
};

//First step in the direction of an Animator
class Event
{
public:
	bool condition;
	Animation animation1;
	Animation animation2;

	void Run()
	{
		if (!condition)
		{
			this->animation1.Show(NULL);
		}
		else
		{
			this->animation2.Show(NULL);
		}
	}
};
