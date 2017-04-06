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
	*游戏启动调用
	*保存窗口句柄
	*传入参数hWnd：绘图用的窗口句柄；
	*/
	int GameStart(HWND hWnd);

	/*
	*继承自cMyTimre的虚函数,处理定时器事件
	*/
	int OnTimer(int id, int iParam, string str);

	/*
	*用于一次性将所有的图形绘制到窗口中
	*/
	int DrawAll();

	/*
	*绘制游戏背景
	*传入参数hDc：窗口DC
	*/
	int DrawStartBg(HDC hDc);

	/*
	*加载游戏资源
	*返回值TRUE：加载成功;返回值FALSE：加载失败
	*/
	BOOL LoadResource();

	/*
	*监测鼠标点击位置是否位于指定区域
	*/
	int CheckMouse();

	/*
	*随机生成方块
	*/
	int RandomCreateDiamonds();

	/*
	*绘制方块
	*传入参数hDc:窗口DC
	*/
	int DrawDiamonds(HDC hDc);

	/*
	*判断生成的方格是否能够放在该位置
	*传入参数i:当前生成方格X坐标；传入参数j:当前方格Y坐标；传入参数type:当前生成方格的类型
	*返回值TRUE:表示可以，返回值FALSE：表示不可以
	*/
	BOOL CheckDiamonds(int i,int j,int type);

	/*
	*开始游戏初始化方块等资源
	*/
	int PlayGame();

	/*
	*判断此次所选的方块是否与上次相邻
	*传入参数i:本次所选方块X坐标；j:本次所选方块Y坐标
	*返回值TRUE:是相邻；返回值FALSE:不相邻
	*/
	BOOL IsAdjacent(int i, int j);

	/*
	*移动方格
	*传入参数i:本次所选方块X坐标；j:本次所选方块Y坐标
	*/
	int MoveDiamonds(int i,int j);

	/*
	*绘制血量
	*传入参数hDc:窗口DC
	*/
	int DrawBlood(HDC hDc);

	/*
	*判断方格能否移动
	*传入参数i:本次所选方格X坐标;传入参数j:本次所选方格Y坐标
	*返回值TRUE:可以i移动；FALSE:不可以移动
	*/
	BOOL CanMove(int i,int j);

	/*
	*绘制移动中的方格块
	*传入参数hDc:窗口DC
	*/
	int DrawMovingDiamonds(HDC hDc);

	/*
	*清除可清除的方格块
	*/
	int ClearDiamonds();

	/*
	*绘制金钱
	*传入参数hDc:窗口DC
	*/
	int DrawMoney(HDC hDc);

	/*
	*填补空格
	*/
	int FillUpBlank();

	/*
	*寻找上面第一个不为空的方格,并填充下面的空格
	*传入参数i:空方格的X坐标；传入参数j:空方格的Y坐标
	*/
	int FindNotNullDiamonds(int i,int j);

	/*
	*生成新的方格填补空缺
	*/
	int AddNewDiamonds();

	/*
	*检测新增的方格是否可以位于该位置
	*传入参数i：新增方格X坐标；传入参数j:新增方格Y坐标；传入参数type：生成的类型
	*返回值TRUE:可以；返回值FALSE：不可以
	*/
	BOOL CheckIsCanPut(int i,int j,int type);

	/*
	*寻找可以消除的方格块并标记消除
	*返回值TRUE:存在可消除的方格块；返回值FALSE:不存在可消除的方格块
	*/
	BOOL FindCanClearDiamonds();

	/*
	*判断该方格块是否可消除
	*传入参数i:该方格的X坐标；传入参数j：该方格的Y坐标
	*返回值TRUE:该方格块可消除；返回值FALSE：该方格块不可消除
	*/
	BOOL DiamondsCanClear(int i,int j);

	/*
	*判断鼠标点击的是否为炸弹
	*传入参数i:点击的X坐标；传入参数j：点击的Y坐标
	*返回值TRUE：点击的是炸弹；返回值FALSE：点击的不是炸弹
	*/
	BOOL IsOrNotBoom(int i, int j);

	/*
	判断鼠标点击的是否为流星
	@params i:点击的x坐标
	@params j：点击的y坐标
	@return TRUE:点击的是流星
	@return FALSE：点击的不是流星
	*/
	BOOL IsOrNotShootingStar(int i, int j);

	/*
	*处理点击炸弹后的效果
	*传入参数i：炸弹的x坐标；传入参数j：炸弹的y坐标
	*/
	int DealBoomResult(int i,int j);

	/*
	*处理炸弹一事件
	*传入参数i：炸弹的x坐标；传入参数j：炸弹的y坐标
	*/
	int DoBoom1(int i, int j);

	/*
	*处理炸弹二事件
	*传入参数i：炸弹的x坐标；传入参数j：炸弹的y坐标
	*/
	int DoBoom2(int i,int j);

	/*
	*处理炸弹三事件
	*传入参数i：炸弹的x坐标；传入参数j：炸弹的y坐标
	*/
	int DoBoom3(int i,int j);

	/*
	*处理炸弹四事件
	*传入参数i：炸弹的x坐标；传入参数j：炸弹的y坐标
	*/
	int DoBoom4(int i,int j);

	/*
	*播放背景音乐
	*/
	int PlayBackMusic();

	/*
	*暂停背景音乐
	*/
	int PauesBackMusic();

	/*
	*绘制音乐图标
	*传入参数hDc:窗口Dc
	*/
	int DrawMusicIcon(HDC hDc);

	/*
	*绘制游戏结束界面
	*传入参数hDc：窗口DC
	*/
	int DrawGameOver(HDC hDc);

	/*
	*画怪物
	*传入参数hDc:设备Dc
	*/
	int DrawMonster(HDC hDc);

	/*
	*初始化防御塔信息
	*/
	int initDefense();

	/*
	*绘制防御塔
	*@params hDc:设备DC
	*/
	int DrawDefense(HDC hDc);

	/*
	*绘制水晶
	*@params hDc:设备DC
	*/
	int DrawCrystal(HDC hDc);

	/*
	*加载水晶资源
	*/
	int LoadCrystalResource();

	/*
	*创造怪物
	*/
	int CreateMonster(MonsterType type);

	/*
	*绘制当前怪物波次
	*@params hDc：设备DC
	*/
	int DrawCurrentWavesTimes(HDC hDc);

	/*
	*绘制当前炮弹数
	*@params hDc：设备DC
	*/
	int DrawCurrentBoomNums(HDC hDc);

	/*
	*发射子弹
	*@params x:子弹的x坐标
	*@params y:子弹的y坐标
	*@params type:子弹的类型
	*@params Dest:子弹的目标
	*@params ATK:子弹的攻击力
	*@params speed:子弹的速度
	*/
	int ShootBullet(int x, int y, BulletType type,int ATK,int speed,void* Dest,int id);

	/*
	*绘制炮弹
	*@params hDc:设备DC
	*/
	int DrawBullet(HDC hDc);

	/*
	*删除炮弹
	*/
	int DeleteBooms();

	/*
	*检测防御塔周围有没有怪物
	*@params defense:防御塔信息
	*/
	int CheckDefenseNearby(cDefense &defense);

	/*
	*检测怪物是否中弹
	*@params x:怪物x作标
	*@params y：怪物y作标
	*@params id:怪物id
	*@return:怪物应失去的血量
	*/
	int CheckMonsterIsGetBullet(int x, int y, int id);

	/*
	*删除死去的怪物
	*/
	int DeleteDieMonster();

	/*
	*删除失去目标的炮弹
	*@params id:怪物id
	*/
	int DeleteNoDestBullet(int id);

	/*
	*鼠标右键点击
	*/
	int ClickRButton();

	/*
	监测鼠标右键是否单击了防御塔
	*@params x：鼠标x作标
	*@params y：鼠标y坐标
	*@return TRUE：单击了
	*@return FALSE：无单击
	*/
	BOOL CheckIsClickDefense(int x, int y);

	/*
	*绘制升级图标
	*@params hDc:设备DC
	*/
	int DrawUgradeIcon(HDC hDc);

	/*
	*绘制流行图标
	*@params hDc:设备DC
	*/
	int DrawShootingIcon(HDC hDc);

	/*
	*绘制当前流星个数
	*@params hDC:设备DC
    */
	int DrawShootingStarNums(HDC hDc);

	/*
	*是否点击了流星技能图表
	*@params x:鼠标点击的x坐标
	*@params y:鼠标点击的y坐标
	*@return TRUE:可以触发流星技能
	*@return FALSE:不可以触发流星技能
	*/
	BOOL IsOrNotClickShootingStarIcon(int x,int y);

	/*
	*激发流星技能
	*/
	int MotivateShootingStar();

	/*
	*绘制流星技能
	*@params hDc:设备DC
	*/
	int DrawShootingStar(HDC hDc);

	/*
	*处理流星技能事件
	*/
	int DoShootingStar();

	/*
	*检测进入下一关
	*/
	int CheckGoNext();

	/*
	*进入下一关
	*/
	int GotoNext();

	/*
	*绘制进入下一关的状态
	*@params hDc：设备DC
	*/
	int DrawGoNext(HDC hDc);
