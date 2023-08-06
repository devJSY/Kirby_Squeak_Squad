#pragma once
#include "syKirby.h"

namespace sy
{
	enum class eIceKirbyState
	{
		Choice,
		Enter,
		Idle,
		Walk,
		Run,
		Jump,
		Turn,
		Drop,
		Down,
		Fly_Start,
		Fly_End,
		Fly_Down,
		Fly_Up,
		Skill,
		End,
	};


	// A,D ���� 
	// S ��ų
	// W ���Ŵɷ� ���
	class IceKirby : public Kirby
	{
	public:
		IceKirby(class Player* owner);
		virtual ~IceKirby();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter() override;
		virtual void Exit() override;

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other)	override;
		virtual void OnCollisionExit(class Collider* other)	override;

		void SetKirbyState(eIceKirbyState state) { mState = state; }
		eIceKirbyState GetKirbyState() { return mState; }

		void SetOnLeftStop(bool trig) { mbOnLeftStop = trig; }
		void SetOnRightStop(bool trig) { mbOnRightStop = trig; }

	private:
		void CheckPixelCollision();

	private:
		// Level Mode State
		void Choice();
		void Level_Enter();
		void Level_Idle();
		void Level_Run();
		void Level_FlyUp();
		void Level_Drop();

	private:
		// Play Mode State
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Turn();
		void Drop();
		void Down();
		void Fly_Start();
		void Fly_End();
		void Fly_Down();
		void Fly_Up();
		void Skill();

	private:
		eIceKirbyState		mState;
		class Animator*		mAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidBody;
		eDirection			mDir;

		bool				mbOnLeftStop;	// ���� ���� �浹�� ���¿���
		bool				mbOnRightStop;	// ������ ���� �浹�� ���¿���
		bool				mbTopStop;		// ��ܿ� �浹�� ���¿���
		bool				mbOnSlope;		// ���ο� �ö�ź ���¿���
	};
}


