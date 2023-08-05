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

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) {};

		eAbilityType GetAbilityType() { return mType; }
		virtual void TakeInhaled() { mInhaled = true; }

	private:
		void CheckPixelCollision();

	private:
		eAbilityType		mType;
		class Animator*		mBubbleAnimator;
		class Animator*		mAbilityAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidbody;
		bool				mInhaled;
	};
}

