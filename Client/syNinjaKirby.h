#pragma once
#include "syKirby.h"

namespace sy
{
	enum class eNinjaKirbyState
	{
		Transformations,
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
		ThrowShuriken,
		Charge,
		Fire,
		End,
	};


	// A,D ���� 
	// S ��ų
	// W ���Ŵɷ� ���
	class NinjaKirby : public Kirby
	{
	public:
		NinjaKirby(class Player* owner);
		virtual ~NinjaKirby();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter() override;
		virtual void Exit() override;

		virtual bool IsTransformableCheck() override;
		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other)	override;
		virtual void OnCollisionExit(class Collider* other)	override;

		void SetKirbyState(eNinjaKirbyState state) { mState = state; }
		eNinjaKirbyState GetKirbyState() const { return mState; }

		void SetOnLeftStop(bool trig) { mbOnLeftStop = trig; }
		void SetOnRightStop(bool trig) { mbOnRightStop = trig; }

	private:
		void CheckPixelCollision();

	private:
		// Level Mode State
		void Level_Transformations();
		void Choice();
		void Level_Enter();
		void Level_Idle();
		void Level_Run();
		void Level_FlyUp();
		void Level_Drop();

	private:
		// Play Mode State
		void Transformations();
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
		void ThrowShuriken();
		void Charge();
		void Fire();

	private:
		eNinjaKirbyState		mState;
		class Animator*			mAnimator;
		class Transform*		mTransform;
		class Rigidbody*		mRigidBody;
		enums::eDirection		mDir;

		bool					mbOnLeftStop;	// ���� ���� �浹�� ���¿���
		bool					mbOnRightStop;	// ������ ���� �浹�� ���¿���
		bool					mbTopStop;		// ��ܿ� �浹�� ���¿���
		bool					mbOnSlope;		// ���ο� �ö�ź ���¿���

		float					mKeyReleaseTime;
		float					mKeyPressdTime;
		float					mChargeTime;
	};
}


