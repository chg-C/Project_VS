#include "Include.h"


Collider coll;


Collider::Collider()
{

}

Collider::~Collider()
{
}

void Collider::Init()
{
	m_rc.left = 0;
	m_rc.top = 600;
	m_rc.right = 1250;
	m_rc.bottom = 720;

}

void Collider::Update()
{
}

void Collider::Draw()
{
	/*if (Gmanager.m_GameStart == true)
	{
		dv_font.DrawString("¡º ", m_rc.left, m_rc.top, D3DCOLOR_ARGB(255, 0, 255, 0));
		dv_font.DrawString(" ¡»", m_rc.right, m_rc.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	}*/

}
