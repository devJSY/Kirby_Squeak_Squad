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
		void Update_State();
		void Update_Move();
		void Update_Animation();

	private:
		eDefaultKirbyState mState;
		eDirection mDir;
	};
}


