#pragma once
#include<iostream>
#include<queue>
#include<string>
#include"WindowsFunc.h"

void Frame();

void Read(std::queue<std::string> *Writer);
//�Ƹ� Read �̰� �����ϴµ� �����̶� ���ϼ� �ִ� ���� ��������
//���� �о���°Ÿ� �Ʒ� �ִ� ����, �� queue�� �ִ¿�Ȱ
void Write(std::ostream& stream, std::queue<std::string> *Writer);
void Refresh(std::ostringstream &paper);
int input();