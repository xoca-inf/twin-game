#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

void mute(bool off);

class AudioManager {
public:
    static AudioManager& instance() {
        static AudioManager instance;
        return instance;
    }

    AudioManager();
    virtual ~AudioManager();

    void playMusic();

    void playClickSound();
    void playWinSound();
    void playMaleSadSound();
    void playMaleHappySound();
    void playDroppingSound();
    void playWaterDropsSound();
    void playRepairSuccessSound();
    void playRepairFailSound();

    void setIsMuted(bool isMuted) {
        this->isMuted = isMuted;
    }

private:
    bool isMuted = false;
    std::string clickSoundPath = "Sounds/Click.mp3";
    std::string winSoundPath = "Sounds/win.mp3";
    std::string musicPath = "Sounds/bg_music.mp3";
    std::string droppingPath = "Sounds/dropping.mp3";
    std::string doorCreakPath = "Sounds/door_creak.mp3";
    std::string maleSadPath = "Sounds/Male_Sad.mp3";
    std::string maleHappyPath = "Sounds/male_happy.mp3";
    std::string repairSuccessPath = "Sounds/repair_success.mp3";
    std::string repairFailPath = "Sounds/repair_fail.mp3";
    std::string waterDropsPath = "Sounds/Water_Drops.mp3";

    void playSound(std::string path);

    sptr<Audio> waterRunning;
    sptr<Audio> music;
    bool isWaterPlaying;
};