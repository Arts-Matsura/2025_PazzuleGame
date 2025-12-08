#include "MeteorManager.h"


namespace
{
	const char* METEOR_MESH = "Meteor2.mv1";
	const Vector3 TEST_CREATE_POS = Vector3(1000.0f, 1800.0f, 1000.0f);
	const float CREATE_INTERVAL = 5.0f;
	const int POOL_SIZE = 40;
}

// Invokeで呼ばれる。
void OnTestEvent(const Transform& _transform) //actionの<>の中を引数にする
{
	DebugLog("流星が消えました ①");//処理
}
void MeteorManager::OnTestEventM(const Transform& _transform)
{
	DebugLog("流星が消えました ②");//処理
}

MeteorManager::MeteorManager()
{
	std::string path = "data/model/";
	h_meteor_mesh = MV1LoadModel((path + METEOR_MESH).c_str());


	#pragma region ActionEventのサンプル
	
	// 普通に登録
	OnDestroyMeteor += OnTestEvent;

	// メソッドを登録 (ラムダ式)
	// ①関数を呼ぶための[ポインタ]を渡す。②型<>を(引数)に記述。③ラムダ式で関数を呼ぶ。
	OnDestroyMeteor += [this](const Transform& t) { this->OnTestEventM(t); };

	#pragma endregion
}

MeteorManager::~MeteorManager()
{
}


void MeteorManager::Start()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		Meteor* meteor = new Meteor(MV1DuplicateModel(h_meteor_mesh));
		meteor_pool.push_back(meteor);
	}

	create_timer = 1.0f;
}

void MeteorManager::Update()
{
	create_timer -= 1.0f / 60.0f;//仮で60fps
	if (create_timer <= 0.0f)
	{
		create_timer = CREATE_INTERVAL;
		if (!meteor_pool.empty())
		{
			// プールから取り出して生成
			Meteor* meteor = meteor_pool.back();
			meteor_pool.pop_back();
			meteor->OnCreate(TEST_CREATE_POS);
			meteor_active_list.push_back(meteor);
		}
	}

	// イテレータで回して、Update後に非アクティブならリストから削除してプールへ戻す
	for (auto it = meteor_active_list.begin(); it != meteor_active_list.end();)
	{
		Meteor* meteor = (*it);
		meteor->Update();

		if (!meteor->transform.is_active)
		{
			OnDestroyMeteor.Invoke(meteor->transform);//イベントを呼ぶ

			it = meteor_active_list.erase(it);
			meteor_pool.push_back(meteor);
		}
		else
		{
			++it;
		}
	}
}

void MeteorManager::Draw()
{
	for (Meteor* meteor : meteor_active_list)
	{
		meteor->Draw();
	}
}

