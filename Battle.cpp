#include "Battle.h"
#include"Monster.h"
#include"Chara.h"
#include"Skill.h"
#include"WindowsFunc.h"
#include"Screen.h"
#include"Enums.h"
#include"Menu.h"
#include"ItemDB.h"

#include<iostream>
//#include<random>//������
#include<sstream>
#include<string>
/*���� ���Ͱ� �������� ����ϰ� �غ���
�ƴϸ� �����̻��� ���������
�װ͵��ƴϸ� �����ͱ����ұ�
*/
decltype(auto) choice_Mob(std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	int choice;
	std::ostringstream oss;
	//�ݺ����� for(i; i<size�� �ٲٰ� �ش� ���Ͱ� ���������쿡�� ī���õǵ��Ϲٲ���
	//���� �ִ���� �����,�ű� �����߿� ���� ���ʹ� false�� �δ½���?
//	int Max_count = Enemys.size();
	Write(oss << "����� ������ �ּ��� : ",clerk);
	int count = 1;
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			Write(oss << count << " : �̸� : " << i->get_name(), clerk);// Name;
		count++;
	}//���̽��¿��� -1�ؾ���
	Read(clerk);
	while (1)
	{
		choice = input();
	choice -= 1;
	if (choice < 0 || choice >= Enemys.size())
	{
		continue;
	}
	else if (Enemys.at(choice)->get_Pos_Hp() <= 0)
		continue;
	return static_cast<CChara*>(Enemys.at(choice));
	}
}
void Item_get(Player * Me, std::vector<std::pair<int, int>> item_Drop)
{//������ ����� ���������ʿ�x Me���ٰ� �߰��ҰŰ� �뿵��x
	std::ostringstream oss;
	for (int i = 0; i < item_Drop.size(); i++)
	{//�ش� ������ ���̺��� ��ġ
		if (item_Drop[i].first == NULL && item_Drop[i].second == NULL)
			continue;
		else
		{//��������������� ��������
			if (item_Drop[i].second >= Random_Gen(1, 950))
			{//���� second�� ���� 1~100���� ũ�Եȴٸ�
				Item * get = item_Init(item_Drop[i].first);
//				Me->inventory_change() �����۹޾ƾ��ϴµ�
				Write(oss << "������ ȹ�� ! : "<< get->get_name(),Me->get_clerk());
				Me->inventory_change( get, 1);
			}
		}
	}
}
//��Ȳ������ clerk�� *�� &�� �޾ƾ��� 
void Show_Enemys(std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			i->Show(clerk);
	}
}

bool kill_check(std::vector<Monster*> Enemys)
{
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			return false;
	}
	return true;
}

bool Battle_Main(CChara * Me, std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	std::ostringstream oss;
	if(Enemys.size() > 1)
	Write(oss << "�� ! �߻��� "<< Enemys[0]->get_name() << "������ �ο��� �ɾ�Դ�!", clerk);
	else
		Write(oss << "�� ! �߻��� " << Enemys[0]->get_name() << "(��)�� �ο��� �ɾ�Դ�!", clerk);
	do
	{
		Me->Show();
		gotoxy(0, 0);
//		CLEAR(40);
		{
			int select;
			Show_Enemys(Enemys,clerk);

			Write(oss << "1. ���� 2. ��ų 3. �����ۻ��", clerk);
			Read(clerk);

			select = input();
//			select -= 1;
			switch (select)
			{
			default:
			case 1: //std::cout << "" ���̽� �ϳ� ����°� ���ڴ�
			{
				if (Enemys.size() > 1)
					Attack(Me, choice_Mob(Enemys,clerk), clerk);//�̰���� ��������
				else
					Attack(Me, Enemys.front(), clerk);
				break;
			}
			case 2: 
			{
				//���� �Ʒ��� �����Ű��� �̰ɻ��� �� ��ų���Կ� �־��
				//�״����� �ű⼭ i�� �Է½�Ű�� Temp�� ����Ǹ� ��Ƽ��?
				std::vector<Iskill*> Temp = Me->Get_Skills();
				Show_Cast(*Me, &Temp, clerk);
				Read(clerk);
				if (Temp.size() != 0)
				{
					for (;;)
					{
						select = input();
						select -= 1;
						if (select == Temp.size())
						{
							Temp.erase(Temp.begin(), Temp.end());
							break;
						}
						else if (select < 0 || select > Temp.size())
							continue;
						else
						{
							if (Skill_Calc(Temp[select], Me,clerk) )
							{
								if (Temp[select]->Get_Non())
									Temp[select]->applySkill(Me, Me, clerk);
								else if (Enemys.size() > 1)//���� 2�����̻�
									Temp[select]->applySkill(Me, choice_Mob(Enemys, clerk), clerk);
								else
									Temp[select]->applySkill(Me, Enemys.front(), clerk);
							}
							else
							{
								Read(clerk); continue;
							}
							break;
						}
					}
				}
				if( Temp.size() == 0 || select == Temp.size()) continue;
				

				break;
			}
			//���̽� Ż��

			case 3://�����ۻ��
			{
				//�ϴ� ������ �ް� �� �������� �����°Ÿ� choicemob�ϴ�����
				//�������� �� ������ �ް��Ұ���
				Item *use_item = get_Item_use(static_cast<Player*>(Me), true);
				//�ߵǳ�?
				if (use_item->get_id() == NULL)
					continue;
				else if (use_item->get_type() >= (int)ITEM_TYPE::CONSUME)
					static_cast<Player*>(Me)->inventory_change(use_item, -1);

				if (use_item->get_type() == static_cast<int>(ITEM_TYPE::CONSUME))
				{
					use_item->Use(Me);
					if (use_item->get_value().first != 0 &&
						use_item->get_value().second != 0)
						Write(oss << "ü���� " << use_item->get_value().first << ", ������ "
							<< use_item->get_value().second << "ȸ�� �Ǿ���!", clerk);
					else if (use_item->get_value().first != 0)
						Write(oss << "ü���� " << use_item->get_value().first
							<< "ȸ�� �Ǿ���!", clerk);
					else
						Write(oss << "������ " << use_item->get_value().second
							<< "ȸ�� �Ǿ���!", clerk);
					break;
				}
				else if (Enemys.size() > 1)
					use_item->Use(choice_Mob(Enemys, clerk));
				else
					use_item->Use(Enemys.at(0) ) ;
				Write(oss <<use_item->get_name()<<"(��)�� ����"<< 
					use_item->get_value().first << "�������� �־���!",clerk);
				break;
			}
			}

			for (auto& i : Enemys )
			{
				if (i->get_Pos_Hp() >= 0)
				{
					int Mob_sel = Random_Gen(0, 10);//�ϴ� �̷��� �ϰ� 0�̸� ��ų���� �ϰ���� + ���� ��ΰ� �����Ѵ�
					switch (Mob_sel)
					{
					default:
					case 0: Attack(i, Me , clerk); break;
					}
				}
			}
			Read(clerk);
			//�������� ���� ������ �׳��Լ��� ���鵵��
		}
		if (Me->get_Pos_Hp() <= 0)
		{
			Write(oss << "�ǽ��� ���� �������..." , clerk);

			Read(clerk);
			return false;
		}
	} while (!kill_check(Enemys));

	int exp_sum = 0;
	for (auto& i : Enemys)//for�� �ʹ� ���ߵǴ°Ű���//�����۵� ���⼭?
	{//�Լ��� �и��ϸ� ���������ϰ���

		//�Ű��� ���⼭ �����۰��� �ޱ������ �׾����۰��� �Ű������ιް�
		//�׷��� ���ʹ̻����� �ݺ��� 1���� �����ݾ�
		Item_get(static_cast<Player*>(Me), i->get_drop_Item());

		exp_sum += i->get_exp();
	}
	//���⿡ ����ǰ�� �����̰�����

	Write(oss << "�¸� ! " << exp_sum << " ����ġ ȹ��! ", clerk);

	Read(clerk);
	Me->Set_Exp(exp_sum);
	Sleep(500);//�ٲ��� �𸣴¾�

	return true;
}
int Damage_Calc(CChara * Actor,int enemy_def)
{
	auto Atk = Actor->get_Atk();

	int damage = Random_Gen(Atk.first, Atk.second);
	
	damage = (damage - enemy_def) ;
	if (damage <= 0)
		return 1;
	return damage;
}

