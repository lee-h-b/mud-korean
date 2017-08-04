#include "ItemDB.h"
#include"Item.h"
decltype(auto) Item_db_Init()
{
	std::unordered_map<int, Item*> IDB;

	IDB.insert(std::make_pair(0, new Equipment(1000, "��", static_cast<int>(ITEM_TYPE::WEAPON), { 1,2 })));
	IDB.insert(std::make_pair(1, new Equipment(1100, "��������", static_cast<int>(ITEM_TYPE::SHIELD), { 0,0 }, 1)));

																			//id, name, type, atk, def, hp, mp, need_lv, usable
	IDB.insert(std::make_pair(2, new Consume(500, "����ü��ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 6, 0, 0, true)));
	IDB.insert(std::make_pair(3, new Consume(501, "���ʸ���ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 6, 0, true)));
	IDB.insert(std::make_pair(4, new Consume(550, "��ô����", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 5, 0, 0, true)));
	IDB.insert(std::make_pair(5, new Equipment(1200, "����", static_cast<int>(ITEM_TYPE::HELMET), { 0,0 },1, -1 )));
	IDB.insert(std::make_pair(6, new Equipment(1300, "��������", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 0, 5, 5)));
	IDB.insert(std::make_pair(7, new Equipment(1400, "����", static_cast<int>(ITEM_TYPE::BOOTS), { 0,0 }, 2, 2, 2)));

	IDB.insert(std::make_pair(8, new Consume(502, "ü��ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 10, 0, 0, true)));
	IDB.insert(std::make_pair(9, new Consume(503, "����ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 10, 0, true)));
	IDB.insert(std::make_pair(10, new Consume(551, "ȭ��", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 11, 0, 0, true)));
	IDB.insert(std::make_pair(11, new Equipment(1001, "�콼 Į", static_cast<int>(ITEM_TYPE::WEAPON), { 3,5 })));
	IDB.insert(std::make_pair(12, new Equipment(1101, "�Ƹ������β���", static_cast<int>(ITEM_TYPE::SHIELD), { -2,-4 }, 3)));
	IDB.insert(std::make_pair(13, new Equipment(1201, "��������", static_cast<int>(ITEM_TYPE::HELMET), { 0,1 }, 2, -5,-2)));
	IDB.insert(std::make_pair(14, new Equipment(1301, "ö����", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 3, 5, 0)));
	IDB.insert(std::make_pair(15, new Equipment(1401, "������ ����", static_cast<int>(ITEM_TYPE::BOOTS), { 3,3 }, 0, 0, 5)));

	IDB.insert(std::make_pair(16, new Consume(504, "�߱�ü��ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 13, 0, 0, true)));
	IDB.insert(std::make_pair(17, new Consume(505, "�߱޸���ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 13, 0, true)));
	IDB.insert(std::make_pair(18, new Consume(552, "����", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 18, 0, 0, true)));
	IDB.insert(std::make_pair(19, new Equipment(1002, "������� ö��", static_cast<int>(ITEM_TYPE::WEAPON), { 7,14 },1)));
	IDB.insert(std::make_pair(20, new Equipment(1102, "ö�� ����", static_cast<int>(ITEM_TYPE::SHIELD), { 0,0 }, 4,2)));
	IDB.insert(std::make_pair(21, new Equipment(1202, "������ ��", static_cast<int>(ITEM_TYPE::HELMET), { 2,2 }, 0, 5,10)));
	IDB.insert(std::make_pair(22, new Equipment(1302, "��ȣ�� �ش�", static_cast<int>(ITEM_TYPE::ARMOR), { 0,-2 }, 3, 12, 5)));
	IDB.insert(std::make_pair(23, new Equipment(1402, "��ǰ�Ź�", static_cast<int>(ITEM_TYPE::BOOTS), { 0,0 }, 3, 10, 10)));

	IDB.insert(std::make_pair(24, new Consume(506, "���ü��ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 20, 0, 0, true)));
	IDB.insert(std::make_pair(25, new Consume(507, "��޸���ȸ����", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 0, 20, 0, true)));
	IDB.insert(std::make_pair(26, new Consume(553, "���", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 25, 0, 0, true)));
	IDB.insert(std::make_pair(27, new Equipment(1003, "�̽��� ���", static_cast<int>(ITEM_TYPE::WEAPON), { 10,19 },0,5,20)));
	IDB.insert(std::make_pair(28, new Equipment(1103, "����Ʈ ����", static_cast<int>(ITEM_TYPE::SHIELD), { -1,-1 }, 6,11)));
	IDB.insert(std::make_pair(29, new Equipment(1203, "����Ʈ ����", static_cast<int>(ITEM_TYPE::HELMET), { 1,3 }, 2, 0,4)));
	IDB.insert(std::make_pair(30, new Equipment(1303, "���� �Ƹ�", static_cast<int>(ITEM_TYPE::ARMOR), { -3,-3 }, 8, 0, -5)));
	IDB.insert(std::make_pair(31, new Equipment(1403, "���ڲ��� ����", static_cast<int>(ITEM_TYPE::BOOTS), { -50,50 } )));

	IDB.insert(std::make_pair(32, new Consume(508, "�ǽ��� ���", static_cast<int>(ITEM_TYPE::CONSUME), { 0,0 }, 0, 50, 50, 0, true)));
	IDB.insert(std::make_pair(33, new Consume(554, "��â", static_cast<int>(ITEM_TYPE::THROW), { 0,0 }, 0, 999, 0, 0, true)));
	IDB.insert(std::make_pair(34, new Equipment(1004, "������", static_cast<int>(ITEM_TYPE::WEAPON), { 18,26 },-3)));
	IDB.insert(std::make_pair(35, new Equipment(1104, "�巡�� ����", static_cast<int>(ITEM_TYPE::SHIELD), { 4,4 }, 10,5,15)));
	IDB.insert(std::make_pair(36, new Equipment(1204, "��ȣ���� ����", static_cast<int>(ITEM_TYPE::HELMET), { 0,5 }, 5, 5,10)));
	IDB.insert(std::make_pair(37, new Equipment(1304, "�⹦�� ����", static_cast<int>(ITEM_TYPE::ARMOR), { 0,0 }, 0, 40, 40)));
	IDB.insert(std::make_pair(38, new Equipment(1404, "���� ����", static_cast<int>(ITEM_TYPE::BOOTS), { 6,6 }, 5,16,23)));

	return IDB;
}

Item* item_Init(int val)
{
	auto DB = Item_db_Init();
	//������ ���������� �ʱ�ȭ
	Item* Item = DB.at(val);
	return Item;
}