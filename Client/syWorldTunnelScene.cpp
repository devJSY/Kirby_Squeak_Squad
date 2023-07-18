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