//��ų�� ������ �̾Ƴ���
bool Skill_Calc(Iskill * Magic, CChara *Hero, std::queue<std::string> *clerk)
//�̰� �÷��̾ ����ѹ��ϰ� �����ϰ�����
//���͵� �Ҽ������� ������
{
	int m_Atk;
	int Pay = Magic->Get_Cost();
	int Type = Magic->Get_Type();
	bool Peace = Magic->Get_Non();

	std::ostringstream oss;
//m_Atk�� Magic�� ��ȯ����
	if (Type == (int)Ability::STR)
	{
		if (Hero->get_Pos_Hp() <= Pay)
		{
			Write(oss << "ü���� �����մϴ�!", clerk);
			return false;
		}
		Hero->Set_Hp(-Pay);
	}
	else
	{
		if (Hero->get_Pos_Mp() < Pay)
		{
			Write(oss << "������ �����մϴ�!", clerk);
			return false;
		}
		Hero->Set_Mp(Pay);
	}

//	m_Atk = Magic->applySkill(Hero);

	
	return 1;
}

void Attack(CChara * Attacker, CChara * Defender, std::queue<std::string> *clerk)
{//�÷��̾� �̸��� �ʿ��� ������ xx�� ����! yy���� n������!
//�׸��� �̰� ������ �Ծ����
	int Damage = Damage_Calc(Attacker, Defender->Get_Def());

	std::ostringstream oss;
	Write(oss << Attacker->get_name() << "�� ����!" << Defender->get_name() << "���� " << Damage << "�������� ������!", clerk);

	Defender->Set_Hp(-Damage);
}

void Show_Cast(CChara Caster,std::vector<Iskill*> *Temp,std::queue<std::string> *clerk)
{//�̷��� �������� ������ ��ų�� �����ٳ༮�� �����
	//�̰� ȣ���ؼ� Temp�� ��ų���ְ� �ű⼭ �� ��ų�Է��ϰԤ�..
	std::ostringstream oss;
//	Temp = Caster.Get_Skills();
	int select;
	for (auto i = Temp->begin(); i != Temp->end();)
	{
		if ((*i)->Get_Lean() == false)
			i = Temp->erase(i);
		else ++i;
	}
	if (Temp->size() == 0)
	{
		Write(oss << "��ų�� �����ϴ�!", clerk);
		return;
	}
	else
	{
		int i;
		for (i = 0; i < Temp->size(); i++)
		{
			if ((*Temp)[i]->Get_Type() != static_cast<int>(Ability::STR))
				Write(oss << i + 1 << ": " << (*Temp)[i]->Get_Name() << " �Ҹ𸶳�: " <<
					(*Temp)[i]->Get_Cost(), clerk);
			else
				Write(oss << i + 1 << ": " << (*Temp)[i]->Get_Name() << " �Ҹ�ü��: " <<
				(*Temp)[i]->Get_Cost(), clerk);
		}
		Write(oss << i + 1 << ": ������", clerk);
		Write(oss << "����� ��ų�� �Է����ּ���", clerk);

	}
}
