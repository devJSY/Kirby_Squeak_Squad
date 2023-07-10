#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syImage.h"


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
		GameObject* Bg = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetImage(ResourceManager::Load<Image>(L"OpeningImage", L"..\\Resources\\Video\\Opening\\Opening000001.436.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		Transform* BgTrans = Bg->GetComponent<Transform>();
		assert(BgTrans);
		BgTrans->SetPosition(Vector2(0.f, 0.f));
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