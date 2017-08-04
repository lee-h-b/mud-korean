#pragma once
#include<vector>
#include<queue>

#include "Player.h"
class Monster :	public CChara
{
private: 
	bool find = false;
	short direction;
	short sight;
	float delay;
	//dropItem의 첫번째는 아이템 키값이고 2번째는 확률임
	std::vector<std::pair<int, int>> drop_Item;
	

public:
	//먼저할것 커맨드디자인을 통해 자신에게 이동하도록 만든 무언가
	//2.닿으면 배틀걸도록 <<이건 내가 덤빌수도 있으니 메인쪽에서 담당하는게 맞다고봄

	Monster(std::string name,char b, char **MAP, int MAP_SIZE, int hp,int mp,int atk, int atk_m,int def,int exp,int color, std::vector<std::pair<int, int>>Drop,short sight = 5)
		:CChara(name,b, MAP, MAP_SIZE,exp), sight(sight)
	{
		drop_Item = Drop;
		this->color = color;
		//맵은 나중에받도록 되있는 생성자가 필요하다
		delay = 0.f;
		this->name = name;
		Chara_Init(hp, mp, atk, atk_m, def);
//		exp = 0;
	}
	Monster(std::string name, char b, int hp, int mp, int atk, int atk_m, int def, int exp, int color, std::vector<std::pair<int, int>>Drop, short sight = 5)
		:CChara(name,b,exp),sight(sight)
	{
		drop_Item = Drop;
		this->color = color;
		delay = 0.f;
		Chara_Init(hp, mp, atk, atk_m, def);
		//이런함수를 부르면 추후에 해야된다
		//그럼 차라리 위의 몹을 지우고 
		//이걸 호출할때 동시에 맵질도 하도록 짜야겠음
	}

	~Monster();
	
	
	//해당 캐릭의 x or y위치가 특정값(일단 임시로 5)내이고 그안에 방해물이 없다면
	//쫓아올수 있도록 하는 무언가가 필요함
	decltype(auto) get_drop_Item() { return drop_Item; }
	void detect(CChara * Actor);
	void MoveMent() override; //이동담당 매개는 현재 모든몹들
	void set_xy_mob();//현재 자신의맵에서 랜덤한위치이되, #가없는곳에 배치한다
	void Show(std::queue<std::string> *clerk);

};
