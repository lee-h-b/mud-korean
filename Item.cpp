#include "Item.h"
#include"Player.h"
#include"Monster.h"
#include"Screen.h"
#include"enums.h"

#include<sstream>
Item::Item()
{
	Item_Init();
}

Item::Item(int id, std::string name, short type, std::pair<short,short> atk, short def, short hp, short mp, short need_lv, bool usable)
{
	Item_Init(id, name, type, atk, def, hp, mp, need_lv, usable);
}


Item::~Item()
{
}

void Item::gain_item(int ea)
{
}

void Item::Item_Init(int id, std::string name , short type , std::pair<short, short> atk, short def , short hp, short mp, short need_lv, bool usable)
{
	this->ATK= atk;
	this->DEF = def;
	this->Ea = 1;
	this->Value.first = hp;
	this->ID = id;
	this->Value.second = mp;
	this->name = name;
	this->Need_Lv = need_lv;
	this->type = type;
	this->usable = usable;
}

Equipment::Equipment()
	:Item()
{

}

void Equipment::Equip(Player * me)
{//�̰Ŵ� �ɷ�ġ �������Ҷ��� ���ԵɰŴ� write����

 //�Ű��� val�� �ʿ��Ѱ�? Ÿ�Ը� ������ ����������?
 //�����������ϸ� ������ �ִ� �������� ������� �׾������� �κ��丮 �ǵڿ� �ֵ����Ѵ�
	Equipment temp = me->get_equip_item(this->type);//me�� ������ �������� ���Թ޴µ� ����ġ���� type��

	if (temp.get_id() != NULL )//���� �ش簪�� NULL�ϰ���ε� static_cast���� �̷��� �׷�
							  //��¶�� �������� �ִٸ�
	{
		temp.UnEquip(me, static_cast<Equipment*>(&temp) );//me�� �ɷ�ġ ����
						 //�׸��� �̾������� �ٽ� �κ��丮�� �־�־߰���
//		me->
	}
	//�������̾��ٸ�? �ش� �������� �Ѱ������ �ϴ�
	//�Ѱ��شٸ� �̾������� ����Ǵ°�? �Ҹ��� ���������Ѱ�?
	//�׳� �������� �������ΰ� ǥ�����Ѽ� �������ϰ��ϰ�
	//���Ƿ� UnEquip�Ͻ�? �̷�����

	//������ ���� �̰� �׳� ���� �ٲ� �����ִ°ſ� �Ұ��ϴ�
	me->set_equip_item(this, this->type, true);
	Add_Stat(me, true);
}

void Equipment::Add_Stat(Player * me,bool Add)
{
	int sign;
	if (Add == true)
		sign = 1;
	else
		sign = -1;
		if (this->ATK.first != 0)
			me->set_Atk(ATK.first*sign, ATK.second*sign);
		if (this->DEF != 0)
			me->set_Def(DEF *sign);
		if (this->Value.first != 0)
			me->up_Hp(Value.first *sign);
		if (this->Value.second != 0)
			me->up_Mp(Value.second *sign);
}

void Equipment::UnEquip(Player * me, Item* that)
{
	me->set_equip_item((Equipment*)that, this->type, false);

	Add_Stat(me, false);
}

void Equipment::Show(std::queue<std::string>* clerk, int num)
{
	/*����?
	1.Ÿ�Ժ��� �ؾ���? << �̰� �����ȵ� type��° ��������ϸ��
	�����ϴ´ɷ�ġ�� ������ ���� ������ �Ⱦ��� <<�Ƹ� �̰Թ���
	ť�� �ȳְ� oss�� ���� ����������?*/
	std::ostringstream oss;
	oss << num << ". �̸� : " << this->name;
	if (ATK.first != 0)
		oss << " ���ݷ� : " << ATK.first << "~" << ATK.second;
	if (oss.str().size() > 40)//�ϵ��ڵ��� ����..
		Write(oss, clerk);
	if (DEF != 0)
		oss << " ���� : " << DEF;
	if (oss.str().size() > 40)
		Write(oss, clerk);
	if (Value.first != 0)
		oss << " ü�� : " << Value.first;
	if (oss.str().size() > 40)
		Write(oss, clerk);
	if (Value.second != 0)
		oss << " ���� : " << Value.second;
		Write(oss, clerk);
	oss << " ���� : " << ITEM_LIST[type];
}

void Item::Item_Init()
{
	this->ATK = { 0,0 };
	this->DEF = 0;
	this->Ea = 0;
	this->Value.first = 0;
	this->ID = NULL;
	this->Value.second = 0;
	this->name = "";
	this->Need_Lv = 0;
	this->type = 0;
	this->usable = 0;
}

void Consume::Use(CChara * me)
{
				  //������ �ش� Ea���� 0���� �����
				  //���� Ea�� 0�̸�Ҹ��ε� how?
				  //�κ��丮�� �׷������� ����
	if (this->type == static_cast<int>(ITEM_TYPE::CONSUME))
	{//�������� �Ҹ�ǰ!
		if (this->Value.first != 0)
		{
			me->Set_Hp(this->Value.first);
		}
		if (this->Value.second != 0)
		{
			me->Set_Mp(-Value.second);//�����ϰ� ü��,������ ����
		}
	}
	else
	{
		me->Set_Hp(-this->Value.first);
		//actor�� set_hp�� ������ �ִ� �Լ�
	}
}
void Consume::Use(Monster * Mob)
{
	//Mob->
	Mob->Set_Hp(this->Value.first * -1);
}
void Consume::Show(std::queue<std::string> *clerk, int num)
{
	std::ostringstream oss;
	if (Value.first != 0 && Value.second != 0 && this->type != static_cast<int>(ITEM_TYPE::THROW))
		Write(oss <<num<< ": �̸� :" << name << " ü�� " << Value.first << "ȸ��, ���� " << 
			Value.second << "ȸ�� "<< Ea<< "��",clerk);
	else if (Value.first != 0 && this->type != static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": �̸� :" << name << " ü�� " << Value.first << "ȸ�� " << Ea << "��", clerk);
	else if (Value.second != 0 && this->type != static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": �̸� :" << name  << " ���� " << Value.second << "ȸ�� " << Ea <<
			"��", clerk);
	else if(this->type == static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": �̸� :" << name << " " << Value.first << "������ " << Ea <<"��",
			clerk);

}
//�켱 �����۸� �غ���
/*�ش�������� ���ٸ� Erase�ϰԵɰ���
�ٵ� �� Erase�� �������?
�������� ������? ���� ���� �������� ������ push_back���� ������ �ְ� 
�ִٸ� �ű⿡ Ea++�����ְԵǰ���
���� �������� �ٽ������?
Erase�� �ش�������� ������Ŵ��

�׷��� use�� �κ��丮 �ϳ� ��� ���°� �����ʳ�?
���ͼ� �Ѵ��ϸ� �ܺο��� �������� �Һ��ؾ���

�Լ��� ������ ����ϴ� �Լ� �ϳ� ������ �ʿ䰡 �ְڴ�
�׷��� ��ų���°͵� �ű⿡ �־��ָ� �̻ܱ�?
Menu���������
*/