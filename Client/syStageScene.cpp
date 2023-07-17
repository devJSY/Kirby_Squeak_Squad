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
		// ��׶��� ����
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Stage_BackGround.bmp"); // �̹��� ����
		assert(tex);
		BgRenderer->SetTexture(tex);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		BgRenderer->SetAffectCamera(false);

		// �������� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		assert(Fg);
		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		assert(FgRenderer);

		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // �̹��� ����
		assert(tex);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		FgRenderer->SetAffectCamera(true);

		// �÷��̾� ����
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);
		assert(mPlayer);
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));


		// �� ����
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




		/////////////// Inventory ��ü�� ���߿� ��� ������ �ϳ��� �����ϵ��� �����ؾ���
		// �ϴ� ȭ�� ������Ʈ ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// �κ��丮 Ŭ���� ��ġ ����
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// �κ��丮 �ִϸ��̼� ����
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(image, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();
		// �ʱ�ȭ�� ���� ������Ʈ���� Delete ��ü������ Enter���� �̷����
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
		// ��׶��� ����
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();
		assert(BgRenderer);
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Stage_BackGround.bmp"); // �̹��� ����
		assert(tex);
		BgRenderer->SetTexture(tex);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		BgRenderer->SetAffectCamera(false);

		// �������� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		assert(Fg);
		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		assert(FgRenderer);

		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // �̹��� ����
		assert(tex);
		FgRenderer->SetTexture(tex);
		FgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����
		FgRenderer->SetAffectCamera(true);

		// �÷��̾� ����
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);
		assert(mPlayer);
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();
		assert(PlayerTrans);
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));


		// �� ����
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


		///////////// Inventory ��ü�� ���߿� ��� ������ �ϳ��� �����ϵ��� �����ؾ���
		// �ϴ� ȭ�� ������Ʈ ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);
		assert(Inven);

		// �κ��丮 Ŭ���� ��ġ ����
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		(Inven->GetComponent<Transform>())->SetPosition(vec);

		// �κ��丮 �ִϸ��̼� ����
		Animator* InvenAt = Inven->AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");

		InvenAt->CreateAnimation(image, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);


		// ī�޶� ���� 
		Camera::SetTarget(mPlayer);
	}

	void StageScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		DeleteAllLayer();
	}
}