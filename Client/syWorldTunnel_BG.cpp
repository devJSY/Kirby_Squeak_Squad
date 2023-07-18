#include "syWorldTunnel_BG.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	WorldTunnel_BG::WorldTunnel_BG()
	{
	}

	WorldTunnel_BG::~WorldTunnel_BG()
	{
	}

	void WorldTunnel_BG::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Texture* tex = ResourceManager::Load<Texture>(L"WorldTunnels", L"..\\Resources\\Map\\WorldTunnels.bmp");
		animator->CreateAnimation(tex, L"WorldTunnel_1", Vector2(2.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_2", Vector2(260.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_3", Vector2(518.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_4", Vector2(776.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_5", Vector2(2.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_6", Vector2(260.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_7", Vector2(518.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"WorldTunnel_8", Vector2(776.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);

		animator->SetAffectedCamera(false);
		animator->PlayAnimation(L"WorldTunnel_1");

		BackGround::Initialize();
	}

	void WorldTunnel_BG::Update()
	{
		BackGround::Update();
	}

	void WorldTunnel_BG::Render(HDC hdc)
	{
		BackGround::Render(hdc);
	}
}