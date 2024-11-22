#pragma once
#pragma once
#include "Singleton.h"
// 옵션 데이터 구조체
typedef struct {
    float bgmVolume;       // 배경음악 볼륨
    int isBGMMuted;        // 배경음악 음소거 여부 (0: 해제, 1: 음소거)
    float soundVolume;     // 사운드 볼륨
    int isSoundMuted;      // 사운드 음소거 여부 (0: 해제, 1: 음소거)
    int showDamageEffect;  // 대미지 이펙트 출력 여부 (0: 비활성화, 1: 활성화)
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