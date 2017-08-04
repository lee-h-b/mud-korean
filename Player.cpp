#include "Player.h"
#include"ItemDB.h"
#include"Monster.h"
#include"Skill.h"

#include"WindowsFunc.h"
#include"Battle.h"
//#include"Skill.h"
#include"Enums.h"
#include"Screen.h"
#include"Menu.h"

#include<sstream>
Player::Player(std::string name,char B, char **MAP, int MAP_SIZE, short Str, short Dex, short Int, int col )
	:CChara(name,B, MAP, MAP_SIZE,0,col)
{
//	inventory_change(new Item(Item_Init(0)), 1);
//	inventory_change(item_Init(0), 5);
//	inventory_change(item_Init(1), 3);
//	inventory.push_back(Item_Init(0));
//	inventory_change(item_Init(3), 1);
	//inventory_change(item_Init(4), 1);
//	inventory_change(item_Init(8), 1);
	//체크다하면 지워주세요!
	
	//착용중인 장비는 안보이게 하고싶음
	Equip[(int)ITEM_TYPE::WEAPON] =static_cast<Equipment&>(*item_Init(0)) ;
	Equip[(int)ITEM_TYPE::SHIELD] = static_cast<Equipment&>(*item_Init(1));

	Stats_Init(Str, Dex, Int);
	Apply_Stat();
	Exp = 0;
	Lv = 1;
	Stats_Point = 5;
	Skill_Point = 3;
	Init_Exp();
	key = NULL;
}



Player::~Player()
{
}
void Player::Skill_Learn()
{
	std::ostringstream oss;
		while (1)
		{
		Write(oss << "보유 포인트 : " << Skill_Point ,&clerk);
			std::vector<Iskill*> Temp;
			Temp = this->Skills;//이 템프는 필요없지 않을까

			//내가 배웠던 그런 스킬들을 전부따낸다군
			int n;
			int i;
			for (i = 0; i < Skills.size(); i++)
			{
				Skills[i]->Show(&clerk, i);
			}//여기 모든 std::cout은 clerk가 쓴다
		Write( oss << i + 1 << " : 나가기 " ,&clerk);
		Write( oss << "번호를 입력해주세요 : ",&clerk);
		Read(&clerk);

			n = input();
			n--;

			if (n > Skills.size() || n < 0)
			{
			Write(oss << "범위초과" ,&clerk);
			Read(&clerk);
				return;
			}
			else if (n == i)
			{
				return;
			}
			else if (Skill_Point < 1)
			{
				Write(oss << "포인트가 부족합니다" ,&clerk);
				Read(&clerk);

				Sleep(500);
				return;
			}
		
			else if (Skill_Point >= 1 && Skills[n]->Learn(this->Skills,&clerk) == true)
			{//learn도 볼것 <인자로 스킬을받아 실질적인 스킬업그레이드임
				
				Skill_Point -= 1;
				Show();
			}
			auto test = *Temp[n];
//			Hero.Set_Skill(test);//? 스킬배움? 만약 이게 스킬배움이면 else의 조건을 바꿔야할듯
		//스킬 적용임 n번째 스킬을 덮어 씌움으로서 해당스킬의 레벨등이되도록함 따라서 필요없다봄
			Read(&clerk);

			Sleep(500);
	}
}
void Player::Init_Exp()
{
	Exp_Max = Lv * 30;
}

void Player::Show()
{
	gotoxy(0, 43);
	printf("레벨 : %3d \t  경험치 : %3d / %3d \n", Lv, Exp, Exp_Max);
	printf("스탯 포인트 : %2d  스킬 포인트 %2d\n", Stats_Point, Skill_Point);
	printf("체력 :%4d / %4d 마나 : %4d / %4d\n공격력 %3d ~ %3d  방어력 %3d\n",
		Hp.first, Hp.second, Mp.first, Mp.second, Atk.first, Atk.second, Def);
	printf("힘 : %3d\t민 : %3d\t지 %3d", Str, Dex, Int);
//	printf("")
}

