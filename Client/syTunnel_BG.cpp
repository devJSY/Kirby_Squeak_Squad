#include "syTunnel_BG.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	Tunnel_BG::Tunnel_BG()
	{
	}

	Tunnel_BG::~Tunnel_BG()
	{
	}

	void Tunnel_BG::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		Texture* tex = ResourceManager::Load<Texture>(L"Tunnels_Tex", L"..\\Resources\\Map\\Tunnels.bmp");
		animator->CreateAnimation(tex, L"Tunnel_1", Vector2(2.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_2", Vector2(260.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_3", Vector2(518.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_4", Vector2(776.f, 2.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_5", Vector2(2.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_6", Vector2(260.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_7", Vector2(518.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);
		animator->CreateAnimation(tex, L"Tunnel_8", Vector2(776.f, 202.f), Vector2(256.f, 200.f), Vector2(256.f, 0.f), 1.f, 1);

		animator->SetAffectedCamera(false);
		//animator->PlayAnimation(L"Tunnel_1");

		BackGround::Initialize();
	}

	void Tunnel_BG::Update()
	{
		BackGround::Update();
	}

	void Tunnel_BG::Render(HDC hdc)
	{
		BackGround::Render(hdc);
	}
}