#include "Chara.h"
//이함수자체는플레이어가 움직여야 하니깐 캐릭터자체를 옮기게될지도
#include"Skill.h"
#include"WindowsFunc.h"
#include<conio.h>
/*상태이상 만들고싶은거같음 어쩌지 우선 장비부터ㅎㅎ?
*/
CChara::CChara(std::string name, char B, char ** MAP, int MAP_SIZE, int Exp, int col )
	:name(name), Body(B), color(col), Exp(Exp)
{
	Stats_Init(0, 0, 0);
	init(&Skills);
	Map_Init(MAP, MAP_SIZE);
}
CChara::CChara(std::string name, char B, int Exp)
{
//	Skills = NULL; <<입력으로 스킬을 받게되면 이게 들어가지
	this->name = name;
	Body = B;
	this->Exp = Exp;
}

CChara::~CChara()
{
}

//Set_Hp는 기본 양수니깐 깎이면 -로해야해
void CChara::Set_Hp(int Val)
{
	Hp.first += Val;
	if (Hp.first > Hp.second)
		Hp.first = Hp.second;
}

void CChara::Map_Init(char **MAP, int MAP_SIZE)
{
	this->MAP = nullptr;
	this->MAP_size=MAP_SIZE;
	this->MAP = MAP;
	this->Pos = { 0, 0 };
}

void CChara::Stats_Init(unsigned short s, unsigned short d, unsigned short i)
{
	this->Str = s;
	Dex = d;
	Int = i;
}

void CChara::Draw(int bc )
{//이함수는 이름 Draw_Chara로 바꿔야 할거고
 //가상함수가 될거
	gotoxy(Pos.second, Pos.first);
	
	COLOR(color,bc);
	std::cout << this->Body;
	COLOR(7, 0);
}

void CChara::Chara_Init(int hp, int mp, int atk,int atk_m, int def)
{
	Hp = { hp,hp };
	Mp = { mp,mp };
	if(atk > atk_m)
		Atk = { atk_m, atk };

	Atk = { atk, atk_m };
	Def = def;
}