void Player::Equip_Show()
{
	gotoxy(44, 43);// 사이즈는 대략 
	printf("머리 : %-14s", Equip[(int)ITEM_TYPE::HELMET].get_name().c_str());
	gotoxy(44, 44);
	printf("무기 : %-14s \t 방패 : %-14s", Equip[(int)ITEM_TYPE::WEAPON].
		get_name().c_str(), Equip[(int)ITEM_TYPE::SHIELD].get_name().c_str());
	gotoxy(44, 45);
	printf("갑옷 : %-14s \t 신발 : %-14s", Equip[(int)ITEM_TYPE::ARMOR].
		get_name().c_str(), Equip[(int)ITEM_TYPE::BOOTS].get_name().c_str());
}

void Player::Lv_Up()
{
	std::ostringstream oss;
	Write(oss << " 레벨 업!", &clerk);
	Read(&clerk);
	Lv += 1;
	Exp_Max = Lv * 30;
	Skill_Point += 1;
	Stats_Point += 3;
	//상황봐서 다시버릴듯
	Hp.first = Hp.second;
	Mp.first = Mp.second;
}

void Player::Stats()
{
	std::ostringstream oss;
	if (Stats_Point <= 0)
	{
		Write( oss<< "포인트가 부족합니다." , &clerk);
		Read(&clerk);
		return;
	}
	else
	{
		for (;;)
		{//여기도 뭔가 써야함
		int sel,Up;
		Write( oss<<"어떤 스탯을 올릴지 선택하여 주십시오", &clerk);
		Write(oss << "1.힘\t 2.민첩\t 3.지능\t 4.안올림", &clerk);
		Read(&clerk);
			sel = 0;
			//cin에 문제있음? ㄴㄴ int가 들어가야만함
			sel = input();
			sel -= 1;
			if (sel < 0 || sel > 3)
				continue;
			else if (sel == 3)
				return;
			else
				Write(oss << "얼마큼 올립니까? 1~" << Stats_Point, &clerk);
				Read(&clerk);
				Up = input();
				if (Up > Stats_Point || Up <= 0)
				{
					Write(oss<<"범위를 벗어난 값입니다", &clerk);
					Read(&clerk);
					continue;
				}

				else
					Stats_Point -= Up;
				switch (sel)
				{
				case 0: Str += Up; Apply_Stat(); Write(oss << "힘이 " << Up << "올랐다!", &clerk); Read(&clerk); return;
				case 1: Dex += Up; Apply_Stat(); Write(oss << "민첩이 " << Up << "올랐다!", &clerk); Read(&clerk); return;
				case 2: Int += Up; Apply_Stat(); Write(oss << "지능이 " << Up << "올랐다!", &clerk); Read(&clerk); return;
				}//이거 하고나면 스탯 갱신 해야지!
		}
	}

}

void Player::Apply_Stat()
{
	Chara_Init(Str* 12.67, Int * 11.52, ((Dex * 0.512) + (Str * 0.186)),
		((Dex * 0.584) + (Str * 0.198)), ((Dex *0.171) + (Str * 0.238)));
	for(int i = 0; i < 5; i++ )// <<하드코딩
	{
		if (this->Equip[i].get_id() != NULL)
			Equip[i].Add_Stat(this, true);
	}
	if (Atk.first <= 0)
		Atk.first = 1;
	//그냥 여기에 추가하자
}

