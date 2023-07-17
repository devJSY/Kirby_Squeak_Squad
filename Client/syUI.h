#pragma once
#include "syGameObject.h"

namespace sy
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	protected:
		class Animator* mAnimator;

	private:
	};
}
