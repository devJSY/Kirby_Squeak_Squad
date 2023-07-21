#include "sySecretSeaScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syLevel_BG.h"
#include "syObject.h"

#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"

namespace sy
{
	SecretSeaScene::SecretSeaScene()
		: mType(eLevelType::Level7)
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

		BackGround* Level = object::Instantiate<BackGround>(eLayerType::BackGround);
		Level->GetComponent<Transform>()->SetPosition(Vector2(72.f, 8.f));

		Animator* LevelAni = Level->AddComponent<Animator>();
		LevelAni->CreateAnimation(Tex, L"Level", Vector2(222.f, 977.f), Vector2(96.f, 15.f), Vector2(113.f, 0.f), 1, 1);
		LevelAni->SetBmpRGB(L"Level", 0, 128, 0);
		LevelAni->PlayAnimation(L"Level");
		LevelAni->SetAffectedCamera(false);

		BackGround* LevelName = object::Instantiate<BackGround>(eLayerType::BackGround);
		LevelName->GetComponent<Transform>()->SetPosition(Vector2(101.f, 15.f));

		Animator* LevelNameAni = LevelName->AddComponent<Animator>();
		LevelNameAni->CreateAnimation(Tex, L"LevelName", Vector2(2.f, 1046.f), Vector2(202.f, 32.f), Vector2(202.f, 0.f), 1, 1);
		LevelNameAni->SetBmpRGB(L"LevelName", 0, 128, 128);
		LevelNameAni->PlayAnimation(L"LevelName");
		LevelNameAni->SetAffectedCamera(false);

		Scene::Initialize();

		// mlevelBG 초기화 이후 호출
		mlevelBG->SetLevelType(mType);
	}

	void SecretSeaScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"GambleGalaxyScene");
		}

		Scene::Update();
	}

	void SecretSeaScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SecretSeaScene::Enter()
	{
	}

	void SecretSeaScene::Exit()
	{
	}
}