private:
	//窗口句柄
	HWND m_hWnd;

	//游戏状态
	int m_gameStatus;

	//图像资源数组
	HBITMAP m_hBitMaps[38];

	//记录方格块位置数组
	Diamonds m_diamonds[8][8];

	//光标上一次的位置
	POINT m_Select;

	//保存当前血量
	int m_currentBlood;

	//记录上一次点击的按钮
	int m_ClickedBtn;

	//判定是否为方格移动状态
	BOOL m_isMoving;
	
	//目标位置
	POINT m_destSite;

	//方格已经移动距离
	int m_haveMoved;

	//分数
	int m_Money;

	//背景音乐状态
	int m_backMusicStatus;

	//播放音乐的装置ID
	DWORD m_curDerviceID;

	//怪物龙资源图
	HBITMAP m_hBitDragon[8];

	//怪物虎资源图
	HBITMAP m_hBitTiger[6];

	//防御塔资源
	HBITMAP m_hBitDefense[20];

	//子弹资源
	HBITMAP m_hBitBullet;

	//防御塔
	cDefense m_defense[6];

	//水晶资源
	HBITMAP m_hBitCrystal[9];

	//水晶信息
	Crystal m_crystal;

	//存储怪物信息
	list<cMonster> m_monsterList;

	//记录当前怪物波次
	int m_currentWaveTimes;

	//怪物最大波次
	int m_maxWaveTimes;

	//每波怪物出场的间隔时间
	int m_waveDelay;

	//每波怪物的数量
	int m_MonsterNums;

	//当前炮弹数
	int m_CurrentBoomNums;

	//最大炮弹数
	int m_maxBoomNums;

	//龙息资源
	HBITMAP m_hBitDragonBoom[10];

	//储存子弹信息
	list<cBullet> m_bulletList;

	//当前怪物id
	int m_monsterID;

	//升级图标
	HBITMAP m_hBitUgrade;

	//保存升级图标信息
	UgradeIcon m_ugradeIcon;

	//当前关卡
	int m_gameLevel;

	//小飞龙图片资源
	HBITMAP m_hBitLittleDragon[23];

	//流星图片
	HBITMAP m_hBitShootingStar[20];

	//流行图标
	HBITMAP m_hBitShootingStarIcon;

	//流星技能个数
	int m_curShootingStarNums;

	//流行技能最大个数
	int m_maxShootingStarNums;

	//是否激发了流星技能
	BOOL m_IsOrMotivateSkill;

	//保存流星信息
	ShootingStar m_ShootingStarList[7];

	//下一关背景图片
	HBITMAP hBitNext;

	//下一关延迟
	int m_NextStatusDelay;
};