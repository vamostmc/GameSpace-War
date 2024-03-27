#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<string>
#include<SDL_image.h>
#include<SDL.h>
#include<SDL_ttf.h>


const int SCREEN_WIDTH = 1099;
const int SCREEN_HEIGHT = 580;
const int SCREEN_BPP = 32;
const int NUMBER = 3;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface *g_img_menu = NULL;
static SDL_Event g_even;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	int ShowMenu(SDL_Surface *des, TTF_Font * font);
	bool CheckFocusWithRect(const int&x , const int &y,const SDL_Rect & rect);
	bool CheckCollision(const SDL_Rect& object1 , const SDL_Rect& object2);

}

#endif