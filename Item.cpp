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
{//이거는 능력치 재조정할때도 쓰게될거니 write자제

 //매개로 val은 필요한가? 타입만 있으면 되지않을까?
 //장착에성공하면 기존에 있던 아이템이 있을경우 그아이템을 인벤토리 맨뒤에 넣도록한다
	Equipment temp = me->get_equip_item(this->type);//me가 장착한 아이템을 대입받는데 그위치값은 type임

	if (temp.get_id() != NULL )//만약 해당값이 NULL일경우인데 static_cast쓰기 쫄려서 그럼
							  //어쨋든 기존템이 있다면
	{
		temp.UnEquip(me, static_cast<Equipment*>(&temp) );//me의 능력치 감소
						 //그리고 이아이템을 다시 인벤토리에 넣어둬야겠음
//		me->
	}
	//기존템이없다면? 해당 아이템을 넘겨줘야지 일단
	//넘겨준다면 이아이템은 어찌되는가? 소멸이 제일적당한가?
	//그냥 장착중인 아이템인걸 표현시켜서 먹지못하게하고ㅂ
	//임의로 UnEquip하실? 이럼되지

	//아이템 장착 이건 그냥 값을 바꿔 끼워주는거에 불과하다
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
	/*문제?
	1.타입별로 해야함? << 이건 문제안됨 type번째 문자출력하면되
	존재하는능력치가 있으면 쓰고 없으면 안쓰고 <<아마 이게문제
	큐에 안넣고 oss에 넣음 되지않을까?*/
	std::ostringstream oss;
	oss << num << ". 이름 : " << this->name;
	if (ATK.first != 0)
		oss << " 공격력 : " << ATK.first << "~" << ATK.second;
	if (oss.str().size() > 40)//하드코딩의 잔해..
		Write(oss, clerk);
	if (DEF != 0)
		oss << " 방어력 : " << DEF;
	if (oss.str().size() > 40)
		Write(oss, clerk);
	if (Value.first != 0)
		oss << " 체력 : " << Value.first;
	if (oss.str().size() > 40)
		Write(oss, clerk);
	if (Value.second != 0)
		oss << " 마력 : " << Value.second;
		Write(oss, clerk);
	oss << " 부위 : " << ITEM_LIST[type];
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
				  //썼으면 해당 Ea값을 0으로 만들고
				  //만약 Ea가 0이면소멸인데 how?
				  //인벤토리나 그런데에서 관리
	if (this->type == static_cast<int>(ITEM_TYPE::CONSUME))
	{//나를위한 소모품!
		if (this->Value.first != 0)
		{
			me->Set_Hp(this->Value.first);
		}
		if (this->Value.second != 0)
		{
			me->Set_Mp(-Value.second);//간단하게 체력,마나만 관리
		}
	}
	else
	{
		me->Set_Hp(-this->Value.first);
		//actor의 set_hp에 영향을 주는 함수
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
		Write(oss <<num<< ": 이름 :" << name << " 체력 " << Value.first << "회복, 마나 " << 
			Value.second << "회복 "<< Ea<< "개",clerk);
	else if (Value.first != 0 && this->type != static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": 이름 :" << name << " 체력 " << Value.first << "회복 " << Ea << "개", clerk);
	else if (Value.second != 0 && this->type != static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": 이름 :" << name  << " 마나 " << Value.second << "회복 " << Ea <<
			"개", clerk);
	else if(this->type == static_cast<int>(ITEM_TYPE::THROW))
		Write(oss << num << ": 이름 :" << name << " " << Value.first << "데미지 " << Ea <<"개",
			clerk);

}
//우선 아이템만 해볼까
/*해당아이템이 없다면 Erase하게될거임
근데 그 Erase를 어디서하죠?
아이템을 얻으면? 만약 같은 아이템이 없으면 push_back으로 아이템 넣고 
있다면 거기에 Ea++를해주게되겠음
만약 아이템을 다써버리면?
Erase로 해당아이템을 삭제시킴ㅇ

그러면 use는 인벤토리 하나 들고 오는게 낫지않나?
들고와서 한다하면 외부에서 아이템을 소비해야함

함수로 아이템 사용하는 함수 하나 만들어둘 필요가 있겠다
그러면 스킬배우는것등등도 거기에 넣어주면 이쁠까?
Menu헤더만들장
*/