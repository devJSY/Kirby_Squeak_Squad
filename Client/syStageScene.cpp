#include "syStageScene.h"
#include "syPlayer.h"
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

namespace sy
{
	StageScene::StageScene()
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
		BgRenderer->SetAffectCamera(true);


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
		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* playerRenderer = player->GetComponent<SpriteRenderer>();
		assert(playerRenderer);
		playerRenderer->SetTexture(ResourceManager::Load<Texture>(L"sword_kirby_change", L"..\\Resources\\Kirby\\SwordKirby\\sword kirby change.png")); // 이미지 설정
		playerRenderer->SetAffectCamera(true);

		//Camera::SetTarget(player); //오브젝트생성은 씬진입시 해야함 여기서 설정한 오브젝트가 다른씬에 영향을 줘선안됨











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

		InvenAt->CreateAnimation(L"Inventory", image, Vector2(0.f, 0.f), Vector2(256.f, 192.f)
			, 16, Vector2(0.f, 0.f), 0.2f);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		Scene::Initialize();
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
		//ShowSceneName(hdc, GetName(), L"Change to WorldTunnelScene : Mouse LBTN");
	}
}