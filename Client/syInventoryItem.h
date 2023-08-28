#pragma once
#include "syGameObject.h"

namespace sy
{
	class InventoryItem : public GameObject
	{
		// Inventory에서만 접근가능
		friend class Inventory;

	private:
		InventoryItem(eAbilityType type, UINT SlotNumber);
		virtual ~InventoryItem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		eAbilityType GetType() const { return mType; }

		UINT GetSlotNumber() const { return mSlotNumber; }
		void SetSlotNumber(UINT idx) { mSlotNumber = idx; }
		Vector2 GetSlotPos() const { return mSlotPos; }

	private:
		eAbilityType		mType;
		class Animator*		mBubbleAnimator;
		class Animator*		mAbilityAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidbody;
		class Collider*		mCollider;

		UINT				mSlotNumber;
		Vector2				mSlotPos;
		float				mEnterTime;
		float				mTime;
	};
}