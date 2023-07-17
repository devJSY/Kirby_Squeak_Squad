#pragma once
#include "syGameObject.h"

namespace sy
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	protected:
		class Animator* mAnimator;
		eDirection mDir;

	private:

	};
}
