#pragma once
#include<iostream>

#include"DrunkWalk.h"
#include"location.h"
#include"Chara.h"

class CMAP
{
private:
	std::pair<int, int> Rect;
	std::pair<int, int> S_Point;
	std::pair<int, int> E_Point;
	int a = 1;
	int max_bar;
	char **MAP;
	unsigned int size;
	DrunkWalk drunker;
public:
	bool check = false;
	CMAP(int _size );
	~CMAP();

	char** Get_Map()
	{
		return this->MAP;
	}
	void set_start(int i, int j)
	{
		S_Point.first = i;
		S_Point.second = j;
	}
//	void set_E
	decltype(auto) get_start()
	{
		return this->S_Point;
	}
	decltype(auto) get_end()
	{
		return this->E_Point;
	}
	int Get_Size()
	{
		return this->Rect.second;
	}
/*
	unsigned int size;
	std::cout << "�ִ� ������ �Է� : ";

	std::cin >> size;
	*/
	void Map_Set();
	void Map_Drawing();
	bool Next(CChara *Player);//��Ȳ������ CChara�� �ƴ϶� CP���ɼ���
//	bool Prev(CChara *Player);
	void Reset();
	void Map_init();



};

