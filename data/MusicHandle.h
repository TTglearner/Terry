
#ifndef __MUSICHANDLE__H__
#define __MUSICHANDLE__H__

#define BackGroundMusic	 "audio/music/Background.mp3" 
#define TouchBtnEffect	 "audio/effect/Audio_Button_Click.ogg"  


#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "Singleton.h"
USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
//	音效管理
class MusicHandle : public Singleton<MusicHandle>
{
	//音乐播放的tag
	int m_nBgmId;

	CC_SYNTHESIZE_READONLY(bool, m_SoundOn, SoundOn);
	CC_SYNTHESIZE_READONLY(bool, m_BgmOn, BgmOn);
	CC_SYNTHESIZE_READONLY(bool, m_ShakeOn, ShakeOn);
public:
	MusicHandle();
	~MusicHandle();
	
	//播放音乐
	static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const experimental::AudioProfile *profile = nullptr);

	//切换音效按钮
	static void switchSoundOn();

	//切换背景音乐按钮
	static void switchBgmOn();

	//切换震动效果
	static void switchShake();
	static void playShake();		//播放手机震动

	//播放背景音乐和暂停背景音乐
	static void playBackgroundMusic();
	static void stopBackgroundMusic();


	static void pasueAllEffect();
	static void resumeAllEffect();
	static void stopAllEffect();

	static void playTouchBtnEffect();

};

#endif //__MUSICHANDLE__H__