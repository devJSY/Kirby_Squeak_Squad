#include "syPrismPlainsScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syStepUI.h"
#include "syUI.h"
#include "sySpriteRenderer.h"
#include "syCamera.h"
#include "syCollisionManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syStepUI.h"
#include "syStarUI.h"
#include "syNumberUI.h"


namespace sy
{
	PrismPlainsScene::PrismPlainsScene()
		: mLevelType(eLevelType::Level1)
		, mlevelBG(nullptr)
		, mbActiveUI{}
		, ExitUI(nullptr)
		, mStepUI{}
		, mStarUI{}
		, mNumberUI{}
		, mDots{}
		, mCurStageState(eStageState::StageExit)
	{
	}

	PrismPlainsScene::~PrismPlainsScene()
	{
	}

	void PrismPlainsScene::Initialize()
	{
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		UI* LevelMarkUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelMarkUI->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelMarkUIAni = LevelMarkUI->AddComponent<Animator>();
		LevelMarkUIAni->CreateAnimation(Tex, L"LevelMarkUI", Vector2(222.f, 869.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelMarkUIAni->SetBmpRGB(L"LevelMarkUI", 0, 128, 0);
		LevelMarkUIAni->PlayAnimation(L"LevelMarkUI");
		LevelMarkUIAni->SetAffectedCamera(false);

		UI* LevelNameUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelNameUI->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameUIAni = LevelNameUI->AddComponent<Animator>();
		LevelNameUIAni->CreateAnimation(Tex, L"LevelNameUI", Vector2(2.f, 842.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameUIAni->SetBmpRGB(L"LevelNameUI", 0, 128, 128);
		LevelNameUIAni->PlayAnimation(L"LevelNameUI");
		LevelNameUIAni->SetAffectedCamera(false);

		// Dot 생성
		CreateDot();

		// StageUI생성
		CreateStageUI();

		Scene::Initialize();

		//stageUI->GetComponent<Animator>()->PlayAnimation(L"NormalStage", true);

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mLevelType);
	}

	void PrismPlainsScene::Update()
	{
		switch (mCurStageState)
		{
		case eStageState::StageExit:
			StageExit();
			break;
		case eStageState::Stage1:
			Stage1();
			break;
		case eStageState::Boss:
			StageBoss();
			break;
		default:
			break;
		}


		// 스테이지 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mLevelType = eLevelType::Level1_Clear;
			mlevelBG->SetLevelType(mLevelType);

			// 현재 스테이지 클리어 처리
			if (mCurStageState == eStageState::Stage1)
			{
				mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"NormalStageClear", true);
				mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
			}
			else if (mCurStageState == eStageState::Boss)
			{
				mStepUI[1]->GetComponent<Animator>()->PlayAnimation(L"BossStageClear", true);
				mStarUI[1]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
				mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"Number_Dedede");
			}
		}

		// 임시로 숫자 키패드로 Stage 활성화
		SetActiveUI();

		Scene::Update();
	}

	void PrismPlainsScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PrismPlainsScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Vector2 vec = Vector2(35.f, 70.f);

		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(vec);
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(false);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(false);

		player->SetPlayerMode(ePlayerMode::LevelMode);
		playerTrans->SetDirection(eDirection::RIGHT);

		// 플레이어 타입에따라 상태 설정 
		eAbilityType playerType = player->GetAbilityType();
		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player);
			defaultKirby->SetKirbyState(eDefaultKirbyState::Turn);
			playerAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}

		mCurStageState = eStageState::StageExit;
	}

	void PrismPlainsScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void PrismPlainsScene::SetActiveUI()
	{
		// type 에 따라 UI 활성화
		if (Input::GetKeyDown(eKeyCode::One))
		{
			mbActiveUI[0] = true;
			mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"NormalStage");
			mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
			mNumberUI[0]->GetComponent<Animator>()->PlayAnimation(L"One");
		}
		else if (Input::GetKeyDown(eKeyCode::Two))
		{
			mbActiveUI[1] = true;
			mStepUI[1]->GetComponent<Animator>()->PlayAnimation(L"BossStage");
			mStarUI[1]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
			mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"QuestionMark");
		}
	}

	void PrismPlainsScene::CreateDot()
	{
	}

	void PrismPlainsScene::CreateStageUI()
	{
		// StageExit UI 생성 
		Texture* Exit_StageScene_Tex = ResourceManager::Load<Texture>(L"Exit_StageScene_Tex", L"..\\Resources\\UI\\Exit_StageScene.bmp");
		ExitUI = object::Instantiate<UI>(eLayerType::LevelUI);
		SpriteRenderer* ExitUIRenderer = ExitUI->AddComponent<SpriteRenderer>();
		ExitUIRenderer->SetTexture(Exit_StageScene_Tex);
		ExitUIRenderer->SetAffectedCamera(false);
		ExitUIRenderer->SetRenderTrig(true);
		ExitUI->GetComponent<Transform>()->SetPosition(Vector2(35.f, 80.f));

		// Create StageUI
		for (size_t i = 0; i < 2; i++)
		{
			mStepUI[i] = object::Instantiate<StepUI>(eLayerType::LevelUI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::LevelUI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::LevelUI);
		}

		// 위치 설정해야함
		// StageUI Position Set
		mStepUI[0]->GetComponent<Transform>()->SetPosition(Vector2(122.f, 140.f));
		mStarUI[0]->GetComponent<Transform>()->SetPosition(Vector2(122.f, 150.f));
		mNumberUI[0]->GetComponent<Transform>()->SetPosition(Vector2(122.f, 150.f));

		// Boss
		mStepUI[1]->GetComponent<Transform>()->SetPosition(Vector2(210.f, 80.f));
		mStarUI[1]->GetComponent<Transform>()->SetPosition(Vector2(210.f, 95.f));
		mNumberUI[1]->GetComponent<Transform>()->SetPosition(Vector2(210.f, 95.f));
	}

	void PrismPlainsScene::StageExit()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[0] == true)
			{
				Vector2 vec = mStepUI[0]->GetComponent<Transform>()->GetPosition();
				vec.y -= 10.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurStageState = eStageState::Stage1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void PrismPlainsScene::Stage1()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			Vector2 vec = Vector2(35.f, 70.f);

			Player* player = SceneManager::GetPlayer();
			Transform* playerTrans = player->GetComponent<Transform>();
			playerTrans->SetPosition(vec);
			mCurStageState = eStageState::StageExit;			
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[1] == true)
			{
				Vector2 vec = mStepUI[1]->GetComponent<Transform>()->GetPosition();
				vec.y -= 10.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurStageState = eStageState::Boss;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void PrismPlainsScene::StageBoss()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[0] == true)
			{
				Vector2 vec = mStepUI[0]->GetComponent<Transform>()->GetPosition();
				vec.y -= 10.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurStageState = eStageState::Stage1;
			}
		}

		//if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		//{
		//	SceneManager::LoadScene(L"보스방 진입");
		//}
	}
}