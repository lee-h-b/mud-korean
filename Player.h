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
	//bool kb;//Ű���� �����°�?
	short key;

	int Exp_Max;
	unsigned short Lv;
	//�����������Ű���
	float speed = 3;
	short Stats_Point;
	short Skill_Point;

	std::vector<Item*> inventory ;
	//���𰡰� �߰��Ǹ� ���κ��丮�� �� ���𰡸� �ִ°�
	Equipment Equip[5]{}; //������ ���� �ش� ������ �ִ´�

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
	//�����Լ��� Chara���ִ°� ���� �ű����
	int Move_to_floor();//S�� -1��, E�̸�1�� ��ȯ�ϵ���
	//�ش簪�� ��� ����(�����̵�)�� �ٰ��ΰ�?

	void In_Battle(std::vector<Monster*> &Mobs, std::queue<std::string> *clerk);
		//�ִ� ������ �������� ���ڽĵ� ���� �������� ���Ǻ���
	void Init_Exp();

	void Show();//�� ���� �Լ��� ��������
	void Equip_Show();

	void Lv_Up();
	void Stats();//�������!
//�޴�������Ű��� ȿ�������� �ϱ����� �ʿ��� queue�� ��ũ��â���θ�����
	void Apply_Stat();


	//�����۰���
	Equipment get_equip_item(int num) { return Equip[num]; }//�̷���ɱ� ���� �Ű������� �ϳ��־���Ѵ�
	decltype(auto) get_inventory() { return inventory; }
	void set_equip_item(Equipment *equip, int num, bool put_on)
	{
		//���⼭ �������� �ܺ��� Equip[num]�� ���̵𸦻���
		//���κ��丮������ ���� id������ ���κ��丮������
		//else�ǰ�쿣 ���κ� �ǵڿ� �߰�����
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
			}//�κ����� ���̵� ������ �Ҹ��Ű��
			Equip[num] = *equip;//������
		}
		else
		{
			inventory.push_back(new Equipment(*equip));
			Equip[num].Item_Init();//������ �Ȳ���!

		}
	}

	void inventory_change(Item* item, int add);//�������� ���� �� �Ҹ��

	void Erase_item();//������ �������� ������������ ����Ű��� �׷��Լ�
					  //���������� �������� ��Ȳ������ ���������Եȴ�

};

