#pragma once
#include <windows.h>

#define DECLARE(ThisClass) \
	CGameApp* CreateObject()\
	{\
		return new ThisClass;\
	}


class CGameApp
{
protected:
	HINSTANCE m_hIns;
	HWND m_hWnd;
public:
	CGameApp()
	{
		m_hIns = 0;
		m_hWnd = 0;
	}
	virtual ~CGameApp()
	{
	
	}
public:
	void SetHandle(HINSTANCE hIns,HWND hwnd)
	{
		m_hIns = hIns;
		m_hWnd = hwnd;
	}
public:
	virtual void OnCreateGame(){}   //  ��Ҫ  HINSTANCE
	virtual void OnGameDraw(){}      //  ��Ҫ HWND
	virtual void OnGameRun(WPARAM nTimerID){}        //  ��Ҫ  WPARAM �����ʱ�����
	virtual void OnKeyDown(WPARAM nKey){}         // ��Ҫ  WPARAM �������İ���
	virtual void OnKeyUp(WPARAM nKey){}			// ��Ҫ  WPARAM �������İ���
	virtual void OnLButtonDown(POINT point){}     //  ��Ҫһ�������  ����Ļ�ȡ��ͨ�� LPARAM
	virtual void OnLButtonUp(POINT point){}		//  ��Ҫһ�������  ����Ļ�ȡ��ͨ�� LPARAM
	virtual void OnMouseMove(POINT point){}		//  ��Ҫһ�������  ����Ļ�ȡ��ͨ�� LPARAM
};