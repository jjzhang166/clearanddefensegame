#include "stdafx.h"
#include<time.h>
#include<mmsystem.h>
#include "cClearGame.h"

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

cClearGame::cClearGame()
{
	m_Select.x = 0;
	m_Select.y = 0;
	m_currentBlood = 123;
	m_Money = 0;
	m_ClickedBtn = NullBtn;
	m_isMoving = NotMoving;
	m_gameStatus = SelectStatus;
	m_backMusicStatus = PAUSE;
	m_curDerviceID = 0;
	m_currentWaveTimes == 1;
	m_maxWaveTimes = 1;
	m_CurrentBoomNums = 0;
	m_maxBoomNums = 100;
	m_curShootingStarNums = 0;
	m_maxShootingStarNums = 4;
	m_IsOrMotivateSkill = FALSE;
	m_gameLevel = 1;
}


cClearGame::~cClearGame()
{
	for (int i = 0;i < 38;i++)
	{
		DeleteObject(m_hBitMaps[i]);
	}
}

int cClearGame::GameStart(HWND hWnd)
{
	m_hWnd = hWnd;
	if (!LoadResource())
	{
		MessageBox(NULL, L"游戏资源加载失败!", L"提示", MB_OK);
	}
	if (LoadCrystalResource() == -1)
	{
		MessageBox(NULL, L"游戏资源加载失败!", L"提示", MB_OK);
	}
	AddTimer(TimerDrawAll, 50);
	AddTimer(Time,2200);
	return 0;
}

int cClearGame::OnTimer(int id, int iParam, string str)
{
	switch (id)
	{
	case TimerDrawAll:
		DrawAll();
		DeleteBooms();
		DeleteDieMonster();
		CheckGoNext();
		if (m_gameStatus==PlayStatus)
		{
			FillUpBlank();
		}
		break;
	case Time:
		if (m_gameStatus == PlayStatus)
		{
			if (m_currentWaveTimes < m_maxWaveTimes)
			{
				
				if (m_MonsterNums > 0&&m_waveDelay==0)
				{
					--m_MonsterNums;
					if (m_gameLevel > 1)
					{
						CreateMonster(m_currentWaveTimes % 2 == 0 ? Type_Dragon : Type_LittleDragon);
					}
					else
					{
						CreateMonster(Type_Dragon);
					}
				}
				else if (m_MonsterNums == 0)
				{
					m_MonsterNums = m_currentWaveTimes*5;
					m_waveDelay = 4;
				}
				else if (m_waveDelay > 0)
				{
					--m_waveDelay;
					if (m_waveDelay == 0)
					{
						++m_currentWaveTimes;
					}
				}
			}
		}
		break;
	default:
		break;
	}
	return 1;
}

int cClearGame::DrawAll()
{
	HDC hDc;
	hDc = GetWindowDC(m_hWnd);

	HDC hMenDc = CreateCompatibleDC(NULL);
	HBITMAP hBitMap = CreateCompatibleBitmap(hDc,1133, 520);
	SelectObject(hMenDc, hBitMap);

	if (m_gameStatus == SelectStatus)
	{
		DrawStartBg(hMenDc);
		DrawMusicIcon(hMenDc);
	}
	else if(m_gameStatus==PlayStatus)
	{
		DrawStartBg(hMenDc);
		DrawDiamonds(hMenDc);
		if (m_isMoving == Moveing)
			DrawMovingDiamonds(hMenDc);
		DrawMusicIcon(hMenDc);
		DrawDefense(hMenDc);
		DrawCrystal(hMenDc);
		DrawMonster(hMenDc);
		DrawCurrentWavesTimes(hMenDc);
		DrawMoney(hMenDc);
		DrawBlood(hMenDc);
		DrawCurrentBoomNums(hMenDc);
		DrawBullet(hMenDc);
		if (m_ugradeIcon.isVisible == TRUE)
		{
			DrawUgradeIcon(hMenDc);
		}
		DrawShootingIcon(hMenDc);
		DrawShootingStarNums(hMenDc);
		if (m_IsOrMotivateSkill == TRUE)
		{
			DrawShootingStar(hMenDc);
		}
	}
	else if (m_gameStatus == GameOverStatus)
	{
		DrawGameOver(hMenDc);
	}
	else if (m_gameStatus == GameNextStatus)
	{
		DrawGoNext(hMenDc);
	}

	BitBlt(hDc, 10,30, 1133, 520, hMenDc, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, hDc);
	DeleteDC(hMenDc);
	DeleteObject(hBitMap);
	return 0;
}

int cClearGame::DrawStartBg(HDC hDc)
{
	HDC hMenDc = CreateCompatibleDC(hDc);
	HPEN Pen = NULL;
	HBRUSH Brush= (HBRUSH)GetStockObject(NULL_BRUSH);

	if (m_gameStatus == SelectStatus)
	{
		SelectObject(hMenDc, m_hBitMaps[27]);
		if (m_ClickedBtn == StartBtn)
		{
			Pen=CreatePen(0, 3, RGB(255,0, 0));
			SelectObject(hMenDc, Pen);
			SelectObject(hMenDc, Brush);
			Rectangle(hMenDc, 492, 177, 683,217);
		}
		else if (m_ClickedBtn == QuitBtn)
		{
			Pen=CreatePen(0, 3, RGB(255,0, 0));
			SelectObject(hMenDc, Pen);
			SelectObject(hMenDc, Brush);
			Rectangle(hMenDc, 492, 244, 683, 281);
		}
		else if(m_ClickedBtn==NullBtn)
		{
			Pen=CreatePen(0, 3, RGB(128, 128, 255));
			SelectObject(hMenDc, Pen);
			SelectObject(hMenDc, Brush);
			Rectangle(hMenDc, 492, 177, 683, 217);
			Rectangle(hMenDc, 492, 244, 683, 281);
		}
	}
	else if (m_gameStatus == PlayStatus)
	{
		SelectObject(hMenDc, m_hBitMaps[28]);
		if (m_ClickedBtn == ReturnBtn)
		{
			Pen=CreatePen(0, 3, RGB(255,0, 0));
			SelectObject(hMenDc, Pen);
			SelectObject(hMenDc, Brush);
			Rectangle(hMenDc, 542, 419, 656, 455);
		}
		else if(m_ClickedBtn==NullBtn)
		{
			Pen=CreatePen(0, 3, RGB(128, 128, 255));
			SelectObject(hMenDc, Pen);
			SelectObject(hMenDc, Brush);
			Rectangle(hMenDc, 542, 419, 656, 455);
		}
	}
	BitBlt(hDc,0,0,1133,520,hMenDc,0,0,SRCCOPY);

	DeleteDC(hMenDc);
	DeleteObject(Pen);
	DeleteObject(Brush);
	return 0;
}

