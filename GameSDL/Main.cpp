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

	g_font_text = TTF_OpenFont("Aller_Rg.ttf",35);      // Chen phong chu menu 
	return true;
}

int main(int arc, char*agrv[])
{
	bool is_quit = false;

	if(Init() == false)
		return 0;

	g_bkground = SDLCommonFunc::LoadImage("aa.png");              //Chen Backgound

	if(g_bkground == NULL)
	{
		return 0;
	}

	
    //Make MainObject
	MainObject human_object;
	human_object.SetRect(20,0);
	bool ret = human_object.LoadImg("boss.png");                  //Chen Anh nhan vat
	if(!ret)
	{
		return 0;
	}


   





    //Make ThreatObject
    ThreatObject* p_threat = new ThreatObject();
    ret = p_threat->LoadImg("boss.png");                                 //Chen anh boss
    if(ret == false)
        {return 0;}
	p_threat->SetRect(SCREEN_WIDTH - 100 , SCREEN_HEIGHT* 0.5);
    p_threat->set_y_val(4);
	p_threat->set_x_val(15);


	AmoObject* p_amo1 = new AmoObject();
	AmoObject* p_amo2 = new AmoObject();
	AmoObject* p_amo3 = new AmoObject();

	p_threat->InitAmo(p_amo1 ,p_amo2, p_amo3);

	int k = 0;
	int d = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if(ret_menu == 1)
	{
		return true;
	}

	while(!is_quit)
	{
		srand(time(NULL));
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

		human_object.HandleMove();
        human_object.Show(g_screen);

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
		
		p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
        p_threat->Show(g_screen);
		p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
		
		//Kiem tra ban dan vs nguoi choi va boss
		bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(),p_threat->GetRect());
		if (is_col)
		{
			if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
			{
				delete p_threat;
				SDLCommonFunc::CleanUp();
				SDL_Quit();
				return 1;
			}
		}

		std::vector<AmoObject*> amo_list = human_object.GetAmoList();
		for (int t = 0 ; t< amo_list.size(); t++)
		{
			AmoObject* p_amo = amo_list.at(t);


			if(p_amo != NULL)
			{
				bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
				if(ret_col == true)
				{
					d = human_object.RemoveAmo(t,d);
					/*if(d>=5)
					{
						p_threat->HandleMove_0(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
					}*/


					if(d==20) 
					{
						if(MessageBox(NULL,L"YOU WIN", L"Info" , MB_OK) == IDOK)
						{
							delete p_threat;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
					break;
				}
			}
		}
		if(d>=5)
				{
					p_threat->HandleMove_0(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
					p_threat->HandleMove_0(SCREEN_WIDTH, SCREEN_HEIGHT,rand()%2);
					
					
				}

		std::vector<AmoObject*> amo_list3 = p_threat->GetAmoList3();
		for (int t = 0 ; t< amo_list3.size(); t++)
		{
			AmoObject* p_amo = amo_list3.at(t);

			if(p_amo != NULL)
			{
					bool ret_col3 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col3 == true)
					{
					p_threat->Reset(t);
					if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
					{
						delete p_threat;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}
					

					break;
					
				}
			}
		}

		std::vector<AmoObject*> amo_list1 = p_threat->GetAmoList1();
		for (int t = 0 ; t< amo_list1.size(); t++)
		{
			AmoObject* p_amo = amo_list1.at(t);

			if(p_amo != NULL)
			{
					bool ret_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col1 == true)
					{
					p_threat->Reset(t);
					if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
					{
						delete p_threat;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}
					

					break;
					
				}
			}
		}

		std::vector<AmoObject*> amo_list2 = p_threat->GetAmoList2();
		for (int t = 0 ; t< amo_list2.size(); t++)
		{
			AmoObject* p_amo = amo_list2.at(t);

			if(p_amo != NULL)
			{
					bool ret_col2 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),human_object.GetRect());
					if(ret_col2 == true)
					{
					p_threat->Reset(t);
					if(MessageBox(NULL,L"GAME OVER", L"Info" , MB_OK) == IDOK)
					{
						delete p_threat;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}
					

					break;
					
				}
			}
		}


		if(SDL_Flip(g_screen) == -1 )
			return 0;
	} 

	SDLCommonFunc::CleanUp();
	SDL_QUIT;
	return 1;
}