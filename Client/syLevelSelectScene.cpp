#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* PlayerRenderer = player->GetComponent<SpriteRenderer>();
		assert(PlayerRenderer);
		PlayerRenderer->SetPenRGB(255, 255, 0);		// yellow
		PlayerRenderer->SetBrushRGB(255, 255, 0);   // yellow
		PlayerRenderer->SetRenderType(eRenderType::Ellipse);

		Transform* PlayerTrans = player->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(300.f, 300.f));
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::E))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to StageScene : E");
	}
}