#include "Common_Function.h" 
#include"TextObject.h"

bool SDLCommonFunc::CheckFocusWithRect(const int&x , const int &y,const SDL_Rect & rect)
{
	if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y<= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface *des, TTF_Font * font)
{
	g_img_menu = LoadImage("MN.png");
	if(g_img_menu == NULL)
	{
		return 1;
	}
	const int kMenuItemNum = 2;
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 200 ;
	pos_arr[0].y = 400 ;

	pos_arr[1].x = 200;
	pos_arr[1].y = 200;

	TextObject text_menu[kMenuItemNum];
	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	bool selected[kMenuItemNum] = {0, 0 };
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while(true)
	{
		SDLCommonFunc :: ApplySurface(g_img_menu,des,0,0);
		for(int i =0 ;i<kMenuItemNum;i++)
		{
			text_menu[i].CreateGameText(font,des);
		}

		while(SDL_PollEvent(&m_event))
		{
			switch(m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;

					for(int i = 0 ;i<kMenuItemNum;i++)
					{
						if(CheckFocusWithRect(xm,ym,text_menu[i].GetRect()))
						{
							if(selected[i] ==false )
							{
								selected[i] = 1;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else 
						{
							if(selected[i] == true )
							{
								selected[i] = 0;
								text_menu[i].SetColor(TextObject::BLACK_TEXT);
							}
						}
					}
				}
			  break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					for(int i = 0 ;i<kMenuItemNum;i++)
					{
						if(CheckFocusWithRect(xm,ym,text_menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if(m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 1;
				}
			default:
				break;

			}
		}
		SDL_Flip(des);
	}

	return 1;
}







SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface*load_image = NULL;
	SDL_Surface*optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());

	if(load_image!=NULL)
	{

	optimize_image = SDL_DisplayFormat(load_image);
	SDL_FreeSurface(load_image);

		if (optimize_image != NULL)  // Xử lí xoá backgound ảnh nhân vật
		{
		UINT32 color_key = SDL_MapRGB(optimize_image->format,0,0,0);
		SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
  return offset;
}

void SDLCommonFunc::CleanUp()
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}
