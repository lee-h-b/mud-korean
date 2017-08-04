#pragma once
#include"Command.h"
#include"Player.h"
void MoveUp::Action(CChara * actor)
{
	auto key = actor->get_xy();
//그다음 해당위치값이 뭐가있는가를 알아보면될것
	//인자로 Key받아성
	if (key.first > 0)
	{
		auto period = actor->get_this_xy(key.first - 1, key.second);
		if (period != '#')
		{
			gotoxy(key);
			if (actor->get_this_zone(key.first, key.second) == 'S' ||
				actor->get_this_zone(key.first, key.second) == 'E'  )
				COLOR(14,10);
			std::cout << actor->get_this_zone(key.first, key.second);
			key.first -= 1;
		}
		actor->set_xy(key);
		//	std::cout << key.second;
	}
}

void MoveDown::Action(CChara * actor)
{
	auto key = actor->get_xy();
	if (key.first < actor->get_MAP_size() -1 && actor->get_this_xy(key.first+1, key.second) != '#')
	{
		gotoxy(key);
		if (actor->get_this_zone(key.first, key.second) == 'S' ||
			actor->get_this_zone(key.first, key.second) == 'E')
			COLOR(14,10);
		std::cout << actor->get_this_zone(key.first, key.second);
		key.first += 1;
	}
	actor->set_xy(key);
}


void MoveRight::Action(CChara * actor)
{

	auto key = actor->get_xy();
//	std::cout << key.second << " " << actor->get_MAP_size();
	if (key.second < actor->get_MAP_size() - 1 && actor->get_this_xy(key.first, key.second + 1) != '#')
	{
		gotoxy(key);
		if (actor->get_this_zone(key.first, key.second) == 'S' ||
			actor->get_this_zone(key.first, key.second) == 'E')
			COLOR(14,10);
		std::cout << actor->get_this_zone(key.first, key.second);
		key.second += 1;
	}
	actor->set_xy(key);
}

void MoveLeft::Action(CChara * actor)
{
	auto key = actor->get_xy();
	if (key.second > 0 && actor->get_this_xy(key.first, key.second - 1) != '#')
	{
		gotoxy(key);
		if (actor->get_this_zone(key.first, key.second) == 'S' ||
			actor->get_this_zone(key.first, key.second) == 'E')
			COLOR(14,10);
		std::cout << actor->get_this_zone(key.first, key.second);

		key.second -= 1;
	}
	actor->set_xy(key);
}

