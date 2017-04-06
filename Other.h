#pragma once

typedef struct Diamonds {
	int type;
	BOOL canClear;
	int clearTime;

	Diamonds()
	{
		type = -1;
		canClear = FALSE;
		clearTime = 1200;
	}
}Diamonds;

typedef struct Crystal {

	int x;
	int y;
	int fps;
	int maxFps;
	int fpsSpeed;

	Crystal()
	{
		x = 520;
		y = 180;
		fps = 0;
		maxFps = 9;
		fpsSpeed = 3;
	}
}Crystal;

typedef struct UgradeIcon {

	int x;
	int y;
	BOOL isVisible;
	int id;

	UgradeIcon()
	{
		x = 0;
		y = 0;
		isVisible = FALSE;
		id = -1;
	}
}UgradeIcon;

typedef struct ShootingStar {
	int x;
	int y;
	int curfps;
	int maxFps;
	int destX;
	int destY;
	int speed;
	BOOL Die;

	ShootingStar()
	{
		x = 0;
		y = 0;
		curfps = 0;
		maxFps = 20;
		destX = 0;
		destY = 0;
		speed = 3;
		Die = FALSE;
	}
};

#define ShootingIcon 1100
