#include "syDash_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syGameObject.h"
#include "syTransform.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syIceKirby.h"

namespace sy
{
	Dash_Effect::Dash_Effect(Player* owner)
		: Effects(owner)
		, mAnimator(nullptr)
	{
		Texture* Dash_Effect_Left_tex = ResourceManager::Load<Texture>(L"Dash_Effect_Left", L"..\\Resources\\Effect\\Dash_Effect_Left.bmp");
		Texture* Dash_Effect_Right_tex = ResourceManager::Load<Texture>(L"Dash_Effect_Right", L"..\\Resources\\Effect\\Dash_Effect_Right.bmp");

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(Dash_Effect_Left_tex, L"Dash_Effect_Left", Vector2(0.f, 0.f), Vector2(57.f, 28.f), Vector2(57.f, 0.f), 0.03f, 19);
		mAnimator->CreateAnimation(Dash_Effect_Right_tex, L"Dash_Effect_Right", Vector2(1026.f, 0.f), Vector2(57.f, 28.f), Vector2(-57.f, 0.f), 0.03f, 19);
		

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
		{
			mAnimator->PlayAnimation(L"Dash_Effect_Right", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"Dash_Effect_Left", false);
		}			
	}

	Dash_Effect::~Dash_Effect()
	{
	}

	void Dash_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Dash_Effect::Update()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 vec = player->GetComponent<Transform>()->GetPosition();
			vec.x -= 20.f;
			tr->SetPosition(vec);
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 vec = player->GetComponent<Transform>()->GetPosition();
			vec.x += 20.f;
			tr->SetPosition(vec);
		}
	

		if (player->GetAbilityType() == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
			// Run 상태가 아니거나 애니메이션이 끝나면 삭제
			if (mAnimator->IsActiveAnimationComplete()
				|| !(defaultKirby->GetKirbyState() == eDefaultKirbyState::Run || defaultKirby->GetKirbyState() == eDefaultKirbyState::Inhaled_Run))
			{
				Destroy(this);
			}
		}
		else if (player->GetAbilityType() == eAbilityType::Fire)
		{

		}
		else if (player->GetAbilityType() == eAbilityType::Ice)
		{
			IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());
			// Run 상태가 아니거나 애니메이션이 끝나면 삭제
			if (mAnimator->IsActiveAnimationComplete()
				|| !(iceKirby->GetKirbyState() == eIceKirbyState::Run))
			{
				Destroy(this);
			}
		}		


		Effects::Update();
	}

	void Dash_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}