#include "FoeTankBox.h"
#include"BigTank.h"
#include"SmallTank.h"

CFoeTankBox::CFoeTankBox(void)
{

}


CFoeTankBox::~CFoeTankBox(void)
{
	list<CFoeTank*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		delete (*ite);
		++ite;
	}
}

void CFoeTankBox::AllFoePlaneMove(CBack&back)
{
	list<CFoeTank*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		if((*ite)->y > 600)
		{
			delete (*ite);
			ite = m_lstFoePlane.erase(ite);
		}
		else
		{
			(*ite)->IsFoxPlaneMove(back);   //  ����̹���ƶ�
			++ite;
		}
	}
}
void CFoeTankBox::AllFoePlaneShow(HDC hdc)
{
	list<CFoeTank*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->ShowFoxPlane(hdc);   //  ��ʾ����̹��
		++ite;
	}	
}

void CFoeTankBox::CreateFoePlane(HINSTANCE hIns)
{
	CFoeTank* pFoePlane1 = 0;
	CFoeTank* pFoePlane2 = 0;

	pFoePlane1 = new CBigTank;
	pFoePlane2 = new CSmallTank;

	//  ��ʼ������̹��
	pFoePlane1->InitFoxPlane(hIns);
	pFoePlane2->InitFoxPlane(hIns);
	
	//  ��ӵ�������
	m_lstFoePlane.push_back(pFoePlane1);
	m_lstFoePlane.push_back(pFoePlane2);
}

void CFoeTankBox::SendGunnerFoePlane(HINSTANCE hIns,CGunnerBox &gunBox)
{
	list<CFoeTank*>::iterator ite = m_lstFoePlane.begin();
	while(ite != m_lstFoePlane.end())
	{
		(*ite)->SendGunner(hIns,gunBox);   //  ����̹�˷����ڵ�
		++ite;
	}	
}
