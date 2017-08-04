#include "Chara.h"
//���Լ���ü���÷��̾ �������� �ϴϱ� ĳ������ü�� �ű�Ե�����
#include"Skill.h"
#include"WindowsFunc.h"
#include<conio.h>
/*�����̻� ���������Ű��� ��¼�� �켱 �����ͤ���?
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
//	Skills = NULL; <<�Է����� ��ų�� �ްԵǸ� �̰� ����
	this->name = name;
	Body = B;
	this->Exp = Exp;
}

CChara::~CChara()
{
}

//Set_Hp�� �⺻ ����ϱ� ���̸� -���ؾ���
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
{//���Լ��� �̸� Draw_Chara�� �ٲ�� �ҰŰ�
 //�����Լ��� �ɰ�
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

