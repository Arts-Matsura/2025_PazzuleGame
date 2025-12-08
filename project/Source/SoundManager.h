#pragma once
#include <string>

// SE‚ÆBGM‚ğŠÇ—EÄ¶‚ğs‚¤

namespace SoundManager {
	void Init();
	void Update();
	void Draw();
	void Release();
	// SE‚ğ–Â‚ç‚·
	void SetFolder(std::string folder);
	void Ready(std::string str);
	int Play(std::string str);
	void Stop(int handle);
	bool IsPlaying(int handle);

	void PlayBGM(std::string str);
	void StopBGM();
	bool IsPlayingBGM();
	void FadeOutBGM(float sec);

	void PlayEnv(std::string str);
};