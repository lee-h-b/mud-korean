#pragma once

void gotoxy(int x, int y); 
void gotoxy(std::pair<int,int> cur);


void COLOR(int val);
void COLOR(int val, int background);
void CLEAR(int size, int size_sx = 0, int size_sy = 0);
void CLEAR_frame(int size);

int Random_Gen(int seed_1, int seed_2);