#include "sySecretSeaScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syUI.h"
#include "syCamera.h"
#include "syCollisionManager.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syTime.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syZoom_Effect.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "syStepUI.h"
#include "syStarUI.h"
#include "syNumberUI.h"
#include "syDotUI.h"
#include "syLevelSelectScene.h"

namespace sy
{
	SecretSeaScene::SecretSeaScene()
		: mLevelType(eLevelType::Level7)
		, mlevelBG(nullptr)
		, mbActiveUI{}
		, ExitUI(nullptr)
		, mStepUI{}
		, mStarUI{}
		, mNumberUI{}
		, mDots{}
		, mCurStageState(eStageState::StageExit)
		, mEnterTime(0.f)
		, mZoom(nullptr)
		, mbSceneChange(false)
	{
	}

	SecretSeaScene::~SecretSeaScene()
	{
	}

	void SecretSeaScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		UI* LevelMarkUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelMarkUI->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelMarkUIAni = LevelMarkUI->AddComponent<Animator>();
		LevelMarkUIAni->CreateAnimation(Tex, L"LevelMarkUI", Vector2(222.f, 977.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelMarkUIAni->SetBmpRGB(L"LevelMarkUI", 0, 128, 0);
		LevelMarkUIAni->PlayAnimation(L"LevelMarkUI");
		LevelMarkUIAni->SetAffectedCamera(false);

		UI* LevelNameUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelNameUI->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameUIAni = LevelNameUI->AddComponent<Animator>();
		LevelNameUIAni->CreateAnimation(Tex, L"LevelNameUI", Vector2(2.f, 1046.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameUIAni->SetBmpRGB(L"LevelNameUI", 0, 128, 128);
		LevelNameUIAni->PlayAnimation(L"LevelNameUI");
		LevelNameUIAni->SetAffectedCamera(false);

		// Dot 생성
		CreateDot();

		// StageUI생성
		CreateStageUI();

		Scene::Initialize();

		// Sound Load
		ResourceManager::Load<Sound>(L"StageSelectSound", L"..\\Resources\\Sound\\Theme\\StageSelect.wav");
		ResourceManager::Load<Sound>(L"Click2Sound", L"..\\Resources\\Sound\\Effect\\Click2.wav");

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mLevelType);
	}

	void SecretSeaScene::Update()
	{
		// Enter 애니메이션 재생용
		mEnterTime += Time::DeltaTime();

		if (mEnterTime > 1.3f && !mbSceneChange)
		{
			switch (mCurStageState)
			{
			case eStageState::StageExit:
				StageExit();
				break;
			case eStageState::Boss:
				Boss();
				break;
			default:
				break;
			}
		}

		if (mbSceneChange && mCurStageState == eStageState::Boss && Camera::IsEmptyCamEffect())
		{
			// 오디오 정지
			ResourceManager::AllSoundStop();
			SceneManager::LoadScene(L"Level7_BossScene");
		}

		// 스테이지 클리어 시 배경화면 변경
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SetClearActiveUI(eStageState::Boss);
		}

		// 임시로 숫자 키패드로 Stage 활성화
		if (Input::GetKeyDown(eKeyCode::One))
			SetActiveUI(eStageState::Boss);

		Scene::Update();
	}

	void SecretSeaScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SecretSeaScene::Enter()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;

		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Vector2 vec = Vector2::Zero;

		if (mCurStageState == eStageState::StageExit)
			vec = ExitUI->GetComponent<Transform>()->GetPosition();
		else if (mCurStageState == eStageState::Boss)
			vec = mStepUI[0]->GetComponent<Transform>()->GetPosition();

		// Offset값 추가
		vec.y -= 10.f;

		// 플레이어 설정
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(vec);
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(false);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(false);
		Rigidbody* palyerRigid = player->GetComponent<Rigidbody>();
		palyerRigid->SetGround(true);

		player->SetPlayerMode(ePlayerMode::LevelMode);
		playerTrans->SetDirection(eDirection::RIGHT);
		player->SetLevelEnter(true);

		// 플레이어 타입에따라 상태 설정 
		eAbilityType playerType = player->GetAbilityType();
		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
			defaultKirby->SetKirbyState(eDefaultKirbyState::Choice);
			playerAni->PlayAnimation(L"Choice", false);
		}
		else if (playerType == eAbilityType::Fire)
		{
			FireKirby* fireKirby = dynamic_cast<FireKirby*>(player->GetActiveKirby());
			fireKirby->SetKirbyState(eFireKirbyState::Choice);
			playerAni->PlayAnimation(L"FireKirby_Choice", false);
		}
		else if (playerType == eAbilityType::Ice)
		{
			IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());
			iceKirby->SetKirbyState(eIceKirbyState::Choice);
			playerAni->PlayAnimation(L"IceKirby_Choice", false);
		}
		else if (playerType == eAbilityType::Cutter)
		{
			CutterKirby* cutterKirby = dynamic_cast<CutterKirby*>(player->GetActiveKirby());
			cutterKirby->SetKirbyState(eCutterKirbyState::Choice);
			playerAni->PlayAnimation(L"CutterKirby_Choice", false);
		}
		else if (playerType == eAbilityType::Tornado)
		{
			TornadoKirby* tornadoKirby = dynamic_cast<TornadoKirby*>(player->GetActiveKirby());
			tornadoKirby->SetKirbyState(eTornadoKirbyState::Choice);
			playerAni->PlayAnimation(L"TornadoKirby_Choice", false);
		}
		else if (playerType == eAbilityType::Ninja)
		{
			NinjaKirby* ninjaKirby = dynamic_cast<NinjaKirby*>(player->GetActiveKirby());
			ninjaKirby->SetKirbyState(eNinjaKirbyState::Choice);
			playerAni->PlayAnimation(L"NinjaKirby_Choice", false);
		}
		else if (playerType == eAbilityType::Spark)
		{
			SparkKirby* sparkKirby = dynamic_cast<SparkKirby*>(player->GetActiveKirby());
			sparkKirby->SetKirbyState(eSparkKirbyState::Choice);
			playerAni->PlayAnimation(L"SparkKirby_Choice", false);
		}
		//else if (playerType == eAbilityType::Wheel)
		//{
		//	WheelKirby* wheelKirby = dynamic_cast<WheelKirby*>(player->GetActiveKirby());
		//	wheelKirby->SetKirbyState(eWheelKirbyState::Choice);
		//	playerAni->PlayAnimation(L"WheelKirby_Choice", false);
		//}

		// 오디오 재생
		ResourceManager::Find<Sound>(L"StageSelectSound")->Play(true);

		SetActiveUI(eStageState::Boss);
	}

	void SecretSeaScene::Exit()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void SecretSeaScene::SetActiveUI(eStageState type)
	{
		if (type == eStageState::Boss)
		{
			if (!mbActiveUI[0])
			{
				mbActiveUI[0] = true;
				mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"BossStageFlash", true);
				mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
				mNumberUI[0]->GetComponent<Animator>()->PlayAnimation(L"QuestionMark");

				for (size_t i = 0; i < mDots[0].size(); i++)
				{
					DotUI* dot = mDots[0][i];
					dot->SetActiveTrig(true);
				}
			}
		}
	}

	void SecretSeaScene::SetClearActiveUI(eStageState type)
	{
		// 현재 스테이지 클리어 처리
		if (type == eStageState::Boss)
		{
			if (mbActiveUI[0])
			{
				mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"BossStageClearFlash", true);
				mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
				mNumberUI[0]->GetComponent<Animator>()->PlayAnimation(L"Number_MetaKnight");
			}
		}

		// 스테이지 전부 클리어
		for (size_t i = 0; i < 1; i++)
		{
			if (mbActiveUI[i] == false)
				return;
		}

		LevelSelectScene* scene = dynamic_cast<LevelSelectScene*>(SceneManager::GetScene(L"LevelSelectScene"));
		scene->SetClearActiveUI(eLevelState::Level7);
	}

	void SecretSeaScene::CreateDot()
	{
		/////////// BossStage ///////////
		DotUI* dot;

		// StageExit 에서 BossStage으로 가는 Dot 8의 간격으로 생성
		for (size_t i = 0; i < 20; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(38.f + (8 * i), 96.f));
			dot->SetDelayTime(0.05f * i);

			mDots[0].push_back(dot);
		}
	}

	void SecretSeaScene::CreateStageUI()
	{
		// StageExit UI 생성 
		Texture* Exit_StageScene_Tex = ResourceManager::Load<Texture>(L"Exit_StageScene_Tex", L"..\\Resources\\UI\\Exit_StageScene.bmp");
		ExitUI = object::Instantiate<UI>(eLayerType::LevelUI);
		SpriteRenderer* ExitUIRenderer = ExitUI->AddComponent<SpriteRenderer>();
		ExitUIRenderer->SetTexture(Exit_StageScene_Tex);
		ExitUIRenderer->SetAffectedCamera(false);
		ExitUIRenderer->SetRenderTrig(true);
		ExitUI->GetComponent<Transform>()->SetPosition(Vector2(30.f, 96.f));

		// Create StageUI
		for (size_t i = 0; i < 1; i++)
		{
			mStepUI[i] = object::Instantiate<StepUI>(eLayerType::LevelUI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::LevelUI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::LevelUI);
		}

		// Boss
		mStepUI[0]->GetComponent<Transform>()->SetPosition(Vector2(192.f, 96.f));
		mStarUI[0]->GetComponent<Transform>()->SetPosition(Vector2(192.f, 111.f));
		mNumberUI[0]->GetComponent<Transform>()->SetPosition(Vector2(192.f, 111.f));
	}

	void SecretSeaScene::StageExit()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbActiveUI[0] == true)
			{
				Vector2 vec = mStepUI[0]->GetComponent<Transform>()->GetPosition();
				vec.y -= 10.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurStageState = eStageState::Boss;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			if (mZoom == nullptr)
			{
				mZoom = new Zoom_Effect(SceneManager::GetPlayer());
				object::ActiveSceneAddGameObject(eLayerType::Zoom, mZoom);
			}

			// 오디오 재생
			ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
		}
	}

	void SecretSeaScene::Boss()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			Vector2 vec = ExitUI->GetComponent<Transform>()->GetPosition();
			vec.y -= 10.f;

			Player* player = SceneManager::GetPlayer();
			Transform* playerTrans = player->GetComponent<Transform>();
			playerTrans->SetPosition(vec);
			mCurStageState = eStageState::StageExit;
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			// 카메라 효과 등록
			Camera::fadeOut(1.f, RGB(255, 255, 255));
			mbSceneChange = true;

			// 오디오 재생
			ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
		}
	}
}