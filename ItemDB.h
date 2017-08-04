#pragma once
class Item;
#include<map>
#include<unordered_map>
#include"Enums.h"

decltype(auto) Item_db_Init();
Item* item_Init(int val);
//몬스터함수에 아이템드랍을 뭘먹일지 정해주는 무언가를 만들어줄꺼임
//그리고 기존 생성자에 아이템을 추가시킬꺼고