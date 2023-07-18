#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syDefaultKirby.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"
#include "syCamera.h"

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
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		Texture* tex = ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp");
		
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // 중점 설정


		// Inventory 생성 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		Inven->GetComponent<Transform>()->SetPosition(vec);

		// UI 생성
		AbilityUI* AbilityUi = object::Instantiate<AbilityUI>(eLayerType::UI);
		Vector2 Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 20.0f; 
		Uivec.y -= 25.f; 
		AbilityUi->GetComponent<Transform>()->SetPosition(Uivec);
		AbilityUi->SetOwner(nullptr); // 오너설정 나중에 설정예정

		HPbarUI* HPbarUi = object::Instantiate<HPbarUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 85.0f;
		Uivec.y -= 12.f;
		HPbarUi->GetComponent<Transform>()->SetPosition(Uivec);
		HPbarUi->SetOwner(nullptr); // 오너설정 나중에 설정예정

		LifeUI* LifeUi = object::Instantiate<LifeUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 65.0f;
		Uivec.y -= 27.f;
		LifeUi->GetComponent<Transform>()->SetPosition(Uivec);
		LifeUi->SetOwner(nullptr); // 오너설정 나중에 설정예정

		//// StageScene에 객체 전달
		//Scene* NextScene = SceneManager::GetScene(L"StageScene");
		//NextScene->AddGameObject(eLayerType::UI, AbilityUi);
		//NextScene->AddGameObject(eLayerType::UI, HPbarUi);
		//NextScene->AddGameObject(eLayerType::UI, LifeUi);
		//NextScene->AddGameObject(eLayerType::Inventory, Inven);

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);
	}

	void LevelSelectScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
	}
}