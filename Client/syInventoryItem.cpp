#include "syInventoryItem.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syTime.h"
#include "syInventory.h"
#include "sySceneManager.h"
#include "syApplication.h"
#include "syInput.h"

namespace sy
{
	InventoryItem::InventoryItem(eAbilityType AbilityType, UINT SlotNumber)
		: mInventoryItemType(eInventoryItemType::AbilityItem)
		, mAbilityType(AbilityType)
		, mItemType(eItemType::End)
		, mBubbleAnimator(nullptr)
		, mItemAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mSlotNumber(SlotNumber)
		, mSlotPos(Vector2::Zero)
		, mEnterTime(0.f)
		, mTime(0.f)
	{
		Texture* Bubble_Tex = ResourceManager::Load<Texture>(L"Bubble_InventoryItem_Tex", L"..\\Resources\\UI\\Item_Bubble.bmp");
		Texture* Ability_UI_Tex = ResourceManager::Load<Texture>(L"Ability_UI_InventoryItem_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");
		Texture* Items_Tex = ResourceManager::Load<Texture>(L"Items_Tex", L"..\\Resources\\Item\\Items.bmp");
		
		Bubble_Tex->SetScale(Vector2(1.3f, 1.3f));
		Ability_UI_Tex->SetScale(Vector2(1.3f, 1.3f));

		mBubbleAnimator = AddComponent<Animator>();
		mItemAnimator = AddComponent<Animator>();

		mBubbleAnimator->SetAffectedCamera(false);
		mItemAnimator->SetAffectedCamera(false);

		Vector2 Animationoffset = Vector2(0.f, 3.f);

		mBubbleAnimator->CreateAnimation(Bubble_Tex, L"BubbleAnimation", Vector2::Zero, Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.08f, 4, Animationoffset);
		mBubbleAnimator->PlayAnimation(L"BubbleAnimation", true);

		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Fire_AbilityItem", Vector2(0.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Ice_AbilityItem", Vector2(15.f, 43.f), Vector2(17.f, 27.f), Vector2(17.f, 0.f), 1.f, 1);
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Cutter_AbilityItem", Vector2(32.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Tornado_AbilityItem", Vector2(47.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 1.f, 1);
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Ninja_AbilityItem", Vector2(63.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 1.f, 1);
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Spark_AbilityItem", Vector2(105.f, 43.f), Vector2(18.f, 27.f), Vector2(18.f, 0.f), 1.f, 1);
		//mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Wheel_AbilityItem", Vector2(25.f, 125.f), Vector2(18.f, 27.f), Vector2(18.f, 0.f), 1.f, 1, Vector2(0.f, 2.f));
		mItemAnimator->CreateAnimation(Ability_UI_Tex, L"Sword_AbilityItem", Vector2(207.f, 43.f), Vector2(17.f, 27.f), Vector2(17.f, 0.f), 1.f, 1);
		
		mItemAnimator->CreateAnimation(Items_Tex, L"BacchusItem", Vector2(180.f, 170.f), Vector2(24.f, 32.f), Vector2(24.f, 0.f), 1.f, 1);
		mItemAnimator->SetBmpRGB(L"BacchusItem", 12, 230, 248);

		if (mAbilityType == eAbilityType::Fire)
			mItemAnimator->PlayAnimation(L"Fire_AbilityItem");
		else if (mAbilityType == eAbilityType::Ice)
			mItemAnimator->PlayAnimation(L"Ice_AbilityItem");
		else if (mAbilityType == eAbilityType::Cutter)
			mItemAnimator->PlayAnimation(L"Cutter_AbilityItem");
		else if (mAbilityType == eAbilityType::Tornado)
			mItemAnimator->PlayAnimation(L"Tornado_AbilityItem");
		else if (mAbilityType == eAbilityType::Ninja)
			mItemAnimator->PlayAnimation(L"Ninja_AbilityItem");
		else if (mAbilityType == eAbilityType::Spark)
			mItemAnimator->PlayAnimation(L"Spark_AbilityItem");
		//else if (mType == eAbilityType::Wheel)
		//	mAbilityAnimator->PlayAnimation(L"Wheel_AbilityItem");
		else if (mAbilityType == eAbilityType::Sword)
			mItemAnimator->PlayAnimation(L"Sword_AbilityItem");

