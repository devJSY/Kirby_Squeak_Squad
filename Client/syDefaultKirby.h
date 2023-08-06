#pragma once
#include "syKirby.h"

namespace sy
{
	enum class eDefaultKirbyState
	{
		Transformations,
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
		Inhaled,
		Inhaled_Idle,
		Inhaled_Walk,
		Inhaled_Run,
		Inhaled_Jump,
		Inhaled_Turn,
		Inhaled_Drop,
		Inhaled_Land,
		Inhaled_Damage,
		Inhaled_Down,
		Inhaled_Skill,
		End,
	};

	enum class InhaledObjectType
	{
		Monster,
		AbilityItem,
		End,
	};

	struct InhaledObjectInfo
	{
		eAbilityType			AbilityType;
		InhaledObjectType		ObjType;
	};

	// A,D ���� 
	// S ���Ƶ��̱�, ���
	// W ���Ŵɷ� ���
	class DefaultKirby : public Kirby
	{
	public:
		DefaultKirby(class Player* owner);
		virtual ~DefaultKirby();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter() override;
		virtual void Exit() override;

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other)	override;
		virtual void OnCollisionExit(class Collider* other)	override;


		void SetKirbyState(eDefaultKirbyState state) { mState = state; }
		eDefaultKirbyState GetKirbyState() { return mState; }

		void SetOnLeftStop(bool trig) { mbOnLeftStop = trig; }
		void SetOnRightStop(bool trig) { mbOnRightStop = trig; }

		void SetInhaledObjectInfo(eAbilityType ability, InhaledObjectType type)
		{
			mInhaledObjectInfo.AbilityType = ability;
			mInhaledObjectInfo.ObjType = type;
		}

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
		void Transformations();
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

		void Inhaled();
		void Inhaled_Idle();
		void Inhaled_Walk();
		void Inhaled_Run();
		void Inhaled_Jump();
		void Inhaled_Turn();
		void Inhaled_Drop();
		void Inhaled_Land();
		void Inhaled_Damage();
		void Inhaled_Down();
		void Inhaled_Skill();

	private:
		eDefaultKirbyState			mState;
		class Animator*				mAnimator;
		class Transform*			mTransform;
		class Rigidbody*			mRigidBody;
		eDirection					mDir;

		bool						mbOnLeftStop;	// ���� ���� �浹�� ���¿���
		bool						mbOnRightStop;	// ������ ���� �浹�� ���¿���
		bool						mbTopStop;		// ��ܿ� �浹�� ���¿���
		bool						mbOnSlope;		// ���ο� �ö�ź ���¿���

		class Inhale_Effect*		mInhaleEffect;
		InhaledObjectInfo			mInhaledObjectInfo;
	};
}


