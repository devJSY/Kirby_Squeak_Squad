#include "syStageScene.h"
#include "syPlayer.h"
#include "syObject.h"
#include "syGameObject.h"
#include "sySpriteRenderer.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"

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
		SpriteRenderer* PlayerRenderer = player->GetComponent<SpriteRenderer>();
		assert(PlayerRenderer);
		PlayerRenderer->SetPenRGB(0, 255, 0);	// Green
		PlayerRenderer->SetBrushRGB(0, 255, 0); // Green
		PlayerRenderer->SetRenderType(eRenderType::Rectangle);

		Transform* PlayerTrans = player->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(350.f, 350.f));
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