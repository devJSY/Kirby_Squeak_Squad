#pragma once
#include "syGameObject.h"

namespace sy
{
	class AbilityItem : public GameObject
	{
	public:
		AbilityItem(eAbilityType type);
		virtual ~AbilityItem();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		eAbilityType		mType;
		class Animator*		mBubbleAnimator;
		class Animator*		mAbilityAnimator;
	};
}

