#pragma once
#include <iostream>
#include <math.h>
#include <string.h>
#include <functional>
#include "Matrix.h"

using namespace std;

ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_EVENT ev;
typedef void (*customFunction)();

#define MAXBUFFERSIZE 4096

//The defined calls for the keys
#pragma region Input

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
#define KS_AL_ADDON_MOUSE_L_DOWN 28
#define KS_AL_ADDON_MOUSE_R_DOWN 29
#define KS_AL_ADDON_MOUSE_M_DOWN 30
#define KS_AL_ADDON_MOUSE_L_PRESSED 31
#define KS_AL_ADDON_MOUSE_R_PRESSED 32
#define KS_AL_ADDON_MOUSE_M_PRESSED 33

#pragma endregion

bool key[34];

#define KS_AL_ADDON_SINGLE_ROW 31
#define KS_AL_ADDON_MULTI_ROW 32

int mouseX, mouseY;

ALLEGRO_MOUSE_STATE state;

//A very curde fix to set keys back to false after getting pressed
void ResetKeys()
{
	for (int i = 0; i < 26; i++)
	{
		key[i] = false;
	}
}

void ScanForMouse()
{
	al_get_mouse_state(&state);
	if (state.buttons & 1) {
		if (!key[KS_AL_ADDON_MOUSE_L_DOWN])
		{
			key[KS_AL_ADDON_MOUSE_L_PRESSED] = true;
			key[KS_AL_ADDON_MOUSE_L_DOWN] = true;
		}
		else
		{
			key[KS_AL_ADDON_MOUSE_L_PRESSED] = false;
		}
	}
	else
	{
		key[KS_AL_ADDON_MOUSE_L_DOWN] = false;
		key[KS_AL_ADDON_MOUSE_L_PRESSED] = false;
	}

	if (state.buttons & 2) {
		if (!key[KS_AL_ADDON_MOUSE_R_DOWN])
		{
			key[KS_AL_ADDON_MOUSE_R_PRESSED] = true;
			key[KS_AL_ADDON_MOUSE_R_DOWN] = true;
		}
		else
		{
			key[KS_AL_ADDON_MOUSE_R_PRESSED] = false;
		}
	}
	else
	{
		key[KS_AL_ADDON_MOUSE_R_DOWN] = false;
		key[KS_AL_ADDON_MOUSE_R_PRESSED] = false;
	}

	if (state.buttons & 4) {
		if (!key[KS_AL_ADDON_MOUSE_M_DOWN])
		{
			key[KS_AL_ADDON_MOUSE_M_PRESSED] = true;
			key[KS_AL_ADDON_MOUSE_M_DOWN] = true;
		}
		else
		{
			key[KS_AL_ADDON_MOUSE_M_PRESSED] = false;
		}
	}
	else
	{
		key[KS_AL_ADDON_MOUSE_M_DOWN] = false;
		key[KS_AL_ADDON_MOUSE_M_PRESSED] = false;
	}

	mouseX = state.x;
	mouseY = state.y;
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

class Text
{
	ALLEGRO_FONT* font;

public:
	int dx, dy, fontsize;
	const char* fontFilepath;
	string content;	
	int color[3] = { 0 };

	void LoadFont()
	{
		if (fontFilepath == NULL)
		{
			font = al_load_font("defaultFont.ttf", fontsize, NULL);
		}
		else
		{
			font = al_load_font(fontFilepath, fontsize, NULL);
		}
	}

	void Show()
	{
		const char* output = this->content.c_str();

		al_draw_text(font, al_map_rgb(color[0], color[1], color[2]), dx, dy, NULL, output);
	}
};

class Button
{
public:
	int dx, dy, wx, wy;
	ALLEGRO_BITMAP* bg_img;

	void Preload()
	{
		if (bg_img == NULL)
		{
			bg_img = al_load_bitmap("defaultButton.jpg");
		}
	}

	bool ButtonPressed()
	{
		if (key[KS_AL_ADDON_MOUSE_L_PRESSED] && (mouseX >= dx && mouseX <= dx + wx) && (mouseY >= dy && mouseY <= dy + wy))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Show()
	{
		al_draw_scaled_bitmap(this->bg_img, 1, 1, al_get_bitmap_width(bg_img), al_get_bitmap_height(bg_img), dx, dy, wx, wy, NULL);
	}
};

class Checkbox
{
public:
	int dx, dy, wx, wy, flag;
	bool active = false;
	Button button;
	ALLEGRO_BITMAP* checkmark;

	void Preload(int dx, int dy, int wx, int wy, int flag, ALLEGRO_BITMAP* bg_img, ALLEGRO_BITMAP* checkmark)
	{
		this->dx = dx;
		this->dy = dy;
		this->wx = wx;
		this->wy = wy;
		this->flag = flag;
		
		this->button.dx = dx;
		this->button.dy = dy;
		this->button.wx = wx;
		this->button.wy = wy;

		if (checkmark == NULL)
		{
			this->checkmark = al_load_bitmap("defaultCheckmark.png");
		}
		else
		{
			this->checkmark = checkmark;
		}

		if (bg_img == NULL)
		{
			this->button.bg_img = al_load_bitmap("defaultCheckbox.png");
		}
		else
		{
			this->button.bg_img = bg_img;
		}

		button.Preload();
	}

	void Run()
	{
		button.Show();

		if (button.ButtonPressed())
		{
			active = !active;
		}
		if (active)
		{
			al_draw_scaled_bitmap(checkmark, 0, 0, al_get_bitmap_width(this->checkmark), al_get_bitmap_height(this->checkmark), this->dx, this->dy, this->wx, this->wy, this->flag);
		}
	}

};

class Slider
{
public:
	Button handle;
	bool used = false;
	float value;
	int dx, dy, wx, wy;

	void Preload(int dx, int dy, int wx, int wy, float startingValue, ALLEGRO_BITMAP* handle)
	{
		this->dx = dx;
		this->dy = dy;
		this->wx = wx;
		this->wy = wy;
		this->value = startingValue;

		this->handle.dx = dx;
		this->handle.dy = dy;
		this->handle.wx = wy;
		this->handle.wy = wy;
		this->handle.bg_img = handle;

		if (handle == NULL)
		{
			this->handle.bg_img = al_load_bitmap("defaultHandle.png");
		}
		else
		{
			this->handle.bg_img = handle;
		}

	}

	void Run()
	{

		if (handle.ButtonPressed())
		{
			used = true;
		}

		if (used && key[KS_AL_ADDON_MOUSE_L_DOWN])
		{

			//this->handle.dx = mouseX;
			if (mouseX < this->dx + 15 + this->wx && mouseX > this->dx + 1)
			{
				this->handle.dx = mouseX - 0.5 * this->wy;
			}

		}
		else
		{
			used = false;
		}

		al_draw_filled_rectangle(this->dx, this->dy + .30 * this->wy, this->dx + this->wx,this->dy + this->wy - .30 * this->wy, al_map_rgb(230, 230 ,230));
		al_draw_filled_rectangle(this->dx, this->dy + .30 * this->wy, this->dx + this->handle.dx - this->dx, this->dy + this->wy - .30 * this->wy, al_map_rgb(255, 255, 255));
		value = ((float)this->handle.dx - (float)this->dx) / ((float)this->dx - ((float)this->dx + (float)this->wx)) * -1;
		cout << value << "\n";
		handle.Show();
	}

};

//Class to handle all Spritesheet animation related buisness
class Animation
{
	int currentX, currentY;

public:
	/*Linker link;*/
	Point position;
	int rows, collums;
	int dx, dy;
	ALLEGRO_BITMAP* animation;

	//Calculating pixel coordinates to show and drawing them
	void Show(int flag)
	{
		//Calculation of the middle of the sprite
		position.dx = dx + (al_get_bitmap_width(animation) / collums) / 2;
		position.dy = dy + (al_get_bitmap_height(animation) / rows) / 2;

		//Calculating and drawing the next part of the animation
		al_draw_bitmap_region(animation, (al_get_bitmap_width(animation) / collums) * currentX, (al_get_bitmap_height(animation) / rows) * currentY, al_get_bitmap_width(animation) / collums, al_get_bitmap_height(animation) / rows, dx, dy, flag);

		//Setting the index for the next sprite used
		if (currentX == collums - 1)
		{
			currentX = 0;
			currentY++;
		}
		else
		{
			currentX++;
		}
		
		if (currentY == rows)
		{
			currentY = 0;
		}

	}
};

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
