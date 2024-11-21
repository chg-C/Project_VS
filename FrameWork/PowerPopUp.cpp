#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp()
{
	id = 2;
	frame.Create("./resource/Img/Frame/frame5_c4.png", false, D3DCOLOR_XRGB(255, 255, 255));
	UIManager::GetInstance().RegisterPopUp(id, this);
}

PowerPopUp::~PowerPopUp()
{

}

void PowerPopUp::RenderElement()
{

}