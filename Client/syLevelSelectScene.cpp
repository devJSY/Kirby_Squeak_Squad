#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syImage.h"

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
		// 상단 화면 오브젝트 생성 
		GameObject* Bg = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetImage(ResourceManager::Load<Image>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		// 하단 화면 오브젝트 생성 
		GameObject* TouchScreen = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(TouchScreen);
		assert(TouchScreen->AddComponent<SpriteRenderer>());
		SpriteRenderer* TSRenderer = TouchScreen->GetComponent<SpriteRenderer>();
		assert(TSRenderer);
		TSRenderer->SetImage(ResourceManager::Load<Image>(L"TouchScreen", L"..\\Resources\\Video\\Non\\None000009.462.bmp")); // 이미지 설정
		TSRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		Transform* TSTransform = TouchScreen->GetComponent<Transform>();
		TSTransform->SetPosition(Vector2(0.f, 192.f));

		Scene::Initialize();
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