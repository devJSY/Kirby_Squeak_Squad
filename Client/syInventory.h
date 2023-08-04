#pragma once
#include "syGameObject.h"

namespace sy
{
	class Inventory : public GameObject
	{
	public:
		Inventory();
		virtual ~Inventory();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void AddItem(eAbilityType type);

	private:
		class Animator*			mAnimator;
		class InventoryItem*	mSlot[5];

	};
}
