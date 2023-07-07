#include "syTitleScene.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"

namespace sy
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* PlayerRenderer = player->GetComponent<SpriteRenderer>();
		assert(PlayerRenderer);
		PlayerRenderer->SetPenRGB(255, 128, 0);		// Orange
		PlayerRenderer->SetBrushRGB(255, 128, 0);   // Orange
		PlayerRenderer->SetRenderType(eRenderType::Rectangle);

		Transform* PlayerTrans = player->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(250.f, 250.f));
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::W) || Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to LevelSelectScene : W or Mouse RBTN");
	}
}