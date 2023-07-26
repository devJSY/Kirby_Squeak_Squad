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
		Choice,
		Enter,
		Fly_Start,
		Fly_End,
		Fly_Down,
		Fly_Up,
		InHaled,
		InHaled_Idle,
		InHaled_Walk,
		InHaled_Run,
		InHaled_Jump,
		InHaled_Turn,
		InHaled_Drop,
		InHaled_Land,
		InHaled_Damage,
		InHaled_Down,
		InHaled_Skill,
		End,
	};

	// A,D 점프 
	// S 빨아들이기, 뱉기
	// W 변신능력 뱉기
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

		void SetLevelEnter(bool enter) { mbLevelEnter = enter; }

	private:
		// Level Mode State
		void Choice();
		void Enter();
		void Level_Idle();
		void Level_FlyUp();
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
		void Fly_Start();
		void Fly_End();
		void Fly_Down();
		void Fly_Up();

		void InHaled();
		void InHaled_Idle();
		void InHaled_Walk();
		void InHaled_Run();
		void InHaled_Jump();
		void InHaled_Turn();
		void InHaled_Drop();
		void InHaled_Land();
		void InHaled_Damage();
		void InHaled_Down();
		void InHaled_Skill();

	private:
		eDefaultKirbyState	mState;
		class Animator*		mAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidBody;
		eDirection			mDir;

		bool				mbLevelEnter; // Level Mode State 첫진입시 설정
	};
}


