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
	std::cout << "������������������������������������������������������" << std::endl;
	for (int i = 0; i < 40; i++)//40�� enum���� �ϴ������ؾ���
	{
		gotoxy(43, 1 + i);
	std::cout << "��                                                  ��";
		//�̰͵� �߰��� �ٽ� |�ִ°žƴϳ�..
		//��¶�� �����Ұ��� queue<string>����� �ű⿡ ��¹� �ֱ�
	}
	gotoxy(43, 38);
	std::cout << "������������������������������������������������������" << std::endl;
	gotoxy(43, 40);
	std::cout << "������������������������������������������������������" << std::endl;
	gotoxy(43, 41);
	std::cout << " Q. ����  W.��ų���� E.������ ��� R.��� ���� X.����" << std::endl;
}

void Read(std::queue<std::string> *Writer)
{//�ۼ��ϴ� �Լ�
	gotoxy(45, 1);
	while (Writer->size() >= 35)
	{
		Writer->pop();
	}//�������� ���ڸ� �޾Ƽ� �ű������ �ϰ��غ���
	CLEAR_frame(Writer->size() );
	
	//������ Ŭ��� �ϴ� ����
	auto temp = *Writer;

	for (int i = 0; i < Writer->size(); i++)
	{

		gotoxy(45, 1 + i);
		std::cout << temp.front();
		temp.pop();
	}
	//������ϸ� Ŭ�����Ű�� �ڿ� ��� ����
	//���� Writer�� �༮�� 
	//������ 40���� ���߰� <<�̰ǿű��
	//�����Ѵ����� �����Ѿ갡 ���
	//��������ϴ°��Ӥ�
}

void Write(std::ostream & stream, std::queue<std::string>* Writer)
{
	std::string be = dynamic_cast<std::ostringstream&>(stream).str();
	Writer->push(be);
	//�̰ɷ� �����ϴ°� 1�ٷ� Ȯ���̰�, clear�� ���ص��ɲ��� ��û����������
	//������ show�ϴ°� 8~90%�� �̰� �ҷ����Ѵٴ���~
	Refresh(static_cast<std::ostringstream&>(stream));
}

void Refresh(std::ostringstream &paper)
{
	paper.str("");
	paper.clear();
}
//�ٸ�������� �׳� �ش� ��ư�� Ŭ���ϰ� ����� �����ߤ���
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
