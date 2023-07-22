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
#include "syDotUI.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
		: mType(eLevelType::LevelSelect)
		, mlevelBG(nullptr)
		, mbActiveUI{}
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

		// 좌상단 UI 생성 
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
						
		// Dot 생성
		CreateDot();	

		// LevelUI생성
		CreateLevelUI();

		Scene::Initialize();

		// 기본 Level1 UI 활성화
		mbActiveUI[1] = true;
		mPlacardUI[1]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
		mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"One");

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

			// 활성화 되어있는 UI의 Star만 Play
			for (size_t i = 1; i <= 8; i++)
			{
				if (mbActiveUI[i])
				{
					mStarUI[i]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
				}
			}
		}

		// 임시로 키입력으로 UI 활성화
		SetActiveUI(eLevelType::None);
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

	void LevelSelectScene::CreateLevelUI()
	{
		// Create LevelUI don't use index zero
		for (size_t i = 1; i <= 8; i++)
		{
			mPlacardUI[i] = object::Instantiate<PlacardUI>(eLayerType::UI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::UI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::UI);
		}

		// LevelUI Position Set
		mPlacardUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		mStarUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 37.f));
		mNumberUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 38.f));

		mPlacardUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 63.f));
		mStarUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 60.f));
		mNumberUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 61.f));

		mPlacardUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 110.f));
		mStarUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 107.f));
		mNumberUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 108.f));

		mPlacardUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 151.f));
		mStarUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 148.f));
		mNumberUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 149.f));

		mPlacardUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 150.f));
		mStarUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 147.f));
		mNumberUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 148.f));

		mPlacardUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 151.f));
		mStarUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 148.f));
		mNumberUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 149.f));

		mPlacardUI[7]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 100.f));
		mStarUI[7]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 97.f));
		mNumberUI[7]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 98.f));

		mPlacardUI[8]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 45.f));
		mStarUI[8]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 42.f));
		mNumberUI[8]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 43.f));
	}

	void LevelSelectScene::SetActiveUI(eLevelType type)
	{
		// type 에 따라 UI 활성화
		if (Input::GetKeyDown(eKeyCode::One) || type == eLevelType::Level1)
		{
			mbActiveUI[1] = true;
			mPlacardUI[1]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"One");
		}
		else if (Input::GetKeyDown(eKeyCode::Two) || type == eLevelType::Level2)
		{
			mbActiveUI[2] = true;
			mPlacardUI[2]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[2]->GetComponent<Animator>()->PlayAnimation(L"Two");

			for (size_t i = 0; i < mDots[2].size(); i++)
			{
				DotUI* dot = mDots[2][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Three) || type == eLevelType::Level3)
		{
			mbActiveUI[3] = true;
			mPlacardUI[3]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[3]->GetComponent<Animator>()->PlayAnimation(L"Three");

			for (size_t i = 0; i < mDots[3].size(); i++)
			{
				DotUI* dot = mDots[3][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Four) || type == eLevelType::Level4)
		{
			mbActiveUI[4] = true;
			mPlacardUI[4]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[4]->GetComponent<Animator>()->PlayAnimation(L"Four");

			for (size_t i = 0; i < mDots[4].size(); i++)
			{
				DotUI* dot = mDots[4][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Five) || type == eLevelType::Level5)
		{
			mbActiveUI[5] = true;
			mPlacardUI[5]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[5]->GetComponent<Animator>()->PlayAnimation(L"Five");

			for (size_t i = 0; i < mDots[5].size(); i++)
			{
				DotUI* dot = mDots[5][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Six) || type == eLevelType::Level6)
		{
			mbActiveUI[6] = true;
			mPlacardUI[6]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[6]->GetComponent<Animator>()->PlayAnimation(L"Six");

			for (size_t i = 0; i < mDots[6].size(); i++)
			{
				DotUI* dot = mDots[6][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Seven) || type == eLevelType::Level7)
		{
			mbActiveUI[7] = true;
			mPlacardUI[7]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[7]->GetComponent<Animator>()->PlayAnimation(L"Seven");

			for (size_t i = 0; i < mDots[7].size(); i++)
			{
				DotUI* dot = mDots[7][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Eight) || type == eLevelType::Level8)
		{
			mbActiveUI[8] = true;
			mPlacardUI[8]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[8]->GetComponent<Animator>()->PlayAnimation(L"Eight");

			for (size_t i = 0; i < mDots[8].size(); i++)
			{
				DotUI* dot = mDots[8][i];
				dot->GetComponent<Animator>()->PlayAnimation(L"Dot");
			}
		}
	}

	void LevelSelectScene::CreateDot()
	{
		// Create DotUI don't use index zero, one

		DotUI* dot;

		/////////// Level2 ///////////

		for (size_t i = 0; i < 6; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(200.f - (8.f * i), 42.f));

			mDots[2].push_back(dot);
		}

		dot = object::Instantiate<DotUI>(eLayerType::UI);
		dot->GetComponent<Transform>()->SetPosition(Vector2(200.f, 50.f));

		mDots[2].push_back(dot);

		/////////// Level3 ///////////

		//Top
		for (size_t i = 0; i < 4; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f - (8.f * i), 65.f));

			mDots[3].push_back(dot);
		}

		// Middle
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f, 73.f + (8.f * i)));

			mDots[3].push_back(dot);
		}

		//Bottom
		for (size_t i = 0; i < 2; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f - (8.f * i), 113.f));

			mDots[3].push_back(dot);
		}

		/////////// Level4 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(215.f, 153.f - (8.f * i)));

			mDots[4].push_back(dot);
		}

		dot = object::Instantiate<DotUI>(eLayerType::UI);
		dot->GetComponent<Transform>()->SetPosition(Vector2(207.f, 153.f));

		mDots[4].push_back(dot);


		/////////// Level5 ///////////
		for (size_t i = 0; i < 6; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(170.f - (8.f * i), 153.f));

			mDots[5].push_back(dot);
		}

		/////////// Level6 ///////////
		for (size_t i = 0; i < 7; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(100.f - (8.f * i), 153.f));

			mDots[6].push_back(dot);
		}

		/////////// Level7 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(35.f, 140.f - (8.f * i)));

			mDots[7].push_back(dot);
		}

		/////////// Level8 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::UI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(35.f, 90.f - (8.f * i)));

			mDots[8].push_back(dot);
		}
	}
}