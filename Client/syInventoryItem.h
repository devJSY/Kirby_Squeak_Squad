#pragma once
#include "syGameObject.h"

namespace sy
{
	class InventoryItem : public GameObject
	{
	public:
		InventoryItem(eAbilityType type, UINT SlotNumber);
		virtual ~InventoryItem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		eAbilityType		mType;
		class Animator*		mBubbleAnimator;
		class Animator*		mAbilityAnimator;
		class Transform*	mTransform;
		UINT				mSlotNumber;

	};
}