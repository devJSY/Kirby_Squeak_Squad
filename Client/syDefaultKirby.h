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

	// A,D Á¡ÇÁ 
	// S »¡¾ÆµéÀÌ±â, ¹ñ±â
	// W º¯½Å´É·Â ¹ñ±â

	class DefaultKirby : public Player
	{
	public:
		DefaultKirby();
		virtual ~DefaultKirby();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		void Idle();
		void Walk();
		void Run();
		void Jump();
		void Turn();
		void Damage();

	private:
		eDefaultKirbyState mState;
	};
}


