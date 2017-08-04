#include <iostream>
#include<random>
#include<string>
#include<Windows.h>
#include<vector>
#include<list>

#include"MAP.h"
#include"Chara.h"
#include"Player.h"
#include"Monster.h"
#include"Command.h"
#include"MonsterDB.h"
#include"Screen.h"


void main()
{
	int floor = 0;
	//몬스터 최대 수
	int M_Max = 4;//플로어 넘어갈수록 높아지도록


	std::pair<int, int> backPos;
	std::vector<CMAP> Map{ 40 ,40, 40, 40, 40 };
	std::pair<int, int> S_point;
	std::pair<int, int> E_point;

	for (auto& i : Map)
	{//Stair
		i.Map_Set();
		//list -> pair로 줄일수있을거같음 < 애초에 시작할땐 1층만받고시작해서
		//다음층가면 새로 다시받는식으로 하면됨
	}
	S_point = Map.at(floor).get_start();
	E_point = Map.at(floor).get_end();

	Map.at(0).Map_Drawing();
	//	Map[floor].Map_Drawing();
	Frame();//옆에틀

		//아래는 크게 신경안써도될거같은데 일단 내버려둠 
		//잘하면 저 'H'는 안씀 + test의 위치를 재정의 할수있는 함수 하나 만들기
	Player test("플레이어",'H', Map[floor].Get_Map(), Map[floor].Get_Size(),5,5,5,9);
	test.set_xy(Map[floor].get_start());//시작지점에 배치
	//몬스터 초기화라는 함수를 하나 만들어야할거같다


	std::vector<Monster*> Mob;
	
	for (int i = 0; i < M_Max; i++)
	{
		Mob.push_back(Mob_Init_1(floor));
		Mob[i]->Map_Init(Map[floor].Get_Map(), Map[floor].Get_Size());
		Mob[i]->set_xy_mob();
	}
//	Mob[0]->set_xy_mob();
	//몬스터 1마리 랜덤위치 가능
	//이제 몬스터 여러마리 랜덤위치가 될수 있도록 할필요O
	//배틀은 누가? 짜피 몬스터위치에 여러다수가있는걸 파악하고 그래야하니깐 플레이어가하도록한다

		backPos = test.get_xy();
	while (1)
	{
		short change = test.Move_to_floor();//뭔가 받아야할까?
/*		gotoxy(41, 0);
		std::cout << "test";
		gotoxy(0, 0);
	*/	//백포스라는걸 만들어서 1번 움직일때마다 해당위치로바꾸도록
		if (change != 0 && backPos != test.get_xy() )
			//이제 턴을 움직였는가에대한 체크여부
			//난제내ㅡ 해결 < 현위치와 기존위치가 다를경우에 이동하도록
		{
			//다음문제 다음층가면 해당층의 S에서 시작하게된다 이걸수정
				floor += change;
				int temp_floor = floor;
				if (floor <= 0)
				{
					floor = 0;
				}
			else if (floor == Map.size())
			{
				std::cout << "END";
				exit(0);
			}


			backPos = test.get_xy();
			CLEAR(Map[floor].Get_Size());
			gotoxy(0, 0);

				//맵을 새로초기화
			Map.at(floor).Map_Drawing();
			test.Map_Init(Map[floor].Get_Map(), Map[floor].Get_Size());
			//새로생긴문제 해당 s,e를 그대로 실행함즉 플로어가 바뀌면 안되는데 바뀜
			//시작위치와 끝위치를 전부 빼서(벡터면될듯) 내캐릭의 위치가 그위치와
			//같은지 비교하는 함수로 다시짠다
			//시작위치,끝위치는 초기화 된거같으니깐 get_start()같은 얘들에게 새로넣음될거같음

			S_point = Map.at(floor).get_start();
			E_point = Map.at(floor).get_end();

			if (change >= 1)
			{
				test.set_xy(Map[floor].get_start());
				M_Max += 1;
			}
			else if (change <= -1 && temp_floor < 0)
			{
				test.set_xy(Map[floor].get_start());
				continue;
			}
			else if (change <= -1 )
			{
				test.set_xy(Map[floor].get_end());
				M_Max -= 1;
			}


			 Mob.erase(Mob.begin(), Mob.end());
			 //이동하면 몬스터 새로만들어야함 즉 다지워버리도록
		}

		if (Mob.size() == M_Max )
		{//없으면 새로만들도록 만들어야징
			//다죽으면 새로만들던가
			for (auto& i : Mob)
			{
				i->detect(&test);
				i->MoveMent();
				i->Draw();
			}
		}
		else
		{
//			Mob.push_back(new Monster('M', Map[floor].Get_Map(), Map[floor].Get_Size(), 15));
			Mob.push_back(Mob_Init_1(floor));
			Mob.at(Mob.size() -1) ->Map_Init(Map[floor].Get_Map(), Map[floor].Get_Size()) ;
			Mob.at(Mob.size() - 1)->set_xy_mob();

		}
		

		test.Show();
		test.Equip_Show();
		test.In_Battle(Mob,test.get_clerk());
		
		backPos = test.get_xy();
		test.MoveMent();
		test.Draw(10);

	}
}