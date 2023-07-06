#include "syTitleScene.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syObject.h"

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
		player->AddComponent<SpriteRenderer>();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName());
	}
}