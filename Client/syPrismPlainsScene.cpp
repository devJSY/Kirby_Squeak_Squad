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
#include "syStepUI.h"
#include "syStarUI.h"
#include "syNumberUI.h"
#include "syDotUI.h"
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
#include "syLevelSelectScene.h"
#include "sySwordKirby.h"

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
		, mEnterTime(0.f)
		, mZoom(nullptr)
		, mbSceneChange(false)
	{
	}

	PrismPlainsScene::~PrismPlainsScene()
	{
	}

	void PrismPlainsScene::Initialize()
	{
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// UI ���� 
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

		// Dot ����
		CreateDot();

		// StageUI����
		CreateStageUI();

		// Sound Load
		ResourceManager::Load<Sound>(L"StageSelectSound", L"..\\Resources\\Sound\\Theme\\StageSelect.wav");
		ResourceManager::Load<Sound>(L"Click2Sound", L"..\\Resources\\Sound\\Effect\\Click2.wav");

		Scene::Initialize();

		// mlevelBG �ʱ�ȭ ���� ȣ��
		mlevelBG->SetLevelType(mLevelType);
	}

	void PrismPlainsScene::Update()
	{
		// Enter �ִϸ��̼� �����
		mEnterTime += Time::DeltaTime();

		if (mEnterTime > 1.3f && !mbSceneChange)
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
				Boss();
				break;
			default:
				break;
			}
		}

		if (mbSceneChange && mCurStageState == eStageState::Stage1 && Camera::IsEmptyCamEffect())
		{
			// ����� ����
			ResourceManager::AllSoundStop();
			SceneManager::LoadScene(L"Level1_Stage1Scene");
		}
		else if (mbSceneChange && mCurStageState == eStageState::Boss && Camera::IsEmptyCamEffect())
		{
			// ����� ����
			ResourceManager::AllSoundStop();
			SceneManager::LoadScene(L"Level1_BossScene");
		}


		// �������� Ŭ���� �� ���ȭ�� ����
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SetClearActiveUI(eStageState::Stage1);
			SetClearActiveUI(eStageState::Boss);
		}

		// �ӽ÷� ���� Ű�е�� Stage Ȱ��ȭ
		if (Input::GetKeyDown(eKeyCode::One))
			SetActiveUI(eStageState::Stage1);
		else if (Input::GetKeyDown(eKeyCode::Two))
			SetActiveUI(eStageState::Boss);		

		Scene::Update();
	}

	void PrismPlainsScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PrismPlainsScene::Enter()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;
		
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		Vector2 vec = Vector2::Zero;

		if (mCurStageState == eStageState::StageExit)
			vec = ExitUI->GetComponent<Transform>()->GetPosition();
		else if (mCurStageState == eStageState::Stage1)
			vec = mStepUI[0]->GetComponent<Transform>()->GetPosition();
		else if (mCurStageState == eStageState::Boss)
			vec = mStepUI[1]->GetComponent<Transform>()->GetPosition();

		// Offset�� �߰�
		vec.y -= 10.f;

		// �÷��̾� ����
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

		// �÷��̾� Ÿ�Կ����� ���� ���� 
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
		else if (playerType == eAbilityType::Sword)
		{
			SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());
			swordKirby->SetKirbyState(eSwordKirbyState::Choice);
			playerAni->PlayAnimation(L"SwordKirby_Choice", false);
		}

		// ����� ���
		ResourceManager::Find<Sound>(L"StageSelectSound")->Play(true);

		SetActiveUI(eStageState::Stage1);
	}

	void PrismPlainsScene::Exit()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;

		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void PrismPlainsScene::SetActiveUI(eStageState type)
	{
		// type �� ���� UI Ȱ��ȭ
		if (type == eStageState::Stage1)
		{
			if (!mbActiveUI[0])
			{
				mbActiveUI[0] = true;
				mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"NormalStageFlash", true);
				mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
				mNumberUI[0]->GetComponent<Animator>()->PlayAnimation(L"One");

				for (size_t i = 0; i < mDots[0].size(); i++)
				{
					DotUI* dot = mDots[0][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eStageState::Boss)
		{
			if (!mbActiveUI[1])
			{
				mbActiveUI[1] = true;
				mStepUI[1]->GetComponent<Animator>()->PlayAnimation(L"BossStageFlash", true);
				mStarUI[1]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
				mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"QuestionMark");

				for (size_t i = 0; i < mDots[1].size(); i++)
				{
					DotUI* dot = mDots[1][i];
					dot->SetActiveTrig(true);
				}
			}
		}
	}

	void PrismPlainsScene::SetClearActiveUI(eStageState type)
	{
		// ���� �������� Ŭ���� ó��
		if (type == eStageState::Stage1)
		{
			if (mbActiveUI[0])
			{
				mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"NormalStageClearFlash", true);
				mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
			}
		}
		else if (type == eStageState::Boss)
		{
			if (mbActiveUI[1])
			{
				mStepUI[1]->GetComponent<Animator>()->PlayAnimation(L"BossStageClearFlash", true);
				mStarUI[1]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
				mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"Number_Dedede");
			}
		}

		// �������� ���� Ŭ���� �� ���ȭ�� ����
		for (size_t i = 0; i < 2; i++)
		{
			if (mbActiveUI[i] == false)
				return;
		}

		mLevelType = eLevelType::Level1_Clear;
		mlevelBG->SetLevelType(mLevelType);

		LevelSelectScene* scene = dynamic_cast<LevelSelectScene*>(SceneManager::GetScene(L"LevelSelectScene"));
		scene->SetClearActiveUI(eLevelState::Level1);
	}

	void PrismPlainsScene::CreateDot()
	{
		// StageStep ���� Stage1���� ���� Dot 8�� �������� ����
		Vector2 vec = Vector2(122.f, 140.f) - Vector2(35.f, 80.f);
		vec.Normalize();
		vec *= 8.f;

		DotUI* dot;

		/////////// Stage1 ///////////

		for (size_t i = 2; i <= 12; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(35.f + (vec.x * i), 80.f + (vec.y * i)));
			dot->SetDelayTime(0.05f * i);

			mDots[0].push_back(dot);
		}

		/////////// BossStage ///////////
		
		// Stage1 ���� BossStage���� ���� Dot 8�� �������� ����
		vec = Vector2(210.f, 80.f) - Vector2(122.f, 140.f);
		vec.Normalize();
		vec *= 8.f;

		for (size_t i = 1; i <= 11; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(122.f + (vec.x * i), 140.f + (vec.y * i)));
			dot->SetDelayTime(0.05f * i);

			mDots[1].push_back(dot);
		}
	}

	void PrismPlainsScene::CreateStageUI()
	{
		// StageExit UI ���� 
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

		// ��ġ �����ؾ���
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
			mbSceneChange = true;

			if (mZoom == nullptr)
			{
				mZoom = new Zoom_Effect(SceneManager::GetPlayer());
				object::ActiveSceneAddGameObject(eLayerType::Zoom, mZoom);
			}

			// ����� ���
			ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
		}
	}

	void PrismPlainsScene::Stage1()
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
			// ī�޶� ȿ�� ���
			Camera::fadeOut(1.f, RGB(255, 255, 255));
			mbSceneChange = true;

			// ����� ���
			ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
		}
	}

	void PrismPlainsScene::Boss()
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

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			// ī�޶� ȿ�� ���
			Camera::fadeOut(1.f, RGB(255, 255, 255));
			mbSceneChange = true;

			// ����� ���
			ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
		}
	}
}