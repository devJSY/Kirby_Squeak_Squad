#pragma once
#include "syPlayer.h"

namespace sy
{
	enum class eDefaultKirbyState
	{
		Idle,
		Walk,
		Run,
		Jump,
		Turn,
		Damage,
		Drop,
		Down,
		Inhale_1,
		Inhale_2,
		Inhale_3,
		End,
	};

	// A,D Á¡ÇÁ 
	// S »¡¾ÆµéÀÌ±â, ¹ñ±â
	// W º¯½Å´É·Â ¹ñ±â
	class DefaultKirby : public Player
	{
	public:
		DefaultKirby();
		virtual ~DefaultKirby();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetKirbyState(eDefaultKirbyState state) { mState = state; }
		eDefaultKirbyState GetKirbyState() { return mState; }

	private:
		// Level Mode State
		void Level_Idle();
		void Level_Jump();
		void Level_Turn();
		void Level_Drop();

	private:
		// Play Mode State
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Turn();
		void Damage();
		void Drop();
		void Down();
		void Inhale_1();
		void Inhale_2();
		void Inhale_3();

	private:
		eDefaultKirbyState mState;
		class Animator* mAnimator;
		class Transform* mTransform;
		class Rigidbody* mRigidBody;

		eDirection	mDir;
	};
}


