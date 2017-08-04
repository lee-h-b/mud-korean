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

3. �� 2������ ���� ����Ŭ������ �����ϴ� ���α׷��� �÷��̾� �߰�.
3 - 1 �����ϴ� ���ֵ�� �÷��̾� ������ ���� ���� �� �� �־���Ѵ�.
//

4. �� 3������ ���� ���α׷��� ���Ͽ� �����ϴ� ���ֵ�� �÷��̾�� ������ ������ �߰�
4 - 1 ������ �����ϰ� �����Ѵ�.
4 - 2 �÷��̾�� �ڽ��� ��Ʈ���� �� �־���Ѵ�
//��Ʋ�ý���
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
	char** MAP = nullptr;//���� ��ĳ���Ͱ� ���� ��ġ
	Command *COM;
	std::pair<int, int> Hp;
	std::pair<int, int> Mp;
	std::pair<int, int> Atk;
	int Def;
	int Exp;
	short color;//���� �ٲ𲨰��� �׷�����
	std::vector<Iskill*> Skills;//���͵� ��ų�� ������ ����


public:
	CChara(std::string name, char B, char ** MAP, int MAP_SIZE, int Exp, int col = 7);
	CChara(std::string name, char B, int Exp);

	decltype(auto) get_name() { return name;  }
	decltype(auto) get_Atk() { return Atk; }
	int Get_Def() { return Def; }
	int get_Pos_Hp() { return Hp.first; }
	int get_Max_Hp() { return Hp.second; } //�ӽ���
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

	void Set_Hp(int Val);//+�� �⺻�����߱⿡ �������� -�����ؾ���
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
	}// �ش� �Լ��� ���Ϳ��� ������ �����Ű���
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
	//�����Լ�
	~CChara();
};

