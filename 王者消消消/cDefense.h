#pragma once

class cDefense
{
public:
	cDefense();
	~cDefense();

public:
	//x坐标

	int m_x;



	//y坐标

	int m_y;



	//防御塔类型

	int type;



	//攻击力

	int m_ATK;



	//攻击延迟

	int m_ATKDelay;



	//最大攻击延迟

	int m_maxATKDelay;



	//当前帧率

	int m_currentFps;



	//最大帧率

	int m_maxFps;



	//发射炮弹的速度

	int m_speed;

};


