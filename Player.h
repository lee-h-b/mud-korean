#pragma once
class Command;
class Monster;
class Iskill;
#include"Command.h"
#include"Item.h"

#include<vector>
#include<queue>
#include<string>
class Player : public CChara
{
private:
	//bool kb;//키보드 눌렀는가?
	short key;

	int Exp_Max;
	unsigned short Lv;
	//직업도넣을거같당
	float speed = 3;
	short Stats_Point;
	short Skill_Point;

	std::vector<Item*> inventory ;
	//무언가가 추가되면 이인벤토리에 그 무언가를 넣는거
	Equipment Equip[5]{}; //임의의 값에 해당 물건을 넣는다

	std::queue<std::string> clerk;

public:
	Player(std::string name, char B, char **MAP, int MAP_SIZE,short Str,short Dex, short Int,int col =3);
	~Player();

	void Skill_Learn();
	short get_key()
	{
		return this->key;
	}
	decltype(auto) get_clerk() { return &clerk;  }
	void set_Atk(int m_atk, int M_atk) { Atk.first += m_atk; Atk.second += M_atk; }
	void set_Def(int val) { Def += val; }
	void up_Hp(int val) { Hp.first += val; Hp.second += val; }
	void up_Mp(int val) { Mp.first += val; Mp.second += val; }

	void MoveMent() override;
	//가상함수로 Chara에있는거 빼서 옮길거임
	int Move_to_floor();//S면 -1을, E이면1을 반환하도록
	//해당값을 어떻게 메인(던전이동)에 줄것인가?

	void In_Battle(std::vector<Monster*> &Mobs, std::queue<std::string> *clerk);
		//있는 몬스터의 수에따라 이자식들 전부 데리고가서 한판붙음
	void Init_Exp();

	void Show();//음 가상 함수로 만들어야지
	void Equip_Show();

	void Lv_Up();
	void Stats();//스탯찍기!
//메뉴도만들거같음 효율적으로 하기위해 맵옆에 queue를 스크롤창으로만들자
	void Apply_Stat();


	//아이템공간
	Equipment get_equip_item(int num) { return Equip[num]; }//이러면될까 ㄴㄴ 매개변수가 하나있어야한다
	decltype(auto) get_inventory() { return inventory; }
	void set_equip_item(Equipment *equip, int num, bool put_on)
	{
		//여기서 제어하자 외부의 Equip[num]의 아이디를빼서
		//내인벤토리뒤져서 같은 id나오면 내인벤토리꺼지움
		//else의경우엔 내인벤 맨뒤에 추가해줌
		if (put_on)
		{
			for (auto i = inventory.begin(); i != inventory.end(); )
			{
				if ((*i)->get_id() == equip->get_id())
				{
					i = inventory.erase(i);
					break;
				}
				else
					i++;	
			}//인벤에서 아이디 같은거 소멸시키고
			Equip[num] = *equip;//장착함
		}
		else
		{
			inventory.push_back(new Equipment(*equip));
			Equip[num].Item_Init();//아이템 안껴요!

		}
	}

	void inventory_change(Item* item, int add);//아이템의 변동 및 소멸맨

	void Erase_item();//임의의 아이템을 지워버리도록 만들거같은 그런함수
					  //내가장착한 아이템은 상황을봐서 지워버리게된다

};

