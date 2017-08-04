#include "Battle.h"
#include"Monster.h"
#include"Chara.h"
#include"Skill.h"
#include"WindowsFunc.h"
#include"Screen.h"
#include"Enums.h"
#include"Menu.h"
#include"ItemDB.h"

#include<iostream>
//#include<random>//빠질듯
#include<sstream>
#include<string>
/*이제 몬스터가 아이템을 드랍하게 해볼까
아니면 상태이상을 먼저만들까
그것도아니면 장비부터구현할까
*/
decltype(auto) choice_Mob(std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	int choice;
	std::ostringstream oss;
	//반복문을 for(i; i<size로 바꾸고 해당 몬스터가 살아있을경우에만 카운팅되도록바꾸자
	//몬스터 최대수를 만들고,거기 몬스터중에 죽은 몬스터는 false로 두는식은?
//	int Max_count = Enemys.size();
	Write(oss << "대상을 선택해 주세요 : ",clerk);
	int count = 1;
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			Write(oss << count << " : 이름 : " << i->get_name(), clerk);// Name;
		count++;
	}//초이스는역시 -1해야지
	Read(clerk);
	while (1)
	{
		choice = input();
	choice -= 1;
	if (choice < 0 || choice >= Enemys.size())
	{
		continue;
	}
	else if (Enemys.at(choice)->get_Pos_Hp() <= 0)
		continue;
	return static_cast<CChara*>(Enemys.at(choice));
	}
}
void Item_get(Player * Me, std::vector<std::pair<int, int>> item_Drop)
{//아이템 드롭은 포인터일필요x Me에다가 추가할거고 얜영향x
	std::ostringstream oss;
	for (int i = 0; i < item_Drop.size(); i++)
	{//해당 아이템 테이블을 서치
		if (item_Drop[i].first == NULL && item_Drop[i].second == NULL)
			continue;
		else
		{//아이템이있을경우 랜덤시작
			if (item_Drop[i].second >= Random_Gen(1, 950))
			{//만약 second가 랜덤 1~100보다 크게된다면
				Item * get = item_Init(item_Drop[i].first);
//				Me->inventory_change() 아이템받아야하는데
				Write(oss << "아이템 획득 ! : "<< get->get_name(),Me->get_clerk());
				Me->inventory_change( get, 1);
			}
		}
	}
}
//상황에따라 clerk가 *나 &를 달아야함 
void Show_Enemys(std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			i->Show(clerk);
	}
}

bool kill_check(std::vector<Monster*> Enemys)
{
	for (auto& i : Enemys)
	{
		if (i->get_Pos_Hp() > 0)
			return false;
	}
	return true;
}

bool Battle_Main(CChara * Me, std::vector<Monster*> Enemys, std::queue<std::string> *clerk)
{
	std::ostringstream oss;
	if(Enemys.size() > 1)
	Write(oss << "앗 ! 야생의 "<< Enemys[0]->get_name() << "무리가 싸움을 걸어왔다!", clerk);
	else
		Write(oss << "앗 ! 야생의 " << Enemys[0]->get_name() << "(이)가 싸움을 걸어왔다!", clerk);
	do
	{
		Me->Show();
		gotoxy(0, 0);
//		CLEAR(40);
		{
			int select;
			Show_Enemys(Enemys,clerk);

			Write(oss << "1. 공격 2. 스킬 3. 아이템사용", clerk);
			Read(clerk);

			select = input();
//			select -= 1;
			switch (select)
			{
			default:
			case 1: //std::cout << "" 초이스 하나 만드는게 좋겠다
			{
				if (Enemys.size() > 1)
					Attack(Me, choice_Mob(Enemys,clerk), clerk);//이결과를 던져야함
				else
					Attack(Me, Enemys.front(), clerk);
				break;
			}
			case 2: 
			{
				//여기 아래를 빼갈거같다 이걸빼서 그 스킬슬롯에 넣어둠
				//그다음에 거기서 i를 입력시키고 Temp에 위배되면 컨티뉴?
				std::vector<Iskill*> Temp = Me->Get_Skills();
				Show_Cast(*Me, &Temp, clerk);
				Read(clerk);
				if (Temp.size() != 0)
				{
					for (;;)
					{
						select = input();
						select -= 1;
						if (select == Temp.size())
						{
							Temp.erase(Temp.begin(), Temp.end());
							break;
						}
						else if (select < 0 || select > Temp.size())
							continue;
						else
						{
							if (Skill_Calc(Temp[select], Me,clerk) )
							{
								if (Temp[select]->Get_Non())
									Temp[select]->applySkill(Me, Me, clerk);
								else if (Enemys.size() > 1)//몹이 2마리이상
									Temp[select]->applySkill(Me, choice_Mob(Enemys, clerk), clerk);
								else
									Temp[select]->applySkill(Me, Enemys.front(), clerk);
							}
							else
							{
								Read(clerk); continue;
							}
							break;
						}
					}
				}
				if( Temp.size() == 0 || select == Temp.size()) continue;
				

				break;
			}
			//케이스 탈출

			case 3://아이템사용
			{
				//일단 아이템 받고 그 아이템이 던지는거면 choicemob하던가함
				//아이템은 방어에 영향을 받게할거임
				Item *use_item = get_Item_use(static_cast<Player*>(Me), true);
				//잘되네?
				if (use_item->get_id() == NULL)
					continue;
				else if (use_item->get_type() >= (int)ITEM_TYPE::CONSUME)
					static_cast<Player*>(Me)->inventory_change(use_item, -1);

				if (use_item->get_type() == static_cast<int>(ITEM_TYPE::CONSUME))
				{
					use_item->Use(Me);
					if (use_item->get_value().first != 0 &&
						use_item->get_value().second != 0)
						Write(oss << "체력이 " << use_item->get_value().first << ", 마력이 "
							<< use_item->get_value().second << "회복 되었다!", clerk);
					else if (use_item->get_value().first != 0)
						Write(oss << "체력이 " << use_item->get_value().first
							<< "회복 되었다!", clerk);
					else
						Write(oss << "마력이 " << use_item->get_value().second
							<< "회복 되었다!", clerk);
					break;
				}
				else if (Enemys.size() > 1)
					use_item->Use(choice_Mob(Enemys, clerk));
				else
					use_item->Use(Enemys.at(0) ) ;
				Write(oss <<use_item->get_name()<<"(를)을 던져"<< 
					use_item->get_value().first << "데미지를 주었다!",clerk);
				break;
			}
			}

			for (auto& i : Enemys )
			{
				if (i->get_Pos_Hp() >= 0)
				{
					int Mob_sel = Random_Gen(0, 10);//일단 이렇게 하고 0이면 스킬쓰게 하고싶음 + 몬스터 모두가 공격한다
					switch (Mob_sel)
					{
					default:
					case 0: Attack(i, Me , clerk); break;
					}
				}
			}
			Read(clerk);
			//위에저거 보기 어려우면 그냥함수로 만들도록
		}
		if (Me->get_Pos_Hp() <= 0)
		{
			Write(oss << "의식이 점점 흐려진다..." , clerk);

			Read(clerk);
			return false;
		}
	} while (!kill_check(Enemys));

	int exp_sum = 0;
	for (auto& i : Enemys)//for가 너무 남발되는거같음//아이템도 여기서?
	{//함수로 분리하면 관리가편하겠지

		//매개로 여기서 아이템겟을 받기로하자 그아이템겟을 매개변수로받고
		//그러면 에너미사이즈 반복을 1개는 줄이잖아
		Item_get(static_cast<Player*>(Me), i->get_drop_Item());

		exp_sum += i->get_exp();
	}
	//여기에 전리품도 지껄이게하자

	Write(oss << "승리 ! " << exp_sum << " 경험치 획득! ", clerk);

	Read(clerk);
	Me->Set_Exp(exp_sum);
	Sleep(500);//바뀔지 모르는애

	return true;
}
int Damage_Calc(CChara * Actor,int enemy_def)
{
	auto Atk = Actor->get_Atk();

	int damage = Random_Gen(Atk.first, Atk.second);
	
	damage = (damage - enemy_def) ;
	if (damage <= 0)
		return 1;
	return damage;
}

