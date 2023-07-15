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
#include "syAnimator.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"

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
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상
		BgRenderer->SetAffectCamera(false);

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // 중점 설정

		// 하단 화면 오브젝트 생성 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// 인벤토리 클래스 위치 설정
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// 인벤토리 애니메이션 설정
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(L"Inventory", image, Vector2(0.f, 0.f), Vector2(256.f, 192.f)
			, 16, Vector2(0.f, 0.f), 0.2f);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);


		//// UI 생성
		//AbilityUI* Ability = object::Instantiate<AbilityUI>(eLayerType::UI);
		//assert(Ability);
		//SpriteRenderer* AbilityRenderer = Ability->AddComponent<SpriteRenderer>();
		//assert(AbilityRenderer);
		//AbilityRenderer->SetAffectCamera(false);
		//Texture* Abilityimage = ResourceManager::Load<Texture>(L"AbilityUI"
		//	, L"..\\Resources\\UI\\Ability_UI.bmp");
		//AbilityRenderer->SetBmpRGB(255, 0, 255);
		//AbilityRenderer->SetTexture(Abilityimage);
		//Ability->GetComponent<Transform>()->SetPosition(Vector2(100.f,100.f)); 


		//HPbarUI* HPbar = object::Instantiate<HPbarUI>(eLayerType::UI);
		//assert(HPbar);
		//SpriteRenderer* HPbarRenderer = HPbar->AddComponent<SpriteRenderer>();
		//assert(AbilityRenderer);

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
		//ShowSceneName(hdc, GetName(), L"Change to StageScene : Mouse LBTN");
	}
	void LevelSelectScene::Enter()
	{
	}
	void LevelSelectScene::Exit()
	{
	}
}