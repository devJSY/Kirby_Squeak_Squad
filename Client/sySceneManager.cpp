
#include "sySceneManager.h"
#include "syTitleScene.h"
#include "syLevelSelectScene.h"
#include "syEndingScene.h"
#include "syOpeningScene.h"
#include "syLevel1_Stage1Scene.h"
#include "syLevel1_Stage2Scene.h"
#include "syLevel1_Stage3Scene.h"
#include "syLevel1_Stage4Scene.h"
#include "syLevel1_BossScene.h"
#include "syTunnelScene.h"
#include "syPrismPlainsScene.h"
#include "syNatureNotchScene.h"
#include "syCushyCloudScene.h"
#include "syJamJungleScene.h"
#include "syVocalVolcanoScene.h"
#include "syIceIslandScene.h"
#include "sySecretSeaScene.h"
#include "syGambleGalaxyScene.h"
#include "syAbilityTestScene.h"
#include "syInventoryItem.h"
#include "syAnimator.h"
#include "syLevel6_BossScene.h"

#include "syObject.h"
#include "syApplication.h"
#include "syTransform.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"
#include "syPlayer.h"

namespace sy
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	// SceneManager에서 Player객체 생성
	Player* SceneManager::mPlayer = new Player(eAbilityType::Normal, ePlayerMode::LevelMode);

	// SceneManager에서 UI객체 생성
	Inventory* SceneManager::mInventory = new Inventory;
	AbilityUI* SceneManager::mAbilityUI = new AbilityUI;
	HPbarUI* SceneManager::mHPbarUI = new HPbarUI;
	LifeUI* SceneManager::mLifeUI = new LifeUI;

	SceneManager::SceneManager()
	{
	}

	void SceneManager::Release()
	{
		std::wstring SceneName = mActiveScene->GetName();

		// 삭제당시 씬이 UI를 추가하지 않은 씬이라면 직접 UI 메모리 해제 해줘야함
		if (SceneName == L"OpeningScene" || SceneName == L"TitleScene" || SceneName == L"EndingScene")
		{
			delete mPlayer;
			mPlayer = nullptr;

			delete mInventory;
			mInventory = nullptr;

			delete mAbilityUI;
			mAbilityUI = nullptr;

			delete mHPbarUI;
			mHPbarUI = nullptr;

			delete mLifeUI;
			mLifeUI = nullptr;			
		}

		for (auto iter : mScenes)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		mScenes.clear();
	}

	void SceneManager::Initialize()
	{
		CreateScene<OpeningScene>(L"OpeningScene");
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<PrismPlainsScene>(L"PrismPlainsScene");
		CreateScene<NatureNotchScene>(L"NatureNotchScene");
		CreateScene<CushyCloudScene>(L"CushyCloudScene");
		CreateScene<JamJungleScene>(L"JamJungleScene");
		CreateScene<VocalVolcanoScene>(L"VocalVolcanoScene");
		CreateScene<IceIslandScene>(L"IceIslandScene");
		CreateScene<SecretSeaScene>(L"SecretSeaScene");
		CreateScene<GambleGalaxyScene>(L"GambleGalaxyScene");
		CreateScene<LevelSelectScene>(L"LevelSelectScene");
		CreateScene<AbilityTestScene>(L"AbilityTestScene");
		CreateScene<Level1_Stage1Scene>(L"Level1_Stage1Scene");
		CreateScene<Level1_Stage2Scene>(L"Level1_Stage2Scene");
		CreateScene<Level1_Stage3Scene>(L"Level1_Stage3Scene");
		CreateScene<Level1_Stage4Scene>(L"Level1_Stage4Scene");
		CreateScene<Level1_BossScene>(L"Level1_BossScene");
		CreateScene<Level6_BossScene>(L"Level6_BossScene");
		CreateScene<TunnelScene>(L"TunnelScene");
		CreateScene<EndingScene>(L"EndingScene");

		for (auto iter : mScenes)
		{
			mActiveScene = iter.second;
			iter.second->Initialize();
		}

		mPlayer->Initialize();
		mInventory->Initialize();
		mAbilityUI->Initialize();
		mHPbarUI->Initialize();
		mLifeUI->Initialize();

		LoadScene(L"OpeningScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::wstring& tempStr = mActiveScene->GetName();

		// 변경전 기존 Scene Exit 호출
		mActiveScene->Exit();

		// 현재 씬에 Player가 존재한다면 삭제
		mActiveScene->RemoveGameObject(eLayerType::Player, mPlayer);

		// 현재 씬에 UI가 존재한다면 삭제
		mActiveScene->RemoveGameObject(eLayerType::Inventory, mInventory);
		mActiveScene->RemoveGameObject(eLayerType::UI, mAbilityUI);
		mActiveScene->RemoveGameObject(eLayerType::UI, mHPbarUI);
		mActiveScene->RemoveGameObject(eLayerType::UI, mLifeUI);

		// 파라메타로 들어온 name 의 Scene 을 찾아 ActiveScene으로 설정해준다
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);
		if (iter == mScenes.end())
			return nullptr;
		mActiveScene = iter->second;

		// 설정한 씬을 제외한 씬에 UI 추가
		if (name != L"OpeningScene" && name != L"TitleScene" && name != L"EndingScene")
		{
			mActiveScene->AddGameObject(eLayerType::Player, mPlayer);
			mActiveScene->AddGameObject(eLayerType::Inventory, mInventory);
			mActiveScene->AddGameObject(eLayerType::UI, mAbilityUI);
			mActiveScene->AddGameObject(eLayerType::UI, mHPbarUI);
			mActiveScene->AddGameObject(eLayerType::UI, mLifeUI);
		}

		// TunnelScene 진입전 이전 씬 이름 등록
		if (name == L"TunnelScene")
		{
			TunnelScene* tunnelScene = dynamic_cast<TunnelScene*>(mActiveScene);
			tunnelScene->SetPrevSceneName(tempStr);
		}

		mActiveScene->Enter();

		return iter->second;
	}

	Scene* SceneManager::GetScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		return iter->second;
	}
}
