#pragma once

#include"Monster.h"
#include<map>
#include<iostream>
#include<random>

decltype(auto) Mob_db_Init()
{

	std::map<int, Monster*> MDB;
	//���� �̸� ǥ��,ü��,����,�ּ�,�ִ��,��,����ġ,��,{��������� Ű,Ȯ��},�þ�
	MDB.insert(std::make_pair(0, new Monster("���", 'g', 10, 0, 3, 5, 0, 5, 11, { { 2,700 },{5,650} }, 3)));
	MDB.insert(std::make_pair(1, new Monster("������", 's', 7, 0, 3, 6, 1, 3, 10, { { 3,650 },{ 7,400 } }, 2)));
	MDB.insert(std::make_pair(2, new Monster("����", 'b', 15, 0, 4, 6, 0, 4, 14, { { 2,270 },{ 3,680 } }, 6)));
	MDB.insert(std::make_pair(3, new Monster("�Ͽ��", 'h', 20, 0, 5, 8, 2, 10, 13, { { 6,80 },{ 5,446 } }, 4)));
	MDB.insert(std::make_pair(4, new Monster("��������", 'm', 20, 0, 3, 5, 1, 8, 12, { { 4, 500 }, { 6,510 } })));

	MDB.insert(std::make_pair(5, new Monster("��ũ", 'o', 27, 0, 4, 7, 1, 12, 10, { { 8, 190 }, {14, 120} }, 3)));
	MDB.insert(std::make_pair(6, new Monster("����", 't', 18, 0, 7, 9, 1, 12, 11, { {8, 236}, {15 , 200}, {11, 140} }, 4)));
	MDB.insert(std::make_pair(7, new Monster("�Ƹ�������", 'm', 29, 0, 5, 8, 3, 13, 13, { { 8, 170},{9, 260}, {12, 180} })));
	MDB.insert(std::make_pair(8, new Monster("�ذ�ü�", 'a', 24, 0, 11, 14, -1, 17, 12, { {10, 200}, {8 ,180}, {13, 200} }, 2)));
	MDB.insert(std::make_pair(9, new Monster("�ذ�����", 's', 36, 0, 6, 10, 2, 19, 12, { {9, 310 }, {8 , 310 }, {13, 230} }, 3)));

	MDB.insert(std::make_pair(10, new Monster("�̶�", 'M', 33, 0, 9, 12, 2, 17, 8, { {16, 177},{22, 110} }, 3)));
	MDB.insert(std::make_pair(11, new Monster("����", 'Z', 25, 0, 11, 16, -3, 13, 6, { {16, 190}, {17, 221}, {23, 110} }, 4)));
	MDB.insert(std::make_pair(12, new Monster("�����", 'D', 20, 0, 10, 15, 5, 15, 10, { {18, 200}, {19, 180 }, {20, 100} }, 4)));
	MDB.insert(std::make_pair(13, new Monster("������", 'F', 40, 0, 12, 18, 3, 20, 13, { {18, 230}, {17 , 190 } })));
	MDB.insert(std::make_pair(14, new Monster("����", 'D', 35, 0, 16, 20, 7, 25, 12, { {21, 200}, {17,200},{16 , 210} }, 7)));

	MDB.insert(std::make_pair(15, new Monster("�����", 'D', 55, 0, 17, 25, 6, 21, 8, { {24,150}, {28, 146},{25,166} }, 6)));
	MDB.insert(std::make_pair(16, new Monster("��", 'G', 65, 0, 10, 25, 10, 25, 8, { {24,200}, {30, 174},{25,122} }, 4)));
	MDB.insert(std::make_pair(17, new Monster("������", 'S', 76, 0, 20, 27, 7, 28, 12, { {26, 222},{27, 161},{29, 71} }, 8)));
	MDB.insert(std::make_pair(18, new Monster("���ڲ�", 'G', 40, 0, 5, 100, 0, 26, 13, { {24, 111}, {25, 199}, {31, 77} }, 5)));
	MDB.insert(std::make_pair(19, new Monster("�ϻ���", 'M', 70, 0, 25, 31, -5, 32, 12, { {24, 251}, { 26, 249 },{ 27, 186 },{ 29, 146 }, {25, 256} }, 2)));

	MDB.insert(std::make_pair(20, new Monster("����", 'N', 70, 0, 26, 31, 10, 34, 1, { {34,78}, {32,32},{38, 60} })));
	MDB.insert(std::make_pair(21, new Monster("���帮��", 'E', 70, 0, 20, 20, 10, 30, 10, { {32, 21},{37, 101} }, 4)));
	MDB.insert(std::make_pair(22, new Monster("����ũ", '#', 5, 0, 1, 2, 0, 1, 7, { {32,89}, {33, 51} }, 0)));
	MDB.insert(std::make_pair(23, new Monster("�巡��", 'D', 100, 0, 30, 36, 12, 50, 12, { {32, 16},{35, 67 } }, 3)));
	MDB.insert(std::make_pair(24, new Monster("�����", 'G', 88, 0, 28, 37, 20, 65, 12, { {36, 88},{32,22} }, 5)));

	return MDB;

}

decltype(auto) Mob_Init_1(int floor)//�ش���~ 5����
{//���� ������ ������ �ٲ㺸�°͵� ������������?
	//������ġ������ �ش� ���͸� ����ϰ� �ϴ°Զ�����
	//���� �Ű��ι������� ���� ��������
	auto DB = Mob_db_Init();
	std::random_device rand;
	std::mt19937_64 seed(rand());
	std::uniform_int_distribution<int> range(floor * 5, floor * 5 + 4);

	int num = range(seed);
	Monster* Mob = DB.at(num);
	return Mob;
	
}