void Player::inventory_change(Item *item, int add)
{
	std::ostringstream oss;
		for (int i = 0; i < inventory.size(); i++)
		{
			if (item->get_id() == inventory[i]->get_id()||
				Equip[item->get_type()].get_id() == item->get_id())
			{
				if (inventory[i]->get_Ea() + add > 1 &&
					inventory[i]->get_type() < (int)ITEM_TYPE::CONSUME ||
					Equip[item->get_type()].get_id() == 
					item->get_id() )
				{
					Write(oss <<item->get_name()<< "은(는) 이미 획득한 장비이므로 버립니다",&clerk);
					return;
				}
				else
					inventory[i]->set_Ea(add);
				if (inventory[i]->get_Ea() <= 0)
				inventory.erase(inventory.begin() + i);
				return;//있으면변동
			}
		}
		inventory.push_back(item);//없다면추가지
								   //.pushback.pushback이거나 이걸 &로받아가야하거나..
}



void Player::MoveMent()
{
	if (speed > 3 )
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000 && speed > 3)
		{
			speed = 0;
			key = VK_UP;
			COM = new MoveUp();
			COM->Action(this);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 && speed > 3)
		{
			speed = 0;
			key = VK_DOWN;
			COM = new MoveDown();
			COM->Action(this);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && speed > 3)
		{
			speed = 0;
			key = VK_LEFT;
			COM = new MoveLeft();
			COM->Action(this);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && speed > 3)
		{//key에 저장해서 NULL이면?
			speed = 0;
			key = VK_RIGHT;
			COM = new MoveRight();
			COM->Action(this);
		}
		//		gotoxy(this->Pos.first, Pos.second);
		if (GetAsyncKeyState('Q') & 0x8000)
		{//대문자를 입력받으면되더라..
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			key = VK_F1;
			this->Stats();
		}
		if ((GetAsyncKeyState('W') & 0x8000) != 0)
		{//대문자를 입력받으면되더라..
			key = 'S';//잘되는지 모르겠음 clerk가필요
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			this->Skill_Learn();
		}
		if ((GetAsyncKeyState('E') & 0x8000) != 0)
		{
			key = 'E';
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			Menu_use(this);
		}
		if ((GetAsyncKeyState('R') & 0x8000) != 0)
		{
			key = 'R';
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			Menu_Equipment(this);
		}

		if (GetAsyncKeyState('X') & 0x8000)
		{
			exit(0);
		}
	}
	else if ( speed <= 3)//바로 출력되니 또바뀜
	{
		//이전처럼 되버린다 스피드라는 걸 만들어서 커트라인
		//시키자 것도아니면 또 저함수들 비교해서 넣던가
		key = NULL;
		speed += 0.05;
	}


}

int Player::Move_to_floor()
{
//	this->MAP;
	if (MAP[Pos.first][Pos.second] == 'S')
		return -1;
	else if (MAP[Pos.first][Pos.second] == 'E')
		return 1;
	else
	return 0;
}

void Player::In_Battle(std::vector<Monster*> &Mobs, std::queue<std::string> *clerk)
{
	std::vector<Monster*> fights;
	for (auto &i : Mobs)
	{	
		if (Pos == i->get_xy())
		{
//			auto t = i->get_xy();
//			std::cout << get_xy
			fights.push_back(i);
		}
	}
	if (fights.size() >= 1)
	{
//		CLEAR(40);
//		system("cls");
		//그뒤에 옆에 로그창 그거만들어내고
		//cls말고 Clear로 퉁치고싶은데..
		this->Show();
		if (Battle_Main(this, fights,clerk))
		{
			//이제 2중돌려서 fights한녀석들 전부지우도록만듬
			for (auto iter = Mobs.cbegin(); iter != Mobs.end();)
			{
				if (Pos == (*iter)->get_xy())
				{
					iter = Mobs.erase(iter);
				}//이건 해당위치의 몹을 지우는거임
				else
					++iter;
			}
		}
		else
		{

			std::ostringstream oss;
			Write(oss<<"패 배",clerk);
			Sleep(500);
			//개행용
			Write(oss << "" , clerk);
			Read(clerk);
			//애니키로 최종나가기
			system("pause");
			exit(0);//졌으면나감
		}
	}
	if (Exp >= Exp_Max)
	{
		Exp = 0;
		Lv_Up();
	}
}
