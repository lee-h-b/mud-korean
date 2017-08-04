#include<algorithm>
#include<sstream>
#include"Skill.h"

#include"Enums.h"
#include"Screen.h"
#include"WindowsFunc.h"

//#include "ALL.h"

#include<vector>//�ѹ� ���ͷ� �غ���



//template<typename T>
void init(std::vector<Iskill*> *book)
{
	book->push_back(new Target("���̾Ʈ", 0.6, 8, 1, (int)Ability::INT, false, 0));
	book->push_back(new Target("�̱״ϼ�", 1.09, 12, 2, (int)Ability::INT, false, 0, "���̾Ʈ"));
	book->push_back(new Target("���ǵ彺Ÿ", 0.55, 10, 1, (int)Ability::DEX));
	book->push_back(new Target("��������", 0.51, 11, 1, (int)Ability::STR));
	book->push_back(new Self("��", 2, 10, 1, (int)Ability::INT));
	book->push_back(new Self("���", 3, 7, 2, (int)Ability::STR, true, 0, true, "��"));
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
{//ȣ���� sel�� �Է¹����� ��book[sel]�� ȣ���ϰ� �Ű��� book�� �ٰŴ�
 //�����ʿ�� �ٸ������� Ȯ���ظԴ��� ��Ե� �ؾ���
 //�Ű� ���ԵǷ���
	std::ostringstream oss;
 //	bool can = false;
	for (auto check : book)
	{
		//���� 2Ƽ��̸� ��ų �̰ų� üũ�� �ʿ佺ų�� �������
		if (check->Need.empty() && tier < 2)
			break;
		//üũ�� �ٳ����� �ϵ�� �Ȱ������� �̰� ����ٸ�
		if (check->Get_Name() == Need && check->lean == true)
			Need.clear();//�ʿ佺ų�� ������ �ذ��ѰŴ� û��
		//�ȹ������ Ż��
		else if (check->Get_Name() == Need && check->lean == false)
			break;
	}
	if (lean == false && this->Need.empty())
	{
		this->Level++;
		this->lean = true;
		Write(oss << this->Name << "�� ���������� ������ϴ�!", chat);
	}
	else if (Need.empty() == false)
	{
		Write(oss << "���ེų�� �ʿ� �մϴ�",chat );
		return false;
	}
	else if (lean == true)
	{
		this->Skill_Up();
		this->Level++;
		//		return false;
		Write(oss << this->Name << "�� ������!", chat);
	}
	return true;

}
void Iskill::Show(std::queue<std::string> *chat, int this_num)
{
	std::ostringstream sen;
	//����â������ �ش罺ų�� �����ٶ�, lean�� ���̸� �Ⱥ��̵�������

		//�����ϳ� �ְڴ� ���� ���ڷ� �޴� ���� �Ƹ� ��� ��ü���Ѿ��Ұ���
	Write(	sen << this_num +1<< ": " << this->Name << " ���� : " << this->Damage <<
		 " ��� : " << this->cost << " Ÿ�� : " << STAT_LIST[this->type],chat );

//	Write(	sen << " ��� : " << this->cost << " Ÿ�� : " << STAT_LIST[this->type],chat );
		//������ �༮�� ��������
		if (tier >= 2 && this->lean == false)
			Write( sen << "������ : " << this->Need ,chat );
		else if (this->lean == true)
			Write( sen << " ���� : " << this->Level, chat);
		else;
		//	std::cout << std::endl; << �ʿ��ұ�?
			//�̰� ť�� �־ �Ұ��� �̰͵� �̳���Ʋ�ڴµ�
			//�Ű��� 
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
	//�� ��ųŸ�Կ� ���� �ٸ� ��ų�� ������
	//�Ƹ� �� ���ö��� ��ų�� �����ؾ� �ߴ��Ű�����
	Hero_Stat = Caster->get_stat(this->type);

	int result = Random_Gen(this->Damage * Hero_Stat * 0.78, Damage * Hero_Stat * 1.058) - Target->Get_Def();
	result += Damage * Hero_Stat * 0.1;

	Write(oss << Name << "! " << Target->get_name()	<< "���� " << result
		<< "��ŭ�� ������!", clerk);
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
	{//�̷��ԵǸ� �׳� ���� ��ȯ�ϰ� Ÿ�Կ����� �����ϰԵǰ���
		result = Damage * Hero_Stat;
		
		Target->Set_Hp(Damage * this->Hero_Stat);//ü��ȸ�� 
		//�Ʒ��� std::cout�� �Է½��Ѿ��ϰԵ� ���� applyskill�� �����������
		Write(oss << Name << " !" << result << 
			"��ŭ ȸ�� �Ǿ���!", clerk);

	}
	else//����ȸ��
	{
		result = Damage * Hero_Stat * 0.6;
		
		Target->Set_Mp(-Damage * this->Hero_Stat *0.6);
		Write(oss << Name << " !" << result <<
			"��ŭ ������ ȸ�� �Ǿ���!", clerk);
	}
	//�������ǿ� �ִ� ������ �ܺη� ��������
	return 0;
}

void Self::Skill_Up()
{
	this->cost += 2;
	this->Hero_Stat += 1;
	this->Damage += 0.2;
}
