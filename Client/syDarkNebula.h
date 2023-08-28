#pragma once
#include "syBossEnemy.h"

namespace sy
{
	enum class eDarkNebulaState
	{
		Idle,
		Move,
		RotationalMove,
		ZigzagMoveReady,
		ZigzagMove,
		StarAttack,
		SkillReady,
		FireSkill,
		IceSkill,
		SparkSkill,
		ModeChangeReady,
		ModeChange,
		Dead,
	};

	enum class eDarkNebulaMode
	{
		Fire,
		Ice,
		Spark,
		End,
	};


    class DarkNebula : public BossEnemy
    {
	public:
		DarkNebula(eAbilityType type);
		virtual ~DarkNebula();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() const { return mbDamaged; }
		virtual bool IsDeadState() const { return mState == eDarkNebulaState::Dead; }

		eDarkNebulaState GetDarkNebulaState() const { return mState; }

	private:
		void SetBossState();

	private:
		void Idle();
		void Move();
		void RotationalMove();
		void ZigzagMoveReady();
		void ZigzagMove();
		void StarAttack();
		void SkillReady();
		void FireSkill();
		void IceSkill();
		void SparkSkill();
		void ModeChangeReady();
		void ModeChange();
		void Dead();

	private:
		eDarkNebulaState			mState;
		eDarkNebulaMode				mMode;
		class Animator*				mAnimator;
		class Transform*			mTransform;
		eDirection					mDir;

		float						mStateChangeDelay;
		float						mModeChangeDelay;
		math::Vector2				mFixedPos[6];
		math::Vector2				mTargetPos;
		bool						mbDamaged; // 연속 피격 방지

		class DarkNebula_Border*	mBorder;
		class DarkNebula_Eye*		mEye;

    };
}

