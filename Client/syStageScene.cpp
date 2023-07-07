#include "syStageScene.h"
#include "syPlayer.h"
#include "syObject.h"
#include "syGameObject.h"
#include "sySpriteRenderer.h"
#include "syInput.h"
#include "sySceneManager.h"

namespace sy
{
	StageScene::StageScene()
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
	}

	void StageScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::R))
		{
			SceneManager::LoadScene(L"WorldTunnelScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to WorldTunnelScene : R");
	}
}