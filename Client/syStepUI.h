#pragma once
#include "syUI.h"

namespace sy
{
	class StepUI : public UI
	{
	public:
		StepUI();
		virtual ~StepUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Animator* mAnimator;

	};
}
