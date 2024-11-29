#pragma once
// FOMD �����Ͻ� ����
#include "FMODENGIN//inc//fmod.hpp"
#pragma	comment (lib, "FMODENGIN/lib/fmodex64_vc.lib") // 1. ����� ����� ȿ��, �Ӽ� â�� ���̺귯�� �߰�
#include "Singleton.h"
#include <string>
using std::string;
using namespace FMOD;

// STL �����̳�
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
		// init(ä�� �ִ뼳����, �ʱ�ȭ ���� , �߰��� ���� ���� ����̹� );
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

	// ���� �߰� 
	int	AddSoundFile(std::string _FullPath, bool _IsLoop);


	// ����Ʈ �÷���
	void EffectPlay(int _SoundNum);


	// ����� �÷���
	void BGPlay(int _SoundNum);


	// ����� ����
	void BGStop();


	// ���� �ٿ�
	void BGVolumDown();

	// ���� ��
	void BGVolumUp();

	void BGSetVolum(int volum);

	void BGMute(bool isMute);

	void EffectVolumDown();
	void EffectVolumUp();
	void EffectSetVolum(int volum);

};