#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatesObject.h"
#include <cstdlib>
#include <ctime>
#include"TextObject.h"

TTF_Font * g_font_text = NULL;

bool Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
	if(g_screen == NULL)
		return false;

	if(TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("Aller_Rg.ttf",20);
	return true;
}

int main(int arc, char*agrv[])
{
	bool is_quit = false;

	if(Init() == false)
		return 0;

	g_bkground = SDLCommonFunc::LoadImage("kk.png");
	if(g_bkground == NULL)
	{
		return 0;
	}
	
    //Make MainObject
	MainObject human_object;
	human_object.SetRect(20,250);
	bool ret = human_object.LoadImg("add.png");
	if(!ret)
	{
		return 0;
	}

   

    //Make ThreatObject
    ThreatObject* p_threat = new ThreatObject();
    ret = p_threat->LoadImg("boss.png");
    if(ret == false)
        {return 0;}
    p_threat->SetRect(500, SCREEN_HEIGHT*0.5);
    p_threat->set_y_val(2);

	AmoObject* p_amo = new AmoObject();
	p_threat->InitAmo(p_amo);

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if(ret_menu == 1)
	{
		return true;
	}

	while(!is_quit)
	{
		while(SDL_PollEvent(&g_even))
		{
			if(g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even);
		}


		SDLCommonFunc:: ApplySurface(g_bkground,g_screen,0,0);
        human_object.Show(g_screen);
      
		human_object.HandleMove();

        for(int i=0; i < human_object.GetAmoList().size(); i++)
        {
         std::vector<AmoObject*> amo_list = human_object.GetAmoList();
         AmoObject* p_amo = amo_list.at(i);
         if(p_amo != NULL)
         {
           if(p_amo->get_is_move())
           {
             p_amo->Show(g_screen);
             p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
           }
           else
           {
             if(p_amo != NULL)
             {
               amo_list.erase(amo_list.begin() + i);
               human_object.SetAmoList(amo_list);

               delete p_amo;
               p_amo = NULL;
             }
           }
         }

        }

        //Run ThreatObject
        p_threat->Show(g_screen);
		srand(time(NULL));
        p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
		p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);


		if(SDL_Flip(g_screen) == -1 )
			return 0;
	} 

	SDLCommonFunc::CleanUp();
	SDL_QUIT;
	return 1;
}