BOOL cClearGame::LoadResource()
{
	memset(m_hBitMaps, NULL, sizeof(HBITMAP));
	memset(m_hBitDragon, NULL, sizeof(HBITMAP));
	memset(m_hBitTiger, NULL, sizeof(HBITMAP));
	memset(m_hBitDefense, NULL, sizeof(HBITMAP));
	memset(m_hBitDragonBoom, NULL, sizeof(HBITMAP));
	memset(m_hBitLittleDragon, NULL, sizeof(HBITMAP));
	memset(m_hBitShootingStar, NULL, sizeof(HBITMAP));
	m_hBitBullet = NULL;
	m_hBitUgrade = NULL;
	m_hBitShootingStarIcon = NULL;
	hBitNext = NULL;

	wchar_t buff1[10] = { 0 };
	for (int i = 0;i < 27;i++)
	{
		wsprintf(buff1, _T("%d.bmp"),i+1);
		m_hBitMaps[i] = (HBITMAP)LoadImage(NULL,buff1,IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	}

	m_hBitMaps[27] = (HBITMAP)LoadImage(NULL, L"sbg.bmp", IMAGE_BITMAP, 1133, 520, LR_LOADFROMFILE);
	m_hBitMaps[28] = (HBITMAP)LoadImage(NULL, L"bg.bmp", IMAGE_BITMAP, 1133, 490, LR_LOADFROMFILE);
	m_hBitMaps[29] = (HBITMAP)LoadImage(NULL, L"Select.bmp", IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE);
	m_hBitMaps[30] = (HBITMAP)LoadImage(NULL, L"Timebar.bmp", IMAGE_BITMAP, 126, 16, LR_LOADFROMFILE);
	m_hBitMaps[31] = (HBITMAP)LoadImage(NULL, L"Boom1.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[32] = (HBITMAP)LoadImage(NULL, L"Boom2.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[33] = (HBITMAP)LoadImage(NULL, L"Boom3.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[34] = (HBITMAP)LoadImage(NULL, L"Boom4.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[35] = (HBITMAP)LoadImage(NULL, L"Play.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[36] = (HBITMAP)LoadImage(NULL, L"Pause.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	m_hBitMaps[37] = (HBITMAP)LoadImage(NULL, L"GameOver.bmp", IMAGE_BITMAP, 1133, 490, LR_LOADFROMFILE);
	m_hBitBullet = (HBITMAP)LoadImage(NULL, L"Bullet.bmp", IMAGE_BITMAP, 35, 35, LR_LOADFROMFILE);
	m_hBitUgrade = (HBITMAP)LoadImage(NULL, L"Ugrade.bmp", IMAGE_BITMAP, 100, 68, LR_LOADFROMFILE);
	m_hBitShootingStarIcon = (HBITMAP)LoadImage(NULL, L"fireBallIcon.bmp", IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	hBitNext = (HBITMAP)LoadImage(NULL, L"Next.bmp", IMAGE_BITMAP, 1133, 520, LR_LOADFROMFILE);

	memset(buff1, 0, sizeof(wchar_t));
	for (size_t i = 0;i < 8;++i)
	{
		wsprintf(buff1, _T("long%d.bmp"), i + 1);
		m_hBitDragon[i] = (HBITMAP)LoadImage(NULL, buff1, IMAGE_BITMAP, 100, 115, LR_LOADFROMFILE);
	}

	wchar_t buff2[15]={ 0 };
	for (int i = 0;i < 6;++i)
	{
		wsprintf(buff2, _T("Tiger%d.bmp"), i + 1);
		m_hBitTiger[i] = (HBITMAP)LoadImage(NULL, buff2, IMAGE_BITMAP, 211,129, LR_LOADFROMFILE);
	}

	wchar_t buff3[20] = { 0 };
	for (int i = 0;i < 20;++i)
	{
		wsprintf(buff3, L"Defense%d.bmp", i + 1);
		m_hBitDefense[i] = (HBITMAP)LoadImage(NULL, buff3, IMAGE_BITMAP, 200, 140, LR_LOADFROMFILE);
	}

	wchar_t buff4[20] = { 0 };
	for (int i = 0;i < 10;++i)
	{
		wsprintf(buff4, L"DragonBoom%d.bmp", i + 1);
		m_hBitDragonBoom[i] = (HBITMAP)LoadImage(NULL, buff4, IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	}

	wchar_t buff5[20] = { 0 };
	for (int i = 0;i < 20;++i)
	{
		wsprintf(buff5, L"fireBall%d.bmp", i + 1);
		m_hBitShootingStar[i] = (HBITMAP)LoadImage(NULL, buff5, IMAGE_BITMAP, 47, 100, LR_LOADFROMFILE);
	}

	wchar_t buff6[20] = { 0 };
	for (int i = 0;i < 23;++i)
	{
		wsprintf(buff6, L"Dragon%d.bmp", i + 1);
		m_hBitLittleDragon[i] = (HBITMAP)LoadImage(NULL, buff6, IMAGE_BITMAP, 120, 109, LR_LOADFROMFILE);
	}

	for (size_t i = 0;i < 37;i++)
	{
		if (m_hBitMaps[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 7;++i)
	{
		if (m_hBitDragon[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 6;++i)
	{
		if (m_hBitTiger[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 20;++i)
	{
		if (m_hBitDefense[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 10;++i)
	{
		if (m_hBitDragonBoom[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 20;++i)
	{
		if (m_hBitShootingStar[i] == NULL)
		{
			return FALSE;
		}
	}

	for (int i = 0;i < 23;++i)
	{
		if(m_hBitLittleDragon[i]==NULL)
		{ 
			return FALSE;
		}		
	}

	if (m_hBitBullet == NULL)
	{
		return FALSE;
	}
	if (m_hBitUgrade == NULL)
	{
		return FALSE;
	}
	if (m_hBitShootingStarIcon == NULL)
	{
		return FALSE;
	}
	if (hBitNext == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

int cClearGame::CheckMouse()
{
	tagPOINT tagPoint;
	GetCursorPos(&tagPoint);
	ScreenToClient(m_hWnd, &tagPoint);
	if (m_gameStatus == PlayStatus)
	{
		int i = 0;
		int j = 0;
		if (tagPoint.x < 480)
		{
			i = tagPoint.x / 60;
			j = tagPoint.y / 60;
			if (IsOrNotBoom(i, j))
			{
				m_Select.x = i;
				m_Select.y = j;
				DealBoomResult(i,j);
				Sleep(500);
				ClearDiamonds();
				Sleep(200);
				while (FindCanClearDiamonds())
				{
					Sleep(1000);
					ClearDiamonds();
					Sleep(200);
				}
				Sleep(800);
				AddNewDiamonds();
			}
			else if (IsOrNotShootingStar(i,j))
			{
				m_Select.x = i;
				m_Select.y = j;
				Sleep(500);
				if (m_curShootingStarNums < 3)
				{
					++m_curShootingStarNums;
				}
				ClearDiamonds();
				Sleep(200);
				while (FindCanClearDiamonds())
				{
					Sleep(1000);
					ClearDiamonds();
					Sleep(200);
				}
				Sleep(800);
				AddNewDiamonds();
			}
			else
			{
				if (IsAdjacent(i, j))
				{
					if (CanMove(i, j))
					{
						m_isMoving = Moveing;
						m_destSite.x = i;
						m_destSite.y = j;
						Sleep(1000);
						ClearDiamonds();
						Sleep(200);
						while (FindCanClearDiamonds())
						{
							Sleep(1000);
							ClearDiamonds();
							Sleep(200);
						}
						Sleep(800);
						AddNewDiamonds();
					}
				}
				m_Select.x = i;
				m_Select.y = j;
			}
		}
		else if(tagPoint.x>542&&tagPoint.x<656&&tagPoint.y>419&&tagPoint.y<455)
		{
			m_ClickedBtn = ReturnBtn;
			Sleep(100);
			m_ClickedBtn = NullBtn;
			m_gameStatus = SelectStatus;
		}
		else if (tagPoint.x>545&&tagPoint.x<545+50&&tagPoint.y>10&&tagPoint.y<10+50)
		{
			if (m_backMusicStatus == PLAY)
			{
				m_backMusicStatus = PAUSE;
				PauesBackMusic();
			}
			else
			{
				m_backMusicStatus = PLAY;
				PlayBackMusic();
			}
		}
		if (m_ugradeIcon.isVisible == TRUE)
		{
			if (abs((m_ugradeIcon.x + 5) - tagPoint.x) < 10 && abs((m_ugradeIcon.y + 34) - tagPoint.y) < 34)
			{
				int currentMoney = m_Money;
				if (currentMoney < 100)
				{
					MessageBox(NULL, L"金钱不足", L"", MB_OK);
				}
				else if (m_defense[m_ugradeIcon.id].m_ATK > 50)
				{
					MessageBox(NULL, L"已达最大攻击力", L"", MB_OK);
				}
				if (m_defense[m_ugradeIcon.id].m_ATK <= 50&& currentMoney >=100)
				{
					m_defense[m_ugradeIcon.id].m_ATK += 10;
					m_Money -= 100;
				}
				m_ugradeIcon.isVisible = FALSE;
			}
			else if (abs((m_ugradeIcon.x + 87) - tagPoint.x) < 10 && abs((m_ugradeIcon.y + 34) - tagPoint.y) < 34)
			{
				int currentMoney = m_Money;
				if (currentMoney < 100)
				{
					MessageBox(NULL, L"金钱不足", L"", MB_OK);
				}
				else if (m_defense[m_ugradeIcon.id].m_maxATKDelay <= 5)
				{
					MessageBox(NULL, L"已达最大攻速", L"", MB_OK);
				}
				if (m_defense[m_ugradeIcon.id].m_maxATKDelay>5&& currentMoney >=100)
				{
					m_defense[m_ugradeIcon.id].m_maxATKDelay -= 5;
					m_defense[m_ugradeIcon.id].m_speed += 1;
					m_Money -= 100;
				}
				m_ugradeIcon.isVisible = FALSE;
			}
			else
			{
				m_ugradeIcon.isVisible = FALSE;
			}
		}
		if (IsOrNotClickShootingStarIcon(tagPoint.x,tagPoint.y))
		{
			MotivateShootingStar();
		}
	}
	else if(m_gameStatus==SelectStatus)
	{
		if (tagPoint.x > 492 && tagPoint.x < 683 && tagPoint.y>177 && tagPoint.y < 219)
		{
			m_ClickedBtn = StartBtn;
			Sleep(100);
			m_ClickedBtn = NullBtn;
			m_gameStatus = PlayStatus;
			PlayGame();
		}
		if (tagPoint.x > 492 && tagPoint.x < 683 && tagPoint.y>244 && tagPoint.y <281)
		{
			m_ClickedBtn = QuitBtn;
			Sleep(200);
			exit(0);
		}
		if (tagPoint.x>553&&tagPoint.x<553+50&&tagPoint.y>100&&tagPoint.y<100+50)
		{
			if (m_backMusicStatus == PLAY)
			{
				m_backMusicStatus = PAUSE;
				PauesBackMusic();
			}
			else
			{
				m_backMusicStatus = PLAY;
				PlayBackMusic();
			}
		}
	}
	else if (m_gameStatus == GameOverStatus)
	{
		if (tagPoint.x >= 475 && tagPoint.x < 765 && tagPoint.y>390 && tagPoint.y < 460)
		{
			Sleep(100);
			m_gameStatus = PlayStatus;
			PlayGame();
		}
	}
	return 0;
}

int cClearGame::RandomCreateDiamonds()
{
	int flag = 0;
	int last = 0;
	int type = 0;

	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (flag == 0)
			{
				flag = 1;
				srand((unsigned)time(NULL) + i*j + i*last);
			}
			else
			{
				flag = 0;
				srand((unsigned)time(NULL) + i*j + j*last);
			}
			type = rand() % 7+1;
			if (CheckDiamonds(i, j, type))
			{
				m_diamonds[i][j].type = type;
				m_diamonds[i][j].canClear = FALSE;
			}
			else
			{
				int Last = type;
				type = type * 35 % type+1;
				if (Last == type)
					type = (type - 1) == 0 ? type + 1 : type - 1;
				m_diamonds[i][j].type= type;
				m_diamonds[i][j].canClear = FALSE;
			}
			last = type;
		}
	return 0;
}

int cClearGame::DrawDiamonds(HDC hDc)
{
	HDC hMenDC = CreateCompatibleDC(hDc);
	SelectObject(hMenDC,m_hBitMaps[29]);
	TransparentBlt(hDc, m_Select.x * 60, m_Select.y* 60, 70, 70,hMenDC, 0, 0, 70, 70, RGB(0, 255, 255));
	for(int i=0;i<8;i++)
		for (int j = 0;j < 8;j++)
		{
			if (m_isMoving==Moveing&&((m_Select.x == i&&m_Select.y == j) || (m_destSite.x == i&&m_destSite.y == j)))
			{
				continue;
			}
			if (m_diamonds[i][j].type!= -1)
			{
				if (m_diamonds[i][j].type == BOOM1)
				{
					SelectObject(hMenDC, m_hBitMaps[31]);
					TransparentBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, 50, 50, RGB(0,255,64));
				}
				else if (m_diamonds[i][j].type == BOOM2)
				{
					SelectObject(hMenDC, m_hBitMaps[32]);
					TransparentBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, 50, 50, RGB(0, 255, 64));
				}
				else if (m_diamonds[i][j].type == BOOM3)
				{
					SelectObject(hMenDC, m_hBitMaps[33]);
					TransparentBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, 50, 50, RGB(0, 255, 64));
				}
				else if (m_diamonds[i][j].type == BOOM4)
				{
					SelectObject(hMenDC, m_hBitMaps[34]);
					TransparentBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, 50, 50, RGB(0, 255, 64));
				}
				else if (m_diamonds[i][j].type == ShootingIcon)
				{
					SelectObject(hMenDC, m_hBitShootingStarIcon);
					BitBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, SRCCOPY);
				}
				else
				{
					SelectObject(hMenDC, m_hBitMaps[m_diamonds[i][j].type]);
					BitBlt(hDc, i * 50 + 10 * (i + 1), j * 50 + 10 * (j + 1), 50, 50, hMenDC, 0, 0, SRCCOPY);
				}
			}
		}
	DeleteDC(hMenDC);
	return 0;
}

BOOL cClearGame::CheckDiamonds(int i, int j, int type)
{
	if (i >= 2)
	{
		if (m_diamonds[i - 1][j].type == type&&m_diamonds[i - 2][j].type == type)
			return FALSE;
	}
	if (j >= 2)
	{
		if (m_diamonds[i][j - 1].type== type&&m_diamonds[i][j - 2].type== type)
			return FALSE;
	}
	return TRUE;
}

int cClearGame::PlayGame()
{

	m_Select.x = 0;
	m_Select.y = 0;
	m_Money = 0;
	m_currentBlood = 123;
	m_monsterID = 0;
	m_maxBoomNums = 90;
	m_currentWaveTimes = 4;
	m_maxWaveTimes = 6;
	m_MonsterNums = 5;
	m_waveDelay = 0;
	m_NextStatusDelay = 10;
	initDefense();
	RandomCreateDiamonds();
	m_monsterList.clear();
	m_bulletList.clear();
	return 0;
}

BOOL cClearGame::IsAdjacent(int i, int j)
{
	if ((m_Select.x == i&&abs(m_Select.y-j)==1) || (m_Select.y == j&&abs(m_Select.x-i)==1))
	{
		return TRUE;
	}
	return FALSE;
}

int cClearGame::MoveDiamonds(int i,int j)
{
	Diamonds iFlag;
	iFlag = m_diamonds[i][j];
	m_diamonds[i][j] = m_diamonds[m_Select.x][m_Select.y];
	m_diamonds[m_Select.x][m_Select.y] = iFlag;
	return 0;
}

int cClearGame::DrawBlood(HDC hDc)
{
	HDC hMenDc = CreateCompatibleDC(hDc);
	SelectObject(hMenDc, m_hBitMaps[30]);
	BitBlt(hDc, 1003, 60,126,16, hMenDc, 126-m_currentBlood, 0, SRCCOPY);
	
	DeleteDC(hMenDc);
	return 0;
}

BOOL cClearGame::CanMove(int i, int j)
{
	BOOL bRet = FALSE;
	int iCount1 = 0;
	int iCount2 = 0;
	Diamonds iFlag = m_diamonds[i][j];
	m_diamonds[i][j] = m_diamonds[m_Select.x][m_Select.y];
	m_diamonds[m_Select.x][m_Select.y] = iFlag;
	for (int Y=j-1;Y >= 0;Y--)
	{
		if (m_diamonds[i][Y].type == m_diamonds[i][j].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int Y = j + 1;Y < 8;Y++)
	{
		if (m_diamonds[i][Y].type == m_diamonds[i][j].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1+iCount2 >= 2)
	{
		for (int Y = 0;Y <= iCount1;++Y)
		{
			m_diamonds[i][j - Y].canClear = TRUE;
		}
		for (int Y = 0;Y <= iCount2;++Y)
		{
			m_diamonds[i][j + Y].canClear = TRUE;
		}
		bRet = TRUE;
	}

	iCount1 = 0;
	iCount2 = 0;
	for (int X =i-1;X>=0 ;X--)
	{
		if (m_diamonds[X][j].type == m_diamonds[i][j].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int X = i + 1;X < 8;X++)
	{
		if (m_diamonds[X][j].type == m_diamonds[i][j].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		for (int X = 0;X <=iCount1;X++)
		{
			m_diamonds[i - X][j].canClear = TRUE;
		}
		for (int X = 0;X <= iCount2;X++)
		{
			m_diamonds[i + X][j].canClear = TRUE;
		}
		bRet = TRUE;
	}

	iCount1 = 0;
	iCount2 = 0;
	for (int Y = m_Select.y - 1;Y >= 0;Y--)
	{
		if (m_diamonds[m_Select.x][m_Select.y].type == m_diamonds[m_Select.x][Y].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int Y = m_Select.y + 1;Y < 8;Y++)
	{
		if (m_diamonds[m_Select.x][m_Select.y].type == m_diamonds[m_Select.x][Y].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		for (int Y = 0;Y <=iCount1;Y++)
		{
			m_diamonds[m_Select.x][m_Select.y - Y].canClear = TRUE;
		}
		for (int Y = 0;Y <=iCount2;Y++)
		{
			m_diamonds[m_Select.x][m_Select.y + Y].canClear = TRUE;
		}
		bRet = TRUE;

	}

	iCount1 = 0;
	iCount2 = 0;
	for (int X = m_Select.x - 1;X >= 0;X--)
	{
		if (m_diamonds[m_Select.x][m_Select.y].type == m_diamonds[X][m_Select.y].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int X = m_Select.x + 1;X < 8;X++)
	{
		if (m_diamonds[m_Select.x][m_Select.y].type == m_diamonds[X][m_Select.y].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		for (int X = 0;X <= iCount1;X++)
		{
			m_diamonds[m_Select.x - X][m_Select.y].canClear = TRUE;
		}
		for (int X = 0;X <= iCount2;X++)
		{
			m_diamonds[m_Select.x + X][m_Select.y].canClear = TRUE;
		}
		bRet = TRUE;
	}

	if (bRet == FALSE)
	{
		iFlag = m_diamonds[i][j];
		m_diamonds[i][j] = m_diamonds[m_Select.x][m_Select.y];
		m_diamonds[m_Select.x][m_Select.y] = iFlag;
	}
	return bRet;
}

int cClearGame::DrawMovingDiamonds(HDC hDc)
{
	HDC hMenDc = CreateCompatibleDC(hDc);
	HDC hMenDc1 = CreateCompatibleDC(hDc);
	
	int typeSelect = m_diamonds[m_Select.x][m_Select.y].type<=7? m_diamonds[m_Select.x][m_Select.y].type:30+m_diamonds[m_Select.x][m_Select.y].type-7;
	int typeDest = m_diamonds[m_destSite.x][m_destSite.y].type <= 7 ? m_diamonds[m_destSite.x][m_destSite.y].type : 30 + m_diamonds[m_destSite.x][m_destSite.y].type - 7;
	SelectObject(hMenDc, m_hBitMaps[typeSelect]);
	SelectObject(hMenDc1, m_hBitMaps[typeDest]);

	if (m_Select.x == m_destSite.x&&m_Select.y > m_destSite.y)
	{
		BitBlt(hDc, m_Select.x * 60 + 10, m_Select.y * 60 + 10-m_haveMoved, 50, 50, hMenDc, 0, 0, SRCCOPY);
		BitBlt(hDc, m_destSite.x * 60 + 10, m_destSite.y * 60 + 10+m_haveMoved, 50, 50, hMenDc1, 0, 0, SRCCOPY);
	}
	else if (m_Select.x == m_destSite.x&&m_Select.y < m_destSite.y)
	{
		BitBlt(hDc, m_Select.x * 60 + 10, m_Select.y * 60 + 10+m_haveMoved, 50, 50, hMenDc, 0, 0, SRCCOPY);
		BitBlt(hDc, m_destSite.x * 60 + 10, m_destSite.y * 60 + 10-m_haveMoved, 50, 50, hMenDc1, 0, 0, SRCCOPY);
	}
	else if (m_Select.x > m_destSite.x&&m_Select.y == m_destSite.y)
	{
		BitBlt(hDc, m_Select.x * 60 + 10-m_haveMoved, m_Select.y * 60 + 10, 50, 50, hMenDc, 0, 0, SRCCOPY);
		BitBlt(hDc, m_destSite.x * 60 + 10+m_haveMoved, m_destSite.y * 60 + 10, 50, 50, hMenDc1, 0, 0, SRCCOPY);
	}
	else if (m_Select.x < m_destSite.x&&m_Select.y == m_destSite.y)
	{
		BitBlt(hDc, m_Select.x * 60 + 10+m_haveMoved, m_Select.y * 60 + 10, 50, 50, hMenDc, 0, 0, SRCCOPY);
		BitBlt(hDc, m_destSite.x * 60 + 10-m_haveMoved, m_destSite.y * 60 + 10, 50, 50, hMenDc1, 0, 0, SRCCOPY);
	}

	m_haveMoved+=10;
	if (m_haveMoved > 60)
	{
		m_haveMoved = 0;
		m_isMoving = NotMoving;
	}
	DeleteDC(hMenDc);
	DeleteDC(hMenDc1);
	return 0;
}

int cClearGame::ClearDiamonds()
{
	int iCount = 0;

	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if (m_diamonds[i][j].canClear == TRUE)
			{
					m_diamonds[i][j].type = -1;
					iCount++;
			}
		}
	}

	m_CurrentBoomNums += iCount;
	m_CurrentBoomNums>m_maxBoomNums?m_CurrentBoomNums=m_maxBoomNums: m_CurrentBoomNums;
	return 0;
}

int cClearGame::DrawMoney(HDC hDc)
{
	wchar_t buff[1024] = { 0 };
	LOGFONT logFont;
	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfCharSet= GB2312_CHARSET;
	logFont.lfHeight = 30;
	HFONT hFont = CreateFontIndirect(&logFont);
	SelectObject(hDc, hFont);
	SetBkMode(hDc, NULL);
	SetTextColor(hDc, RGB(255, 242, 0));
	wsprintf(buff, L"%d", m_Money);
	TextOut(hDc, 746, 10, buff, lstrlen(buff));
	return 0;
}

int cClearGame::FillUpBlank()
{
	for (int i = 7;i >= 0;--i)
	{
		for (int j = 7;j >= 0;--j)
		{
			if (m_diamonds[i][j].type == -1)
			{
				FindNotNullDiamonds(i,j);
			}
		}
	}

	return 0;
}

int cClearGame::FindNotNullDiamonds(int i, int j)
{
	for (int Y = j;Y>= 0;--Y)
	{
		if (m_diamonds[i][Y].type != -1&&m_diamonds[i][Y].canClear==FALSE)
		{
			Diamonds iFlag = m_diamonds[i][Y];
			m_diamonds[i][Y] = m_diamonds[i][j];
			m_diamonds[i][j]= iFlag;
			break;
		}
	}

	return 0;
}

int cClearGame::AddNewDiamonds()
{
	int type = -1;
	int randNum = 0;
	srand(GetTickCount());

	for(int i=0;i<8;++i)
		for (int j = 0;j < 8;++j)
		{
			if (m_diamonds[i][j].type == -1)
			{
				type = rand() % 7 + 1;
				randNum = rand() % 100;
				if (randNum < 12)
				{
					if (randNum <=7)
					{
						m_diamonds[i][j].type = 8 + rand() % 4;
						m_diamonds[i][j].canClear = FALSE;
					}
					else
					{
						m_diamonds[i][j].type = ShootingIcon;
						m_diamonds[i][j].canClear = FALSE;
					}
				}
				else
				{
					if (CheckIsCanPut(i, j, type))
					{
						m_diamonds[i][j].type = type;
						m_diamonds[i][j].canClear = FALSE;
					}
					else
					{
						m_diamonds[i][j].type = (type == 1) ? type + 1 : type - 1;
						m_diamonds[i][j].canClear = FALSE;
					}
				}
			}
		}

	return 0;
}

BOOL cClearGame::CheckIsCanPut(int i,int j,int type)
{
	int iCount1 = 0;
	int iCount2 = 0;
	BOOL bRet = TRUE;

	for (int Y = j - 1;Y >= 0;Y--)
	{
		if (m_diamonds[i][Y].type == type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int Y = j + 1;Y < 8;Y++)
	{
		if (m_diamonds[i][Y].type == type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		bRet = FALSE;
	}

	iCount1 = 0;
	iCount2 = 0;
	for (int X = i - 1;X >= 0;--X)
	{
		if (m_diamonds[X][j].type == type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int X = i + 1;X < 8;++X)
	{
		if (m_diamonds[X][j].type == type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL cClearGame::FindCanClearDiamonds()
{
	BOOL bRet = FALSE;

	for (int i = 0;i < 8;++i)
	{
		for (int j = 0;j < 8;++j)
		{
			if (m_diamonds[i][j].canClear == FALSE)
			{
				if (DiamondsCanClear(i, j))
				{
					bRet = TRUE;
				}
			}
		}
	}

	return bRet;
}

BOOL cClearGame::DiamondsCanClear(int i, int j)
{
	int iCount1 = 0;
	int iCount2 = 0;
	BOOL bRet = FALSE;

	for (int Y = j - 1;Y >= 0;--Y)
	{
		if (m_diamonds[i][Y].type == m_diamonds[i][j].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int Y = j + 1;Y < 8;++Y)
	{
		if (m_diamonds[i][Y].type == m_diamonds[i][j].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		for (int Y = 0;Y <= iCount1;++Y)
		{
			m_diamonds[i][j - Y].canClear = TRUE;
		}
		for (int Y = 0;Y <= iCount2;++Y)
		{
			m_diamonds[i][j + Y].canClear = TRUE;
		}
		bRet = TRUE;
	}

	iCount1 = 0;
	iCount2 = 0;
	for (int X = i - 1;X >= 0;--X)
	{
		if (m_diamonds[X][j].type == m_diamonds[i][j].type)
		{
			iCount1++;
		}
		else
		{
			break;
		}
	}
	for (int X = i + 1;X < 8;++X)
	{
		if (m_diamonds[X][j].type == m_diamonds[i][j].type)
		{
			iCount2++;
		}
		else
		{
			break;
		}
	}
	if (iCount1 + iCount2 >= 2)
	{
		for (int X = 0;X <= iCount1;++X)
		{
			m_diamonds[i - X][j].canClear = TRUE;
		}
		for (int X = 0;X <= iCount2;++X)
		{
			m_diamonds[i + X][j].canClear = TRUE;
		}
		bRet = TRUE;
	}

	return bRet;
}

BOOL cClearGame::IsOrNotBoom(int i, int j)
{
	if (m_diamonds[i][j].type > 7&&m_diamonds[i][j].type<12)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL cClearGame::IsOrNotShootingStar(int i, int j)
{
	if (m_diamonds[i][j].type == ShootingIcon)
	{
		m_diamonds[i][j].canClear = TRUE;
		return TRUE;
	}

	return FALSE;
}

int cClearGame::DealBoomResult(int i, int j)
{
	switch (m_diamonds[i][j].type)
	{
	case BOOM1:
		DoBoom1(i,j);
		break;
	case BOOM2:
		DoBoom2(i, j);
		break;
	case BOOM3:
		DoBoom3(i, j);
		break;
	case BOOM4:
		DoBoom4(i, j);
		break;
	default:
		break;
	}
	return 0;
}

int cClearGame::DoBoom1(int i, int j)
{
	for (int x = 0;x < 8;++x)
	{
		m_diamonds[x][j].canClear = TRUE;
	}
	return 0;
}

int cClearGame::DoBoom2(int i,int j)
{
	for (int y = 0;y < 8;++y)
	{
		m_diamonds[i][y].canClear = TRUE;
	}
	return 0;
}

int cClearGame::DoBoom3(int i,int j)
{
	for (int x = 0;x < 8;++x)
	{
		m_diamonds[x][j].canClear = TRUE;
	}
	for (int y = 0;y < 8;++y)
	{
		m_diamonds[i][y].canClear = TRUE;
	}
	return 0;
}

int cClearGame::DoBoom4(int i,int j)
{
	srand(GetTickCount());
	int type=rand() % 7 + 1;

	m_diamonds[i][j].canClear = TRUE;
	for (int x = 0;x < 8;++x)
	{
		for (int y = 0;y < 8;++y)
		{
			if (m_diamonds[x][y].type == type)
			{
				m_diamonds[x][y].canClear = TRUE;
			}
		}
	}
	return 0;
}

int cClearGame::PlayBackMusic()
{
	PlaySound(L"my_music.wav", NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);
	return 0;
}

int cClearGame::PauesBackMusic()
{
	PlaySound(NULL, NULL, SND_FILENAME);
	return 0;
}

int cClearGame::DrawMusicIcon(HDC hDc)
{
	HDC hMenDc = CreateCompatibleDC(hDc);
	if (m_backMusicStatus == PAUSE)
	{
		SelectObject(hMenDc, m_hBitMaps[36]);
	}
	else
	{
		SelectObject(hMenDc, m_hBitMaps[35]);
	}
	if (m_gameStatus == SelectStatus)
	{
		BitBlt(hDc, 553,100,50,50,hMenDc,0,0,SRCCOPY);
	}
	else
	{
		BitBlt(hDc, 545,10 , 50, 50, hMenDc, 0, 0, SRCCOPY);
	}

	DeleteDC(hMenDc);
	return 0;
}

int cClearGame::DrawGameOver(HDC hDc)
{
	HDC hMenDc = CreateCompatibleDC(hDc);
	SelectObject(hMenDc, m_hBitMaps[37]);
	BitBlt(hDc, 0, 0, 1133, 490, hMenDc, 0, 0, SRCCOPY);

	DeleteDC(hMenDc);
	return 0;
}

int cClearGame::DrawMonster(HDC hDc)
{
	HDC hMemDC = CreateCompatibleDC(hDc);
	for (list<cMonster>::iterator it = m_monsterList.begin();it != m_monsterList.end();++it)
	{
		if (it->m_type == Type_Dragon)
		{
			SelectObject(hMemDC, m_hBitDragon[it->m_fps]);
			it->m_fps = (it->m_fps + 1) % it->m_maxFps;
			if (it->m_x >= 680)
			{
				it->Move();
			}
			else
			{
				if (it->m_ATKDelay == 0)
				{
					tagPOINT *Point = new tagPOINT;
					Point->x = 598;
					Point->y = 240;
					it->m_ATKDelay = 40;
					ShootBullet(it->m_x - 30, it->m_y + 55, Bullet_Dragon, 10, 2, Point, -1);
				}
				else
				{
					--it->m_ATKDelay;
				}
			}
			TransparentBlt(hDc, it->m_x, it->m_y, 100, 115, hMemDC, 0, 0, 100, 115, RGB(128, 128, 128));
			it->m_life -= CheckMonsterIsGetBullet(it->m_x, it->m_y, it->m_id);
		}
		else
		{
			SelectObject(hMemDC, m_hBitLittleDragon[it->m_fps]);
			it->m_fps = (it->m_fps + 1) % it->m_maxFps;
			if (it->m_x >= 680)
			{
				it->Move();
			}
			else
			{
				if (it->m_ATKDelay == 0)
				{
					tagPOINT *Point = new tagPOINT;
					Point->x = 598;
					Point->y = 240;
					it->m_ATKDelay = 40;
					ShootBullet(it->m_x - 10, it->m_y + 25, Bullet_Dragon, 10, 2, Point, -1);
				}
				else
				{
					--it->m_ATKDelay;
				}
			}
			TransparentBlt(hDc, it->m_x, it->m_y, 120,109, hMemDC, 0, 0, 120, 109, RGB(128, 128, 128));
			it->m_life -= CheckMonsterIsGetBullet(it->m_x, it->m_y, it->m_id);
		}
	}

	DeleteDC(hMemDC);
	return 0;
}

int cClearGame::initDefense()
{
	for (int i = 0;i < 6;++i)
	{
		m_defense[i].m_x = 650+(i%3)*150;
		m_defense[i].m_y = 70 + (i/3)*240;
		m_defense[i].m_ATK = 20;
		m_defense[i].m_ATKDelay = 2;
		m_defense[i].m_maxATKDelay = 30;
		m_defense[i].m_currentFps = 0;
		m_defense[i].m_maxFps = 20;
		m_defense[i].m_speed = 4;
	}

	return 0;
}

int cClearGame::DrawDefense(HDC hDc)
{
	HDC hMemDC = CreateCompatibleDC(hDc);

	for (int  i=0;i<6;++i)
	{
		SelectObject(hMemDC, m_hBitDefense[m_defense[i].m_currentFps]);
		m_defense[i].m_currentFps = (m_defense[i].m_currentFps + 1) % m_defense[i].m_maxFps;
		TransparentBlt(hDc,m_defense[i].m_x,m_defense[i].m_y, 200, 140, hMemDC, 0, 0, 200, 140, RGB(0, 0, 0));
		CheckDefenseNearby(m_defense[i]);
	}

	DeleteDC(hMemDC);
	return 0;
}

int cClearGame::DrawCrystal(HDC hDc)
{
	--m_crystal.fpsSpeed;
	HDC hMemDc = CreateCompatibleDC(hDc);
	SelectObject(hMemDc, m_hBitCrystal[m_crystal.fps]);
	TransparentBlt(hDc, m_crystal.x,m_crystal.y , 150,141, hMemDc,0, 0, 150, 141, RGB(128, 128, 128));
	
	if (m_crystal.fpsSpeed == 0)
	{
		m_crystal.fpsSpeed = 3;
		m_crystal.fps = (m_crystal.fps + 1) % m_crystal.maxFps;
	}
	
	DeleteDC(hMemDc);
	return 0;
}

int cClearGame::LoadCrystalResource()
{
	memset(m_hBitCrystal, NULL, sizeof(HBITMAP));

	wchar_t buff4[15] = { 0 };
	for (int i = 0;i < 9;++i)
	{
		wsprintf(buff4, L"Crystal%d.bmp", i + 1);
		m_hBitCrystal[i] = (HBITMAP)LoadImage(NULL, buff4, IMAGE_BITMAP, 150, 141, LR_LOADFROMFILE);
	}

	for (int i = 0;i < 9;++i)
	{
		if (m_hBitCrystal[i] == NULL)
		{
			return -1;
		}
	}

	return 0;
}

int cClearGame::CreateMonster(MonsterType type)
{
	cMonster monster;
	monster.m_x = 1134;
	monster.m_y = 200;
	monster.m_type = type;
	monster.m_ATKDelay = 4;
	monster.m_fps = 0;
	if (type == Type_Dragon)
	{
		monster.m_ATK = 10;
		monster.m_life = 30 * m_currentWaveTimes;
		monster.m_maxFps = 8;
	}
	else
	{
		monster.m_ATK = 15;
		monster.m_life = 30 * m_currentWaveTimes+100;
		monster.m_maxFps = 23;
	}
	monster.m_speed = 2+m_currentWaveTimes;
	monster.m_speed < 6 ? monster.m_speed : monster.m_speed = 4;
	monster.m_id = m_monsterID++;
	if (m_monsterID == 1000)
	{
		m_monsterID = 0;
	}

	m_monsterList.push_back(monster);
	return 0;
}

int cClearGame::DrawCurrentWavesTimes(HDC hDc)
{
	wchar_t buff[15] = { 0 };
	SetBkMode(hDc, NULL);
	SetTextColor(hDc, RGB(128, 0, 128));
	wsprintf(buff, L"%d次", m_currentWaveTimes);
	TextOut(hDc, 1007, 25, buff, lstrlen(buff));

	return 0;
}

int cClearGame::DrawCurrentBoomNums(HDC hDc)
{

	wchar_t buff[15] = { 0 };
	SetBkMode(hDc, NULL);
	SetTextColor(hDc, RGB(255, 201, 14));
	wsprintf(buff, L"%d发",m_CurrentBoomNums);
	TextOut(hDc, 1010, 450, buff, lstrlen(buff));

	return 0;
}


int cClearGame::ShootBullet(int x, int y, BulletType type,int ATK,int speed,void * Dest,int id)
{
	cBullet bullet;
	bullet.m_x = x;
	bullet.m_y = y;
	bullet.m_ATK = ATK;
	bullet.m_isDie = FALSE;
	bullet.m_speed = speed;
	bullet.m_fps = 0;
	if (type == Bullet_Dragon)
	{
		bullet.m_mxfps = 10;
	}
	bullet.m_type = type;
	bullet.m_Dest = Dest;
	bullet.m_destId = id;

	m_bulletList.push_back(bullet);
	return 0;
}

int cClearGame::DrawBullet(HDC hDc)
{
	HDC hMemDc = CreateCompatibleDC(hDc);
	for (list<cBullet>::iterator it = m_bulletList.begin();it != m_bulletList.end();++it)
	{
		if (it->m_type == Bullet_Dragon)
		{
			SelectObject(hMemDc, m_hBitDragonBoom[it->m_fps]);
			it->m_fps = (it->m_fps + 1) % it->m_mxfps;
			it->Move();
			TransparentBlt(hDc, it->m_x, it->m_y, 50, 50, hMemDc, 0, 0, 50, 50, RGB(128, 128, 128));
		}
		else if (it->m_type == Bullet_Defense)
		{
			SelectObject(hMemDc, m_hBitBullet);
			it->m_fps = (it->m_fps + 1) % it->m_mxfps;
			TransparentBlt(hDc, it->m_x, it->m_y, 35, 35, hMemDc, 0, 0, 35, 35, RGB(128, 128, 128));
		}
	}
	
	DeleteDC(hMemDc);
	return 0;
}

int cClearGame::DeleteBooms()
{
	for (list<cBullet>::iterator it = m_bulletList.begin();it != m_bulletList.end();)
	{
		if (it->m_isDie == TRUE)
		{
			if (it->m_type == Bullet_Dragon)
			{
				/*m_currentBlood >= 0 ? m_currentBlood -= it->m_ATK : m_currentBlood;*/
				if (m_currentBlood <= 0)
				{
					m_gameStatus = GameOverStatus;
					return 0;
				}
			}
			it=m_bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}
	return 0;
}

int cClearGame::CheckDefenseNearby(cDefense &defense)
{
	for (list<cMonster>::iterator it = m_monsterList.begin();it != m_monsterList.end();++it)
	{
		if (it->m_x < 1133)
		{
			int distance = sqrt(((defense.m_x + 100) - (it->m_x + 50))*((defense.m_x + 100) - (it->m_x + 50)) + ((defense.m_y + 70) - (it->m_y + 53))*((defense.m_y + 70) - (it->m_y + 53)));
			if (distance < 160)
			{
				if (defense.m_ATKDelay == 0)
				{
					defense.m_ATKDelay = defense.m_maxATKDelay;
					if (m_CurrentBoomNums > 0)
					{
						--m_CurrentBoomNums;
						ShootBullet(defense.m_x + 100, defense.m_y + 70, Bullet_Defense,defense.m_ATK,defense.m_speed, NULL, it->m_id);
					}
				}
				else
				{
					--defense.m_ATKDelay;
				}
			}
		}
	}
	return 0;
}

BOOL cClearGame::CheckMonsterIsGetBullet(int x, int y, int id)
{
	for (list<cBullet>::iterator it = m_bulletList.begin();it != m_bulletList.end();++it)
	{
		if (id == it->m_destId&&abs(it->m_x - (x+30)) < 20 && abs(it->m_y - (y+30)) < 20)
		{
			it->m_isDie = TRUE;
			return it->m_ATK;
		}
	    if (id == it->m_destId)
		{
			if (abs((x + 30) - (it->m_x)) < 20)
			{
				it->m_x = it->m_x;
			}
			else
			{
				(x + 30) - (it->m_x) >= 0 ? it->m_x += it->m_speed : it->m_x -= it->m_speed;
			}
			if (abs(it->m_y - (y + 30)) < 20)
			{
				it->m_y = it->m_y;
			}
			else
			{
				(y + 30) - (it->m_y) >= 0 ? it->m_y += it->m_speed : it->m_y -= it->m_speed;
			}
		}
	}

	return 0;
}

int cClearGame::DeleteDieMonster()
{
	for (list<cMonster>::iterator it = m_monsterList.begin();it != m_monsterList.end();)
	{
		if (it->m_life <= 0)
		{
			DeleteNoDestBullet(it->m_id);
			it = m_monsterList.erase(it);
			m_Money += 50;
		}
		else
		{
			++it;
		}
	}

	return 0;
}

int cClearGame::DeleteNoDestBullet(int id)
{
	for(list<cBullet>::iterator it = m_bulletList.begin();it != m_bulletList.end();++it)
	{
		if (it->m_destId == id)
		{
			it->m_isDie = TRUE;
		}
	}
	return 0;
}

int cClearGame::ClickRButton()
{
	tagPOINT tagPos;
	GetCursorPos(&tagPos);
	ScreenToClient(m_hWnd, &tagPos);

	if (CheckIsClickDefense(tagPos.x,tagPos.y))
	{
		m_ugradeIcon.isVisible = TRUE;
	}
	return 0;
}

BOOL cClearGame::CheckIsClickDefense(int x, int y)
{
	for (int i = 0;i < 6;++i)
	{
		if (abs((m_defense[i].m_x+100)- x) < 30 && abs((m_defense[i].m_y+70) - y) < 30)
		{
			m_ugradeIcon.x = m_defense[i].m_x + 53;
			m_ugradeIcon.y = m_defense[i].m_y + 30;
			m_ugradeIcon.id = i;
			return TRUE;
		}
	}

	return FALSE;
}

int cClearGame::DrawUgradeIcon(HDC hDc)
{
	HDC hMemDc = CreateCompatibleDC(hDc);
	SelectObject(hMemDc,m_hBitUgrade);
	TransparentBlt(hDc, m_ugradeIcon.x, m_ugradeIcon.y, 100, 68, hMemDc, 0, 0, 100, 68, RGB(255, 255, 255));
	
	DeleteDC(hMemDc);
	return 0;
}

int cClearGame::DrawShootingIcon(HDC hDc)
{
	HDC hMemDc = CreateCompatibleDC(hDc);
	SelectObject(hMemDc, m_hBitShootingStarIcon);
	BitBlt(hDc,545,80,50,50,hMemDc,0,0,SRCCOPY);

	DeleteDC(hMemDc);
	return 0;
}

int cClearGame::DrawShootingStarNums(HDC hDc)
{
	SetBkMode(hDc, NULL);
	SetTextColor(hDc, RGB(247,56,9));
	wchar_t buff[10] = { 0 };
	wsprintf(buff, L"%d个",m_curShootingStarNums);
	TextOut(hDc, 600, 90, buff, lstrlen(buff));

	return 0;
}

BOOL cClearGame::IsOrNotClickShootingStarIcon(int x, int y)
{
	if (x > 545 && x < 545 + 50 && y>80 && y < 80 + 50&&m_curShootingStarNums>0)
	{
		--m_curShootingStarNums;
		return TRUE;
	}

	return FALSE;
}

int cClearGame::MotivateShootingStar()
{
	for (int i = 0;i < 7;++i)
	{
		if (i < 3)
		{
			m_ShootingStarList[i].x = 750 + i * 120;
			m_ShootingStarList[i].y = 0;
			m_ShootingStarList[i].destX = 800 + i * 200;
			m_ShootingStarList[i].destY = 140;
			m_ShootingStarList[i].speed = 15;
			m_ShootingStarList[i].Die = FALSE;
		}
		else
		{
			m_ShootingStarList[i].x = 700 + (i-3) * 120;
			m_ShootingStarList[i].y = 0;
			m_ShootingStarList[i].destX = 700 + (i - 3) * 120;
			m_ShootingStarList[i].destY = 260;
			m_ShootingStarList[i].speed = 15;
			m_ShootingStarList[i].Die = FALSE;
		}
	}
	m_IsOrMotivateSkill = TRUE;
	return 0;
}

int cClearGame::DrawShootingStar(HDC hDc)
{
	HDC hMemDc = CreateCompatibleDC(hDc);
	int iCount = 0;
	for (int i = 0;i < 7;++i)
	{
		if (!m_ShootingStarList[i].Die)
		{
			SelectObject(hMemDc, m_hBitShootingStar[m_ShootingStarList[i].curfps]);
			m_ShootingStarList[i].curfps = (m_ShootingStarList[i].curfps + 1) % m_ShootingStarList[i].maxFps;
			TransparentBlt(hDc, m_ShootingStarList[i].x, m_ShootingStarList[i].y, 47, 100, hMemDc, 0, 0, 47, 100, RGB(128, 128, 128));
			m_ShootingStarList[i].destY > m_ShootingStarList[i].y ? m_ShootingStarList[i].y += m_ShootingStarList[i].speed : m_ShootingStarList[i].y;
			if (m_ShootingStarList[i].y >= m_ShootingStarList[i].destY)
			{
				m_ShootingStarList[i].Die = TRUE;
			}
		}
		else
		{
			++iCount;
		}
	}

	if (iCount == 7)
	{
		m_IsOrMotivateSkill = FALSE;
		DoShootingStar();
	}
	DeleteDC(hMemDc);
	return 0;
}

int cClearGame::DoShootingStar()
{
	for (list<cMonster>::iterator it = m_monsterList.begin();it != m_monsterList.end();++it)
	{
		it->m_life = 0;
	}
	return 0;
}

int cClearGame::CheckGoNext()
{
	if (m_currentWaveTimes == m_maxWaveTimes)
	{
		if (m_NextStatusDelay > 0)
		{
			m_gameStatus = GameNextStatus;
			--m_NextStatusDelay;
		}
		else
		{
			GotoNext();
		}
	}
	return 0;
}

int cClearGame::GotoNext()
{
	m_Select.x = 0;
	m_Select.y = 0;
	m_Money = m_Money;
	m_currentBlood = 123;
	m_monsterID = 0;
	m_maxBoomNums = 90;
	m_currentWaveTimes = 1;
	m_maxWaveTimes = m_gameLevel*5+1;
	m_MonsterNums = 5;
	m_waveDelay = 0;
	m_NextStatusDelay = 10;
	initDefense();
	RandomCreateDiamonds();
	m_monsterList.clear();
	m_bulletList.clear();
	++m_gameLevel;
	m_gameStatus = PlayStatus;
	return 0;
}

int cClearGame::DrawGoNext(HDC hDc)
{
	HDC hMemDC = CreateCompatibleDC(hDc);
	SelectObject(hMemDC, hBitNext);
	BitBlt(hDc, 0, 0, 1133, 520, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(hMemDC);
	return 0;
}