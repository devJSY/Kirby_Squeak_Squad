#include "syEndingScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"

namespace sy
{
	EndingScene::EndingScene()
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"EndingImage", L"..\\Resources\\Video\\Ending\\Ending000017.304.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		Scene::Initialize();
	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::Y) || Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"OpeningScene");
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to OpeningScene : Y or Mouse LBTN");
	}
}