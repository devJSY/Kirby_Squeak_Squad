#include "syJamJungleScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syUI.h"

namespace sy
{
	JamJungleScene::JamJungleScene()
		: mType(eLevelType::Level4)
	{
	}

	JamJungleScene::~JamJungleScene()
	{
	}

	void JamJungleScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);


		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		UI* LevelMarkUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelMarkUI->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelMarkUIAni = LevelMarkUI->AddComponent<Animator>();
		LevelMarkUIAni->CreateAnimation(Tex, L"LevelMarkUI", Vector2(222.f, 923.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelMarkUIAni->SetBmpRGB(L"LevelMarkUI", 0, 128, 0);
		LevelMarkUIAni->PlayAnimation(L"LevelMarkUI");
		LevelMarkUIAni->SetAffectedCamera(false);

		UI* LevelNameUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelNameUI->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameUIAni = LevelNameUI->AddComponent<Animator>();
		LevelNameUIAni->CreateAnimation(Tex, L"LevelNameUI", Vector2(2.f, 944.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameUIAni->SetBmpRGB(L"LevelNameUI", 0, 128, 128);
		LevelNameUIAni->PlayAnimation(L"LevelNameUI");
		LevelNameUIAni->SetAffectedCamera(false);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void JamJungleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"VocalVolcanoScene");

		}
		Scene::Update();
	}

	void JamJungleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void JamJungleScene::Enter()
	{
	}

	void JamJungleScene::Exit()
	{
	}
}