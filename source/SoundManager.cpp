#include "SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() {
    soundEngine = createIrrKlangDevice();
    soundEngine->setSoundVolume(0.5);
}

SoundManager::~SoundManager()
{
    if (instance != nullptr) delete instance;
}

SoundManager* SoundManager::getInstance()
{
    if (instance == nullptr) instance = new SoundManager();
    return instance;
}

ISound* SoundManager::playOnce(const char* filepath)
{
    return soundEngine->play2D(filepath, false);
}

ISound* SoundManager::playInLoop(const char* filepath)
{
    return soundEngine->play2D(filepath, true);
}

void SoundManager::stopPlaying()
{
    return soundEngine->stopAllSounds();
}

void SoundManager::changeVolume(float value)
{
    return soundEngine->setSoundVolume(value);
}

bool SoundManager::drop()
{
    return soundEngine->drop();
}
