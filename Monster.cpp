#include<cmath>
#include<iomanip>
#include<random>
#include<sstream>
#include "Monster.h"

/*

Monster::Monster()
{
}*/


Monster::~Monster()
{
}

void Monster::detect(CChara * Actor)
{
	std::pair<int, int> target = Actor->get_xy();
	double dist = std::pow(target.first - Pos.first,2) + std::pow(target.second - Pos.second,2);
	//나중에 리펙토링한다면 이 dist는 참,거짓을 뺏는걸로 변할거임
	if (dist <= 5)
	{
		if (this->Pos.first - target.first > 0)
		{
			direction = 0;
		}
		else if (this->Pos.first - target.first < 0)
		{
			direction = 1;
		}
		else if (this->Pos.second - target.second > 0)
		{
			direction = 2;
		}
		else if (this->Pos.second - target.second < 0)
		{
			direction = 3;
		}
	}
	else
	{
		//다이렉션 0~3까지의 랜덤값
		std::random_device rand;
		std::mt19937_64 seed(rand());
		std::uniform_int_distribution<int> range(0, 3);
		//나중에 함수로만들어서 매개 a~b까지 이렇게 만들어야지 시드 언제다써
		direction = range(seed);
	}

//	MoveMent();//여기서 스위치 < 찾으면 트루내고 그결과로 가는걸로함
	//만약 5이하라면추적 몬스터와 플레이어의 first값 계산을 해서 -라면 아래로 +면 위로 
	//변동될수있겠다 mob.first - 
}
//해당 캐릭의 x or y위치가 특정값(일단 임시로 5)내이고 그안에 방해물이 없다면
//쫓아올수 있도록 하는 무언가가 필요함 만약 발견했는데 벗어난다면?


void Monster::MoveMent()
{
	std::pair<int, int> there;
	if (delay >= 1)
	{
		delay = 0;
		switch (direction)
		{//우선 디텍트 먼저하고 없으면 랜덤돌린다 << actor어디서가져옴? 차라리 디텍트가 bool로되고
			//바로 무브먼트 실행하는게 더낫겠음
			//여기서 케이스에 따른 변화
	//		if (there_is_null(mob, there = { Pos.first - 1, Pos.second }))
			//맵에서 그려내면 편할텐데ㅇㅇ
		case 0:COM = new MoveUp(); COM->Action(this);	break;
		case 1:COM = new MoveDown(); COM->Action(this); break;
		case 2:COM = new MoveLeft(); COM->Action(this); break;
		case 3:COM = new MoveRight(); COM->Action(this); break;
		}
	}
	else
		delay += 0.01;

}

void Monster::set_xy_mob()
{
do
{
	std::random_device rand;
	std::mt19937_64 seed(rand());
	std::uniform_int_distribution<int> range(41, 40 * 38);
	//위의 range는 바뀔확률이 매우높음
	Pos.first = range(seed) / 40;
	Pos.second = range(seed) % 40;
	} while (MAP[Pos.first][Pos.second] != '.');
}


void Monster::Show(std::queue<std::string> *clerk)
{
	std::ostringstream oss;
	oss << "이름 : " << name ;//마나는 안쓸가능성이 있음
	//이넣는건 넣고 개행을 다른곳 즉 쓰는곳에서 할거니 endl안함
	clerk->push(oss.str());
	oss.str("");
	oss.clear();
	
	oss << "체력:" << std::setw(4) << Hp.first << "/" << std::setw(4)
	<< Hp.second << " 공격력:" << std::setw(3) << Atk.first <<
		" ~ " << std::setw(3) << Atk.second;
		//방어력 % 2d",Hp.first, Hp.second, Atk.first, Atk.second,Def);
	clerk->push(oss.str());
	oss.str("");
	oss.clear();
oss << "방어력 " << std::setw(2) << Def << "\t 경험치 : " << std::setw(2) <<Exp;
	clerk->push(oss.str());
//이 clerk에 이런식으로 저장하고 write 함수로 뱉어냄ㅇㅇ
	//잘하면 클리어는 무의미한듯함
}
