#pragma once
#pragma once
#include "Singleton.h"
// �ɼ� ������ ����ü
typedef struct {
    float bgmVolume;       // ������� ����
    int isBGMMuted;        // ������� ���Ұ� ���� (0: ����, 1: ���Ұ�)
    float soundVolume;     // ���� ����
    int isSoundMuted;      // ���� ���Ұ� ���� (0: ����, 1: ���Ұ�)
    int showDamageEffect;  // ����� ����Ʈ ��� ���� (0: ��Ȱ��ȭ, 1: Ȱ��ȭ)
} GameOptions;

class Option : public Singleton<Option>
{
    friend class Singleton<Option>;
private:
    Option() {  }
    ~Option() {}
private:
    GameOptions options;
private:
    void SaveOption() {
        FILE* fp;
        if ((fp = fopen("./options.opt", "wb")) == NULL)
        {
            return;
        }
        //fwrite(&m_SysTem, sizeof(SysTem), 1, fp);
        fwrite(&options, sizeof(options), 1, fp);

        fclose(fp);
    }
    void LoadOption() {
        FILE* fp;
        if ((fp = fopen("./options.opt", "rb")) == NULL)
        {
            return;
        }
        fread(&options, sizeof(options), 1, fp);

        //fread(&m_SysTem, sizeof(SysTem), 1, fp);

        fclose(fp);
    }
public:
    void Init() { LoadOption(); }
public:
    void MuteBGM() { options.isBGMMuted = true; SaveOption(); }
    void MuteSound() { options.isSoundMuted = true; SaveOption(); }

    void UnmuteBGM() { options.isBGMMuted = false; SaveOption(); }
    void UnmuteSound() { options.isSoundMuted = false; SaveOption(); }

    void ActiveDamageEffect() { options.showDamageEffect = true; SaveOption(); }
    void DeactiveDamageEffect() { options.showDamageEffect = false; SaveOption(); }

    bool IsBGMMuted() const { return options.isBGMMuted; }
    bool IsSoundMuted() const { return options.isSoundMuted; }
    bool WillDamageEffect() const { return options.showDamageEffect; }
};