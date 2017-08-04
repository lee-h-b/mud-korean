#pragma once
#include<string>
#include<queue>

//여기 있는것들은 Skill을 구현하고 하도록하기
//대충 집에있는건 스킬 발동하도록만들면되고
//Battle에서 스킬공격하는 함수를 하나 만들어내면 될거같음th
class Monster;
class Player;
class CChara;

//아이템하면 또문제는? 인벤토리~ 우선 장착부터 대충 구상하고 인벤토리를 보여줄 show를 짜야겠음
//인벤토리는 list로 쓰일거같음
class Item
{
protected:
	unsigned int ID;//아이디 있음 멋지지않음? 농담이고 해당 아이디가 있어야 찾기할때 조금이라도 더잘하지않을까
	std::string name;
	short type;
	std::pair<short,short> ATK;
	short DEF;

	//퍼스트는 체력 세컨드는 마나
	std::pair<int, int> Value;

	//어택,DEF하나로 묶을수 있을것
	short Need_Lv;//다른것도? no 레벨만
	unsigned short Ea;//갯수
					  //사용으로 나오는건 가상함수
	bool usable;//있어야할지도 모름

public:
	Item();
	Item(int id, std::string name = 0, short type = 0, std::pair<short, short> atk= { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false);
	~Item();
	decltype(auto) get_value(){return Value;}
	int get_type() { return type; }
	bool get_usable() { return usable; }
	int get_id() { return ID; }
	decltype(auto) get_name() { return name; }
	//	bool Equiped() { return }
	void set_Ea(short val) { Ea += val; }
	int get_Ea() { return Ea; }
	void gain_item(int ea = 0);//ea수만큼 해당 아이템을 얻는다
	virtual void Use(CChara *me) {}; //매개가 필요하다 소모품이던 뭐던 했는데 그걸 안쓰면 난감함
								  //use는 적이될수도, 아군이 될수도 있음ㅇ
								  //type에따라 다르도록해야지
	virtual void Use(Monster* Mob) {};

	virtual void Equip(Player *me) {};
	virtual void UnEquip(Player *me,Item* that) {};//대체할게 없을때 빼고싶으면
									 //이미 장착한 아이템의경우는 매개로 필요하지않음 왜냐면 me에 있는걸 빼면되니깐 이렇게되면 get에는 매개변수가 있어야겠지? 해당타입으로?
	virtual void Show(std::queue<std::string> *clerk, int num) {};
	//종류별로 표시해야할게 다르니 가상화
	void Item_Init();
	void Item_Init(int id, std::string name = 0, short type = 0, std::pair<short, short> atk = { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false);
	
						//집가면 할거같은거
						//따로 장착메뉴 만들고 사용메뉴도 만들어서 뽑아내야겠음
						//용도에 따라 다르게 함수를 호출하게 하고싶다
						//그러면 함수1개 만들고 그함수의 매개변수로 bool넣고 이게 거짓이면 ~~를
						//참이면 oo를 출력하게 만들면 되겠지?
						//일단 Item의 Show는 올라가는능력치를 알려주고(즉 0이면 없는것)
						//소모품이면 갯수를 알려주고 회복량은 Hp : Mp : 이런식으로 쓰게하자
};

//무기 방패 헬멧 갑옷 신발 포션 대충 이정도만
//ㄴ포션빼면 나머진다 유사함
/*장착은 어떻게? 별수있나 함수 전부다 돌려넣어야지?
문제는 중복장착 안되게하는거아닐까
1.아이템배열로 [0]~ [5]로 만들고 n(타입)에 값이 있는질 확인, 없으면 move, 있으면 swap하기?

2.각클래스별로 만들고 해당 클래스와 맞는 타입에 값이 null이 아닌지 확인, 없으면 move,있으면 swap?
두개의 가장큰차이는 클래스별로 나누느냐 부위별로 나누느냐임
부위별로 나눠서 뭐에씀?
일단 배열로 만들고 그배열n에 값이 있는가여부로결정하도록함ㅇㅇ

type은 enum으로

//자꾸 간과하는게있다면 이아이템을 내가 받으면 그아이템이 소멸해야하는건 아니라고봄
//아이템을 애초에 하나의 리스트나 거대한 테이블로두고 그아이템을 내가 인벤토리에 소지
//한다면 그때서야 내수중에 있단 느낌이 들게 되는거
*/
class Equipment : public Item
{//장비 장착하는것부터만들어보기
protected://뭘넣을수 있을까?
public:

	Equipment();
	//show로 장비들을 보여주고(그러면 내부에 vector나 리스트하나 만들게되겠지) 장착을하고
	Equipment(int id, std::string name = 0, short type = 0, std::pair<short, short> atk = { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false)
		:Item(id, name, type, atk, def, hp, mp, need_lv, usable)
		{}
	//그 만한 값의 능력치를 올려줌 만약 이미 낀게있다면 해당장착아이템을 뺌
	//따라서 아이템의 능력치를 감소하는건 UnEquip
	virtual void Equip(Player *me) override;
	void Add_Stat(Player *me,bool Add);
	//여기에 me를받는이유는 장비를 벗었으니 그장비의 능력치를 다시뺌 
	//그러면 내가 끼고있는것 또한 벗어야지
	virtual void UnEquip(Player *me, Item* that) override;
	virtual void Show(std::queue<std::string> *clerk, int num);
};

class Consume : public Item
{
protected:
public:
	Consume(int id, std::string name = 0, short type = 0, std::pair<short, short> atk = { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false)
		:Item(id, name, type, atk, def, hp, mp, need_lv, usable)
	{}

	//	virtual void use(CChara *me);
	virtual void Use(CChara *me);
	virtual void Use(Monster* Mob);
	virtual void Show(std::queue<std::string> *clerk,int num) ;
};