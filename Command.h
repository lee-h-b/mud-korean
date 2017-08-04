#pragma once
class CChara;
#include"Chara.h"

class Command
{
public:
	virtual void Action(CChara *actor) =0;

};
//그냥 방향전부다 클래스로
class MoveUp : public Command
{
	void Action(CChara * actor);
};

class MoveDown : public Command
{
	void Action(CChara * actor);
};
class MoveRight : public Command
{
	void Action(CChara * actor);
};
class MoveLeft : public Command
{
	void Action(CChara * actor);
};



