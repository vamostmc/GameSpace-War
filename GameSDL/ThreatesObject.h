#ifndef THREATES_OBJECT_H_
#define THREATES_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include<vector>

#define WIDTH_THREAT 86
#define HEIGHT_THREAT 91
class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();
	
	void HandleMove (const int & x_bordr , const int &y_bordr, int hangso);
	void HandleMove_0 (const int & x_bordr , const int &y_bordr, int hangso);
	void HandleInputAction(SDL_Event events);
	
	void set_x_val(const int &val ) {x_val_ = val;}
	void set_y_val(const int &val ) {y_val_ = val;}
	int get_x_val() const {return x_val_ ;}
	int get_y_val() const {return y_val_ ;}
	void SetAmoList1(std::vector<AmoObject*> amo1_list) {p_amo1_list_ = amo1_list;}
	std::vector<AmoObject*> GetAmoList1() const {return p_amo1_list_;} 
	
	void SetAmoList2(std::vector<AmoObject*> amo2_list) {p_amo2_list_ = amo2_list;}
	std::vector<AmoObject*> GetAmoList2() const {return p_amo2_list_;}

	void SetAmoList3(std::vector<AmoObject*> amo3_list) {p_amo3_list_ = amo3_list;}
	std::vector<AmoObject*> GetAmoList3() const {return p_amo3_list_;}

	void InitAmo(AmoObject * p_amo1, AmoObject *p_amo2,AmoObject *p_amo3);
	void MakeAmo(SDL_Surface *des , const int &x_limit ,const int & y_limit);
	void Reset(const int &xboder);
	void ResetAmo();
private:
	int x_val_;
	int y_val_;
	int hangso;
	std::vector<AmoObject*> p_amo1_list_;
	std::vector<AmoObject*> p_amo2_list_;
	std::vector<AmoObject*> p_amo3_list_;
};



#endif 
