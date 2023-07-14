#pragma once
#include "CommonInclude.h"

namespace sy
{
	enum class eKeyCode
	{
		LEFT, RIGHT, UP, DOWN,
		Q, W, E, R, T, Y, A, S, D,
		ENTER, ESC,
		MOUSE_LBTN, MOUSE_RBTN,
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

	private:
		static std::vector<Key> mKeys;
		static math::Vector2 mMousePos;
	};
}
