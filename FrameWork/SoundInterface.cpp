#include "SoundInterface.h"

SoundInterface::SoundInterface()
{
	m_EffectSound["MenuSelect"] = FmodSoundManager::GetInstance().AddSoundFile("./resource/Sound/MenuSelection.mp3", false);
	m_EffectSound["Click"] = FmodSoundManager::GetInstance().AddSoundFile("./resource/Sound/Click.mp3", false);
	m_BackGroundSound["MenuBGM"] = FmodSoundManager::GetInstance().AddSoundFile("./resource/Sound/MenuBGM.mp3", true);
}

SoundInterface::~SoundInterface()
{
}

int SoundInterface::GetEffectSoundIndex(const string& soundName)const
{
	auto it = m_EffectSound.find(soundName);
	if (it != m_EffectSound.end())
	{
		return it->second;
	}
	else
		return -1;
}
int SoundInterface::GetBackGroundSoundIndex(const string& soundName)const
{
	auto it = m_BackGroundSound.find(soundName);
	if (it != m_BackGroundSound.end())
	{
		return it->second;
	}
	else
		return -1;
}
void SoundInterface::BackGroundSoundPlay(const string& soundName)
{
	int index = GetBackGroundSoundIndex(soundName);
	if (index != -1) {
		FmodSoundManager::GetInstance().BGPlay(index);
	}
}

void SoundInterface::EffectSoundPlay(const string& soundName)
{
	int index = GetEffectSoundIndex(soundName);
	if (index != -1) {
		FmodSoundManager::GetInstance().EffectPlay(index);
	}
}

void SoundInterface::StopBackGroundSound(const string& soundName)
{
	int index = GetBackGroundSoundIndex(soundName);
	if (index != -1)
	{
		FmodSoundManager::GetInstance().BGStop();
	}
}
