#pragma once

enum MonsterType
{
	Type_NULL,
	Type_Dragon,
	Type_Tiger,
	Type_LittleDragon,
};

class cMonster
{
public:
	cMonster();
	~cMonster();

	/*
	*移动怪物
	*/
	int Move();
public:
	//怪物id
	int m_id;

	//x坐标
	int m_x;

	//y坐标
	int m_y;

	//怪物类型
	MonsterType m_type;

	//生命值
	int m_life;

	//攻击力
	int m_ATK;

	//移动速度
	int m_speed;

	//当前帧率
	int m_fps;

	//最大帧率
	int m_maxFps;

	//攻击延迟
	int m_ATKDelay;
};

