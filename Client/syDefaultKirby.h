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

		virtual void TakeHit(int DamageAmount, Vector2 HitDir) override;

		void SetKirbyState(eDefaultKirbyState state) { mState = state; }
		eDefaultKirbyState GetKirbyState() { return mState; }

		void SetLevelEnter(bool enter) { mbLevelEnter = enter; }

	private:
		void CheckPixelCollision();

	private:
		// Level Mode State
		void Choice();
		void Enter();
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
		eDefaultKirbyState	mState;
		class Animator*		mAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidBody;
		eDirection			mDir;

		bool				mbLevelEnter;	// Level Mode State 첫진입시 설정
		bool				mbOnLeftStop;	// 왼쪽 벽에 충돌한 상태여부
		bool				mbOnRightStop;	// 오른쪽 벽에 충돌한 상태여부
		bool				mbTopStop;		// 상단에 충돌한 상태여부
		bool				mbOnSlope;		// 경사로에 올라탄 상태여부
	};
}


