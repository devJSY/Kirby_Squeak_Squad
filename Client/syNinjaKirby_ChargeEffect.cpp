#include "syNinjaKirby_ChargeEffect.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syNinjaKirby.h"

namespace sy
{
	NinjaKirby_ChargeEffect::NinjaKirby_ChargeEffect(Player* owner)
		: Effects(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Texture* Ninja_Charge_Effect = ResourceManager::Load<Texture>(L"Ninja_Charge_Effect_Tex", L"..\\Resources\\Effect\\Ninja_Charge_Effect.bmp");
		Animator* animator = GetComponent<Animator>();
		std::vector<Vector2> Animationoffset = { Vector2(0.f, -12.f) };
		animator->CreateAnimation(Ninja_Charge_Effect, L"Ninja_Charge_Effect", Vector2(0.f, 0.f), Vector2(52.f, 50.f), Vector2(52.f, 0.f), 0.02f, 10, Animationoffset);
		animator->PlayAnimation(L"Ninja_Charge_Effect", true);
	}

	NinjaKirby_ChargeEffect::~NinjaKirby_ChargeEffect()
	{
	}

	void NinjaKirby_ChargeEffect::Initialize()
	{
		Effects::Initialize();
	}

	void NinjaKirby_ChargeEffect::Update()
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Player* player = dynamic_cast<Player*>(GetOwner());
		NinjaKirby* ninjaKirby = dynamic_cast<NinjaKirby*>(player->GetActiveKirby());
		
		if (ninjaKirby == nullptr || ninjaKirby->GetKirbyState() != eNinjaKirbyState::Charge)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void NinjaKirby_ChargeEffect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}