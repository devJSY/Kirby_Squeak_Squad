#include "syIceIslandScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"

namespace sy
{
	IceIslandScene::IceIslandScene()
		: mType(eLevelType::Level6)
		, mlevelBG(nullptr)
	{
	}

	IceIslandScene::~IceIslandScene()
	{
	}

	void IceIslandScene::Initialize()
	{
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		BackGround* Level = object::Instantiate<BackGround>(eLayerType::BackGround);
		Level->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelAni = Level->AddComponent<Animator>();
		LevelAni->CreateAnimation(Tex, L"Level", Vector2(222.f, 959.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelAni->SetBmpRGB(L"Level", 0, 128, 0);
		LevelAni->PlayAnimation(L"Level");
		LevelAni->SetAffectedCamera(false);

		BackGround* LevelName = object::Instantiate<BackGround>(eLayerType::BackGround);
		LevelName->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameAni = LevelName->AddComponent<Animator>();
		LevelNameAni->CreateAnimation(Tex, L"LevelName", Vector2(2.f, 1012.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameAni->SetBmpRGB(L"LevelName", 0, 128, 128);
		LevelNameAni->PlayAnimation(L"LevelName");
		LevelNameAni->SetAffectedCamera(false);

		Scene::Initialize();

		mlevelBG->SetLevelType(eLevelType::Level6);
	}

	void IceIslandScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"SecretSeaScene");
		}

		// 스테이지 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::Level6_Clear;
			mlevelBG->SetLevelType(mType);
		}

		Scene::Update();
	}

	void IceIslandScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void IceIslandScene::Enter()
	{
	}

	void IceIslandScene::Exit()
	{
	}
}