#pragma once
#include "syUI.h"

namespace sy
{
	class LifeUI :
		public UI
	{
	public:
		LifeUI();
		virtual ~LifeUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetOwner(Player* owner) { mOwner = owner; }

	private:
		Player* mOwner;
		class SpriteRenderer* mSpriteRenderer;
		class Animator* mAnimator;			
	};
}
