#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syLevel_BG.h"
#include "syCollisionManager.h"
#include "syBackGround.h"
#include "syResourceManager.h"
#include "syNumberUI.h"
#include "syPlacardUI.h"
#include "syStarUI.h"
#include "syPrismPlainsScene.h"
#include "syNatureNotchScene.h"
#include "syCushyCloudScene.h"
#include "syJamJungleScene.h"
#include "syVocalVolcanoScene.h"
#include "syIceIslandScene.h"
#include "sySecretSeaScene.h"
#include "syGambleGalaxyScene.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
		: mType(eLevelType::LevelSelect)
		, mlevelBG(nullptr)
		, mPlacardUI{}
		, mStarUI{}
		, mNumberUI{}
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// 상단 화면 오브젝트 생성 
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		BackGround* Level = object::Instantiate<BackGround>(eLayerType::BackGround);
		Level->GetComponent<Transform>()->SetPosition(Vector2(80.f, 7.f));

		Animator* LevelAni = Level->AddComponent<Animator>();
		LevelAni->CreateAnimation(Tex, L"Level", Vector2(222.f, 850.f), Vector2(113.f, 17.f),Vector2(113.f, 0.f), 1, 1);
		LevelAni->SetBmpRGB(L"Level", 0, 128, 0);
		LevelAni->PlayAnimation(L"Level");
		LevelAni->SetAffectedCamera(false);

		BackGround* LevelName = object::Instantiate<BackGround>(eLayerType::BackGround);
		LevelName->GetComponent<Transform>()->SetPosition(Vector2(101.f, 16.f));

		Animator* LevelNameAni = LevelName->AddComponent<Animator>();
		LevelNameAni->CreateAnimation(Tex, L"LevelName", Vector2(2.f, 1148.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameAni->SetBmpRGB(L"LevelName", 0, 128, 128);
		LevelNameAni->PlayAnimation(L"LevelName");
		LevelNameAni->SetAffectedCamera(false);

		// Create Level UI 
		for (size_t i = 1; i <= 8 ; i++)
		{
			mPlacardUI[i] = object::Instantiate<PlacardUI>(eLayerType::UI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::UI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::UI);
		}

		//mPlacardUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		//mStarUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		//mNumberUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		
		for (size_t i = 1; i <= 8; i++)
		{
			mPlacardUI[i]->GetComponent<Transform>()->SetPosition(Vector2(14.f + (i * 20.f), 40.f));
			mStarUI[i]->GetComponent<Transform>()->SetPosition(Vector2(14.f + (i * 20.f), 40.f));
			mNumberUI[i]->GetComponent<Transform>()->SetPosition(Vector2(14.f + (i * 20.f), 40.f));
		}

		Scene::Initialize();

		for (size_t i = 1; i <= 8; i++)
		{
			mPlacardUI[i]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mStarUI[i]->GetComponent<Animator>()->PlayAnimation(L"StarUI", true);
			if(i == 1)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"One");
			else if (i == 2)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Two");
			else if (i == 3)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Three");
			else if (i == 4)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Four");
			else if (i == 5)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Five");
			else if (i == 6)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Six");
			else if (i == 7)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Seven");
			else if (i == 8)
				mNumberUI[i]->GetComponent<Animator>()->PlayAnimation(L"Eight");
		}

		mlevelBG->SetLevelType(eLevelType::LevelSelect);
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			// 특정 조건에 따라 Level 설정
			if (1)
				SceneManager::LoadScene(L"PrismPlainsScene");
			else if (0)
				SceneManager::LoadScene(L"NatureNotchScene");
			else if (0)
				SceneManager::LoadScene(L"CushyCloudScene");
			else if (0)
				SceneManager::LoadScene(L"JamJungleScene");
			else if (0)
				SceneManager::LoadScene(L"VocalVolcanoScene");
			else if (0)
				SceneManager::LoadScene(L"IceIslandScene");
			else if (0)
				SceneManager::LoadScene(L"SecretSeaScene");
			else if (0)
				SceneManager::LoadScene(L"GambleGalaxyScene");
		}


		// 스테이지 전부 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::AllClear_LevelSelect;
			mlevelBG->SetLevelType(mType);
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
		CollisionManager::Clear();
	}
}