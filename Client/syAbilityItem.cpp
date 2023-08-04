#include "syAbilityItem.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syInventory.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syRigidbody.h"

namespace sy
{
	AbilityItem::AbilityItem(eAbilityType type)
		: mType(type)
		, mBubbleAnimator(nullptr)
		, mAbilityAnimator(nullptr)
		, mRigidbody(nullptr)
	{
	}

	AbilityItem::~AbilityItem()
	{
	}

	void AbilityItem::Initialize()
	{
		Texture* Bubble_Tex = ResourceManager::Load<Texture>(L"Bubble_Tex", L"..\\Resources\\UI\\Item_Bubble.bmp");
		Texture* Ability_UI_Tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");

		mBubbleAnimator = AddComponent<Animator>();
		mAbilityAnimator = AddComponent<Animator>();

		mBubbleAnimator->CreateAnimation(Bubble_Tex, L"BubbleAnimation", Vector2::Zero, Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.08f, 4, Vector2(0.f, 3.f));
		mBubbleAnimator->PlayAnimation(L"BubbleAnimation", true);

		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Fire_AbilityItem", Vector2(0.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Ice_AbilityItem", Vector2(15.f, 43.f), Vector2(17.f, 27.f), Vector2(17.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Cutter_AbilityItem", Vector2(32.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Tornado_AbilityItem", Vector2(47.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 1.f, 1);

		if (mType == eAbilityType::Fire)
			mAbilityAnimator->PlayAnimation(L"Fire_AbilityItem");
		else if(mType == eAbilityType::Ice)
			mAbilityAnimator->PlayAnimation(L"Ice_AbilityItem");
		else if (mType == eAbilityType::Cutter)
			mAbilityAnimator->PlayAnimation(L"Cutter_AbilityItem");
		else if (mType == eAbilityType::Tornado)
			mAbilityAnimator->PlayAnimation(L"Tornado_AbilityItem");

		Collider* col = AddComponent<Collider>();
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(16.f);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetFloat(true);

		GameObject::Initialize();
	}

	void AbilityItem::Update()
	{
		GameObject::Update();
	}

	void AbilityItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AbilityItem::OnCollisionEnter(Collider* other)
	{
		Player* plyer = dynamic_cast<Player*>(other->GetOwner());

		// �÷��̾ �ƴϸ� ����
		if (plyer == nullptr)
			return;

		// �κ��丮�� Ÿ������ // �������¶�� ����X �о����		
		Inventory* inventory = SceneManager::GetInventory();
		if (!inventory->IsFullSlot())
		{
			Destroy(this);
			inventory->AddItem(mType);
		}
	}

	void AbilityItem::OnCollisionStay(Collider* other)
	{
		// �κ��丮�� Ÿ������ // �������¶�� ����X �о����		
		Inventory* inventory = SceneManager::GetInventory();
		if (inventory->IsFullSlot())
		{
			// ��ų �� ���� ����
			Vector2 Dir = GetComponent<Transform>()->GetPosition() - other->GetOwner()->GetComponent<Transform>()->GetPosition();
			Dir.Normalize();
			Dir *= 30.f;
			mRigidbody->SetVelocity(Dir);
		}
	}

	void AbilityItem::OnCollisionExit(Collider* other)
	{
	}
}