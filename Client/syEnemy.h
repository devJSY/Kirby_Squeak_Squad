#pragma once
#include "syGameObject.h"

namespace sy
{
	class Enemy : public GameObject
	{
	public:
		Enemy(eAbilityType type);
		virtual ~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);	

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		eAbilityType GetAbilityType() { return mAbilityType; }
		class Animator* GetAnimator() { return mAnimator; }

	private:
		class Animator* mAnimator;
		enums::eAbilityType mAbilityType;
	};
}
