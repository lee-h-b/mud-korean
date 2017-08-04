#pragma once

#include<vector>
#include<string>

#include"Player.h"
class Iskill
{
protected:
	int type;
	int Level;
	std::string Name;
	int Hero_Stat;
	double Damage;
	int cost;
	int tier;
	std::string Need;
	bool lean;
	bool Non;
	short duration;
	double per = 0;
public:
	Iskill(std::string name, double damage, int cost, int tier, bool Non,
		short duration, const std::string code = "")
		:Name(name), Damage(damage), cost(cost), tier(tier), duration(duration),
		Need(code), Non(Non)
	{
		lean = false;
		Level = 0;
	}
	bool Get_Non();
	bool Get_Lean() { return this->lean; }

	virtual int applySkill(CChara *Caster, CChara *Target, std::queue<std::string> *clerk)
	{
		return 0;
	}
	virtual double Get_Per()
	{
		return 0;
	}

	//�갡�������� �ְ� ��뵵 �ϰ� ���� ���ϰ� ��
	virtual void Skill_Up() {}
	void Show(std::queue<std::string> *chat, int this_num);
	bool Learn(std::vector<Iskill*> book, std::queue<std::string> *chat);
	int Get_Cost();
	int Get_Type();
	std::string Get_Name();

};
/*���������Լ��� ��ų�� ���밡 �Ǿ���
�׸��� �ϰ������ų�� �� ��ų�� �����ϵ����ϵ� nƼ��� n-1Ƽ���� ��ų�� ��ӹ޵�����
������ ���� �װɾ�Թ�ȯ?
��ų�� ����Ʈ�� �ؾ��ұ� �ű⼭ ���� �����? �ϰ� �����ε帮�� �ɰ�
*/

class Target : public Iskill
{
public:
	Target(std::string name, double damage, int cost, int tier,
		int type, bool Non = 0, short duration = 0, const std::string Need = "")
		:Iskill(name, damage, cost, tier, Non, duration, Need)
	{
		this->type = type;
	}
	virtual int applySkill(CChara *Caster, CChara *Target, std::queue<std::string> *clerk) override;
	virtual void Skill_Up();

};
class Self : public Iskill
{
private:
	short Mana_heal;//ü�� or���� ȸ�� 
public:
	Self(std::string name, double damage, int cost, int tier,
		int type, bool Non = 1, short duration = 0, bool h_type = 0,
		const std::string Need = "")
		:Iskill(name, damage, cost, tier, Non, duration, Need)
	{
		Mana_heal = h_type;
		this->type = type;
	}

	virtual int applySkill(CChara *Caster, CChara *Target, std::queue<std::string> *clerk) override;
	virtual void Skill_Up();

};

//template<typename T>
void init(std::vector<Iskill*> *book);


/*
����Ʈ�����ϴٸ�������
����7 ������������ּ��䰡�������¾ȵ�
����5.�ִ�ü�³ѱ��
����6 �� �������� -����? �װ� ������
*/