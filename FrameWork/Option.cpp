#include "Option.h"

Option::Option():exitBtn(1,false)
{
	sprite.Create("./resource/Img/Frame/frame5_c4.png",false,D3DCOLOR_XRGB(0,0,0));
	exitBtn.Init("./resource/Img/Button/button_c8.png");
}
Option::~Option()
{

}
void Option::Open()
{

}