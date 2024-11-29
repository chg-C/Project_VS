#pragma once
// FOMD 비지니스 로직
#include "FMODENGIN//inc//fmod.hpp"
#pragma	comment (lib, "FMODENGIN/lib/fmodex64_vc.lib") // 1. 경로의 명시적 효과, 속성 창에 라이브러리 추가
#include "Singleton.h"
#include <string>
using std::string;
using namespace FMOD;

// STL 컨테이너
#include <map>

class FmodSoundManager :public Singleton<FmodSoundManager>
{
public:
	friend class Singleton<FmodSoundManager>;

private:
	System* m_pSystem;
	int			m_Index;
	Channel* m_pBGChannel;
	Channel* m_pEffectChannel;
	float       m_bgVolum;
	float		m_efVolum;

	FmodSoundManager()
	{
		System_Create(&m_pSystem);
		// init(채널 최대설정값, 초기화 시점 , 추가로 넣을 보조 드라이버 );
		m_pSystem->init(10, FMOD_INIT_NORMAL, 0);

		m_Index = 0;
		m_bgVolum = 1.0f;
		m_efVolum = 1.0f;
 		m_pBGChannel = nullptr;
		m_pEffectChannel = nullptr;
	}
	~FmodSoundManager()
	{
		m_CheckList.clear();

		for (auto& Iter : m_SoundList)
		{
			Iter.second->release();
		}
		m_SoundList.clear();

		m_pSystem->release();
		m_pSystem->close();
	}

public:
	std::map<std::string, int >	m_CheckList;
	std::map<int, Sound* >		m_SoundList;

	// 사운드 추가 
	int	AddSoundFile(std::string _FullPath, bool _IsLoop);


	// 이펙트 플레이
	void EffectPlay(int _SoundNum);


	// 배경음 플레이
	void BGPlay(int _SoundNum);


	// 배경음 멈춤
	void BGStop();


	// 볼륨 다운
	void BGVolumDown();

	// 볼륨 업
	void BGVolumUp();

	void BGSetVolum(int volum);

	void BGMute(bool isMute);

	void EffectVolumDown();
	void EffectVolumUp();
	void EffectSetVolum(int volum);

};