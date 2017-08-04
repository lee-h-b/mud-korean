#pragma once
#include<string>
#include<queue>

//���� �ִ°͵��� Skill�� �����ϰ� �ϵ����ϱ�
//���� �����ִ°� ��ų �ߵ��ϵ��ϸ����ǰ�
//Battle���� ��ų�����ϴ� �Լ��� �ϳ� ������ �ɰŰ���th
class Monster;
class Player;
class CChara;

//�������ϸ� �ǹ�����? �κ��丮~ �켱 �������� ���� �����ϰ� �κ��丮�� ������ show�� ¥�߰���
//�κ��丮�� list�� ���ϰŰ���
class Item
{
protected:
	unsigned int ID;//���̵� ���� ����������? ����̰� �ش� ���̵� �־�� ã���Ҷ� �����̶� ��������������
	std::string name;
	short type;
	std::pair<short,short> ATK;
	short DEF;

	//�۽�Ʈ�� ü�� ������� ����
	std::pair<int, int> Value;

	//����,DEF�ϳ��� ������ ������
	short Need_Lv;//�ٸ��͵�? no ������
	unsigned short Ea;//����
					  //������� �����°� �����Լ�
	bool usable;//�־�������� ��

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
	void gain_item(int ea = 0);//ea����ŭ �ش� �������� ��´�
	virtual void Use(CChara *me) {}; //�Ű��� �ʿ��ϴ� �Ҹ�ǰ�̴� ���� �ߴµ� �װ� �Ⱦ��� ������
								  //use�� ���̵ɼ���, �Ʊ��� �ɼ��� ������
								  //type������ �ٸ������ؾ���
	virtual void Use(Monster* Mob) {};

	virtual void Equip(Player *me) {};
	virtual void UnEquip(Player *me,Item* that) {};//��ü�Ұ� ������ ���������
									 //�̹� ������ �������ǰ��� �Ű��� �ʿ��������� �ֳĸ� me�� �ִ°� ����Ǵϱ� �̷��ԵǸ� get���� �Ű������� �־�߰���? �ش�Ÿ������?
	virtual void Show(std::queue<std::string> *clerk, int num) {};
	//�������� ǥ���ؾ��Ұ� �ٸ��� ����ȭ
	void Item_Init();
	void Item_Init(int id, std::string name = 0, short type = 0, std::pair<short, short> atk = { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false);
	
						//������ �ҰŰ�����
						//���� �����޴� ����� ���޴��� ���� �̾Ƴ��߰���
						//�뵵�� ���� �ٸ��� �Լ��� ȣ���ϰ� �ϰ�ʹ�
						//�׷��� �Լ�1�� ����� ���Լ��� �Ű������� bool�ְ� �̰� �����̸� ~~��
						//���̸� oo�� ����ϰ� ����� �ǰ���?
						//�ϴ� Item�� Show�� �ö󰡴´ɷ�ġ�� �˷��ְ�(�� 0�̸� ���°�)
						//�Ҹ�ǰ�̸� ������ �˷��ְ� ȸ������ Hp : Mp : �̷������� ��������
};

//���� ���� ��� ���� �Ź� ���� ���� ��������
//�����ǻ��� �������� ������
/*������ ���? �����ֳ� �Լ� ���δ� �����־����?
������ �ߺ����� �ȵǰ��ϴ°žƴұ�
1.�����۹迭�� [0]~ [5]�� ����� n(Ÿ��)�� ���� �ִ��� Ȯ��, ������ move, ������ swap�ϱ�?

2.��Ŭ�������� ����� �ش� Ŭ������ �´� Ÿ�Կ� ���� null�� �ƴ��� Ȯ��, ������ move,������ swap?
�ΰ��� ����ū���̴� Ŭ�������� �������� �������� ����������
�������� ������ ������?
�ϴ� �迭�� ����� �׹迭n�� ���� �ִ°����ηΰ����ϵ����Ԥ���

type�� enum����

//�ڲ� �����ϴ°��ִٸ� �̾������� ���� ������ �׾������� �Ҹ��ؾ��ϴ°� �ƴ϶��
//�������� ���ʿ� �ϳ��� ����Ʈ�� �Ŵ��� ���̺�εΰ� �׾������� ���� �κ��丮�� ����
//�Ѵٸ� �׶����� �����߿� �ִ� ������ ��� �Ǵ°�
*/
class Equipment : public Item
{//��� �����ϴ°ͺ��͸�����
protected://�������� ������?
public:

	Equipment();
	//show�� ������ �����ְ�(�׷��� ���ο� vector�� ����Ʈ�ϳ� ����Եǰ���) �������ϰ�
	Equipment(int id, std::string name = 0, short type = 0, std::pair<short, short> atk = { 0,0 }, short def = 0, short hp = 0, short mp = 0, short need_lv = 0, bool usable = false)
		:Item(id, name, type, atk, def, hp, mp, need_lv, usable)
		{}
	//�� ���� ���� �ɷ�ġ�� �÷��� ���� �̹� �����ִٸ� �ش������������� ��
	//���� �������� �ɷ�ġ�� �����ϴ°� UnEquip
	virtual void Equip(Player *me) override;
	void Add_Stat(Player *me,bool Add);
	//���⿡ me���޴������� ��� �������� ������� �ɷ�ġ�� �ٽû� 
	//�׷��� ���� �����ִ°� ���� �������
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