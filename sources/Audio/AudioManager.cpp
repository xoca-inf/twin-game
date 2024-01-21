#include "AudioManager.h"

AudioManager::AudioManager()
{
    W4_LOG_DEBUG("[AudioManager] Loaded");
}

AudioManager::~AudioManager()
{
}

void AudioManager::playSound(std::string path)
{
    if (!isMuted) {
        auto audio = make::sptr<Audio>(path);
        audio->play();
    }
}

void mute(bool off) {
    if (off) {
        AudioManager::instance().setIsMuted(true);
        Audio::setGlobalGain(0);
    }
    else {
        AudioManager::instance().setIsMuted(false);
        Audio::setGlobalGain(1.0);
    }
}

void AudioManager::playMaleSadSound() {
    playSound(maleSadPath);
}

void AudioManager::playMaleHappySound() {
    playSound(maleHappyPath);
}

void AudioManager::playDroppingSound() {
    playSound(droppingPath);
}

void AudioManager::playWaterDropsSound() {
    playSound(waterDropsPath);
}

void AudioManager::playRepairSuccessSound() {
    playSound(repairSuccessPath);
}

void AudioManager::playRepairFailSound() {
    playSound(repairFailPath);
}

void AudioManager::playWinSound()
{
    playSound(winSoundPath);
}

void AudioManager::playClickSound()
{
    playSound(clickSoundPath);
}

void AudioManager::playMusic()
{
    if (!isMuted) {
        music = make::sptr<Audio>(musicPath);
        music->play();
        music->setGain(0.1f);
        music->setLooped(true);
    }
}

