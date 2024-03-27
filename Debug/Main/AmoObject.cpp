#include"AmoObject.h"
#include <cstdlib>
#include <ctime>

AmoObject:: AmoObject()
{
rect_.x = 0;
rect_.y = 0;
x_val_ = 0;
y_val_ = 0;
is_move_ = false;
amo_type_ = NONE;
}

AmoObject:: ~AmoObject()
{

}

void AmoObject:: HandleMove(const int& x_border, const int& y_border)
{
	rect_.x += 20;
	if(rect_.x > x_border) is_move_ = false;
}


void AmoObject::HandleMoveRightToLeft1()
{
	srand(time(NULL));
	int k1 = rand()%7;
	int k2 = rand()%8;
	int k3 = rand()%7;
	
	rect_.x -= k3;
	rect_.y -= k2;
	rect_.x -= k1;
	rect_.y += 4;

	if(rect_.x < 0 || rect_.y < 0 || rect_.x > SCREEN_WIDTH || rect_.y > SCREEN_HEIGHT) 
	{
		is_move_ = false;
	}
}

void AmoObject::HandleMoveRightToLeft2()
{
	srand(time(NULL));
	int k1 = rand()%6;
	int k2 = rand()%8;
	int k3 = rand()%6;
	
	rect_.x -= k3;
	rect_.y += k2;
	rect_.x -= k1;
	rect_.y -= 4;

	if(rect_.x < 0 || rect_.y < 0 || rect_.x > SCREEN_WIDTH || rect_.y > SCREEN_HEIGHT) 
	{
		is_move_ = false;
	}
}

void AmoObject::HandleMoveRightToLeft3()
{
	rect_.x -= 15;
	
	if(rect_.x < 0 || rect_.y < 0 || rect_.x > SCREEN_WIDTH || rect_.y > SCREEN_HEIGHT) 
	{
		is_move_ = false;
	}
}

void AmoObject:: HandleInputAction(SDL_Event events)
{
;
}