#pragma once
#include "FmodSoundManager.h"

class SoundInterface
{
public:
	SoundInterface();
	~SoundInterface();

	int GetEffectSoundIndex(const string& soundName)const;
	int GetBackGroundSoundIndex(const string& soundName)const;
	void BackGroundSoundPlay(const string& soundName);
	void EffectSoundPlay(const string& soundName);
	void StopBackGroundSound(const string& soundName);
private:
	std::map<std::string, int> m_BackGroundSound;
	std::map<std::string, int>m_EffectSound;
};