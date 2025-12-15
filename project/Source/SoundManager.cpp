#include "SoundManager.h"
#include <DxLib.h>
#include <unordered_map>
#include <assert.h>
#include "../Library/resourceLoader.h"
#include "../Library/time.h"

std::unordered_map<std::string, int> soundFiles;
std::string soundFolder = "data/Sound/SE/";
int hBGM = -1;
float fadeMaxTime;
float fadeTime;

int hEnv = -1;
int watchCounter = 0;

void SoundManager::Init()
{
	soundFiles.clear();
}

void SoundManager::Update()
{
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
}

void SoundManager::Draw()
{
}

void SoundManager::Release()
{
	for (auto itr = soundFiles.begin(); itr != soundFiles.end();) {
		ResourceLoader::DeleteSoundMem(itr->second);
		itr = soundFiles.erase(itr);
	}
}

void SoundManager::SetFolder(std::string folder)
{
	soundFolder = folder;
}

void SoundManager::Ready(std::string filename)
{
	int h = -1;
	if (soundFiles.contains(filename)) {
		h = soundFiles[filename];
	} else {
		h = ResourceLoader::LoadSoundMem(soundFolder + filename);
		assert(h > 0);
	}
	soundFiles[filename] = h; // ’Ç‰Á
}

int SoundManager::Play(std::string filename)
{
	Ready(filename);
	int h = soundFiles[filename];
	PlaySoundMem(h, DX_PLAYTYPE_BACK);
	return h;
}

void SoundManager::Stop(int handle)
{
	StopSoundMem(handle);
}

bool SoundManager::IsPlaying(int handle)
{
	return (CheckSoundMem(handle)>0);
}

void SoundManager::PlayBGM(std::string filename)
{
	if (hBGM>0) return;

	Ready(filename);
	int h = soundFiles[filename];
	hBGM = PlaySoundMem(h, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255, hBGM);
}

void SoundManager::StopBGM()
{
	StopSoundMem(hBGM);
	hBGM = -1;
}

bool SoundManager::IsPlayingBGM()
{
	return CheckSoundMem(hBGM) > 0;
}

void SoundManager::FadeOutBGM(float sec)
{
	fadeMaxTime = sec;
	fadeTime = 0.0f;
}

void SoundManager::PlayEnv(std::string str)
{
	if (hEnv < 0) {
		Ready(str);
		hEnv = soundFiles[str];
		PlaySoundMem(hEnv, DX_PLAYTYPE_BACK);
	}
	watchCounter = 3;

//	Update()‚ÅAwatchCounter‚ğŒ¸‚ç‚µ‚ÄA0‚É‚È‚Á‚½‚ç‰¹‚ğ~‚ß‚é
}
