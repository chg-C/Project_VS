#include "FmodSoundManager.h"

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
	auto Find = m_SoundList.find(_SoundNum);

	// ���� ����Ʈ�� ���� ���� ���ϸ� Ŭ���� ����� ������
	Channel* pChannel = nullptr;

	// playSound(ä�α׷�, sound, �Ͻ�������?,ä��);
	m_pSystem->playSound(FMOD_CHANNEL_FREE, Find->second, 0, &pChannel);
}

/// <summary>
/// ����� �÷���
/// </summary>
/// <param name="_SoundNum"></param>
void FmodSoundManager::BGPlay(int _SoundNum)
{
	auto Find = m_SoundList.find(_SoundNum);

	m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
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
void FmodSoundManager::VolumDown()
{
	m_volum -= 0.1f;
	if (m_volum <= 0) m_volum = 0;
	m_pBGChannel->setVolume(m_volum);
}

/// <summary>
/// ���� ��
/// </summary>
void FmodSoundManager::VolumUp()
{
	m_volum += 0.1f;
	if (m_volum >= 1.0) m_volum = 1.0;
	m_pBGChannel->setVolume(m_volum);
}


void FmodSoundManager::SetVolum(int volum)
{
	if (volum < 0)
		m_volum = 0;
	else if (volum > 1)
		m_volum = 1;
	else
		m_volum = volum;
}
