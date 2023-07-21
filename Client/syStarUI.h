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

		void SetAllClear()
		{
			mbAllClear = true;
			if(nullptr != mAnimator)
			mAnimator->PlayAnimation(L"StarUI", true);
		}

		bool IsAllClear() { return mbAllClear; }

	private:
		class Animator* mAnimator;
		bool mbAllClear;

	};
}

