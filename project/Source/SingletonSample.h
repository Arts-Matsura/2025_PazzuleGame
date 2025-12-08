#pragma once
// シングルトンの書き方のサンプル

class Sample {
public:
	static Sample* GetInstance() { // インスタンスを返す関数
		static Sample* inst = nullptr; // 自分自身にインスタンスを持つ
		if (inst == nullptr)
			inst = new Sample(); // インスタンスがなければ作る
		return inst;
	}
	void Func();
private:
	Sample(); // シングルトンのコンストラクターはprivateに作る
	~Sample();

	int x;
};
