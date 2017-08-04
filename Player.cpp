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
	//üũ���ϸ� �����ּ���!
	
	//�������� ���� �Ⱥ��̰� �ϰ����
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
		Write(oss << "���� ����Ʈ : " << Skill_Point ,&clerk);
			std::vector<Iskill*> Temp;
			Temp = this->Skills;//�� ������ �ʿ���� ������

			//���� ����� �׷� ��ų���� ���ε����ٱ�
			int n;
			int i;
			for (i = 0; i < Skills.size(); i++)
			{
				Skills[i]->Show(&clerk, i);
			}//���� ��� std::cout�� clerk�� ����
		Write( oss << i + 1 << " : ������ " ,&clerk);
		Write( oss << "��ȣ�� �Է����ּ��� : ",&clerk);
		Read(&clerk);

			n = input();
			n--;

			if (n > Skills.size() || n < 0)
			{
			Write(oss << "�����ʰ�" ,&clerk);
			Read(&clerk);
				return;
			}
			else if (n == i)
			{
				return;
			}
			else if (Skill_Point < 1)
			{
				Write(oss << "����Ʈ�� �����մϴ�" ,&clerk);
				Read(&clerk);

				Sleep(500);
				return;
			}
		
			else if (Skill_Point >= 1 && Skills[n]->Learn(this->Skills,&clerk) == true)
			{//learn�� ���� <���ڷ� ��ų���޾� �������� ��ų���׷��̵���
				
				Skill_Point -= 1;
				Show();
			}
			auto test = *Temp[n];
//			Hero.Set_Skill(test);//? ��ų���? ���� �̰� ��ų����̸� else�� ������ �ٲ���ҵ�
		//��ų ������ n��° ��ų�� ���� �������μ� �ش罺ų�� �������̵ǵ����� ���� �ʿ���ٺ�
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
	printf("���� : %3d \t  ����ġ : %3d / %3d \n", Lv, Exp, Exp_Max);
	printf("���� ����Ʈ : %2d  ��ų ����Ʈ %2d\n", Stats_Point, Skill_Point);
	printf("ü�� :%4d / %4d ���� : %4d / %4d\n���ݷ� %3d ~ %3d  ���� %3d\n",
		Hp.first, Hp.second, Mp.first, Mp.second, Atk.first, Atk.second, Def);
	printf("�� : %3d\t�� : %3d\t�� %3d", Str, Dex, Int);
//	printf("")
}

void Player::Equip_Show()
{
	gotoxy(44, 43);// ������� �뷫 
	printf("�Ӹ� : %-14s", Equip[(int)ITEM_TYPE::HELMET].get_name().c_str());
	gotoxy(44, 44);
	printf("���� : %-14s \t ���� : %-14s", Equip[(int)ITEM_TYPE::WEAPON].
		get_name().c_str(), Equip[(int)ITEM_TYPE::SHIELD].get_name().c_str());
	gotoxy(44, 45);
	printf("���� : %-14s \t �Ź� : %-14s", Equip[(int)ITEM_TYPE::ARMOR].
		get_name().c_str(), Equip[(int)ITEM_TYPE::BOOTS].get_name().c_str());
}

void Player::Lv_Up()
{
	std::ostringstream oss;
	Write(oss << " ���� ��!", &clerk);
	Read(&clerk);
	Lv += 1;
	Exp_Max = Lv * 30;
	Skill_Point += 1;
	Stats_Point += 3;
	//��Ȳ���� �ٽù�����
	Hp.first = Hp.second;
	Mp.first = Mp.second;
}

