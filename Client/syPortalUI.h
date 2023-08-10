#pragma once
#include "syUI.h"

namespace sy
{
	class PortalUI : public UI
	{
	public:
		PortalUI();
		virtual ~PortalUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionStay(class Collider* other) override;

	private:
		class Animator* mAnimator;
		bool			mbSceneChange;
	};
}