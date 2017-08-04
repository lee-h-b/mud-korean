#pragma once
#include"location.h"
class DrunkWalk : public location
{//개선사항
 /*
 2.방향을 상시바꾸진 말기 < 너무못생김 서바이벌맵같이생김 <<좀더나아가서 복도제작기,방제작기 이렇게 나누는건?

 3.시작지점,끝지점은 건드리지 않거나 특정표시를 내기*/
private:
	std::pair<int, int> Size_x;
	std::pair<int, int> Size_y;
	int R_dir;
	int goal;
public:
	/*추가사항 배열이 있으니 그배열의 크기만큼을 세팅해야함
	2.드렁큰워커가 지나갔던 길을 그배열에 저장을 해야함ㅇㅇ
	어떻게? draw역활을 바꿈 해당위치 드로우에서 해당위치배열대입
	*/
	DrunkWalk(std::pair<int, int>X_size, std::pair<int, int>Y_size, int goal)
		: location(X_size.second)
	{
		this->Size_x = X_size;
		this->Size_y = Y_size;
		this->goal = goal;
	}
	int draw_bar(std::mt19937_64 randSeed);
	void Randomdrawing(std::mt19937_64 Seed, char **MAP);
	void Exit_Draw(char **MAP);
	
};