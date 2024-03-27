#include"MainObject.h"

MainObject::MainObject()
{
	rect_.x=0;
	rect_.y=0;
	rect_.w=WIDTH_MAIN_OBJECT;
	rect_.h=HEIGHT_MAIN_OBJECT;
	x_val_=0;
	y_val_=0;
}
MainObject::~MainObject()
{
	;
}
void MainObject::HandleInputAction(SDL_Event events)
{
     if(events.type==SDL_KEYDOWN)
	{
	switch (events.key.keysym.sym)
	{
		case SDLK_UP:
			y_val_-=HEIGHT_MAIN_OBJECT/10;
		break;
		case SDLK_DOWN:
			y_val_+=HEIGHT_MAIN_OBJECT/10;
		break;
		case SDLK_RIGHT:
			x_val_+=WIDTH_MAIN_OBJECT/10;
		break;
		case SDLK_LEFT:
			x_val_-=WIDTH_MAIN_OBJECT/10;
		break;
		default:
		break;
	}
	}
	else if(events.type==SDL_KEYUP)
	{
	switch (events.key.keysym.sym)
	{
		case SDLK_UP:
            y_val_+=HEIGHT_MAIN_OBJECT/10;
		break;
		case SDLK_DOWN:
            y_val_-=HEIGHT_MAIN_OBJECT/10;
		break;
        case SDLK_RIGHT:
            x_val_-=WIDTH_MAIN_OBJECT/10;
		break;
		case SDLK_LEFT:
			x_val_+=WIDTH_MAIN_OBJECT/10;
		break;
	}
	}
	else if(events.type==SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();
		if(events.button.button == SDL_BUTTON_LEFT)
		{
          p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
          p_amo->LoadImg("dan.jpg");
          p_amo->set_type(AmoObject::LASER);
		}
        else if(events.button.button==SDL_BUTTON_RIGHT)
        {
          p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
          p_amo->LoadImg("tenlua.jpg");
          p_amo->set_type(AmoObject::SPHERE);
        }

        p_amo->SetRect(this->rect_.x + 86, this->rect_.y + 24);     //Chỉnh đạn của nhân vật
        p_amo->set_is_move(true);

        p_amo_list_.push_back(p_amo);

	}
	else if(events.type==SDL_MOUSEBUTTONUP)
		{

		}
	else
		{
		;
		}
}
void MainObject::HandleMove()
{
	rect_.x +=x_val_;

	if(rect_.x < 0 || rect_.x+ WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		rect_.x -= x_val_;
	}
	rect_.y+=y_val_;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
	{ 
		rect_.y -= y_val_;
	}

}