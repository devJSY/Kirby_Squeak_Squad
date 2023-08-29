#pragma once
#include "syGameObject.h"

namespace sy
{
	enum class eInventoryItemType
	{
		AbilityItem,
		NormalItem,
		End
	};

	enum class eItemType
	{
		Bacchus,
		Omelet,
		End,
	};

	class InventoryItem : public GameObject
	{
		// Inventory에서만 접근가능
		friend class Inventory;

	private:
		InventoryItem(eAbilityType AbilityType, UINT SlotNumber);
		InventoryItem(eItemType ItemType, UINT SlotNumber);
		virtual ~InventoryItem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		eAbilityType GetAbilityType() const { return mAbilityType; }

		UINT GetSlotNumber() const { return mSlotNumber; }
		void SetSlotNumber(UINT idx) { mSlotNumber = idx; }
		Vector2 GetSlotPos() const { return mSlotPos; }

	private:	
		eInventoryItemType	mInventoryItemType;
		eAbilityType		mAbilityType;
		eItemType			mItemType;
		class Animator*		mBubbleAnimator;
		class Animator*		mItemAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidbody;
		class Collider*		mCollider;

		UINT				mSlotNumber;
		Vector2				mSlotPos;
		float				mEnterTime;
		float				mTime;
	};
}