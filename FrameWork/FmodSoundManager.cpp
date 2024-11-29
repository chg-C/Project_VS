#include "FmodSoundManager.h"
#include "Option.h"
/// <summary>
/// 사운드 추가
/// </summary>
/// <param name="_FullPath">사운드 경로</param>
/// <param name="_IsLoop">사운드 루프 여부 True시 Loop</param>
/// <returns>사운드 채널 인덱스</returns>
int FmodSoundManager::AddSoundFile(std::string _FullPath, bool _IsLoop)
{
	auto Find = m_CheckList.find(_FullPath);

	if (Find != m_CheckList.end())
	{
		return Find->second;
	}

	Sound* pSound = nullptr;
	int		Mode = FMOD_HARDWARE | (_IsLoop ? FMOD_LOOP_NORMAL | FMOD_DEFAULT : FMOD_LOOP_OFF);

	// 사운드를 지정된 경로에서 두 번째 인자인 LOOP/ONCE 로 선택 해서 로딩
	m_pSystem->createSound(_FullPath.c_str(), Mode, 0, &pSound);

	if (pSound == nullptr)
	{
		return -1;
	}

	m_CheckList.insert(std::make_pair(_FullPath, m_Index));
	m_SoundList.insert(std::make_pair(m_Index, pSound));

	return m_Index++;
}

/// <summary>
/// 이펙트 플레이
/// </summary>
/// <param name="_SoundNum"></param>
void FmodSoundManager::EffectPlay(int _SoundNum)
{
	if (Option::GetInstance().IsSoundMuted())
		return;
	auto Find = m_SoundList.find(_SoundNum);

	// 만약 이펙트도 볼륨 조절 원하면 클래스 멤버로 빼야함

	// playSound(채널그룹, sound, 일시정지니?,채널);
	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pEffectChannel);
}

/// <summary>
/// 배경음 플레이
/// </summary>
/// <param name="_SoundNum"></param>
void FmodSoundManager::BGPlay(int _SoundNum)
{
	auto Find = m_SoundList.find(_SoundNum);

	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
	BGMute(Option::GetInstance().IsBGMMuted());
}

/// <summary>
/// 배경음 멈춤
/// </summary>
void FmodSoundManager::BGStop()
{
	if (m_pBGChannel != nullptr)
	{
		m_pBGChannel->stop();
	}
}

/// <summary>
/// 볼륨 다운
/// </summary>
void FmodSoundManager::BGVolumDown()
{
	m_bgVolum -= 0.1f;
	if (m_bgVolum <= 0) m_bgVolum = 0;
	m_pBGChannel->setVolume(m_bgVolum);
}

/// <summary>
/// 볼륨 업
/// </summary>
void FmodSoundManager::BGVolumUp()
{
	m_bgVolum += 0.1f;
	if (m_bgVolum >= 1.0) m_bgVolum = 1.0;
	m_pBGChannel->setVolume(m_bgVolum);
}


void FmodSoundManager::BGSetVolum(int volum)
{
	if (volum < 0)
		m_bgVolum = 0;
	else if (volum > 1)
		m_bgVolum = 1;
	else
		m_bgVolum = volum;
	m_pBGChannel->setVolume(m_bgVolum);
}
void FmodSoundManager::BGMute(bool isMute)
{
	if (isMute)
		m_bgVolum = 0;
	else
		m_bgVolum = 1;
	m_pBGChannel->setVolume(m_bgVolum);
}

void FmodSoundManager::EffectVolumDown()
{
	m_efVolum -= 0.1f;
	if (m_efVolum >= 1.0) m_efVolum = 1.0;
	m_pEffectChannel->setVolume(m_efVolum);
}

void FmodSoundManager::EffectVolumUp()
{
	m_efVolum += 0.1f;
	if (m_efVolum >= 1.0) m_efVolum = 1.0;
	m_pEffectChannel->setVolume(m_efVolum);
}

void FmodSoundManager::EffectSetVolum(int volum)
{
	if (volum < 0)
		m_efVolum = 0;
	else if (volum > 1)
		m_efVolum = 1;
	else
		m_efVolum = volum;
	m_pEffectChannel->setVolume(m_efVolum);
}