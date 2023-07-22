#pragma once
#include "syUI.h"

namespace sy
{
	class StarUI : public UI
	{
	public:
		StarUI();
		virtual ~StarUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Animator* mAnimator;	};
}

