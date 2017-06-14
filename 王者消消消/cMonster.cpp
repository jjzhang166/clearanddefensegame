#include "stdafx.h"

#include "cMonster.h"



cMonster::cMonster()
{
}


cMonster::~cMonster()
{
}

int cMonster::Move()
{
	m_x -= m_speed;
	return 0;
}
