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


	private:
		class Animator*			mAnimator;
		InventoryItem*			mSlot[5];
		InventoryItem*			mFocusItem;
		float					mFocusTime;

	};
}
