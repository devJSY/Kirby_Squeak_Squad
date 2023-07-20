#pragma once
#include "syUI.h"

namespace sy
{
	class Player;

	class AbilityUI : public UI
	{
	public:
		AbilityUI();
		virtual ~AbilityUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetOwner(Player* owner) { mOwner = owner; }

	private:
		Player* mOwner;
		class Animator* mAnimator;
	};
}