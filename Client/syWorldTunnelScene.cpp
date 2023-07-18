#include "syWorldTunnelScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syAnimator.h"
#include "syWorldTunnel.h"
#include "syInventory.h"
#include "syAbilityUI.h"
#include "syHPbarUI.h"
#include "syLifeUI.h"

namespace sy
{
	WorldTunnelScene::WorldTunnelScene()
	{
	}

	WorldTunnelScene::~WorldTunnelScene()
	{
	}

	void WorldTunnelScene::Initialize()
	{
		WorldTunnel* Bg = object::Instantiate<WorldTunnel>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����

		/////////////// Inventory ��ü�� ���߿� ��� ������ �ϳ��� �����ϰų� �����ؼ� �������ִ� ������� �����ؾ���
		// �ϴ� ȭ�� ������Ʈ ���� 
		Inventory* Inven = object::Instantiate<Inventory>(eLayerType::Inventory);

		// �κ��丮 Ŭ���� ��ġ ����
		vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		Inven->GetComponent<Transform>()->SetPosition(vec);


		// UI ����
		AbilityUI* AbilityUi = object::Instantiate<AbilityUI>(eLayerType::UI);
		Vector2 Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 20.0f;
		Uivec.y -= 25.f;
		AbilityUi->GetComponent<Transform>()->SetPosition(Uivec);
		AbilityUi->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		HPbarUI* HPbarUi = object::Instantiate<HPbarUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 85.0f;
		Uivec.y -= 12.f;
		HPbarUi->GetComponent<Transform>()->SetPosition(Uivec);
		HPbarUi->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		LifeUI* LifeUi = object::Instantiate<LifeUI>(eLayerType::UI);
		Uivec = Vector2(Application::GetResolution()) / 2.f;
		Uivec.x = 65.0f;
		Uivec.y -= 27.f;
		LifeUi->GetComponent<Transform>()->SetPosition(Uivec);
		LifeUi->SetOwner(nullptr); // ���ʼ��� ���߿� ��������

		Scene::Initialize();
	}

	void WorldTunnelScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"EndingScene");
		}
	}

	void WorldTunnelScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void WorldTunnelScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);
	}

	void WorldTunnelScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}