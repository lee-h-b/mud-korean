#pragma once

#include<string>
#include<sstream>
#include<vector>
class Item;
class Player;
class CChara;
//해야하는거
//소모품아이템 3개정도 만들기
//1.소모품아이템사용되는지 실험
//회복1개,투척1개
//2간단하게 1층 몬스터들 전부가 그소모품아이템을 무조건드랍
//
//인배틀이 없는이유는 밖에서 이미 인배틀을 알기 때문.얘는 그저 아이템을 써줌
//ㄴ정정 얘가 아이템을쓰는 실질적인얘임 캐릭(쓰는애)이 아이템을 사용하는
//무언가를 부르고 그아이템의 use의매개로 타겟을 넣어버린다
//아이템의 경우 일단 해당아이템을 고르고, 그아이템이 Throw형이면
//초이스에너미, 아니면 자기자식에게 쓰도록
void Menu_use(Player * user);
//배틀에서 3번으로 호출하는거랑 논배틀일때 호출하는거 2개만든다
//3번의경우 true로해서 호출하는데 item클래스가 받음
Item* get_Item_use(Player *me,bool In_Battle);//아이템 인벤토리자체는 외부에서 꺼냄
void Menu_Equipment(Player *user);