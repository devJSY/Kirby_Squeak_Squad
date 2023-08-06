#pragma once
#include "syPlayer.h"

namespace sy
{
	enum class eIceKirbyState
	{
		Choice,
		Enter,
		Idle,
		Walk,
		Run,
		Skill,
		Down,
		Jump,
		Turn,
		Drop,
		Fly_Start,
		Fly_End,
		Fly_Down,
		Fly_Up,
		End,
	};


	// A,D 점프 
	// S 스킬
	// W 변신능력 뱉기
	class IceKirby : public Player
	{
	public:
		IceKirby();
		virtual ~IceKirby();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

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
		void Skill();
		void Down();
		void Jump();
		void Turn();
		void Drop();
		void Fly_Start();
		void Fly_End();
		void Fly_Down();
		void Fly_Up();

	private:
		eIceKirbyState		mState;
		class Animator*		mAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidBody;
		eDirection			mDir;

		bool				mbOnLeftStop;	// 왼쪽 벽에 충돌한 상태여부
		bool				mbOnRightStop;	// 오른쪽 벽에 충돌한 상태여부
		bool				mbTopStop;		// 상단에 충돌한 상태여부
		bool				mbOnSlope;		// 경사로에 올라탄 상태여부
	};
}