void Player::Stats()
{
	std::ostringstream oss;
	if (Stats_Point <= 0)
	{
		Write( oss<< "����Ʈ�� �����մϴ�." , &clerk);
		Read(&clerk);
		return;
	}
	else
	{
		for (;;)
		{//���⵵ ���� �����
		int sel,Up;
		Write( oss<<"� ������ �ø��� �����Ͽ� �ֽʽÿ�", &clerk);
		Write(oss << "1.��\t 2.��ø\t 3.����\t 4.�ȿø�", &clerk);
		Read(&clerk);
			sel = 0;
			//cin�� ��������? ���� int�� ���߸���
			sel = input();
			sel -= 1;
			if (sel < 0 || sel > 3)
				continue;
			else if (sel == 3)
				return;
			else
				Write(oss << "��ŭ �ø��ϱ�? 1~" << Stats_Point, &clerk);
				Read(&clerk);
				Up = input();
				if (Up > Stats_Point || Up <= 0)
				{
					Write(oss<<"������ ��� ���Դϴ�", &clerk);
					Read(&clerk);
					continue;
				}

				else
					Stats_Point -= Up;
				switch (sel)
				{
				case 0: Str += Up; Apply_Stat(); Write(oss << "���� " << Up << "�ö���!", &clerk); Read(&clerk); return;
				case 1: Dex += Up; Apply_Stat(); Write(oss << "��ø�� " << Up << "�ö���!", &clerk); Read(&clerk); return;
				case 2: Int += Up; Apply_Stat(); Write(oss << "������ " << Up << "�ö���!", &clerk); Read(&clerk); return;
				}//�̰� �ϰ��� ���� ���� �ؾ���!
		}
	}

}

void Player::Apply_Stat()
{
	Chara_Init(Str* 12.67, Int * 11.52, ((Dex * 0.512) + (Str * 0.186)),
		((Dex * 0.584) + (Str * 0.198)), ((Dex *0.171) + (Str * 0.238)));
	for(int i = 0; i < 5; i++ )// <<�ϵ��ڵ�
	{
		if (this->Equip[i].get_id() != NULL)
			Equip[i].Add_Stat(this, true);
	}
	if (Atk.first <= 0)
		Atk.first = 1;
	//�׳� ���⿡ �߰�����
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
					Write(oss <<item->get_name()<< "��(��) �̹� ȹ���� ����̹Ƿ� �����ϴ�",&clerk);
					return;
				}
				else
					inventory[i]->set_Ea(add);
				if (inventory[i]->get_Ea() <= 0)
				inventory.erase(inventory.begin() + i);
				return;//�����麯��
			}
		}
		inventory.push_back(item);//���ٸ��߰���
								   //.pushback.pushback�̰ų� �̰� &�ι޾ư����ϰų�..
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
		{//key�� �����ؼ� NULL�̸�?
			speed = 0;
			key = VK_RIGHT;
			COM = new MoveRight();
			COM->Action(this);
		}
		//		gotoxy(this->Pos.first, Pos.second);
		if (GetAsyncKeyState('Q') & 0x8000)
		{//�빮�ڸ� �Է¹�����Ǵ���..
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			key = VK_F1;
			this->Stats();
		}
		if ((GetAsyncKeyState('W') & 0x8000) != 0)
		{//�빮�ڸ� �Է¹�����Ǵ���..
			key = 'S';//�ߵǴ��� �𸣰��� clerk���ʿ�
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
	else if ( speed <= 3)//�ٷ� ��µǴ� �ǹٲ�
	{
		//����ó�� �ǹ����� ���ǵ��� �� ���� ĿƮ����
		//��Ű�� �͵��ƴϸ� �� ���Լ��� ���ؼ� �ִ���
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
		//�׵ڿ� ���� �α�â �װŸ�����
		//cls���� Clear�� ��ġ�������..
		this->Show();
		if (Battle_Main(this, fights,clerk))
		{
			//���� 2�ߵ����� fights�ѳ༮�� �������쵵�ϸ���
			for (auto iter = Mobs.cbegin(); iter != Mobs.end();)
			{
				if (Pos == (*iter)->get_xy())
				{
					iter = Mobs.erase(iter);
				}//�̰� �ش���ġ�� ���� ����°���
				else
					++iter;
			}
		}
		else
		{

			std::ostringstream oss;
			Write(oss<<"�� ��",clerk);
			Sleep(500);
			//�����
			Write(oss << "" , clerk);
			Read(clerk);
			//�ִ�Ű�� ����������
			system("pause");
			exit(0);//�����鳪��
		}
	}
	if (Exp >= Exp_Max)
	{
		Exp = 0;
		Lv_Up();
	}
}
