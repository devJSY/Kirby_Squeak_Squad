#include "syVocalVolcanoScene.h"
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
#include "syTonadoKirby.h"

namespace sy
{
	VocalVolcanoScene::VocalVolcanoScene()
		: mLevelType(eLevelType::Level5)
		, ExitUI(nullptr)
		, mCurStageState(eStageState::StageExit)
		, mEnterTime(0.f)
		, mZoom(nullptr)
	{
	}

	VocalVolcanoScene::~VocalVolcanoScene()
	{
	}

	void VocalVolcanoScene::Initialize()
	{
		Level_BG* mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);


		// UI 생성 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");

		UI* LevelMarkUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelMarkUI->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelMarkUIAni = LevelMarkUI->AddComponent<Animator>();
		LevelMarkUIAni->CreateAnimation(Tex, L"LevelMarkUI", Vector2(222.f, 941.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelMarkUIAni->SetBmpRGB(L"LevelMarkUI", 0, 128, 0);
		LevelMarkUIAni->PlayAnimation(L"LevelMarkUI");
		LevelMarkUIAni->SetAffectedCamera(false);

		UI* LevelNameUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelNameUI->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameUIAni = LevelNameUI->AddComponent<Animator>();
		LevelNameUIAni->CreateAnimation(Tex, L"LevelNameUI", Vector2(2.f, 978.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameUIAni->SetBmpRGB(L"LevelNameUI", 0, 128, 128);
		LevelNameUIAni->PlayAnimation(L"LevelNameUI");
		LevelNameUIAni->SetAffectedCamera(false);

		// Stage UI 생성
		CreateStageUI();

		// Sound Load
		ResourceManager::Load<Sound>(L"StageSelectSound", L"..\\Resources\\Sound\\Theme\\StageSelect.wav");
		ResourceManager::Load<Sound>(L"Click2Sound", L"..\\Resources\\Sound\\Effect\\Click2.wav");

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mLevelType);
	}

	void VocalVolcanoScene::Update()
	{
		// Enter 애니메이션 재생용
		mEnterTime += Time::DeltaTime();

		if (mEnterTime > 1.3f)
		{
			switch (mCurStageState)
			{
			case eStageState::StageExit:
				StageExit();
				break;
			default:
				break;
			}
		}


		Scene::Update();
	}

	void VocalVolcanoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void VocalVolcanoScene::Enter()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;

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
			TonadoKirby* tonadoKirby = dynamic_cast<TonadoKirby*>(player->GetActiveKirby());
			tonadoKirby->SetKirbyState(eTonadoKirbyState::Choice);
			playerAni->PlayAnimation(L"TornadoKirby_Choice", false);
		}

		mCurStageState = eStageState::StageExit;

		// 오디오 재생
		ResourceManager::Find<Sound>(L"StageSelectSound")->Play(true);
	}

	void VocalVolcanoScene::Exit()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void VocalVolcanoScene::CreateStageUI()
	{
		// StageExit UI 생성 
		Texture* Exit_StageScene_Tex = ResourceManager::Load<Texture>(L"Exit_StageScene_Tex", L"..\\Resources\\UI\\Exit_StageScene.bmp");
		ExitUI = object::Instantiate<UI>(eLayerType::LevelUI);
		SpriteRenderer* ExitUIRenderer = ExitUI->AddComponent<SpriteRenderer>();
		ExitUIRenderer->SetTexture(Exit_StageScene_Tex);
		ExitUIRenderer->SetAffectedCamera(false);
		ExitUIRenderer->SetRenderTrig(true);
		ExitUI->GetComponent<Transform>()->SetPosition(Vector2(35.f, 80.f));
	}

	void VocalVolcanoScene::StageExit()
	{
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
}