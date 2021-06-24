#include "TankApp.h"

DECLARE(CTankApp)
CTankApp::CTankApp(void)
{
}


CTankApp::~CTankApp(void)
{
}

void CTankApp::OnCreateGame()
{
	//1.������ʼ��
	back.LoadMap(); 
	back.InitBack(m_hIns);
	foetankbox.CreateFoePlane(m_hIns);
	//2.���̹�˳�ʼ��
	player.InitPlayer(m_hIns);
	
	//3.�������ж�ʱ��
	::SetTimer(m_hWnd,PLAYER_MOVE_TIMER_ID,100,0);	//���̹������
	::SetTimer(m_hWnd,PLANER_SENGGUNNER_TIMER_ID,1000,0);	//���̹��350ms����һ���ڵ�
	::SetTimer(m_hWnd,FOETANK_SENDGUNNER_TIMER_ID,2000,0);	//����̹�˷����ڵ�
	::SetTimer(m_hWnd,FOETANK_MOVE_TIMER_ID,100,0);	//����̹���ƶ�
	::SetTimer(m_hWnd,GUNNER_MOVE_TIMER_ID,100,0);	//�ڵ�10ms�ƶ�һ��
	
}
void CTankApp::OnGameDraw()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(m_hWnd,&ps);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,600,600);
	::SelectObject(hMemDC,hBitmap);

	//================================================
	back.ShowBack(hMemDC);
	gunnerbox.AllGunnerShow(hMemDC);
	gunnerFoebox.AllGunnerShow(hMemDC);
	foetankbox.AllFoePlaneShow(hMemDC);
	player.ShowPlayer(hMemDC);
	
	
	
	//====================================================

	::BitBlt(hdc,0,0,600,600,hMemDC,0,0,SRCCOPY);

	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::EndPaint(m_hWnd,&ps);
}
void CTankApp::OnGameRun(WPARAM TimerID)
{

	if(TimerID == FOETANK_SENDGUNNER_TIMER_ID)
	{	
		foetankbox.SendGunnerFoePlane(m_hIns,gunnerFoebox);

	}
	if(TimerID == FOETANK_MOVE_TIMER_ID)
	{
		foetankbox.AllFoePlaneMove(back);		
	}
	if(TimerID == PLANER_SENGGUNNER_TIMER_ID)
	{player.SendGunner(m_hIns,gunnerbox);
	}
	if(TimerID == GUNNER_MOVE_TIMER_ID)
	{gunnerbox.AllGunnerMove(back);
	gunnerFoebox.AllGunnerMove(back);
	int a = this->GunnerHitPlane();
	int b = this->IsFoeGunnerHitPlayer();
	
	if(this->IsGameOver()==true ||a==1||b==1)
		{
		
			::KillTimer(m_hWnd,PLAYER_MOVE_TIMER_ID);
			::KillTimer(m_hWnd,PLANER_SENGGUNNER_TIMER_ID);//��ҷɻ�350ms����һ���ڵ�
			::KillTimer(m_hWnd,GUNNER_MOVE_TIMER_ID);	//�ڵ�10ms�ƶ�һ��
			::KillTimer(m_hWnd,FOETANK_SENDGUNNER_TIMER_ID);	//�������˷ɻ�
			::KillTimer(m_hWnd,FOETANK_MOVE_TIMER_ID);	//���˷ɻ��ƶ�
		
			MessageBox(m_hWnd,"gameover","message",MB_OK);
		}
	
	}
		if(TimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(GetAsyncKeyState(VK_RIGHT))	//GetAsyncKeyState:��һ�¶�һ�£�GetKeyState����һ�²���ͣ
			player.MovePlayer(VK_RIGHT,back);
		if(GetAsyncKeyState(VK_LEFT))
			player.MovePlayer(VK_LEFT,back);
		if(GetAsyncKeyState(VK_UP))
			player.MovePlayer(VK_UP,back);
		if(GetAsyncKeyState(VK_DOWN))
			player.MovePlayer(VK_DOWN,back);
		
	}			
	//�ػ�
	RECT rect = {0,0,600,600};
	::InvalidateRect(m_hWnd,&rect,FALSE);
}
//void CTankApp::OnKeyDown(WPARAM nKey)
//{
//
//}

int CTankApp::GunnerHitPlane()	//�ڵ�ײ������̹��
{
	
	list<CGunner*>::iterator iteGun = gunnerbox.m_lstGunner.begin();
	bool bflag = false;

	while(iteGun != gunnerbox.m_lstGunner.end())
	{
		list<CFoeTank*>::iterator iteFoe = foetankbox.m_lstFoePlane.begin();
		while(iteFoe != foetankbox.m_lstFoePlane.end())
		{
			if((*iteFoe)->IsGunnerHitFoxPlane(*iteGun) ==true)	//����̹�˱�����ڵ�����
			{
				//�򵽵���̹��
				bflag = true;
				//1.ɾ���ڵ�
				delete(*iteGun);
				iteGun = gunnerbox.m_lstGunner.erase(iteGun);
				//2.����̹�˵�Ѫ
				(*iteFoe)->DownBlood();
				if((*iteFoe)->IsBoom() == true)
				{					
					//1.ɾ������̹��
					foetankbox.m_lstFoePlane.erase(iteFoe);

				}	
				break;
			}
			++iteFoe;
		}
		
		if(bflag == false)
		{
			//2.�ж�����ڵ�����home
			if((*iteGun)->GunnerHitHome(back)==true)
			{
				return true;
			}
			++iteGun;
		}
		else
			bflag = false;
	}
	return false;
}

bool CTankApp::IsFoeGunnerHitPlayer()	//�ڵ�ײ�����̹��
{
	
	list<CGunner*>::iterator iteGun = gunnerFoebox.m_lstGunner.begin();
	bool bflag = false;

	while(iteGun != gunnerFoebox.m_lstGunner.end())
	{
			if(player.IsGunnerHitPlayer(*iteGun) ==true)	//���̹�˱��ڵ�����
			{
				//�����̹��
				bflag = true;
				//1.ɾ���ڵ�
				delete(*iteGun);
				iteGun = gunnerFoebox.m_lstGunner.erase(iteGun);
				//2.���̹�˵�Ѫ
				player.DownBlood();
				
				if(player.m_blood == 0)
				{					
					//1.ɾ�����̹�ˣ���Ϸ����
					return true;
				}	
			}
		
		if(bflag == false)
		{//2.�жϵ����ڵ�����home
			if((*iteGun)->GunnerHitHome(back))
				return true;
				++iteGun;
		}
		else
			bflag = false;
	}
	return false;
}

bool CTankApp::IsGameOver()
{
	list<CFoeTank*>::iterator ite = foetankbox.m_lstFoePlane.begin();

	while(ite != foetankbox.m_lstFoePlane.end())
	{
		if((*ite)->IsFoeHitPlayer(player)==true )
			return true;
		++ite;
	}
	if(player.m_blood==0)
		return true;

	return false;
}