		mCollider = AddComponent<Collider>();
		mCollider->SetAffectedCamera(false);
		mCollider->SetColliderType(eColliderType::Sphere);
		mCollider->SetRadius(20.f);

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector2(128.f, 192.f));

		if (mSlotNumber == 0)
			mSlotPos = Vector2(30.f, 270.f);
		else if(mSlotNumber == 1)
			mSlotPos = Vector2(63.f, 330.f);
		else if (mSlotNumber == 2)
			mSlotPos = Vector2(128.f, 353.f);
		else if (mSlotNumber == 3)
			mSlotPos = Vector2(190.f, 330.f);
		else if (mSlotNumber == 4)
			mSlotPos = Vector2(225.f, 270.f);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetFloat(true);
		mRigidbody->SetVelocity(Vector2(0.f, 500.f));
	}

	InventoryItem::InventoryItem(eItemType ItemType, UINT SlotNumber)
		: mInventoryItemType(eInventoryItemType::NormalItem)
		, mAbilityType(eAbilityType::End)
		, mItemType(ItemType)
		, mBubbleAnimator(nullptr)
		, mItemAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mSlotNumber(SlotNumber)
		, mSlotPos(Vector2::Zero)
		, mEnterTime(0.f)
		, mTime(0.f)
	{
		Texture* Bubble_Tex = ResourceManager::Load<Texture>(L"Bubble_InventoryItem_Tex", L"..\\Resources\\UI\\Item_Bubble.bmp");
		Texture* Items_Tex = ResourceManager::Load<Texture>(L"Items_Tex", L"..\\Resources\\Item\\Items.bmp");

		Bubble_Tex->SetScale(Vector2(1.3f, 1.3f));

		mBubbleAnimator = AddComponent<Animator>();
		mItemAnimator = AddComponent<Animator>();

		mBubbleAnimator->SetAffectedCamera(false);
		mItemAnimator->SetAffectedCamera(false);

		Vector2 Animationoffset = Vector2(0.f, 3.f);

		mBubbleAnimator->CreateAnimation(Bubble_Tex, L"BubbleAnimation", Vector2::Zero, Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.08f, 4, Animationoffset);
		mBubbleAnimator->PlayAnimation(L"BubbleAnimation", true);

		mItemAnimator->CreateAnimation(Items_Tex, L"BacchusItem", Vector2(180.f, 170.f), Vector2(24.f, 32.f), Vector2(24.f, 0.f), 1.f, 1);
		mItemAnimator->SetBmpRGB(L"BacchusItem", 12, 230, 248);

		mItemAnimator->CreateAnimation(Items_Tex, L"OmeletItem", Vector2(280.f, 170.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 1.f, 1);
		mItemAnimator->SetBmpRGB(L"OmeletItem", 12, 230, 248);

		if(mItemType == eItemType::Bacchus)
			mItemAnimator->PlayAnimation(L"BacchusItem");
		else if (mItemType == eItemType::Omelet)
			mItemAnimator->PlayAnimation(L"OmeletItem");

		mCollider = AddComponent<Collider>();
		mCollider->SetAffectedCamera(false);
		mCollider->SetColliderType(eColliderType::Sphere);
		mCollider->SetRadius(20.f);

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector2(128.f, 192.f));

		if (mSlotNumber == 0)
			mSlotPos = Vector2(30.f, 270.f);
		else if (mSlotNumber == 1)
			mSlotPos = Vector2(63.f, 330.f);
		else if (mSlotNumber == 2)
			mSlotPos = Vector2(128.f, 353.f);
		else if (mSlotNumber == 3)
			mSlotPos = Vector2(190.f, 330.f);
		else if (mSlotNumber == 4)
			mSlotPos = Vector2(225.f, 270.f);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetFloat(true);
		mRigidbody->SetVelocity(Vector2(0.f, 500.f));
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
		if (mSlotNumber == 0)
			mSlotPos = Vector2(30.f, 270.f);
		else if (mSlotNumber == 1)
			mSlotPos = Vector2(63.f, 330.f);
		else if (mSlotNumber == 2)
			mSlotPos = Vector2(128.f, 353.f);
		else if (mSlotNumber == 3)
			mSlotPos = Vector2(190.f, 330.f);
		else if (mSlotNumber == 4)
			mSlotPos = Vector2(225.f, 270.f);

		mEnterTime += Time::DeltaTime();


		// 처음먹었을때 효과
		if (mEnterTime < 1.f)
		{
			Transform* transform = GetComponent<Transform>();
			Vector2 pos = transform->GetPosition();
			if (pos.y > 384.f)
			{
				pos.y = 384.f;
				mRigidbody->SetVelocity(Vector2(0.f, -100.f));
				transform->SetPosition(pos);
				mEnterTime = 1.f;
			}
		}
		else
		{
			// mFocusItem가 아닌경우 떨어진 거리에 비례해서 이동
			Vector2 CurPos = mTransform->GetPosition();

			Vector2 Dir = mSlotPos - CurPos;
			Dir.Length();
			mRigidbody->SetVelocity(Dir);
		}


		// Focus 아이템이 있는경우에 마우스범위안에 들어온경우 Mix아이템으로 설정
		if (SceneManager::GetInventory()->IsExistFocusItem() && !SceneManager::GetInventory()->IsExistmMixItem()
			&& SceneManager::GetInventory()->GetFocusItem() != this)
		{
			Vector2 mousePos = Input::GetMousePos();

			// 화면크기 이동한 거리, 화면 비율만큼 계산
			Vector2 SlotPos = mCollider->GetPosition();
			SlotPos *= Application::GetScreenMinRatio();
			SlotPos += Application::GetScreenRenderPos();

			// 화면 비율만큼 계산
			float SlotRadius = mCollider->GetRadius();
			SlotRadius *= Application::GetScreenMinRatio();

			Vector2 distance = SlotPos - mousePos;
			float Length = distance.Length();

			// 콜라이더 범위 안에 들어왔다
			if (Length <= SlotRadius)
			{
				// 위치설정
				// 화면크기 이동한 거리, 화면 비율만큼 계산
				if(SceneManager::GetInventory()->GetFocusItem()->GetInventoryItemType() == eInventoryItemType::AbilityItem
					&& GetInventoryItemType() == eInventoryItemType::AbilityItem)
					SceneManager::GetInventory()->SetMixItem(this);
			}			
		}

		GameObject::Update();
	}

	void InventoryItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}