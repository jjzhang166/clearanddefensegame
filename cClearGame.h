#pragma once
#include<list>
#include"cMyTimer.h"
#include"cDefense.h"
#include"cMonster.h"
#include"cBullet.h"
#include"Other.h"
using namespace std;

class cClearGame:public cMyTimer
{
public:
	cClearGame();
	~cClearGame();

	/*
	*��Ϸ��������
	*���洰�ھ��
	*�������hWnd����ͼ�õĴ��ھ����
	*/
	int GameStart(HWND hWnd);

	/*
	*�̳���cMyTimre���麯��,����ʱ���¼�
	*/
	int OnTimer(int id, int iParam, string str);

	/*
	*����һ���Խ����е�ͼ�λ��Ƶ�������
	*/
	int DrawAll();

	/*
	*������Ϸ����
	*�������hDc������DC
	*/
	int DrawStartBg(HDC hDc);

	/*
	*������Ϸ��Դ
	*����ֵTRUE�����سɹ�;����ֵFALSE������ʧ��
	*/
	BOOL LoadResource();

	/*
	*��������λ���Ƿ�λ��ָ������
	*/
	int CheckMouse();

	/*
	*������ɷ���
	*/
	int RandomCreateDiamonds();

	/*
	*���Ʒ���
	*�������hDc:����DC
	*/
	int DrawDiamonds(HDC hDc);

	/*
	*�ж����ɵķ����Ƿ��ܹ����ڸ�λ��
	*�������i:��ǰ���ɷ���X���ꣻ�������j:��ǰ����Y���ꣻ�������type:��ǰ���ɷ��������
	*����ֵTRUE:��ʾ���ԣ�����ֵFALSE����ʾ������
	*/
	BOOL CheckDiamonds(int i,int j,int type);

	/*
	*��ʼ��Ϸ��ʼ���������Դ
	*/
	int PlayGame();

	/*
	*�жϴ˴���ѡ�ķ����Ƿ����ϴ�����
	*�������i:������ѡ����X���ꣻj:������ѡ����Y����
	*����ֵTRUE:�����ڣ�����ֵFALSE:������
	*/
	BOOL IsAdjacent(int i, int j);

	/*
	*�ƶ�����
	*�������i:������ѡ����X���ꣻj:������ѡ����Y����
	*/
	int MoveDiamonds(int i,int j);

	/*
	*����Ѫ��
	*�������hDc:����DC
	*/
	int DrawBlood(HDC hDc);

	/*
	*�жϷ����ܷ��ƶ�
	*�������i:������ѡ����X����;�������j:������ѡ����Y����
	*����ֵTRUE:����i�ƶ���FALSE:�������ƶ�
	*/
	BOOL CanMove(int i,int j);

	/*
	*�����ƶ��еķ����
	*�������hDc:����DC
	*/
	int DrawMovingDiamonds(HDC hDc);

	/*
	*���������ķ����
	*/
	int ClearDiamonds();

	/*
	*���ƽ�Ǯ
	*�������hDc:����DC
	*/
	int DrawMoney(HDC hDc);

	/*
	*��ո�
	*/
	int FillUpBlank();

	/*
	*Ѱ�������һ����Ϊ�յķ���,���������Ŀո�
	*�������i:�շ����X���ꣻ�������j:�շ����Y����
	*/
	int FindNotNullDiamonds(int i,int j);

	/*
	*�����µķ������ȱ
	*/
	int AddNewDiamonds();

	/*
	*��������ķ����Ƿ����λ�ڸ�λ��
	*�������i����������X���ꣻ�������j:��������Y���ꣻ�������type�����ɵ�����
	*����ֵTRUE:���ԣ�����ֵFALSE��������
	*/
	BOOL CheckIsCanPut(int i,int j,int type);

	/*
	*Ѱ�ҿ��������ķ���鲢�������
	*����ֵTRUE:���ڿ������ķ���飻����ֵFALSE:�����ڿ������ķ����
	*/
	BOOL FindCanClearDiamonds();

	/*
	*�жϸ÷�����Ƿ������
	*�������i:�÷����X���ꣻ�������j���÷����Y����
	*����ֵTRUE:�÷���������������ֵFALSE���÷���鲻������
	*/
	BOOL DiamondsCanClear(int i,int j);

