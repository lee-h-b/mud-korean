#include<iostream>
#include<sstream>
#include<queue>
#include<string>
#include<Windows.h>

#include"WindowsFunc.h"
#include "Screen.h"

void Frame()
{
	gotoxy(43, 0);
	std::cout << "┌─────────────────────────┐" << std::endl;
	for (int i = 0; i < 40; i++)//40을 enum으로 하던가좀해야지
	{
		gotoxy(43, 1 + i);
	std::cout << "│                                                  │";
		//이것도 중간에 다시 |넣는거아니냐..
		//어쨋든 지금할것은 queue<string>만들고 거기에 출력문 넣기
	}
	gotoxy(43, 38);
	std::cout << "├─────────────────────────┤" << std::endl;
	gotoxy(43, 40);
	std::cout << "└─────────────────────────┘" << std::endl;
	gotoxy(43, 41);
	std::cout << " Q. 스탯  W.스킬습득 E.아이템 사용 R.장비 착용 X.종료" << std::endl;
}

void Read(std::queue<std::string> *Writer)
{//작성하는 함수
	gotoxy(45, 1);
	while (Writer->size() >= 35)
	{
		Writer->pop();
	}//프레임이 인자를 받아서 거기까지만 하게해볼까
	CLEAR_frame(Writer->size() );
	
	//프레임 클리어를 하는 무언가
	auto temp = *Writer;

	for (int i = 0; i < Writer->size(); i++)
	{

		gotoxy(45, 1 + i);
		std::cout << temp.front();
		temp.pop();
	}
	//다출력하면 클리어시키자 뒤에 찌꺼기 남네
	//들어온 Writer란 녀석을 
	//사이즈 40으로 맞추고 <<이건옮길듯
	//복제한다음에 복제한얘가 대신
	//전부출력하는거임ㅇ
}

void Write(std::ostream & stream, std::queue<std::string>* Writer)
{
	std::string be = dynamic_cast<std::ostringstream&>(stream).str();
	Writer->push(be);
	//이걸로 대입하는걸 1줄로 확줄이고, clear도 안해도될꺼고 엄청편해지긴함
	//문제는 show하는거 8~90%는 이걸 불러야한다는점~
	Refresh(static_cast<std::ostringstream&>(stream));
}

void Refresh(std::ostringstream &paper)
{
	paper.str("");
	paper.clear();
}
//다른방법으로 그냥 해당 버튼을 클릭하게 만들까 생각중ㅇㅇ
int input()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	gotoxy(45, 39);
	std::string a;
	std::getline(std::cin, a);
	if(a.empty())
	a = '0';

//	a.at(0) -= '0';
	int real = atoi(a.c_str());
	
	return real;
}
