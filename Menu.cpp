#include "Menu.h"
#include"Player.h"
#include"Screen.h"
#include<sstream>
//나중에 플레이어 중일부를 여기로 옮겨 넣고싶음

void Menu_Equipment(Player *user)
{
	std::ostringstream oss;//여긴 필요없을지도모름
	auto equip_item = user->get_inventory();
	//이 겟인벤토리를 좀 개조했다면 반복문 여러번 안해도됬을거임

	if (equip_item.size() <= 0)
	{
		return;//필요하면 Read하고리턴
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
	Write(oss << equip_item.size()+1 << " : 나가기", user->get_clerk());
//	std::cout << equip_item.size();

	Write(oss << "어떤 아이템을 장착할까요", user->get_clerk());

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
			{//같은아이템 끼고있음 불가능
				//실제장착
//				user->set_equip_item(equip_item[pos], equip_item[pos]->get_type(), true);
				equip_item[pos]->Equip(user);
				//ㄴ이걸 외부에서 받기에 실제 인벤은 무사함 <<장착인벤에 
				//해당아이템을 지우도록하고 해제하면 해당아이템 추가하자
				Write(oss << equip_item[pos]->get_name() << "을 장착했습니다", user->get_clerk());
			}
			else
				Write(oss << "이미 장착중 입니다", user->get_clerk());
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
			Write(oss << "체력이 " << use_item->get_value().first <<", 마력이 " 
			<< use_item->get_value().second << "회복 되었다!",user->get_clerk());
		else if(use_item->get_value().first != 0)
			Write(oss << "체력이 " << use_item->get_value().first 
				<< "회복 되었다!", user->get_clerk());
		else
			Write(oss << "마력이 " << use_item->get_value().second
				<< "회복 되었다!", user->get_clerk());
		Read(user->get_clerk());
	}
		else return;
//	get_item_use(target,)
}

//아이템을 던진다 그럼 그쪽에선 item id가 0이면 실행못하게
//그렇다면 이걸 호출하는애는 사용될 아이템이겠음
Item* get_Item_use(Player * me,bool In_Battle)
{//배틀에서 쓰일 유즈도 하나만들어야할까?
	std::vector<Item*> inven = me->get_inventory();
	std::ostringstream oss;


//		auto inven = me->get_inventory();
	if (me->get_inventory().size() == 0)
	{
		inven.push_back(new Item());
		inven[0]->Item_Init();//혹시나해서
		Write(oss << "아이템이 없습니다", me->get_clerk());
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
			inven[0]->Item_Init();//혹시나해서

			Write(oss << "사용가능한 아이템이 없습니다", me->get_clerk());
			Read(me->get_clerk());

			return inven[0];//0반환
		}
		else//타입을 봐서던지는 물건인데  안 배틀이면 안쓰게 
		{
			int select;

			Write(oss << "어떤 아이템을 쓸것인가요", me->get_clerk());
			for (int i = 0; i < inven.size(); i++)
			{
				inven[i]->Show(me->get_clerk() , i+1);
			}

			Write(oss << inven.size()+1 << ": 나가기", me->get_clerk() );
			for (;;)
			{
				Read(me->get_clerk());
				select = input();

				select -= 1;
				if (select < 0 || select == inven.size())
				{
					//아이템이 이걸받으면 쓰레기를 받는거임
					return new Item();
				}
				if (select > inven.size())
				{
					Write(oss << "범 위 초 과", me->get_clerk());
					continue;
				}
				if (inven[select]->get_type() == (int)ITEM_TYPE::THROW	
					&& !In_Battle)
				{
					Write( oss << "배틀중이 아닙니다!",me->get_clerk() );
					continue;
				}
				else 
				{
					//그냥 찾은걸 반환하고, 그값이랑 똑같은 id찾아서 감소?
					//아이템사용을 어찌 표현할지를 몰라서 다시 찾아재끼는짓함
					//ㄴ 간단하게 리턴만하기로함

					//배틀중이면 어쩌게? 아이템을 맞출 대상이 있어야하는건데
					//아이템값의 밸류를 들고있다가 몬스터고르면 그몬스터에게쏨
					return (inven[select]);
					//값만 반환시킨다? 데미지 계산은 밖에서 시키니깐..
					//여긴 아이템을 고르는거고 실질적인 사용은 밖이함
				}
			}
			
		}
//inven이 빈값이아니면
//	Write(oss << "어떤 아이템 사용?!");
}
