#pragma once

enum BulletType
{
	Bullet_Num,
	Bullet_Dragon,
	Bullet_Tiger,
	Bullet_Defense,
};

class cBullet
{
public:
	cBullet();
	~cBullet();

	/*
	*ÒÆ¶¯ÅÚµ¯
	*/
	int Move();
public:
	int m_x;
	int m_y;
	int m_ATK;
	int m_speed;
	int m_fps;
	int m_mxfps;
	BOOL m_isDie;
	BulletType m_type;
    void *m_Dest;
	int m_destId;
};