	/*
	*�ж���������Ƿ�Ϊը��
	*�������i:�����X���ꣻ�������j�������Y����
	*����ֵTRUE���������ը��������ֵFALSE������Ĳ���ը��
	*/
	BOOL IsOrNotBoom(int i, int j);

	/*
	�ж���������Ƿ�Ϊ����
	@params i:�����x����
	@params j�������y����
	@return TRUE:�����������
	@return FALSE������Ĳ�������
	*/
	BOOL IsOrNotShootingStar(int i, int j);

	/*
	*������ը�����Ч��
	*�������i��ը����x���ꣻ�������j��ը����y����
	*/
	int DealBoomResult(int i,int j);

	/*
	*����ը��һ�¼�
	*�������i��ը����x���ꣻ�������j��ը����y����
	*/
	int DoBoom1(int i, int j);

	/*
	*����ը�����¼�
	*�������i��ը����x���ꣻ�������j��ը����y����
	*/
	int DoBoom2(int i,int j);

	/*
	*����ը�����¼�
	*�������i��ը����x���ꣻ�������j��ը����y����
	*/
	int DoBoom3(int i,int j);

	/*
	*����ը�����¼�
	*�������i��ը����x���ꣻ�������j��ը����y����
	*/
	int DoBoom4(int i,int j);

	/*
	*���ű�������
	*/
	int PlayBackMusic();

	/*
	*��ͣ��������
	*/
	int PauesBackMusic();

	/*
	*��������ͼ��
	*�������hDc:����Dc
	*/
	int DrawMusicIcon(HDC hDc);

	/*
	*������Ϸ��������
	*�������hDc������DC
	*/
	int DrawGameOver(HDC hDc);

	/*
	*������
	*�������hDc:�豸Dc
	*/
	int DrawMonster(HDC hDc);

	/*
	*��ʼ����������Ϣ
	*/
	int initDefense();

	/*
	*���Ʒ�����
	*@params hDc:�豸DC
	*/
	int DrawDefense(HDC hDc);

	/*
	*����ˮ��
	*@params hDc:�豸DC
	*/
	int DrawCrystal(HDC hDc);

	/*
	*����ˮ����Դ
	*/
	int LoadCrystalResource();

	/*
	*�������
	*/
	int CreateMonster(MonsterType type);

	/*
	*���Ƶ�ǰ���ﲨ��
	*@params hDc���豸DC
	*/
	int DrawCurrentWavesTimes(HDC hDc);

	/*
	*���Ƶ�ǰ�ڵ���
	*@params hDc���豸DC
	*/
	int DrawCurrentBoomNums(HDC hDc);

	/*
	*�����ӵ�
	*@params x:�ӵ���x����
	*@params y:�ӵ���y����
	*@params type:�ӵ�������
	*@params Dest:�ӵ���Ŀ��
	*@params ATK:�ӵ��Ĺ�����
	*@params speed:�ӵ����ٶ�
	*/
	int ShootBullet(int x, int y, BulletType type,int ATK,int speed,void* Dest,int id);

	/*
	*�����ڵ�
	*@params hDc:�豸DC
	*/
	int DrawBullet(HDC hDc);

	/*
	*ɾ���ڵ�
	*/
	int DeleteBooms();

	/*
	*����������Χ��û�й���
	*@params defense:��������Ϣ
	*/
	int CheckDefenseNearby(cDefense &defense);

	/*
	*�������Ƿ��е�
	*@params x:����x����
	*@params y������y����
	*@params id:����id
	*@return:����Ӧʧȥ��Ѫ��
	*/
	int CheckMonsterIsGetBullet(int x, int y, int id);

	/*
	*ɾ����ȥ�Ĺ���
	*/
	int DeleteDieMonster();

	/*
	*ɾ��ʧȥĿ����ڵ�
	*@params id:����id
	*/
	int DeleteNoDestBullet(int id);

	/*
	*����Ҽ����
	*/
	int ClickRButton();

	/*
	�������Ҽ��Ƿ񵥻��˷�����
	*@params x�����x����
	*@params y�����y����
	*@return TRUE��������
	*@return FALSE���޵���
	*/
	BOOL CheckIsClickDefense(int x, int y);

