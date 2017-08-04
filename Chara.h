#pragma once
#include<iostream>
#include<string>

#include<Windows.h>
#include<vector>
#include"Enums.h"
#include"WindowsFunc.h"
class Iskill;
class Command;
/*

3. 위 2번에서 만든 유닛클래스를 관리하는 프로그램에 플레이어 추가.
3 - 1 관리하는 유닛들과 플레이어 유닛이 서로 공격 할 수 있어야한다.
//

4. 위 3번에서 만든 프로그램을 통하여 관리하는 유닛들과 플레이어간의 랜덤한 전투를 추가
4 - 1 유닛은 랜덤하게 조우한다.
4 - 2 플레이어는 자신이 컨트롤할 수 있어야한다
//배틀시스템
*/
class CChara
{
protected:
	std::pair<int,int> Pos;
	char Body;
	std::string name;
	unsigned short Str;
	unsigned short Dex;
	unsigned short Int;

	int MAP_size;
	char** MAP = nullptr;//현재 이캐릭터가 있을 위치
	Command *COM;
	std::pair<int, int> Hp;
	std::pair<int, int> Mp;
	std::pair<int, int> Atk;
	int Def;
	int Exp;
	short color;//추후 바뀔꺼같은 그런색임
	std::vector<Iskill*> Skills;//몬스터도 스킬을 쓸수가 있음


public:
	CChara(std::string name, char B, char ** MAP, int MAP_SIZE, int Exp, int col = 7);
	CChara(std::string name, char B, int Exp);

	decltype(auto) get_name() { return name;  }
	decltype(auto) get_Atk() { return Atk; }
	int Get_Def() { return Def; }
	int get_Pos_Hp() { return Hp.first; }
	int get_Max_Hp() { return Hp.second; } //임시임
	int get_Pos_Mp() { return Mp.first; }
	int get_exp() { return Exp; }
	std::vector<Iskill*> Get_Skills()
	{	return this->Skills; }
	int get_stat(int val)
	{
		switch (val)
		{
		case(static_cast<int>(Ability::STR)): return Str;
		case(static_cast<int>(Ability::DEX)): return Dex;
		case(static_cast<int>(Ability::INT)): return Int;
		}
	}

	void Set_Hp(int Val);//+를 기본으로했기에 데미지면 -연산해야함
	void Set_Exp(int Val) { Exp += Val; }
	void Set_Mp(int val) { Mp.first -= val;  if (Mp.first > Mp.second) Mp.first = Mp.second;
	}
	decltype(auto) get_this_zone(int y, int x)
	{
		return MAP[y][x];
	}
	void set_xy(std::pair<int, int> xy)
	{
		Pos = xy;
	}
	decltype(auto) get_xy()
	{
		return Pos;
	}// 해당 함수는 몬스터에서 쓸일은 없을거같음
/*	short get_key()
	{
		return this->key;
	}*/
	int get_MAP_size()
	{
		return this->MAP_size;
	}

	template<typename T>
	decltype(auto) get_this_xy(T y, T x)
	{
		return MAP[y][x];
	}
	
	decltype(auto) get_map()
	{
		return this->MAP;
	}
	

	void Draw(int bc = 0);
	void Chara_Init(int hp, int mp, int atk, int atk_m, int def);

	void Map_Init(char **MAP, int MAP_SIZE);
	void Stats_Init(unsigned short s, unsigned short d, unsigned short i);
	virtual void MoveMent() {};
	virtual void Show() {};
	//가상함수
	~CChara();
};

