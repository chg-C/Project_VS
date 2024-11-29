#include "FmodSoundManager.h"
#include "Option.h"
/// <summary>
/// ���� �߰�
/// </summary>
/// <param name="_FullPath">���� ���</param>
/// <param name="_IsLoop">���� ���� ���� True�� Loop</param>
/// <returns>���� ä�� �ε���</returns>
int FmodSoundManager::AddSoundFile(std::string _FullPath, bool _IsLoop)
{
	auto Find = m_CheckList.find(_FullPath);

	if (Find != m_CheckList.end())
	{
		return Find->second;
	}

	Sound* pSound = nullptr;
	int		Mode = FMOD_HARDWARE | (_IsLoop ? FMOD_LOOP_NORMAL | FMOD_DEFAULT : FMOD_LOOP_OFF);

	// ���带 ������ ��ο��� �� ��° ������ LOOP/ONCE �� ���� �ؼ� �ε�
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
/// ����Ʈ �÷���
/// </summary>
/// <param name="_SoundNum"></param>
void FmodSoundManager::EffectPlay(int _SoundNum)
{
	if (Option::GetInstance().IsSoundMuted())
		return;
	auto Find = m_SoundList.find(_SoundNum);

	// ���� ����Ʈ�� ���� ���� ���ϸ� Ŭ���� ����� ������

	// playSound(ä�α׷�, sound, �Ͻ�������?,ä��);
	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pEffectChannel);
}

/// <summary>
/// ����� �÷���
/// </summary>
/// <param name="_SoundNum"></param>
void FmodSoundManager::BGPlay(int _SoundNum)
{
	auto Find = m_SoundList.find(_SoundNum);

	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
	BGMute(Option::GetInstance().IsBGMMuted());
}

/// <summary>
/// ����� ����
/// </summary>
void FmodSoundManager::BGStop()
{
	if (m_pBGChannel != nullptr)
	{
		m_pBGChannel->stop();
	}
}

/// <summary>
/// ���� �ٿ�
/// </summary>
void FmodSoundManager::BGVolumDown()
{
	m_bgVolum -= 0.1f;
	if (m_bgVolum <= 0) m_bgVolum = 0;
	m_pBGChannel->setVolume(m_bgVolum);
}

/// <summary>
/// ���� ��
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