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
		: mType(eLevelType::Level1)
		, mlevelBG(nullptr)
		, mbActiveUI{}
		, mStepUI{}
		, mStarUI{}
		, mNumberUI{}
		, mDots{}
		, eCurStageState(eStageState::StageExit)
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

		Scene::Initialize();

		//stageUI->GetComponent<Animator>()->PlayAnimation(L"NormalStage", true);

		// mlevelBG �ʱ�ȭ ���� ȣ��
		mlevelBG->SetLevelType(mType);

		// ExitUI ���� Ȱ��ȭ
		mbActiveUI[0] = true;
	}

	void PrismPlainsScene::Update()
	{
		switch (eCurStageState)
		{
		case eStageState::StageExit:
			StageExit();
			break;
		case eStageState::Stage1:
			Stage1();
			break;
		case eStageState::Stage2:
			Stage2();
			break;
		case eStageState::Stage3:
			Stage3();
			break;
		case eStageState::Stage4:
			Stage4();
			break;
		case eStageState::Ex:
			Ex();
			break;
		case eStageState::Boss:
			StageBoss();
			break;
		default:
			break;
		}

		// Test
		if (Input::GetKeyDown(eKeyCode::S))
		{
			mbActiveUI[0] = true;
			mStepUI[0]->GetComponent<Animator>()->PlayAnimation(L"NormalStage");
			mStarUI[0]->GetComponent<Animator>()->PlayAnimation(L"StageStar");
			mNumberUI[0]->GetComponent<Animator>()->PlayAnimation(L"One");
		}


		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			//SceneManager::LoadScene(L"NatureNotchScene");
			SceneManager::LoadScene(L"StageScene");
		}

		// �������� Ŭ���� �� ���ȭ�� ����
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::Level1_Clear;
			mlevelBG->SetLevelType(mType);
		}

		Scene::Update();
	}

	void PrismPlainsScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PrismPlainsScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		Vector2 vec = Vector2(35.f, 70.f);

		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(vec);
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(false);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(false);

		player->SetPlayerMode(ePlayerMode::LevelMode);
		playerTrans->SetDirection(eDirection::RIGHT);

		// �÷��̾� Ÿ�Կ����� ���� ���� 
		eAbilityType playerType = player->GetAbilityType();
		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player);
			defaultKirby->SetKirbyState(eDefaultKirbyState::Turn);
			playerAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}

		eCurStageState = eStageState::StageExit;
	}

	void PrismPlainsScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void PrismPlainsScene::CreateDot()
	{
	}

	void PrismPlainsScene::CreateStageUI()
	{
		// StageExit UI ���� 
		Texture* Exit_StageScene_Tex = ResourceManager::Load<Texture>(L"Exit_StageScene_Tex", L"..\\Resources\\UI\\Exit_StageScene.bmp");
		ExitUI = object::Instantiate<UI>(eLayerType::LevelUI);
		SpriteRenderer* ExitUIRenderer = ExitUI->AddComponent<SpriteRenderer>();
		ExitUIRenderer->SetTexture(Exit_StageScene_Tex);
		ExitUIRenderer->SetAffectedCamera(false);
		ExitUIRenderer->SetRenderTrig(false);
		ExitUI->GetComponent<Transform>()->SetPosition(Vector2(35.f, 80.f));

		// Create StageUI
		for (size_t i = 0; i < 7; i++)
		{
			mStepUI[i] = object::Instantiate<StepUI>(eLayerType::LevelUI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::LevelUI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::LevelUI);
		}

		// ��ġ �����ؾ���
		// StageUI Position Set
		mStepUI[0]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		mStarUI[0]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 37.f));
		mNumberUI[0]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 38.f));

		mStepUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 40.f));
		mStarUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 37.f));
		mNumberUI[1]->GetComponent<Transform>()->SetPosition(Vector2(140.f, 38.f));

		mStepUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 63.f));
		mStarUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 60.f));
		mNumberUI[2]->GetComponent<Transform>()->SetPosition(Vector2(200.f, 61.f));

		mStepUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 110.f));
		mStarUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 107.f));
		mNumberUI[3]->GetComponent<Transform>()->SetPosition(Vector2(215.f, 108.f));

		mStepUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 151.f));
		mStarUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 148.f));
		mNumberUI[4]->GetComponent<Transform>()->SetPosition(Vector2(188.f, 149.f));

		// Ex
		mStepUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 150.f));
		mStarUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 147.f));
		mNumberUI[5]->GetComponent<Transform>()->SetPosition(Vector2(115.f, 148.f));

		// Boss
		mStepUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 151.f));
		mStarUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 148.f));
		mNumberUI[6]->GetComponent<Transform>()->SetPosition(Vector2(35.f, 149.f));
	}

	void PrismPlainsScene::StageExit()
	{
	}

	void PrismPlainsScene::Ex()
	{
	}

	void PrismPlainsScene::Stage1()
	{
	}

	void PrismPlainsScene::Stage2()
	{
	}

	void PrismPlainsScene::Stage3()
	{
	}

	void PrismPlainsScene::Stage4()
	{
	}

	void PrismPlainsScene::Stage5()
	{
	}

	void PrismPlainsScene::StageBoss()
	{
	}
}