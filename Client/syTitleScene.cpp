#include "syTitleScene.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syImage.h"


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
		GameObject* Bg = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetImage(ResourceManager::Load<Image>(L"TitleImage", L"..\\Resources\\Video\\Title\\Title.mp4_000000.267.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		Transform* BgTrans = Bg->GetComponent<Transform>();
		assert(BgTrans);
		BgTrans->SetPosition(Vector2(0.f, 0.f));
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