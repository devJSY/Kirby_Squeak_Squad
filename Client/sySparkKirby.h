#pragma once
#include "syKirby.h"

namespace sy
{
	enum class eSparkKirbyState
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
		Skill,
		End,
	};

	// A,D ���� 
	// S ��ų
	// W ���Ŵɷ� ���
	class SparkKirby : public Kirby
	{
	public:
		SparkKirby(class Player* owner);
		virtual ~SparkKirby();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter() override;
		virtual void Exit() override;

		virtual bool IsTransformableCheck() override;
		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other)	override;
		virtual void OnCollisionExit(class Collider* other)	override;

		void SetKirbyState(eSparkKirbyState state) { mState = state; }
		eSparkKirbyState GetKirbyState() const { return mState; }

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
		void Skill();

	private:
		eSparkKirbyState		mState;
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

		class SparkKirby_Skill* mSkill;
	};
}