	/*
	*��������ͼ��
	*@params hDc:�豸DC
	*/
	int DrawUgradeIcon(HDC hDc);

	/*
	*��������ͼ��
	*@params hDc:�豸DC
	*/
	int DrawShootingIcon(HDC hDc);

	/*
	*���Ƶ�ǰ���Ǹ���
	*@params hDC:�豸DC
    */
	int DrawShootingStarNums(HDC hDc);

	/*
	*�Ƿ��������Ǽ���ͼ��
	*@params x:�������x����
	*@params y:�������y����
	*@return TRUE:���Դ������Ǽ���
	*@return FALSE:�����Դ������Ǽ���
	*/
	BOOL IsOrNotClickShootingStarIcon(int x,int y);

	/*
	*�������Ǽ���
	*/
	int MotivateShootingStar();

	/*
	*�������Ǽ���
	*@params hDc:�豸DC
	*/
	int DrawShootingStar(HDC hDc);

	/*
	*�������Ǽ����¼�
	*/
	int DoShootingStar();

	/*
	*��������һ��
	*/
	int CheckGoNext();

	/*
	*������һ��
	*/
	int GotoNext();

	/*
	*���ƽ�����һ�ص�״̬
	*@params hDc���豸DC
	*/
	int DrawGoNext(HDC hDc);
private:
	//���ھ��
	HWND m_hWnd;

	//��Ϸ״̬
	int m_gameStatus;

	//ͼ����Դ����
	HBITMAP m_hBitMaps[38];

	//��¼�����λ������
	Diamonds m_diamonds[8][8];

	//�����һ�ε�λ��
	POINT m_Select;

	//���浱ǰѪ��
	int m_currentBlood;

	//��¼��һ�ε���İ�ť
	int m_ClickedBtn;

	//�ж��Ƿ�Ϊ�����ƶ�״̬
	BOOL m_isMoving;
	
	//Ŀ��λ��
	POINT m_destSite;

	//�����Ѿ��ƶ�����
	int m_haveMoved;

	//����
	int m_Money;

	//��������״̬
	int m_backMusicStatus;

	//�������ֵ�װ��ID
	DWORD m_curDerviceID;

	//��������Դͼ
	HBITMAP m_hBitDragon[8];

	//���ﻢ��Դͼ
	HBITMAP m_hBitTiger[6];

	//��������Դ
	HBITMAP m_hBitDefense[20];

	//�ӵ���Դ
	HBITMAP m_hBitBullet;

	//������
	cDefense m_defense[6];

	//ˮ����Դ
	HBITMAP m_hBitCrystal[9];

	//ˮ����Ϣ
	Crystal m_crystal;

	//�洢������Ϣ
	list<cMonster> m_monsterList;

	//��¼��ǰ���ﲨ��
	int m_currentWaveTimes;

	//������󲨴�
	int m_maxWaveTimes;

	//ÿ����������ļ��ʱ��
	int m_waveDelay;

	//ÿ�����������
	int m_MonsterNums;

	//��ǰ�ڵ���
	int m_CurrentBoomNums;

	//����ڵ���
	int m_maxBoomNums;

	//��Ϣ��Դ
	HBITMAP m_hBitDragonBoom[10];

	//�����ӵ���Ϣ
	list<cBullet> m_bulletList;

	//��ǰ����id
	int m_monsterID;

	//����ͼ��
	HBITMAP m_hBitUgrade;

	//��������ͼ����Ϣ
	UgradeIcon m_ugradeIcon;

	//��ǰ�ؿ�
	int m_gameLevel;

	//С����ͼƬ��Դ
	HBITMAP m_hBitLittleDragon[23];

	//����ͼƬ
	HBITMAP m_hBitShootingStar[20];

	//����ͼ��
	HBITMAP m_hBitShootingStarIcon;

	//���Ǽ��ܸ���
	int m_curShootingStarNums;

	//���м���������
	int m_maxShootingStarNums;

	//�Ƿ񼤷������Ǽ���
	BOOL m_IsOrMotivateSkill;

	//����������Ϣ
	ShootingStar m_ShootingStarList[7];

	//��һ�ر���ͼƬ
	HBITMAP hBitNext;

	//��һ���ӳ�
	int m_NextStatusDelay;
};