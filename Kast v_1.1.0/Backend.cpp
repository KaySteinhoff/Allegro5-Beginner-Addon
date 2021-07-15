// Allegro.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
#include "Source.h"

//Necessary Variables
ALLEGRO_TIMER* timer;

bool redraw = true;
bool running = true;

int defaultWindowColor[3] = { 200, 200, 200 };

//Source class
Source source;

void ScanForMouse();

int main()
{

	//Initializing Allegro5 and installing mouse and keyboard
	if (!al_init())
	{
		cout << "ERROR 0001: Could not initialize Allegro5!\nPlease check for all necessary .dll files";
	}

	if (!al_install_mouse())
	{
		cout << "ERROR 0002: Could not install mouse!\nPlease check for all necessary .dll files";
	}
	
	if (!al_install_keyboard())
	{
		cout << "ERROR 0003: Could not install keyboard!\nPlease check for all necessary .dll files";
	}

	//Seting up the window
	display = al_create_display(1920, 1080);
	if (!display)
	{
		cout << "ERROR SET_1: Could not initialize display at Backend.cpp(32).\n Please check for all necessary .dll files.\n";
		return 1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		cout << "ERROR SET_2: Could not initialize event_queue at Backend.cpp(39).\n Please check for all necessary .dll files.\n";
		return 1;
	}

	timer = al_create_timer(0.03);

	//Registering all event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_set_window_title(display, "Example");

	//Running the Start() function
	source.Start();

	al_start_timer(timer);
	//Main Loop
	while (running)
	{
		al_wait_for_event(event_queue, &ev);

		switch (ev.type)
		{
			case ALLEGRO_EVENT_TIMER:
				redraw = true;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				running = false;
				break;

			//Very basic Input system
			case ALLEGRO_EVENT_KEY_DOWN:
				key[KS_AL_ADDON_KEY_UP] = false;
				key[KS_AL_ADDON_KEY_DOWN] = true;
				switch (ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_A:
						key[KS_AL_ADDON_KEY_A] = true;
						break;

					case ALLEGRO_KEY_B:
						key[KS_AL_ADDON_KEY_B] = true;
						break;

					case ALLEGRO_KEY_C:
						key[KS_AL_ADDON_KEY_C] = true;
						break;

					case ALLEGRO_KEY_D:
						key[KS_AL_ADDON_KEY_D] = true;
						break;

					case ALLEGRO_KEY_E:
						key[KS_AL_ADDON_KEY_E] = true;
						break;

					case ALLEGRO_KEY_F:
						key[KS_AL_ADDON_KEY_F] = true;
						break;

					case ALLEGRO_KEY_G:
						key[KS_AL_ADDON_KEY_G] = true;
						break;

					case ALLEGRO_KEY_H:
						key[KS_AL_ADDON_KEY_H] = true;
						break;

					case ALLEGRO_KEY_I:
						key[KS_AL_ADDON_KEY_I] = true;
						break;

					case ALLEGRO_KEY_J:
						key[KS_AL_ADDON_KEY_J] = true;
						break;

					case ALLEGRO_KEY_K:
						key[KS_AL_ADDON_KEY_K] = true;
						break;

					case ALLEGRO_KEY_L:
						key[KS_AL_ADDON_KEY_L] = true;
						break;

					case ALLEGRO_KEY_M:
						key[KS_AL_ADDON_KEY_M] = true;
						break;

					case ALLEGRO_KEY_N:
						key[KS_AL_ADDON_KEY_N] = true;
						break;

					case ALLEGRO_KEY_O:
						key[KS_AL_ADDON_KEY_O] = true;
						break;

					case ALLEGRO_KEY_P:
						key[KS_AL_ADDON_KEY_P] = true;
						break;

					case ALLEGRO_KEY_Q:
						key[KS_AL_ADDON_KEY_Q] = true;
						break;

					case ALLEGRO_KEY_R:
						key[KS_AL_ADDON_KEY_R] = true;
						break;

					case ALLEGRO_KEY_S:
						key[KS_AL_ADDON_KEY_S] = true;
						break;

					case ALLEGRO_KEY_T:
						key[KS_AL_ADDON_KEY_T] = true;
						break;

					case ALLEGRO_KEY_U:
						key[KS_AL_ADDON_KEY_U] = true;
						break;

					case ALLEGRO_KEY_V:
						key[KS_AL_ADDON_KEY_V] = true;
						break;

					case ALLEGRO_KEY_W:
						key[KS_AL_ADDON_KEY_W] = true;
						break;

					case ALLEGRO_KEY_X:
						key[KS_AL_ADDON_KEY_X] = true;
						break;

					case ALLEGRO_KEY_Y:
						key[KS_AL_ADDON_KEY_Y] = true;
						break;

					case ALLEGRO_KEY_Z:
						key[KS_AL_ADDON_KEY_Z] = true;
						break;
				}
				break;
				
			case ALLEGRO_EVENT_KEY_UP:
				ResetKeys();
				key[KS_AL_ADDON_KEY_UP] = true;
				key[KS_AL_ADDON_KEY_DOWN] = false;
				break;

		}

		//Redrawing the window and running the Update() function in our Source class
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			al_clear_to_color(al_map_rgb((char)defaultWindowColor[0], (char)defaultWindowColor[1], (char)defaultWindowColor[2]));
			source.Update();

			ScanForMouse();

			al_flip_display();
			redraw = false;
		}
	}

	return 0;
}


