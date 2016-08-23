
#include "MusicHandle.h"
//#include "AdsHelper.h"

using namespace cocos2d::experimental;



MusicHandle::MusicHandle()
{
	m_nBgmId = AudioEngine::INVALID_AUDIO_ID;
	m_SoundOn = UserDefault::getInstance()->getBoolForKey("SoundOn", true);
	m_BgmOn = UserDefault::getInstance()->getBoolForKey("BgmOn", true);
	m_ShakeOn = UserDefault::getInstance()->getBoolForKey("ShakeOn", true);
}

MusicHandle::~MusicHandle()
{

}

void MusicHandle::playBackgroundMusic()
{
	if (MusicHandle::getInstance()->getBgmOn())
	{
		int audioId = MusicHandle::getInstance()->m_nBgmId;
		if (audioId == AudioEngine::INVALID_AUDIO_ID||
			AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING){

			MusicHandle::getInstance()->m_nBgmId=AudioEngine::play2d(BackGroundMusic, true);
		}
	}
}

int MusicHandle::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile *profile)
{
	if (MusicHandle::getInstance()->getSoundOn())
		return AudioEngine::play2d(filePath, loop, volume, profile);
	else
		return AudioEngine::INVALID_AUDIO_ID;
}

void MusicHandle::switchSoundOn()
{
	auto _muiceHandle = MusicHandle::getInstance();
	_muiceHandle->m_SoundOn = !_muiceHandle->m_SoundOn;
	UserDefault::getInstance()->setBoolForKey("SoundOn", _muiceHandle->m_SoundOn);
}

void MusicHandle::switchBgmOn()
{
	auto _muiceHandle = MusicHandle::getInstance();
	_muiceHandle->m_BgmOn = !_muiceHandle->m_BgmOn;
	UserDefault::getInstance()->setBoolForKey("BgmOn", _muiceHandle->m_BgmOn);
	if (_muiceHandle->m_BgmOn)
		playBackgroundMusic();
	else
		stopBackgroundMusic();
}

//ÇÐ»»Õð¶¯Ð§¹û
void MusicHandle::switchShake()
{
	auto _muiceHandle = MusicHandle::getInstance();
	_muiceHandle->m_ShakeOn = !_muiceHandle->m_ShakeOn;
	UserDefault::getInstance()->setBoolForKey("ShakeOn", _muiceHandle->m_ShakeOn);
}

void MusicHandle::playShake()
{
	auto _muiceHandle = MusicHandle::getInstance();
	if (_muiceHandle->m_ShakeOn){
		//AdsHelper::StartPhoneShake();
	}
}

void MusicHandle::stopBackgroundMusic(){
	int audioId = MusicHandle::getInstance()->m_nBgmId;
	if (audioId != AudioEngine::INVALID_AUDIO_ID){
		AudioEngine::stop(audioId);
	}
}
void MusicHandle::pasueAllEffect(){
	AudioEngine::pauseAll();
};
void MusicHandle::resumeAllEffect(){
	AudioEngine::resumeAll();
};
void MusicHandle::stopAllEffect(){
	AudioEngine::stopAll();
};

void MusicHandle::playTouchBtnEffect(){
	play2d(TouchBtnEffect);
}
