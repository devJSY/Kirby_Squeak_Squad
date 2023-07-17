#include "syLevelSelectScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syDefaultKirby.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"
#include "syCamera.h"

namespace sy
{
	LevelSelectScene::LevelSelectScene()
	{
	}

	LevelSelectScene::~LevelSelectScene()
	{
	}

	void LevelSelectScene::Initialize()
	{
		// ��� ȭ�� ������Ʈ ���� 
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		Texture* tex = ResourceManager::Load<Texture>(L"LevelSelectImage", L"..\\Resources\\Map\\Level_Select.bmp");
		
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����

		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����




		// Inventory ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);

		// Inventory ��ġ ����
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		Inven->GetComponent<Transform>()->SetPosition(vec);


		//// UI ����
		//AbilityUI* Ability = object::Instantiate<AbilityUI>(eLayerType::UI);
		//assert(Ability);
		//SpriteRenderer* AbilityRenderer = Ability->AddComponent<SpriteRenderer>();
		//assert(AbilityRenderer);
		//AbilityRenderer->SetAffectCamera(false);
		//Texture* Abilityimage = ResourceManager::Load<Texture>(L"AbilityUI"
		//	, L"..\\Resources\\UI\\Ability_UI.bmp");
		//AbilityRenderer->SetBmpRGB(255, 0, 255);
		//AbilityRenderer->SetTexture(Abilityimage);
		//Ability->GetComponent<Transform>()->SetPosition(Vector2(100.f,100.f)); 


		//HPbarUI* HPbar = object::Instantiate<HPbarUI>(eLayerType::UI);
		//assert(HPbar);
		//SpriteRenderer* HPbarRenderer = HPbar->AddComponent<SpriteRenderer>();
		//assert(AbilityRenderer);

		Scene::Initialize();
	}

	void LevelSelectScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"StageScene");
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
	}
}