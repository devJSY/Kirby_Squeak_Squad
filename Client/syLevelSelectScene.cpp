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
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syGameObject.h"
#include "syRigidbody.h"
#include "syTime.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syZoom_Effect.h"
#include "syMixItem.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "syInventory.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
		: mLevelType(eLevelType::LevelSelect)
		, mlevelBG(nullptr)
		, mbActiveUI{}
		, mPlacardUI{}
		, mStarUI{}
		, mNumberUI{}
		, mDots{}
		, mCurLevelState(eLevelState::Level1)
		, mEnterTime(0.f)
		, mZoom(nullptr)
		, mbSceneChange(false)
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

		UI* LevelMarkUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelMarkUI->GetComponent<Transform>()->SetPosition(Vector2(80.f, 7.f));

		Animator* LevelMarkUIAni = LevelMarkUI->AddComponent<Animator>();
		LevelMarkUIAni->CreateAnimation(Tex, L"LevelMarkUI", Vector2(222.f, 850.f), Vector2(113.f, 17.f),Vector2(113.f, 0.f), 1, 1);
		LevelMarkUIAni->SetBmpRGB(L"LevelMarkUI", 0, 128, 0);
		LevelMarkUIAni->PlayAnimation(L"LevelMarkUI");
		LevelMarkUIAni->SetAffectedCamera(false);

		UI* LevelNameUI = object::Instantiate<UI>(eLayerType::LevelUI);
		LevelNameUI->GetComponent<Transform>()->SetPosition(Vector2(101.f, 16.f));

		Animator* LevelNameUIAni = LevelNameUI->AddComponent<Animator>();
		LevelNameUIAni->CreateAnimation(Tex, L"LevelNameUI", Vector2(2.f, 1148.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameUIAni->SetBmpRGB(L"LevelNameUI", 0, 128, 128);
		LevelNameUIAni->PlayAnimation(L"LevelNameUI");
		LevelNameUIAni->SetAffectedCamera(false);
						
		// Dot 생성
		CreateDot();	

		// LevelUI생성
		CreateLevelUI();

		// Sound Load
		ResourceManager::Load<Sound>(L"WorldSelectSound", L"..\\Resources\\Sound\\Theme\\WorldSelect.wav");
		ResourceManager::Load<Sound>(L"Click2Sound", L"..\\Resources\\Sound\\Effect\\Click2.wav");

		Scene::Initialize();

		// 기본 Level1 UI 활성화
		SetActiveUI(eLevelType::Level1);

		mlevelBG->SetLevelType(eLevelType::LevelSelect);
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		// Enter 애니메이션 재생용
		mEnterTime += Time::DeltaTime();
		 
		if (mEnterTime > 1.3f && !mbSceneChange)
		{
			// 현재 레벨상태 지정
			switch (mCurLevelState)
			{
			case eLevelState::Level1:
				Level1();
				break;
			case eLevelState::Level2:
				Level2();
				break;
			case eLevelState::Level3:
				Level3();
				break;
			case eLevelState::Level4:
				Level4();
				break;
			case eLevelState::Level5:
				Level5();
				break;
			case eLevelState::Level6:
				Level6();
				break;
			case eLevelState::Level7:
				Level7();
				break;
			case eLevelState::Level8:
				Level8();
				break;
			case eLevelState::AbilityTest:
				AbilityTest();
				break;
			default:
				break;
			}

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
			{
				mbSceneChange = true;

				if (mCurLevelState == eLevelState::AbilityTest)
				{
					Camera::fadeOut(1.f, RGB(255, 255, 255));
				}
				else
				{
					if (mZoom == nullptr)
					{
						mZoom = new Zoom_Effect(SceneManager::GetPlayer());
						object::ActiveSceneAddGameObject(eLayerType::Zoom, mZoom);
					}
				}

				// 오디오 재생
				ResourceManager::Find<Sound>(L"Click2Sound")->Play(false);
			}			
		}

		if (mbSceneChange && mCurLevelState == eLevelState::AbilityTest && Camera::IsEmptyCamEffect())
		{
			SceneManager::LoadScene(L"AbilityTestScene");
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SetClearActiveUI(eLevelState::Level1);
			SetClearActiveUI(eLevelState::Level2);
			SetClearActiveUI(eLevelState::Level3);
			SetClearActiveUI(eLevelState::Level4);
			SetClearActiveUI(eLevelState::Level5);
			SetClearActiveUI(eLevelState::Level6);
			SetClearActiveUI(eLevelState::Level7);
			SetClearActiveUI(eLevelState::Level8);
		}

		// 임시로 키입력으로 UI 활성화
		if (Input::GetKeyDown(eKeyCode::One))
			SetActiveUI(eLevelType::Level1);
		else if (Input::GetKeyDown(eKeyCode::Two))
			SetActiveUI(eLevelType::Level2);
		else if (Input::GetKeyDown(eKeyCode::Three))
			SetActiveUI(eLevelType::Level3);
		else if (Input::GetKeyDown(eKeyCode::Four))
			SetActiveUI(eLevelType::Level4);
		else if (Input::GetKeyDown(eKeyCode::Five))
			SetActiveUI(eLevelType::Level5);
		else if (Input::GetKeyDown(eKeyCode::Six))
			SetActiveUI(eLevelType::Level6);
		else if (Input::GetKeyDown(eKeyCode::Seven))
			SetActiveUI(eLevelType::Level7);
		else if (Input::GetKeyDown(eKeyCode::Eight))
			SetActiveUI(eLevelType::Level8);
		else if (Input::GetKeyDown(eKeyCode::Nine))
			SetActiveUI(eLevelType::AbilityTest);
	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;

		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Vector2 vec = Vector2::Zero;

		// mCurLevel 상태에 따라 위치 설정
		if (mCurLevelState == eLevelState::Level1)
			vec = mPlacardUI[1]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level2)
			vec = mPlacardUI[2]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level3)
			vec = mPlacardUI[3]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level4)
			vec = mPlacardUI[4]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level5)
			vec = mPlacardUI[5]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level6)
			vec = mPlacardUI[6]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level7)
			vec = mPlacardUI[7]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::Level8)
			vec = mPlacardUI[8]->GetComponent<Transform>()->GetPosition();
		else if (mCurLevelState == eLevelState::AbilityTest)
			vec = mPlacardUI[9]->GetComponent<Transform>()->GetPosition();

		// Offset값 추가
		vec.y -= 17.f;

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
		ResourceManager::Find<Sound>(L"WorldSelectSound")->Play(true);
	}

	void LevelSelectScene::Exit()
	{
		mEnterTime = 0.f;
		mZoom = nullptr;
		mbSceneChange = false;

		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}

	void LevelSelectScene::CreateLevelUI()
	{
		// Create LevelUI don't use index zero
		for (size_t i = 1; i <= 9; i++)
		{
			mPlacardUI[i] = object::Instantiate<PlacardUI>(eLayerType::LevelUI);
			mStarUI[i] = object::Instantiate<StarUI>(eLayerType::LevelUI);
			mNumberUI[i] = object::Instantiate<NumberUI>(eLayerType::LevelUI);
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

		mPlacardUI[9]->GetComponent<Transform>()->SetPosition(Vector2(128.f, 100.f));
		mStarUI[9]->GetComponent<Transform>()->SetPosition(Vector2(128.f, 97.f));
		mNumberUI[9]->GetComponent<Transform>()->SetPosition(Vector2(128.f, 98.f));
	}

	void LevelSelectScene::Level1()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[2] == true)
			{
				Vector2 vec = mPlacardUI[2]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level2;
			}
		}
	}

	void LevelSelectScene::Level2()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[1] == true)
			{
				Vector2 vec = mPlacardUI[1]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level1;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[3] == true)
			{
				Vector2 vec = mPlacardUI[3]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level3;
			}
		}
	}

	void LevelSelectScene::Level3()
	{
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[2] == true)
			{
				Vector2 vec = mPlacardUI[2]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level2;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[4] == true)
			{
				Vector2 vec = mPlacardUI[4]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level4;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			if (mbActiveUI[9] == true)
			{
				Vector2 vec = mPlacardUI[9]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::AbilityTest;
			}
		}
	}

	void LevelSelectScene::Level4()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[3] == true)
			{
				Vector2 vec = mPlacardUI[3]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level3;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[5] == true)
			{
				Vector2 vec = mPlacardUI[5]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level5;
			}
		}
	}

	void LevelSelectScene::Level5()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbActiveUI[4] == true)
			{
				Vector2 vec = mPlacardUI[4]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level4;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[6] == true)
			{
				Vector2 vec = mPlacardUI[6]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level6;
			}
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[9] == true)
			{
				Vector2 vec = mPlacardUI[9]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::AbilityTest;
			}
		}
	}

	void LevelSelectScene::Level6()
	{
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[5] == true)
			{
				Vector2 vec = mPlacardUI[5]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level5;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[7] == true)
			{
				Vector2 vec = mPlacardUI[7]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level7;
			}
		}
	}

	void LevelSelectScene::Level7()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[6] == true)
			{
				Vector2 vec = mPlacardUI[6]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level6;
			}
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (mbActiveUI[8] == true)
			{
				Vector2 vec = mPlacardUI[8]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level8;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbActiveUI[9] == true)
			{
				Vector2 vec = mPlacardUI[9]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::AbilityTest;
			}
		}
	}

	void LevelSelectScene::Level8()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[7] == true)
			{
				Vector2 vec = mPlacardUI[7]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level7;
			}
		}
	}

	void LevelSelectScene::AbilityTest()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			if (mbActiveUI[7] == true)
			{
				Vector2 vec = mPlacardUI[7]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level7;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			if (mbActiveUI[3] == true)
			{
				Vector2 vec = mPlacardUI[3]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level3;
			}
		}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mbActiveUI[5] == true)
			{
				Vector2 vec = mPlacardUI[5]->GetComponent<Transform>()->GetPosition();
				vec.y -= 17.f;

				Player* player = SceneManager::GetPlayer();
				Transform* playerTrans = player->GetComponent<Transform>();
				playerTrans->SetPosition(vec);
				mCurLevelState = eLevelState::Level5;
			}
		}
	}

	void LevelSelectScene::SetActiveUI(eLevelType type)
	{
		// type 에 따라 UI 활성화
		if (type == eLevelType::Level1)
		{
			if (!mbActiveUI[1])
			{
				mbActiveUI[1] = true;
				mPlacardUI[1]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"One");
			}
		}
		else if (type == eLevelType::Level2)
		{
			if (!mbActiveUI[2])
			{
				mbActiveUI[2] = true;
				mPlacardUI[2]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[2]->GetComponent<Animator>()->PlayAnimation(L"Two");

				for (size_t i = 0; i < mDots[2].size(); i++)
				{
					DotUI* dot = mDots[2][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level3)
		{
			if (!mbActiveUI[3])
			{
				mbActiveUI[3] = true;
				mPlacardUI[3]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[3]->GetComponent<Animator>()->PlayAnimation(L"Three");

				for (size_t i = 0; i < mDots[3].size(); i++)
				{
					DotUI* dot = mDots[3][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level4)
		{
			if (!mbActiveUI[4])
			{
				mbActiveUI[4] = true;
				mPlacardUI[4]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[4]->GetComponent<Animator>()->PlayAnimation(L"Four");

				for (size_t i = 0; i < mDots[4].size(); i++)
				{
					DotUI* dot = mDots[4][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level5)
		{
			if (!mbActiveUI[5])
			{
				mbActiveUI[5] = true;
				mPlacardUI[5]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[5]->GetComponent<Animator>()->PlayAnimation(L"Five");

				for (size_t i = 0; i < mDots[5].size(); i++)
				{
					DotUI* dot = mDots[5][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level6)
		{
			if (!mbActiveUI[6])
			{
				mbActiveUI[6] = true;
				mPlacardUI[6]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[6]->GetComponent<Animator>()->PlayAnimation(L"Six");

				for (size_t i = 0; i < mDots[6].size(); i++)
				{
					DotUI* dot = mDots[6][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level7)
		{
			if (!mbActiveUI[7])
			{
				mbActiveUI[7] = true;
				mPlacardUI[7]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[7]->GetComponent<Animator>()->PlayAnimation(L"Seven");

				for (size_t i = 0; i < mDots[7].size(); i++)
				{
					DotUI* dot = mDots[7][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::Level8)
		{
			if (!mbActiveUI[8])
			{
				mbActiveUI[8] = true;
				mPlacardUI[8]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[8]->GetComponent<Animator>()->PlayAnimation(L"Eight");

				for (size_t i = 0; i < mDots[8].size(); i++)
				{
					DotUI* dot = mDots[8][i];
					dot->SetActiveTrig(true);
				}
			}
		}
		else if (type == eLevelType::AbilityTest)
		{
			if (!mbActiveUI[9])
			{
				mbActiveUI[9] = true;
				mPlacardUI[9]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
				mNumberUI[9]->GetComponent<Animator>()->PlayAnimation(L"Number_9");

				for (size_t i = 0; i < mDots[9].size(); i++)
				{
					DotUI* dot = mDots[9][i];
					dot->SetActiveTrig(true);
				}
			}
		}
	}

	void LevelSelectScene::SetClearActiveUI(eLevelState type)
	{
		if (type == eLevelState::Level1)
		{
			if (mbActiveUI[1])
				mStarUI[1]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level2)
		{
			if (mbActiveUI[2])
				mStarUI[2]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level3)
		{
			if (mbActiveUI[3])
				mStarUI[3]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level4)
		{
			if (mbActiveUI[4])
				mStarUI[4]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level5)
		{
			if (mbActiveUI[5])
				mStarUI[5]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level6)
		{
			if (mbActiveUI[6])
				mStarUI[6]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level7)
		{
			if (mbActiveUI[7])
				mStarUI[7]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}
		else if (type == eLevelState::Level8)
		{
			if (mbActiveUI[8])
				mStarUI[8]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
		}


		// 스테이지 전부 클리어 시 배경화면 변경
		for (size_t i = 1; i <= 8; i++)
		{
			if (mbActiveUI[i] == false)
				return;
		}

		mLevelType = eLevelType::AllClear_LevelSelect;
		mlevelBG->SetLevelType(mLevelType);
	}

	void LevelSelectScene::CreateDot()
	{
		// Create DotUI don't use index zero, one

		DotUI* dot;

		/////////// Level2 ///////////

		for (size_t i = 0; i < 6; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(200.f - (8.f * i), 42.f));
			dot->SetDelayTime(0.3f - (0.05f * i));

			mDots[2].push_back(dot);
		}

		dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
		dot->GetComponent<Transform>()->SetPosition(Vector2(200.f, 50.f));
		dot->SetDelayTime(0.35f);

		mDots[2].push_back(dot);

		/////////// Level3 ///////////

		//Top
		for (size_t i = 0; i < 4; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f - (8.f * i), 65.f));
			dot->SetDelayTime(0.2f - (0.05f * i));

			mDots[3].push_back(dot);
		}

		// Middle
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f, 73.f + (8.f * i)));
			dot->SetDelayTime(0.25f + (0.05f * i));

			mDots[3].push_back(dot);
		}

		//Bottom
		for (size_t i = 0; i < 2; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(240.f - (8.f * i), 113.f));
			dot->SetDelayTime(0.55f + (0.05f * i));

			mDots[3].push_back(dot);
		}

		/////////// Level4 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(215.f, 153.f - (8.f * i)));
			dot->SetDelayTime(0.25f - (0.05f * i));

			mDots[4].push_back(dot);
		}

		dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
		dot->GetComponent<Transform>()->SetPosition(Vector2(207.f, 153.f));
		dot->SetDelayTime(0.3f);

		mDots[4].push_back(dot);


		/////////// Level5 ///////////
		for (size_t i = 0; i < 6; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(170.f - (8.f * i), 153.f));
			dot->SetDelayTime(0.05f * i);

			mDots[5].push_back(dot);
		}

		/////////// Level6 ///////////
		for (size_t i = 0; i < 7; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(100.f - (8.f * i), 153.f));
			dot->SetDelayTime(0.05f * i);

			mDots[6].push_back(dot);
		}

		/////////// Level7 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(35.f, 140.f - (8.f * i)));
			dot->SetDelayTime(0.05f * i);

			mDots[7].push_back(dot);
		}

		/////////// Level8 ///////////
		for (size_t i = 0; i < 5; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(35.f, 90.f - (8.f * i)));
			dot->SetDelayTime(0.05f * i);

			mDots[8].push_back(dot);
		}

		/////////// AbilityTest ///////////
		for (size_t i = 0; i < 9; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(51.f + (8.f * i), 103.f));
			dot->SetDelayTime(0.05f * i);

			mDots[9].push_back(dot);
		}

		for (size_t i = 0; i < 6; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(142.f + (8.f * i), 103.f));
			dot->SetDelayTime(0.45f + (0.05f * i));

			mDots[9].push_back(dot);
		}

		dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
		dot->GetComponent<Transform>()->SetPosition(Vector2(190.f, 108.f));
		dot->SetDelayTime(0.75f);

		mDots[9].push_back(dot);


		for (size_t i = 0; i < 3; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(126.f, 110 + (i * 8.f)));
			dot->SetDelayTime(0.45f + (0.05f * i));

			mDots[9].push_back(dot);
		}

		for (size_t i = 0; i < 3; i++)
		{
			dot = object::Instantiate<DotUI>(eLayerType::LevelUI);
			dot->GetComponent<Transform>()->SetPosition(Vector2(118.f, 126.f + (i * 8.f)));
			dot->SetDelayTime(0.60f + (0.05f * i));

			mDots[9].push_back(dot);
		}		
	}
}