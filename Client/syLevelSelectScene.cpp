#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"

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
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp")); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����

		// �ϴ� ȭ�� ������Ʈ ���� 
		BackGround* Inventory = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Inventory);
		assert(Inventory->AddComponent<SpriteRenderer>());
		SpriteRenderer* InvenRenderer = Inventory->GetComponent<SpriteRenderer>();
		assert(InvenRenderer);
		InvenRenderer->SetTexture(ResourceManager::Load<Texture>(L"Inventory", L"..\\Resources\\Inventory\\Inventory.bmp")); // �̹��� ����
		InvenRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

		Transform* InvenTransform = Inventory->GetComponent<Transform>();
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.x += vec.x;	// �ӽ÷� ����
		vec.y += vec.y / 2.f;
		InvenTransform->SetPosition(vec); // ���� ����
		InvenTransform->SetPosition(vec);

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::E) || Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to StageScene : E or Mouse LBTN");
	}
}