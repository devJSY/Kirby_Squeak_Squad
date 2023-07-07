#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"

namespace sy
{
	OpeningScene::OpeningScene()
	{
	}

	OpeningScene::~OpeningScene()
	{
	}

	void OpeningScene::Initialize()
	{
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* PlayerRenderer = player->GetComponent<SpriteRenderer>();
		assert(PlayerRenderer);
		PlayerRenderer->SetPenRGB(255, 0, 0);	// Red
		PlayerRenderer->SetBrushRGB(255, 0, 0); // Red
		PlayerRenderer->SetRenderType(eRenderType::Ellipse);
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::Q) || Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void OpeningScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to TitleScene : Q or Mouse LBTN");
	}
}