#pragma once
#include "syUI.h"

namespace sy
{
    class DotUI : public UI
    {
	public:
		DotUI();
		virtual ~DotUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetDelayTime(float time) { mDelayTime = time;  }
		void SetActiveTrig(bool trig) { mActiveTrig = trig; }

	private:
		class Animator* mAnimator;
		float			mDelayTime;
		bool			mActiveTrig;
    };
}

