#pragma once
#include "CommonInclude.h"

namespace sy
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
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
	};
}
