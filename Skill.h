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

	//얘가데미지를 주고 사용도 하고 별거 다하게 됨
	virtual void Skill_Up() {}
	void Show(std::queue<std::string> *chat, int this_num);
	bool Learn(std::vector<Iskill*> book, std::queue<std::string> *chat);
	int Get_Cost();
	int Get_Type();
	std::string Get_Name();

};
/*순수가상함수로 스킬의 뼈대가 되야함
그리고 하고싶은스킬은 이 스킬을 참조하도록하되 n티어면 n-1티어의 스킬을 상속받도록함
문제ㅡ 배우면 그걸어떻게반환?
스킬의 리스트라 해야할까 거기서 만약 배웠니? 하고 존나두드리면 될걸
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
	short Mana_heal;//체력 or마나 회복 
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
포인트부족하다말안해줌
버그7 대상을선택해주세요가제대로출력안됨
버그5.최대체력넘긴다
버그6 방어가 더높으면 -되지? 그게 엿같아
*/