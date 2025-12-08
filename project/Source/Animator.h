#pragma once
//Animator.h
// GameObjectのComponentとして使う
#include <vector>
#include <string>

class GameObject;

/// <summary>
/// アニメーションの再生を行う
/// </summary>
class Animator {
public:
	Animator(GameObject* _parent);
	~Animator();
	void Update();

	/// <summary>
	/// アニメーションファイルをロードする
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="loop">ループアニメーションの場合はtrue</param>
	void LoadAnimFile(std::string filename, bool loop);

	/// <summary>
	/// アニメーションを再生する
	/// 同じアニメーションの場合は、無視する
	/// </summary>
	/// <param name="id">アニメーション番号</param>
	void Play(int id);

	/// <summary>
	/// ループしないアニメーションが最後まで再生したか調べる
	/// </summary>
	/// <returns>最後にtrue</returns>
	bool IsFinished();

	/// <summary>
	/// 今のアニメーションのフレームを返す
	/// </summary>
	/// <returns>今のフレーム</returns>
	inline float CurrentFrame() { return current.frame; }

	/// <summary>
	/// アニメーションの再生速度（倍率）を変更する
	/// 標準速度は1.0f
	/// </summary>
	/// <param name="speed">再生速度</param>
	void SetPlaySpeed(float speed);

	int PlayingID() { return playingID; }

private:
	GameObject* parent;
	struct AnimInfo {
		int handle;
		bool loop;
	};
	std::vector<AnimInfo> anims;
	struct AttachInfo {
		int attachID;
		float frame;
		float maxFrame;
	};
	AttachInfo current;
	AttachInfo prev;

	int parentModel;
	int playingID;

	float mergeTime;

	float playSpeed;
};