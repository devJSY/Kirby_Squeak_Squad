#pragma once
#include "syGameObject.h"
#include "syInventoryItem.h"

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

		void AddItem(eAbilityType AbilityType);
		void AddItem(eItemType ItemType);
		void AddMixItem();
		void SetMixItem(InventoryItem* item) { mMixItem = item; }
		bool IsFullSlot() const
		{
			for (auto iter : mSlot)
			{
				if (iter == nullptr)
					return false;
			}
			return true;
		}

		InventoryItem* GetItem(UINT idx) const { return mSlot[idx]; }
		bool IsExistFocusItem() const { return mFocusItem != nullptr; }
		bool IsExistmMixItem() const { return mMixItem != nullptr; }

		InventoryItem* GetFocusItem() const { return mFocusItem; }

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
