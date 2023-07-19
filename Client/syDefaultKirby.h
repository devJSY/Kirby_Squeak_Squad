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

	private:
		eDirection DirectionUpdate();
		
		void Idle(eDirection Dir);
		void Walk(eDirection Dir);
		void Run(eDirection Dir);
		void Jump(eDirection Dir);
		void Turn(eDirection Dir);
		void Damage(eDirection Dir);

	private:
		eDefaultKirbyState mState;
	};
}


