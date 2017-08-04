#include "ItemDB.h"
#include"Item.h"
decltype(auto) Item_db_Init()
{
	std::unordered_map<int, Item*> IDB;

	IDB.insert(std::make_pair(0, new Equipment(1000, "목도", static_cast<int>(ITEM_TYPE::WEAPON), { 1,2 })));
	IDB.insert(std::make_pair(1, new Equipment(1100, "나무방패", static_cast<int>(ITEM_TYPE::SHIELD), { 0,0 }, 1)));

																			//id, name, type, atk, def, hp, mp, need_lv, usable
	IDB.insert(std::make_pair(2, new Consume(500, "기초체력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 6, 0, 0, true)));
	IDB.insert(std::make_pair(3, new Consume(501, "기초마력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 6, 0, true)));
	IDB.insert(std::make_pair(4, new Consume(550, "투척가시", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 5, 0, 0, true)));
	IDB.insert(std::make_pair(5, new Equipment(1200, "투구", static_cast<int>(ITEM_TYPE::HELMET), { 0,0 },1, -1 )));
	IDB.insert(std::make_pair(6, new Equipment(1300, "나무갑옷", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 0, 5, 5)));
	IDB.insert(std::make_pair(7, new Equipment(1400, "부츠", static_cast<int>(ITEM_TYPE::BOOTS), { 0,0 }, 2, 2, 2)));

	IDB.insert(std::make_pair(8, new Consume(502, "체력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 10, 0, 0, true)));
	IDB.insert(std::make_pair(9, new Consume(503, "마력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 10, 0, true)));
	IDB.insert(std::make_pair(10, new Consume(551, "화살", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 11, 0, 0, true)));
	IDB.insert(std::make_pair(11, new Equipment(1001, "녹슨 칼", static_cast<int>(ITEM_TYPE::WEAPON), { 3,5 })));
	IDB.insert(std::make_pair(12, new Equipment(1101, "아르마딜로껍질", static_cast<int>(ITEM_TYPE::SHIELD), { -2,-4 }, 3)));
	IDB.insert(std::make_pair(13, new Equipment(1201, "군용투구", static_cast<int>(ITEM_TYPE::HELMET), { 0,1 }, 2, -5,-2)));
	IDB.insert(std::make_pair(14, new Equipment(1301, "철갑옷", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 3, 5, 0)));
	IDB.insert(std::make_pair(15, new Equipment(1401, "도적의 부츠", static_cast<int>(ITEM_TYPE::BOOTS), { 3,3 }, 0, 0, 5)));

	IDB.insert(std::make_pair(16, new Consume(504, "중급체력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 13, 0, 0, true)));
	IDB.insert(std::make_pair(17, new Consume(505, "중급마력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 13, 0, true)));
	IDB.insert(std::make_pair(18, new Consume(552, "폭약", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 18, 0, 0, true)));
	IDB.insert(std::make_pair(19, new Equipment(1002, "드워프식 철검", static_cast<int>(ITEM_TYPE::WEAPON), { 7,14 },1)));
	IDB.insert(std::make_pair(20, new Equipment(1102, "철제 방패", static_cast<int>(ITEM_TYPE::SHIELD), { 0,0 }, 4,2)));
	IDB.insert(std::make_pair(21, new Equipment(1202, "데몬의 뿔", static_cast<int>(ITEM_TYPE::HELMET), { 2,2 }, 0, 5,10)));
	IDB.insert(std::make_pair(22, new Equipment(1302, "보호용 붕대", static_cast<int>(ITEM_TYPE::ARMOR), { 0,-2 }, 3, 12, 5)));
	IDB.insert(std::make_pair(23, new Equipment(1402, "명품신발", static_cast<int>(ITEM_TYPE::BOOTS), { 0,0 }, 3, 10, 10)));

	IDB.insert(std::make_pair(24, new Consume(506, "상급체력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 20, 0, 0, true)));
	IDB.insert(std::make_pair(25, new Consume(507, "상급마력회복약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 20, 0, true)));
	IDB.insert(std::make_pair(26, new Consume(553, "비수", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 25, 0, 0, true)));
	IDB.insert(std::make_pair(27, new Equipment(1003, "미스릴 대거", static_cast<int>(ITEM_TYPE::WEAPON), { 10,19 },0,5,20)));
	IDB.insert(std::make_pair(28, new Equipment(1103, "나이트 쉴드", static_cast<int>(ITEM_TYPE::SHIELD), { -1,-1 }, 6,11)));
	IDB.insert(std::make_pair(29, new Equipment(1203, "나이트 비젼", static_cast<int>(ITEM_TYPE::HELMET), { 1,3 }, 2, 0,4)));
	IDB.insert(std::make_pair(30, new Equipment(1303, "스톤 아머", static_cast<int>(ITEM_TYPE::ARMOR), { -3,-3 }, 8, 0, -5)));
	IDB.insert(std::make_pair(31, new Equipment(1403, "도박꾼의 부츠", static_cast<int>(ITEM_TYPE::BOOTS), { -50,50 } )));

	IDB.insert(std::make_pair(32, new Consume(508, "의신의 비약", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 50, 50, 0, true)));
	IDB.insert(std::make_pair(33, new Consume(554, "죽창", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 999, 0, 0, true)));
	IDB.insert(std::make_pair(34, new Equipment(1004, "수리검", static_cast<int>(ITEM_TYPE::WEAPON), { 18,26 },-3)));
	IDB.insert(std::make_pair(35, new Equipment(1104, "드래곤 쉴드", static_cast<int>(ITEM_TYPE::SHIELD), { 4,4 }, 10,5,15)));
	IDB.insert(std::make_pair(36, new Equipment(1204, "수호자의 투구", static_cast<int>(ITEM_TYPE::HELMET), { 0,5 }, 5, 5,10)));
	IDB.insert(std::make_pair(37, new Equipment(1304, "기묘한 갑옷", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 0, 40, 40)));
	IDB.insert(std::make_pair(38, new Equipment(1404, "닌자 부츠", static_cast<int>(ITEM_TYPE::BOOTS), { 6,6 }, 5,16,23)));

	return IDB;
}

Item* item_Init(int val)
{
	auto DB = Item_db_Init();
	//임의의 아이템으로 초기화
	Item* Item = DB.at(val);
	return Item;
}