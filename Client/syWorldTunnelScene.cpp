#include "syWorldTunnelScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"
#include "syTransform.h"

namespace sy
{
	WorldTunnelScene::WorldTunnelScene()
	{
	}

	WorldTunnelScene::~WorldTunnelScene()
	{
	}

	void WorldTunnelScene::Initialize()
	{
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* PlayerRenderer = player->GetComponent<SpriteRenderer>();
		assert(PlayerRenderer);
		PlayerRenderer->SetPenRGB(0, 128, 255);		// blue
		PlayerRenderer->SetBrushRGB(0, 128, 255);   // blue
		PlayerRenderer->SetRenderType(eRenderType::Ellipse);

		Transform* PlayerTrans = player->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(400.f, 400.f));
	}

	void WorldTunnelScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SceneManager::LoadScene(L"EndingScene");
		}
	}

	void WorldTunnelScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to EndingScene : T");
	}
}