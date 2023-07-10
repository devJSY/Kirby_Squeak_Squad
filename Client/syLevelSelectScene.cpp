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
		// ��� ȭ�� ������Ʈ ���� 
		GameObject* Bg = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetImage(ResourceManager::Load<Image>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp")); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

		// �ϴ� ȭ�� ������Ʈ ���� 
		GameObject* TouchScreen = object::Instantiate<GameObject>(eLayerType::BackGround);
		assert(TouchScreen);
		assert(TouchScreen->AddComponent<SpriteRenderer>());
		SpriteRenderer* TSRenderer = TouchScreen->GetComponent<SpriteRenderer>();
		assert(TSRenderer);
		TSRenderer->SetImage(ResourceManager::Load<Image>(L"TouchScreen", L"..\\Resources\\Video\\Non\\None000009.462.bmp")); // �̹��� ����
		TSRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

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