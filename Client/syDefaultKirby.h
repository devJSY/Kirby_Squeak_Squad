#pragma once
#include "syPlayer.h"
#include "syAnimator.h"

namespace sy
{
	class DefaultKirby : public Player
	{
	public:
		DefaultKirby();
		virtual ~DefaultKirby();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAni;
	};
}


