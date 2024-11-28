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
	void EffectSoundRegister(const char* path,const char* name,bool isLoop=false);
	void BackGroundSoundRegister(const char* path,const char* name,bool isLoop=true);
	void Effectmute(bool isMute);
	void BGMute(bool isMute);
private:
	std::map<std::string, int> m_BackGroundSound;
	std::map<std::string, int>m_EffectSound;
};