#include "syInventoryItem.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syRigidbody.h"

namespace sy
{
	InventoryItem::InventoryItem(eAbilityType type, UINT SlotNumber)
		: mType(type)
		, mBubbleAnimator(nullptr)
		, mAbilityAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mSlotNumber(SlotNumber)
	{
		Texture* Bubble_Tex = ResourceManager::Load<Texture>(L"Bubble_Tex", L"..\\Resources\\UI\\Item_Bubble.bmp");
		Texture* Ability_UI_Tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");

		mBubbleAnimator = AddComponent<Animator>();
		mAbilityAnimator = AddComponent<Animator>();

		mBubbleAnimator->SetAffectedCamera(false);
		mAbilityAnimator->SetAffectedCamera(false);

		mBubbleAnimator->CreateAnimation(Bubble_Tex, L"BubbleAnimation", Vector2::Zero, Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.08f, 4, Vector2(0.f, 3.f));
		mBubbleAnimator->PlayAnimation(L"BubbleAnimation", true);

		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Fire_AbilityItem", Vector2(0.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Ice_AbilityItem", Vector2(15.f, 43.f), Vector2(17.f, 27.f), Vector2(17.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Cutter_AbilityItem", Vector2(32.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Tornado_AbilityItem", Vector2(47.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 1.f, 1);

		if (mType == eAbilityType::Fire)
			mAbilityAnimator->PlayAnimation(L"Fire_AbilityItem");
		else if (mType == eAbilityType::Ice)
			mAbilityAnimator->PlayAnimation(L"Ice_AbilityItem");
		else if (mType == eAbilityType::Cutter)
			mAbilityAnimator->PlayAnimation(L"Cutter_AbilityItem");
		else if (mType == eAbilityType::Tornado)
			mAbilityAnimator->PlayAnimation(L"Tornado_AbilityItem");

		Collider* col = AddComponent<Collider>();
		col->SetAffectedCamera(false);
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(20.f);

		mTransform = GetComponent<Transform>();

		if (mSlotNumber == 0)
			mTransform->SetPosition(Vector2(30.f, 270.f));
		else if(mSlotNumber == 1)
			mTransform->SetPosition(Vector2(63.f, 330.f));
		else if (mSlotNumber == 2)
			mTransform->SetPosition(Vector2(128.f, 353.f));
		else if (mSlotNumber == 3)
			mTransform->SetPosition(Vector2(190.f, 330.f));
		else if (mSlotNumber == 4)
			mTransform->SetPosition(Vector2(225.f, 270.f));

		mTransform->SetScale(Vector2(1.3f, 1.3f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetFloat(true);
	}

	InventoryItem::~InventoryItem()
	{
	}

	void InventoryItem::Initialize()
	{
		GameObject::Initialize();
	}

	void InventoryItem::Update()
	{
		// mFocusItem가 아닌경우 떨어진 거리에 비례해서 이동
		Vector2 CurPos = mTransform->GetPosition();
		Vector2 SlotPos = Vector2::Zero;
		
		if (mSlotNumber == 0)
			SlotPos = Vector2(30.f, 270.f);
		else if (mSlotNumber == 1)
			SlotPos = Vector2(63.f, 330.f);
		else if (mSlotNumber == 2)
			SlotPos = Vector2(128.f, 353.f);
		else if (mSlotNumber == 3)
			SlotPos = Vector2(190.f, 330.f);
		else if (mSlotNumber == 4)
			SlotPos = Vector2(225.f, 270.f);

		Vector2 Dir = SlotPos - CurPos;
		Dir.Length();

		mRigidbody->SetVelocity(Dir);

		GameObject::Update();
	}

	void InventoryItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}