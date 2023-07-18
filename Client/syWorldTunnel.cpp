#include "syWorldTunnel.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	WorldTunnel::WorldTunnel()
	{
	}

	WorldTunnel::~WorldTunnel()
	{
	}

	void WorldTunnel::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Texture* tex = ResourceManager::Load<Texture>(L"WorldTunnels", L"..\\Resources\\Map\\WorldTunnels.bmp");
		animator->CreateAnimation(tex, L"WorldTunnel1", Vector2(2.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel2", Vector2(260.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel3", Vector2(518.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel4", Vector2(776.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel5", Vector2(2.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel6", Vector2(260.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel7", Vector2(518.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel8", Vector2(776.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);

		animator->SetAffectedCamera(false);
		animator->PlayAnimation(L"WorldTunnel1");

		BackGround::Initialize();
	}

	void WorldTunnel::Update()
	{
		BackGround::Update();
	}

	void WorldTunnel::Render(HDC hdc)
	{
		BackGround::Render(hdc);
	}
}