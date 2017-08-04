#include<algorithm>
#include<sstream>
#include"Skill.h"

#include"Enums.h"
#include"Screen.h"
#include"WindowsFunc.h"

//#include "ALL.h"

#include<vector>//한번 벡터로 해보자



//template<typename T>
void init(std::vector<Iskill*> *book)
{
	book->push_back(new Target("파이어볼트", 0.6, 8, 1, (int)Ability::INT, false, 0));
	book->push_back(new Target("이그니션", 1.09, 12, 2, (int)Ability::INT, false, 0, "파이어볼트"));
	book->push_back(new Target("스피드스타", 0.55, 10, 1, (int)Ability::DEX));
	book->push_back(new Target("돌던지기", 0.51, 11, 1, (int)Ability::STR));
	book->push_back(new Self("힐", 2, 10, 1, (int)Ability::INT));
	book->push_back(new Self("희생", 3, 7, 2, (int)Ability::STR, true, 0, true, "힐"));
}
std::string Iskill::Get_Name()
{
	return this->Name;
}
bool Iskill::Get_Non()
{
	return this->Non;
}
bool Iskill::Learn(std::vector<Iskill*> book, std::queue<std::string> *chat)
{//호출방식 sel을 입력받으면 그book[sel]로 호출하고 매개로 book을 줄거다
 //선행필요는 다른곳에서 확인해먹던가 어떻게든 해야함
 //매개 쓰게되려나
	std::ostringstream oss;
 //	bool can = false;
	for (auto check : book)
	{
		//내가 2티어미만 스킬 이거나 체크의 필요스킬이 비어있음
		if (check->Need.empty() && tier < 2)
			break;
		//체크의 겟네임이 니드랑 똑같은은데 이걸 배웠다면
		if (check->Get_Name() == Need && check->lean == true)
			Need.clear();//필요스킬의 조건을 해결한거니 청소
		//안배웠으면 탈출
		else if (check->Get_Name() == Need && check->lean == false)
			break;
	}
	if (lean == false && this->Need.empty())
	{
		this->Level++;
		this->lean = true;
		Write(oss << this->Name << "을 성공적으로 배웠습니다!", chat);
	}
	else if (Need.empty() == false)
	{
		Write(oss << "선행스킬이 필요 합니다",chat );
		return false;
	}
	else if (lean == true)
	{
		this->Skill_Up();
		this->Level++;
		//		return false;
		Write(oss << this->Name << "의 레벨업!", chat);
	}
	return true;

}
void Iskill::Show(std::queue<std::string> *chat, int this_num)
{
	std::ostringstream sen;
	//습득창에서는 해당스킬을 보여줄때, lean이 참이면 안보이도록하자

		//문제하나 있겠다 지금 인자로 받는 순서 아마 몇개는 합체시켜야할거임
	Write(	sen << this_num +1<< ": " << this->Name << " 위력 : " << this->Damage <<
		 " 비용 : " << this->cost << " 타입 : " << STAT_LIST[this->type],chat );

//	Write(	sen << " 비용 : " << this->cost << " 타입 : " << STAT_LIST[this->type],chat );
		//비용없는 녀석은 없을거임
		if (tier >= 2 && this->lean == false)
			Write( sen << "└선행 : " << this->Need ,chat );
		else if (this->lean == true)
			Write( sen << " 레벨 : " << this->Level, chat);
		else;
		//	std::cout << std::endl; << 필요할까?
			//이건 큐로 넣어서 할거임 이것도 겁나비틀겠는데
			//매개로 
}
int Iskill::Get_Cost()
{
	return this->cost;
}
int Iskill::Get_Type()
{
	return this->type;
}
int Target::applySkill(CChara *Caster, CChara *Target, std::queue<std::string> *clerk)
{
	std::ostringstream oss;
	//이 스킬타입에 따라 다른 스킬이 나감ㅇ
	//아마 이 어플라이 스킬을 개선해야 했던거같은데
	Hero_Stat = Caster->get_stat(this->type);

	int result = Random_Gen(this->Damage * Hero_Stat * 0.78, Damage * Hero_Stat * 1.058) - Target->Get_Def();
	result += Damage * Hero_Stat * 0.1;

	Write(oss << Name << "! " << Target->get_name()	<< "에게 " << result
		<< "만큼의 데미지!", clerk);
	Target->Set_Hp(-result);

	return 0;
}
void Target::Skill_Up()
{
	this->Hero_Stat += 1;
	this->Damage += 0.175;
	this->cost += 1;
}

int Self::applySkill(CChara *Caster, CChara *Target, std::queue<std::string> *clerk)
{
	Hero_Stat =Caster->get_stat(this->type);
	int result;
	std::ostringstream oss;
	if (this->Mana_heal == false)
	{//이렇게되면 그냥 힐을 반환하고 타입에따라 결정하게되겠음
		result = Damage * Hero_Stat;
		
		Target->Set_Hp(Damage * this->Hero_Stat);//체력회복 
		//아래의 std::cout을 입력시켜야하게됨 따라서 applyskill의 명령을따도록
		Write(oss << Name << " !" << result << 
			"만큼 회복 되었다!", clerk);

	}
	else//마나회복
	{
		result = Damage * Hero_Stat * 0.6;
		
		Target->Set_Mp(-Damage * this->Hero_Stat *0.6);
		Write(oss << Name << " !" << result <<
			"만큼 마력이 회복 되었다!", clerk);
	}
	//위의조건에 있는 문장을 외부로 빼내야함
	return 0;
}

void Self::Skill_Up()
{
	this->cost += 2;
	this->Hero_Stat += 1;
	this->Damage += 0.2;
}
