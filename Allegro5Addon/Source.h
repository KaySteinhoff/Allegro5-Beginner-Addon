#pragma once
#include "Addon.h"
using namespace std;

//<summary>
//This class is used to programm the behavior of the Window.
//It is simplified so that a Person with little knowledge can
//addapt easily to this Addon.
//Obviously this is very much inspired by the workflow in Unity
//</summary>
class Source
{
	//Declaration of the variables (can be added in the Function too like in Unity)
	/*bool movingRight = true;
	int pX, pY;
	Animation idle;
	Animation walk;*/
	Character player;

public:
	//Called at the start of the Application
	void Start()
	{
		player.walking.animation = al_load_bitmap("Dinowalk.png");
		player.idle.animation = al_load_bitmap("Idle.png");
		player.pX = 0;
		player.pY = 0;
		////Loading the Spritesheet for the animation(EventSystem is non-existent yet)
		//idle.animation = al_load_bitmap("Idle.png");
		////Giving the number of Sprites contained
		//idle.numberOfSprites = 4;
		////Setting Screenposition
		//idle.dx = pX;
		//idle.dy = pY;

		//walk.animation = al_load_bitmap("Dinowalk.png");
		//walk.numberOfSprites = 6;
		//walk.dx = pX;
		//walk.dy = pY;
		ks_al_addon_install_cam2D();
	}

	//Called everyframe
	void Update()
	{
		/*if (key[KS_AL_ADDON_KEY_DOWN])
		{
			if (key[KS_AL_ADDON_KEY_W])
			{
				pY -= 4;
				walk.dy = pY;
				idle.dy = pY;
				walk.Show(NULL);
			}
			
			if (key[KS_AL_ADDON_KEY_A])
			{
				pX -= 4;
				walk.dx = pX;
				idle.dx = pX;
				walk.Show(ALLEGRO_FLIP_HORIZONTAL);
			}
			
			if (key[KS_AL_ADDON_KEY_S])
			{
				pY += 4;
				walk.dy = pY;
				idle.dy = pY;
				walk.Show(NULL);
			}
			
			if (key[KS_AL_ADDON_KEY_D])
			{
				pX += 4;
				walk.dx = pX;
				idle.dx = pX;
				walk.Show(NULL);
			}
		}
		else
		{
			idle.Show(NULL);
		}*/
		player.Move();

	}
};