#pragma once
#include "CommonInclude.h"

namespace sy
{
	enum class eKeyCode
	{
		LEFT, RIGHT, UP, DOWN,
		W,A,S,D,
		ENTER, ESC,
		MOUSE_LBTN, MOUSE_RBTN, MOUSE_MBTN,
		T, C, R, M,
		One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		End,
	};

	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool bPrevPressed;
			float Time;				// 이전 TakenPressedTime 계산한 값
			float TakenPressedTime;
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code) 
		{
			return mKeys[(int)code].state == eKeyState::Down;
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Up;
		}
		__forceinline static bool GetKeyPressed(eKeyCode code)
		{
			return mKeys[(int)code].state == eKeyState::Pressed;
		}

		static bool IsDoubleKeyPressed(eKeyCode code)
		{
			// 0.2초 안에 다시눌린경우
			if (mKeys[(int)code].Time < 0.2f && Input::GetKeyDown(code))
				return true;		

			return false;
		}

		static math::Vector2 GetMousePos() { return mMousePos; }

	private:
		static std::vector<Key> mKeys;
		static math::Vector2 mMousePos;
	};
}
