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
bool Skill_Calc(Iskill *Magic, CChara *Hero, std::queue<std::string> *clerk);//�÷��̾��
void Attack(CChara * Attacker, CChara * Defender, std::queue<std::string> *clerk);
//�켱 ��ų�� choice�� �ؾ���? 
//�ٵ� �Ʊ����� ���� ��������� ����?
//�׷��� ��ų������ ���ο��� ��Ȳ������ �ٸ�ȿ���� �ɰ���
//���࿡ ���� ����̸� �����ϴ°� �ƴϰԵǴµ�? 
//�����δ� ������ -������ ���ϴ¼��̴� �׳ɾ��ÿ� �־��
void Show_Cast(CChara  Caster, std::vector<Iskill*> *Temp, std::queue<std::string> *clerk);


decltype(auto) choice_Mob(std::vector<Monster*> Enemys,std::queue<std::string> *clerk);
//������ ���� ���� <�������ΰ� ��������������.. �̸��� ������ؼ�

void Item_get(Player *Me, std::vector<std::pair<int, int>> item_Drop);