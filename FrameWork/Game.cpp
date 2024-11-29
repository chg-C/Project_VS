#include "Include.h"
#include "ResourceManager.h"
Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	uiIdx = 0;
	ResourceManager::GetInstance().InitResources();

	/*map.Init();
	bird.Init();
	player.Init();
	coll.Init();
	sound.Init();*/
	//Gmanager.Init();
	GameManager::GetInstance().Init();
	sound.BackGroundSoundRegister("./resource/Sound/InGameBGM.mp3", "InGameBGM");
	sound.BackGroundSoundRegister("./resource/Sound/MenuSelection.mp3", "MenuSelection");
	// 데이타 베이스///////////////////
	//sql.Init();
}

void Game::Draw()
{
	
	/*map.Draw();
	bird.Draw();
	player.Draw();
	coll.Draw();*/
	GameManager::GetInstance().Draw();
	if (UIManager::GetInstance().GetPopUp(1)->GetIsOpen())
	{
		UIManager::GetInstance().GetButtons()[1].SetToggleValue(Option::GetInstance().IsSoundMuted());
		UIManager::GetInstance().GetButtons()[2].SetToggleValue(Option::GetInstance().IsBGMMuted());
		UIManager::GetInstance().GetButtons()[3].SetToggleValue(!Option::GetInstance().WillDamageEffect());		
		curPopUp->Draw();
		curPopUp->RenderElement();

	}
	// 데이타 베이스///////////////////
	//sql.Draw();
}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	Time::GetInstance().UpdateTime(1);
	//static int a = 0;
	//if(a == 0) 
	//{
	//	GameTime = GetTickCount();
	//	a = 1;
	//}
	static DWORD a = 0;

	if (GetTickCount64() - a > frame)
	{
		key.Update();
		//bird.Update();
		//player.Update();
		//coll.Update();
		//// 입 맛에 맞게
		//map.Update(130);
		if(!UIManager::GetInstance().GetPopUp(1)->GetIsOpen() && !GameManager::GetInstance().IsPause())
			GameManager::GetInstance().Update();
		// 데이타 베이스///////////////////
		// 입 맛에 맞게 (여기선 안쓰임..프레임 값이 필요 할때만.. 그냥 방법만...)
		//sql.Update(frame+3000);

		a = GetTickCount64();
	}
	

}
void Game::OnMessage( MSG* msg )
{
	switch (msg->message)
	{
	case WM_KEYDOWN:
	case WM_CHAR:
		switch (msg->wParam)
		{
		case VK_UP:
			HandleKeyInput(VK_UP);
			break;
		case VK_DOWN:
			HandleKeyInput(VK_DOWN);
			break;
		case VK_LEFT:
			HandleKeyInput(VK_LEFT);
			break;
		case VK_RIGHT:
			HandleKeyInput(VK_RIGHT);
			break;

		case VK_ESCAPE:
			if (!UIManager::GetInstance().GetPopUp(1)->GetIsOpen())
			{
				UIManager::GetInstance().OpenPopUp(1);
				curPopUp = UIManager::GetInstance().GetPopUp(1);
				UIManager::GetInstance().SetButtonMap(*curPopUp->GetButtonMap());
				UIManager::GetInstance().SetButtons(*curPopUp->GetButtons());
				
			}
			break;
		case VK_RETURN:
			if (UIManager::GetInstance().GetIsButton())
			{
				if (UIManager::GetInstance().GetButtons()[uiIdx].GetIsToggle() == false)
				{
					UIManager::GetInstance().GetButtons()[uiIdx].Clicked();
				}
			}
			wasReturnPressed = true;
		}
		break;
	case WM_KEYUP:
		if (msg->wParam == VK_RETURN)
		{
			if (wasReturnPressed)
			{
				if (UIManager::GetInstance().GetPopUp(1)->GetIsOpen())
					OptionInput();
				wasReturnPressed = false;
			}
		}

	}
}


void Game::HandleKeyInput(int direction)
{
	if (!UIManager::GetInstance().GetPopUp(1)->GetIsOpen())
		return;
	if (!UIManager::GetInstance().GetButtons()[uiIdx].GetActivated())
		return;
	if (UIManager::GetInstance().GetButtonMap().count(uiIdx) > 0 && GetTickCount64() - key.KeyTime > 100) {
		key.KeyTime = GetTickCount64();

		// 방향에 따라 새로운 인덱스 가져오기
		int newIdx;
		switch (direction) {
		case VK_DOWN:  newIdx = std::get<3>(UIManager::GetInstance().GetButtonMap()[uiIdx]); break;
		case VK_UP:    newIdx = std::get<2>(UIManager::GetInstance().GetButtonMap()[uiIdx]); break;
		case VK_LEFT:  newIdx = std::get<0>(UIManager::GetInstance().GetButtonMap()[uiIdx]); break;
		case VK_RIGHT: newIdx = std::get<1>(UIManager::GetInstance().GetButtonMap()[uiIdx]); break;
		}

		if (newIdx >= 0) {
			sound.EffectSoundPlay("MenuSelect");
			UIManager::GetInstance().GetButtons()[uiIdx].SetIsSelected(false);
			uiIdx = newIdx;
			UIManager::GetInstance().GetButtons()[uiIdx].SetIsSelected(true);
			UIManager::GetInstance().SetIsButton(true);
		}
	}
}

void Game::OptionInput()
{
	for (int i = 0; i < UIManager::GetInstance().GetButtons().size(); i++)
	{
		if (UIManager::GetInstance().GetButtons()[i].GetActivated() && UIManager::GetInstance().GetButtons()[i].GetIsSelected())
		{
			if (uiIdx == 0)
			{
				curPopUp->SetClose();
			}
			else if (uiIdx == 1)
			{
				UIManager::GetInstance().GetButtons()[uiIdx].Clicked();
				if (Option::GetInstance().IsSoundMuted())
				{
					Option::GetInstance().UnmuteSound();
				}
				else
				{
					Option::GetInstance().MuteSound();
				}
			}
			else if (uiIdx == 2)
			{
				UIManager::GetInstance().GetButtons()[uiIdx].Clicked();
				if (Option::GetInstance().IsBGMMuted())
				{
					Option::GetInstance().UnmuteBGM();
					sound.BGMute(Option::GetInstance().IsBGMMuted());
				}
				else
				{
					Option::GetInstance().MuteBGM();
					sound.BGMute(Option::GetInstance().IsBGMMuted());
				}

			}
			else if (uiIdx == 3)
			{
				UIManager::GetInstance().GetButtons()[uiIdx].Clicked();
				if (Option::GetInstance().WillDamageEffect())
				{
					Option::GetInstance().DeactiveDamageEffect();
				}
				else
				{
					Option::GetInstance().ActiveDamageEffect();
				}
			}
		}
	}
}

void Game::OnSwitched()
{
	sound.BackGroundSoundPlay("InGameBGM");
	Time::GetInstance().UpdateTime(1);
}