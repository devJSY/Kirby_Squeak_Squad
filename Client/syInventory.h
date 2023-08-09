#pragma once
#include "syGameObject.h"

namespace sy
{
	class InventoryItem;

	class Inventory : public GameObject
	{
	public:
		Inventory();
		virtual ~Inventory();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void AddItem(eAbilityType type);
		void AddMixItem();
		void SetMixItem(InventoryItem* item) { mMixItem = item; }
		bool IsFullSlot()
		{
			for (auto iter : mSlot)
			{
				if (iter == nullptr)
					return false;
			}
			return true;
		}

		InventoryItem* GetItem(UINT idx) { return mSlot[idx]; }
		bool IsExistFocusItem() { return mFocusItem != nullptr; }
		bool IsExistmMixItem() { return mMixItem != nullptr; }

		InventoryItem* GetFocusItem() { return mFocusItem; }

	private:
		class Animator*					mAnimator;
		InventoryItem*					mSlot[5];
		InventoryItem*					mFocusItem;
		float							mFocusTime;
		InventoryItem*					mMixItem;
		float							mAngle;
		std::vector<class MixItem*>		mMixItems;

	};
}
