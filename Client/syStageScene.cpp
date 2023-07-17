#include "syStageScene.h"
#include "syDefaultKirby.h"
#include "syObject.h"
#include "syGameObject.h"
#include "sySpriteRenderer.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syForeGround.h"
#include "syInventory.h"
#include "syAnimator.h"
#include "syPlayer.h"

#include "syWaddleDee.h"
#include "syBlockEnemy.h"
#include "syFlower.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"
#include "syIce.h"
#include "sySirKibble.h"

namespace sy
{
	StageScene::StageScene()
		: mPlayer(nullptr)
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		// 백그라운드 설정
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Stage_BackGround.bmp"); // 이미지 설정
		assert(tex);
		BgRenderer->SetTexture(tex);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // 중점 설정
		BgRenderer->SetAffectCamera(false);

		// 스테이지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		assert(Fg);
		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		assert(FgRenderer);

		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // 이미지 설정
		assert(tex);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // 중점 설정
		FgRenderer->SetAffectCamera(true);

		// 플레이어 설정
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);
		assert(mPlayer);
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));


		// 적 생성
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));

		BlockEnemy* Block = object::Instantiate<BlockEnemy>(eLayerType::Enemy);
		Block->GetComponent<Transform>()->SetPosition(Vector2(150.f, 100.f));

		Flower* flower = object::Instantiate<Flower>(eLayerType::Enemy);
		flower->GetComponent<Transform>()->SetPosition(Vector2(200.f, 100.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.f));

		Ice* ice = object::Instantiate<Ice>(eLayerType::Enemy);
		ice->GetComponent<Transform>()->SetPosition(Vector2(300.f, 100.f));

		SirKibble* sirkibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirkibble->GetComponent<Transform>()->SetPosition(Vector2(350.f, 100.f));




		/////////////// Inventory 객체는 나중에 모든 씬에서 하나만 생성하도록 수정해야함
		// 하단 화면 오브젝트 생성 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// 인벤토리 클래스 위치 설정
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// 인벤토리 애니메이션 설정
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(image, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		// 생성한 모든 오브젝트 초기화 
		Scene::Initialize();
		// 초기화가 끝난 오브젝트들은 Delete 객체생성은 Enter에서 이루어짐
		DeleteAllLayer();
	}

	void StageScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"WorldTunnelScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void StageScene::Enter()
	{
		// 백그라운드 설정
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Stage_BackGround.bmp"); // 이미지 설정
		assert(tex);
		BgRenderer->SetTexture(tex);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // 중점 설정
		BgRenderer->SetAffectCamera(false);

		// 스테이지 설정
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		assert(Fg);
		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		assert(FgRenderer);

		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // 이미지 설정
		assert(tex);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // 중점 설정
		FgRenderer->SetAffectCamera(true);

		// 플레이어 설정
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);
		assert(mPlayer);
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));


		// 적 생성
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));

		BlockEnemy* Block = object::Instantiate<BlockEnemy>(eLayerType::Enemy);
		Block->GetComponent<Transform>()->SetPosition(Vector2(150.f, 100.f));

		Flower* flower = object::Instantiate<Flower>(eLayerType::Enemy);
		flower->GetComponent<Transform>()->SetPosition(Vector2(200.f, 100.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.f));

		Ice* ice = object::Instantiate<Ice>(eLayerType::Enemy);
		ice->GetComponent<Transform>()->SetPosition(Vector2(300.f, 100.f));

		SirKibble* sirkibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirkibble->GetComponent<Transform>()->SetPosition(Vector2(350.f, 100.f));


		///////////// Inventory 객체는 나중에 모든 씬에서 하나만 생성하도록 수정해야함
		// 하단 화면 오브젝트 생성 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// 인벤토리 클래스 위치 설정
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// 인벤토리 애니메이션 설정
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(image, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);


		// 카메라 설정 
		Camera::SetTarget(mPlayer);
	}

	void StageScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		DeleteAllLayer();
	}
}