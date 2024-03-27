#include "ThreatesObject.h"
#include "Common_Function.h"
#include "AmoObject.h"
#include "BaseObject.h"
ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{

}

void ThreatObject::InitAmo(AmoObject * p_amo)
{
	if(p_amo != NULL)
	{
		bool ret = p_amo->LoadImg("tenlua.jpg");
		if(ret != NULL)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface *des , const int &x_limit ,const int & y_limit)
{
	for(int i=0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			if(p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else 
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x , rect_.y + rect_.h * 0.5);
			}
		}
	}
}


void ThreatObject::HandleMove(const int & x_bordr , const int &y_bordr,int hangso)
{
	int k = 0 ;
	if(rect_.y < 10 ) { rect_.y += y_val_; k = 1;}
	if(hangso == 0 || k==1) {rect_.y += y_val_;}
	
	k = 0;
	if(rect_.y + HEIGHT_THREAT > SCREEN_HEIGHT) 
	{
		rect_.y -= y_val_; k = 1 ;
	}
	if(hangso == 1 || k==1 ) {rect_.y -= y_val_;}
}