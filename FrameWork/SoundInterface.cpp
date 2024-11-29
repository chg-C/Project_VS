#include "SoundInterface.h"
#include "Include.h"
SoundInterface::SoundInterface()
{
}

SoundInterface::~SoundInterface()
{
}

void SoundInterface::EffectSoundRegister(const char* path,const char* name,bool isLoop)
{
	m_EffectSound[name] = FmodSoundManager::GetInstance().AddSoundFile(path, isLoop);
}

void SoundInterface::BackGroundSoundRegister(const char* path, const char* name, bool isLoop)
{
	m_BackGroundSound[name] = FmodSoundManager::GetInstance().AddSoundFile(path, isLoop);
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

void SoundInterface::Effectmute(bool isMute)
{

	FmodSoundManager::GetInstance().EffectSetVolum(isMute);
}

void SoundInterface::BGMute(bool isMute)
{
	FmodSoundManager::GetInstance().BGMute(isMute);
}