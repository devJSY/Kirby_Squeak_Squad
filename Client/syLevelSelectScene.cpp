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
		// ��� ȭ�� ������Ʈ ���� 
		mlevelBG = object::Instantiate<Level_BG>(eLayerType::BackGround);

		// �»�� UI ���� 
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


		

		for (size_t i = 0; i < 100; i++)
		{			
			object::Instantiate<DotUI>(eLayerType::UI)->GetComponent<Transform>()->SetPosition(Vector2(10.f + (10.f * i), 37.f));
		}
	

		// Create LevelUI don't use index zero
		for (size_t i = 1; i <= 8 ; i++)
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


		Scene::Initialize();

		// 1�� LevelUI Ȱ��ȭ
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
			// Ư�� ���ǿ� ���� Level ����
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


		// �������� ���� Ŭ���� �� ���ȭ�� ����
		if (Input::GetKeyDown(eKeyCode::T))
		{
			mType = eLevelType::AllClear_LevelSelect;
			mlevelBG->SetLevelType(mType);

			// Ȱ��ȭ �Ǿ��ִ� UI�� Star�� Play
			for (size_t i = 1; i <= 8; i++)
			{
				if(mbActiveUI[i]) mStarUI[i]->GetComponent<Animator>()->PlayAnimation(L"Portal_Star", true);
			}
		}

		// Ư�� ���ǿ� ���� UI Ȱ��ȭ
		if (Input::GetKeyDown(eKeyCode::One))
		{
			mbActiveUI[1] = true;
			mPlacardUI[1]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[1]->GetComponent<Animator>()->PlayAnimation(L"One");
		}
		else if (Input::GetKeyDown(eKeyCode::Two))
		{
			mbActiveUI[2] = true;
			mPlacardUI[2]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[2]->GetComponent<Animator>()->PlayAnimation(L"Two");
		}
		else if (Input::GetKeyDown(eKeyCode::Three))
		{
			mbActiveUI[3] = true;
			mPlacardUI[3]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[3]->GetComponent<Animator>()->PlayAnimation(L"Three");
		}
		else if (Input::GetKeyDown(eKeyCode::Four))
		{
			mbActiveUI[4] = true;
			mPlacardUI[4]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[4]->GetComponent<Animator>()->PlayAnimation(L"Four");
		}
		else if (Input::GetKeyDown(eKeyCode::Five))
		{
			mbActiveUI[5] = true;
			mPlacardUI[5]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[5]->GetComponent<Animator>()->PlayAnimation(L"Five");
		}
		else if (Input::GetKeyDown(eKeyCode::Six))
		{
			mbActiveUI[6] = true;
			mPlacardUI[6]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[6]->GetComponent<Animator>()->PlayAnimation(L"Six");
		}
		else if (Input::GetKeyDown(eKeyCode::Seven))
		{
			mbActiveUI[7] = true;
			mPlacardUI[7]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[7]->GetComponent<Animator>()->PlayAnimation(L"Seven");
		}
		else if (Input::GetKeyDown(eKeyCode::Eight))
		{
			mbActiveUI[8] = true;
			mPlacardUI[8]->GetComponent<Animator>()->PlayAnimation(L"PlacardUI");
			mNumberUI[8]->GetComponent<Animator>()->PlayAnimation(L"Eight");
		}

	}

	void LevelSelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void LevelSelectScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);
	}

	void LevelSelectScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}