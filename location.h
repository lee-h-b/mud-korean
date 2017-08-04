#pragma once
#include<iostream>
#include<random>
class location
{
protected:
	int set_x, set_y;
	int now_x, now_y;
//	char **MAP;
	bool Start;
	bool End;
public:

	location( int size);

	void Draw(char **MAP);
	void Make_Start(char **MAP);
	decltype(auto) Get_now()
	{
		std::pair<int, int> now = { now_x, now_y };
		return now;
	}
};