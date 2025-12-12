#include "SoundManager.h"
#include <DxLib.h>
#include <unordered_map>
#include <assert.h>
#include "../Library/resourceLoader.h"
#include "../Library/time.h"

//#define ENABLE_SoundManager 1

#ifdef ENABLE_SoundManager

std::unordered_map<std::string, int> soundFiles;
std::string soundFolder = "data/Sound/SE/";
int hBGM = -1;
float fadeMaxTime;
float fadeTime;

int hEnv = -1;
int watchCounter = 0;
#endif

void SoundManager::Init()
{
#ifdef ENABLE_SoundManager
	soundFiles.clear();
#endif
}

void SoundManager::Update()
{
#ifdef ENABLE_SoundManager
	// a¨b ‚Ì•âŠÔ‚ÍA(b-a)*rate+a
	fadeTime += Time::DeltaTime();
	int vol = (0-255) * (fadeTime / fadeMaxTime) + 255; // 255¨0‚ÉŒü‚©‚¤
	ChangeVolumeSoundMem(vol, hBGM);
	if (fadeTime <= 0) {
		StopSoundMem(hBGM);
	}
	if (hEnv > 0) {
		if (--watchCounter <= 0) {
			Stop(hEnv);
			hEnv = -1;
		}
	}
#endif
}

void SoundManager::Draw()
{
}

void SoundManager::Release()
{
#ifdef ENABLE_SoundManager
	for (auto itr = soundFiles.begin(); itr != soundFiles.end();) {
		ResourceLoader::DeleteSoundMem(itr->second);
		itr = soundFiles.erase(itr);
	}
#endif
}

void SoundManager::SetFolder(std::string folder)
{
#ifdef ENABLE_SoundManager
	soundFolder = folder;
#endif
}

void SoundManager::Ready(std::string filename)
{
#ifdef ENABLE_SoundManager
	int h = -1;
	if (soundFiles.contains(filename)) {
		h = soundFiles[filename];
	} else {
		h = ResourceLoader::LoadSoundMem(soundFolder + filename);
		assert(h > 0);
	}
	soundFiles[filename] = h; // ’Ç‰Á
#endif
}

int SoundManager::Play(std::string filename)
{
#ifdef ENABLE_SoundManager
	Ready(filename);
	int h = soundFiles[filename];
	PlaySoundMem(h, DX_PLAYTYPE_BACK);
	return h;
#endif
	return -1;
}

void SoundManager::Stop(int handle)
{
#ifdef ENABLE_SoundManager
	StopSoundMem(handle);
#endif
}

bool SoundManager::IsPlaying(int handle)
{
	return (CheckSoundMem(handle)>0);
}

void SoundManager::PlayBGM(std::string filename)
{
#ifdef ENABLE_SoundManager
	if (hBGM>0) return;

	Ready(filename);
	int h = soundFiles[filename];
	hBGM = PlaySoundMem(h, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255, hBGM);
#endif
}

void SoundManager::StopBGM()
{
#ifdef ENABLE_SoundManager
	StopSoundMem(hBGM);
	hBGM = -1;
#endif
}

bool SoundManager::IsPlayingBGM()
{
#ifdef ENABLE_SoundManager
	return CheckSoundMem(hBGM) > 0;
#endif
	return true;
}

void SoundManager::FadeOutBGM(float sec)
{
#ifdef ENABLE_SoundManager
	fadeMaxTime = sec;
	fadeTime = 0.0f;
#endif
}

void SoundManager::PlayEnv(std::string str)
{
#ifdef ENABLE_SoundManager
	if (hEnv < 0) {
		Ready(str);
		hEnv = soundFiles[str];
		PlaySoundMem(hEnv, DX_PLAYTYPE_BACK);
	}
	watchCounter = 3;

//	Update()‚ÅAwatchCounter‚ğŒ¸‚ç‚µ‚ÄA0‚É‚È‚Á‚½‚ç‰¹‚ğ~‚ß‚é
#endif
}
