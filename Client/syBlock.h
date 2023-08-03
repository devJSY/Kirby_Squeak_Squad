#pragma once
#include "syGameObject.h"

namespace sy
{
	class Block : public GameObject
	{
	public:
		Block();
		virtual ~Block();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Animator* mAnimator;
	};
}
