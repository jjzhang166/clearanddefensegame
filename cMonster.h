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
	*�ƶ�����
	*/
	int Move();
public:
	//����id
	int m_id;

	//x����
	int m_x;

	//y����
	int m_y;

	//��������
	MonsterType m_type;

	//����ֵ
	int m_life;

	//������
	int m_ATK;

	//�ƶ��ٶ�
	int m_speed;

	//��ǰ֡��
	int m_fps;

	//���֡��
	int m_maxFps;

	//�����ӳ�
	int m_ATKDelay;
};

