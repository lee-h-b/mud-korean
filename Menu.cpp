#include "Menu.h"
#include"Player.h"
#include"Screen.h"
#include<sstream>
//���߿� �÷��̾� ���Ϻθ� ����� �Ű� �ְ����

void Menu_Equipment(Player *user)
{
	std::ostringstream oss;//���� �ʿ����������
	auto equip_item = user->get_inventory();
	//�� ���κ��丮�� �� �����ߴٸ� �ݺ��� ������ ���ص���������

	if (equip_item.size() <= 0)
	{
		return;//�ʿ��ϸ� Read�ϰ���
	}

	for (int i = 0; i < equip_item.size();)
	{
		if (equip_item[i]->get_type() == (int)ITEM_TYPE::CONSUME ||
			equip_item[i]->get_type() == (int)ITEM_TYPE::THROW || equip_item[i]->get_id() == 0)
			equip_item.erase(equip_item.begin() + i);
		else
		{
			equip_item[i]->Show(user->get_clerk(), i+1);
			i++;
		}
	}
	Write(oss << equip_item.size()+1 << " : ������", user->get_clerk());
//	std::cout << equip_item.size();

	Write(oss << "� �������� �����ұ��", user->get_clerk());

		Read(user->get_clerk());
		while (true)
		{
			int pos = input();
			pos -= 1;
			if (pos == equip_item.size())
				return;
			else if (pos > equip_item.size() || pos < 0) continue;

			else if (equip_item[pos]->get_id() != user->
				get_equip_item(equip_item[pos]->get_type()).get_id())
			{//���������� �������� �Ұ���
				//��������
//				user->set_equip_item(equip_item[pos], equip_item[pos]->get_type(), true);
				equip_item[pos]->Equip(user);
				//���̰� �ܺο��� �ޱ⿡ ���� �κ��� ������ <<�����κ��� 
				//�ش�������� ���쵵���ϰ� �����ϸ� �ش������ �߰�����
				Write(oss << equip_item[pos]->get_name() << "�� �����߽��ϴ�", user->get_clerk());
			}
			else
				Write(oss << "�̹� ������ �Դϴ�", user->get_clerk());
			Read(user->get_clerk()); 
			return;
		}
}
void Menu_use(Player * user)
{
//	ostringstream oss;
	std::ostringstream oss;
	Item *use_item;
		use_item = get_Item_use(user, false);
	if (use_item->get_id() != NULL)
	{

		use_item->Use(user);
		if(use_item->get_type() >= (int)ITEM_TYPE::CONSUME )
		user->inventory_change(use_item, -1);
//		Write(oss << "");
		if (use_item->get_value().first != 0 &&
			use_item->get_value().second != 0)
			Write(oss << "ü���� " << use_item->get_value().first <<", ������ " 
			<< use_item->get_value().second << "ȸ�� �Ǿ���!",user->get_clerk());
		else if(use_item->get_value().first != 0)
			Write(oss << "ü���� " << use_item->get_value().first 
				<< "ȸ�� �Ǿ���!", user->get_clerk());
		else
			Write(oss << "������ " << use_item->get_value().second
				<< "ȸ�� �Ǿ���!", user->get_clerk());
		Read(user->get_clerk());
	}
		else return;
//	get_item_use(target,)
}

//�������� ������ �׷� ���ʿ��� item id�� 0�̸� ������ϰ�
//�׷��ٸ� �̰� ȣ���ϴ¾ִ� ���� �������̰���
Item* get_Item_use(Player * me,bool In_Battle)
{//��Ʋ���� ���� ��� �ϳ��������ұ�?
	std::vector<Item*> inven = me->get_inventory();
	std::ostringstream oss;


//		auto inven = me->get_inventory();
	if (me->get_inventory().size() == 0)
	{
		inven.push_back(new Item());
		inven[0]->Item_Init();//Ȥ�ó��ؼ�
		Write(oss << "�������� �����ϴ�", me->get_clerk());
		Read(me->get_clerk() );
		return inven[0];

	}
		for (auto iter = inven.cbegin(); iter != inven.end();)
		{
			if ((*iter)->get_usable() != true)
				iter = inven.erase(iter);
			else
				++iter;
		}
		if (inven.size() <= 0)
		{
			inven.push_back(new Item());
			inven[0]->Item_Init();//Ȥ�ó��ؼ�

			Write(oss << "��밡���� �������� �����ϴ�", me->get_clerk());
			Read(me->get_clerk());

			return inven[0];//0��ȯ
		}
		else//Ÿ���� ���������� �����ε�  �� ��Ʋ�̸� �Ⱦ��� 
		{
			int select;

			Write(oss << "� �������� �����ΰ���", me->get_clerk());
			for (int i = 0; i < inven.size(); i++)
			{
				inven[i]->Show(me->get_clerk() , i+1);
			}

			Write(oss << inven.size()+1 << ": ������", me->get_clerk() );
			for (;;)
			{
				Read(me->get_clerk());
				select = input();

				select -= 1;
				if (select < 0 || select == inven.size())
				{
					//�������� �̰ɹ����� �����⸦ �޴°���
					return new Item();
				}
				if (select > inven.size())
				{
					Write(oss << "�� �� �� ��", me->get_clerk());
					continue;
				}
				if (inven[select]->get_type() == (int)ITEM_TYPE::THROW	
					&& !In_Battle)
				{
					Write( oss << "��Ʋ���� �ƴմϴ�!",me->get_clerk() );
					continue;
				}
				else 
				{
					//�׳� ã���� ��ȯ�ϰ�, �װ��̶� �Ȱ��� idã�Ƽ� ����?
					//�����ۻ���� ���� ǥ�������� ���� �ٽ� ã���糢������
					//�� �����ϰ� ���ϸ��ϱ����

					//��Ʋ���̸� ��¼��? �������� ���� ����� �־���ϴ°ǵ�
					//�����۰��� ����� ����ִٰ� ���Ͱ��� �׸��Ϳ��Խ�
					return (inven[select]);
					//���� ��ȯ��Ų��? ������ ����� �ۿ��� ��Ű�ϱ�..
					//���� �������� ���°Ű� �������� ����� ������
				}
			}
			
		}
//inven�� ���̾ƴϸ�
//	Write(oss << "� ������ ���?!");
}
