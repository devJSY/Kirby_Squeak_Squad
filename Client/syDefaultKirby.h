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
		End,
	};

	// A,D ���� 
	// S ���Ƶ��̱�, ���
	// W ���Ŵɷ� ���

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

	private:
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Turn();
		void Damage();

	private:
		eDefaultKirbyState mState;
		class Animator* mAnimator;
		class Transform* mTransform;
	};
}


