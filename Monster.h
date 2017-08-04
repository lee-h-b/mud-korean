#pragma once
#include<vector>
#include<queue>

#include "Player.h"
class Monster :	public CChara
{
private: 
	bool find = false;
	short direction;
	short sight;
	float delay;
	//dropItem�� ù��°�� ������ Ű���̰� 2��°�� Ȯ����
	std::vector<std::pair<int, int>> drop_Item;
	

public:
	//�����Ұ� Ŀ�ǵ�������� ���� �ڽſ��� �̵��ϵ��� ���� ����
	//2.������ ��Ʋ�ɵ��� <<�̰� ���� �������� ������ �����ʿ��� ����ϴ°� �´ٰ�

	Monster(std::string name,char b, char **MAP, int MAP_SIZE, int hp,int mp,int atk, int atk_m,int def,int exp,int color, std::vector<std::pair<int, int>>Drop,short sight = 5)
		:CChara(name,b, MAP, MAP_SIZE,exp), sight(sight)
	{
		drop_Item = Drop;
		this->color = color;
		//���� ���߿��޵��� ���ִ� �����ڰ� �ʿ��ϴ�
		delay = 0.f;
		this->name = name;
		Chara_Init(hp, mp, atk, atk_m, def);
//		exp = 0;
	}
	Monster(std::string name, char b, int hp, int mp, int atk, int atk_m, int def, int exp, int color, std::vector<std::pair<int, int>>Drop, short sight = 5)
		:CChara(name,b,exp),sight(sight)
	{
		drop_Item = Drop;
		this->color = color;
		delay = 0.f;
		Chara_Init(hp, mp, atk, atk_m, def);
		//�̷��Լ��� �θ��� ���Ŀ� �ؾߵȴ�
		//�׷� ���� ���� ���� ����� 
		//�̰� ȣ���Ҷ� ���ÿ� ������ �ϵ��� ¥�߰���
	}

	~Monster();
	
	
	//�ش� ĳ���� x or y��ġ�� Ư����(�ϴ� �ӽ÷� 5)���̰� �׾ȿ� ���ع��� ���ٸ�
	//�Ѿƿü� �ֵ��� �ϴ� ���𰡰� �ʿ���
	decltype(auto) get_drop_Item() { return drop_Item; }
	void detect(CChara * Actor);
	void MoveMent() override; //�̵���� �Ű��� ���� ������
	void set_xy_mob();//���� �ڽ��Ǹʿ��� ��������ġ�̵�, #�����°��� ��ġ�Ѵ�
	void Show(std::queue<std::string> *clerk);

};
