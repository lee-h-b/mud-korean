#pragma once
#include <vector>
#include <string>
#include<queue>
class Iskill;
class Player;
class CChara;
class Monster;

void Show_Enemys(std::vector<Monster*> Enemys, std::queue<std::string> *clerk);
bool kill_check(std::vector<Monster*> Enemys);
bool Battle_Main(CChara *Me, std::vector<Monster*> Enemys, std::queue<std::string> *clerk);
int Damage_Calc(CChara * Actor, int enemy_def);
bool Skill_Calc(Iskill *Magic, CChara *Hero, std::queue<std::string> *clerk);//플레이어용
void Attack(CChara * Attacker, CChara * Defender, std::queue<std::string> *clerk);
//우선 스킬도 choice를 해야지? 
//근데 아군에게 쓰는 기술일지도 모르지?
//그러면 스킬어택은 내부에서 상황에따라 다른효과가 될거임
//만약에 내가 대상이면 어택하는게 아니게되는데? 
//실제로는 나에게 -공격을 가하는셈이니 그냥어택에 넣어도됨
void Show_Cast(CChara  Caster, std::vector<Iskill*> *Temp, std::queue<std::string> *clerk);


decltype(auto) choice_Mob(std::vector<Monster*> Enemys,std::queue<std::string> *clerk);
//몬스터의 값을 먹음 <사이즈인게 더나을꺼같지만.. 이름도 얻기위해서

void Item_get(Player *Me, std::vector<std::pair<int, int>> item_Drop);