#pragma once
#include<iostream>
#include<queue>
#include<string>
#include"WindowsFunc.h"

void Frame();

void Read(std::queue<std::string> *Writer);
//아마 Read 이걸 남발하는데 조금이라도 줄일수 있는 법이 있을거임
//위가 읽어오는거면 아래 애는 쓰는, 즉 queue에 넣는역활
void Write(std::ostream& stream, std::queue<std::string> *Writer);
void Refresh(std::ostringstream &paper);
int input();