//스킬의 데미지 뽑아내기
bool Skill_Calc(Iskill * Magic, CChara *Hero, std::queue<std::string> *clerk)
//이걸 플레이어가 계산한번하고 실행하게하자
//몬스터도 할수있을거 같은데
{
	int m_Atk;
	int Pay = Magic->Get_Cost();
	int Type = Magic->Get_Type();
	bool Peace = Magic->Get_Non();

	std::ostringstream oss;
//m_Atk로 Magic을 반환받음
	if (Type == (int)Ability::STR)
	{
		if (Hero->get_Pos_Hp() <= Pay)
		{
			Write(oss << "체력이 부족합니다!", clerk);
			return false;
		}
		Hero->Set_Hp(-Pay);
	}
	else
	{
		if (Hero->get_Pos_Mp() < Pay)
		{
			Write(oss << "마력이 부족합니다!", clerk);
			return false;
		}
		Hero->Set_Mp(Pay);
	}

//	m_Atk = Magic->applySkill(Hero);

	
	return 1;
}

void Attack(CChara * Attacker, CChara * Defender, std::queue<std::string> *clerk)
{//플레이어 이름이 필요함 구성은 xx의 공격! yy에게 n데미지!
//그리고 이걸 복사해 먹어야함
	int Damage = Damage_Calc(Attacker, Defender->Get_Def());

	std::ostringstream oss;
	Write(oss << Attacker->get_name() << "의 공격!" << Defender->get_name() << "에게 " << Damage << "데미지를 입혔다!", clerk);

	Defender->Set_Hp(-Damage);
}

void Show_Cast(CChara Caster,std::vector<Iskill*> *Temp,std::queue<std::string> *clerk)
{//이렇게 한이유는 간단함 스킬을 보여줄녀석은 얘뿐임
	//이걸 호출해서 Temp의 스킬을넣고 거기서 또 스킬입력하게ㅇ..
	std::ostringstream oss;
//	Temp = Caster.Get_Skills();
	int select;
	for (auto i = Temp->begin(); i != Temp->end();)
	{
		if ((*i)->Get_Lean() == false)
			i = Temp->erase(i);
		else ++i;
	}
	if (Temp->size() == 0)
	{
		Write(oss << "배운스킬이 없습니다!", clerk);
		return;
	}
	else
	{
		int i;
		for (i = 0; i < Temp->size(); i++)
		{
			if ((*Temp)[i]->Get_Type() != static_cast<int>(Ability::STR))
				Write(oss << i + 1 << ": " << (*Temp)[i]->Get_Name() << " 소모마나: " <<
					(*Temp)[i]->Get_Cost(), clerk);
			else
				Write(oss << i + 1 << ": " << (*Temp)[i]->Get_Name() << " 소모체력: " <<
				(*Temp)[i]->Get_Cost(), clerk);
		}
		Write(oss << i + 1 << ": 나가기", clerk);
		Write(oss << "사용할 스킬을 입력해주세요", clerk);

	}
}
