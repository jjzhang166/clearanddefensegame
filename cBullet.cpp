#include "stdafx.h"
#include "cBullet.h"
#include"cMonster.h"


cBullet::cBullet()
{
	m_isDie = FALSE;
}


cBullet::~cBullet()
{

}

int cBullet::Move()
{
	if (m_type == Bullet_Dragon || m_type == Bullet_Tiger)
	{
		tagPOINT Dest = *(tagPOINT*)m_Dest;
		if (Dest.x < m_x)
		{
			m_x =m_x-m_speed*2;
		}
		if (Dest.y < m_y)
		{
			m_y -= m_speed;
		}
		if (Dest.x >= m_x&&Dest.y >= m_y)
		{
			m_isDie = TRUE;
			delete m_Dest;
		}
	}
	return 0;
}
