#pragma once
#include"location.h"
class DrunkWalk : public location
{//��������
 /*
 2.������ ��ùٲ��� ���� < �ʹ������� �����̹��ʰ��̻��� <<�������ư��� �������۱�,�����۱� �̷��� �����°�?

 3.��������,�������� �ǵ帮�� �ʰų� Ư��ǥ�ø� ����*/
private:
	std::pair<int, int> Size_x;
	std::pair<int, int> Size_y;
	int R_dir;
	int goal;
public:
	/*�߰����� �迭�� ������ �׹迭�� ũ�⸸ŭ�� �����ؾ���
	2.�巷ū��Ŀ�� �������� ���� �׹迭�� ������ �ؾ��Ԥ���
	���? draw��Ȱ�� �ٲ� �ش���ġ ��ο쿡�� �ش���ġ�迭����
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