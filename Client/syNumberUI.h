#pragma once
#include "syUI.h"

namespace sy
{
    class NumberUI : public UI
    {
	public:
		NumberUI();
		virtual ~NumberUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Animator* mAnimator;

    };
}

