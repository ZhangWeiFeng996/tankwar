#include "GuunerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
		//ɾ�������ڵ�����
	list<CGunner*>::iterator ite = m_lstGunner.begin();

	while(ite != m_lstGunner.end())
	{
		delete *ite;
		ite = m_lstGunner.erase(ite);
	}
}
void CGunnerBox::AllGunnerMove(CBack &back)
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		if((*ite)->y<-9||(*ite)->x<-9||(*ite)->y>609||(*ite)->x>609||true ==(*ite)->GunnerHitWall(back)||true == (*ite)->MoveGunner(back))
		{
			//ɾ������ڵ�����
			delete (*ite);
			ite = m_lstGunner.erase(ite);
		}
		else
		{
			(*ite)->MoveGunner(back);
			++ite;	//****!!!!!����ite++
		}

	}
}
void CGunnerBox::AllGunnerShow(HDC hdc)
{
	list<CGunner*>::iterator ite = m_lstGunner.begin();
	while(ite != m_lstGunner.end())
	{
		(*ite)->ShowGunner(hdc);
		++ite;
	}
}