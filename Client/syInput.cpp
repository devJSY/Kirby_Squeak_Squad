#include "syInput.h"
#include "syApplication.h"
#include "syTime.h"

namespace sy
{
	std::vector<Input::Key> Input::mKeys = {};
	math::Vector2 Input::mMousePos = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D',
		VK_RETURN, VK_ESCAPE, 
		VK_LBUTTON, VK_RBUTTON,
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (size_t)eKeyCode::End; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPrevPressed = false;
			key.TakenPressedTime = 0.0f;
			key.Time = 0.0f;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		HWND hWnd = Application::GetHwnd();
		HWND NowHwnd = GetFocus();

		if (hWnd == NowHwnd)
		{
			for (size_t i = 0; i < (size_t)eKeyCode::End; i++)
			{
				// 각Key 경과한 시간 누적
				mKeys[i].TakenPressedTime += Time::DeltaTime();

				// 해당키가 눌려졌다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌러져 있었다.
					if (mKeys[i].bPrevPressed == true)
						mKeys[i].state = eKeyState::Pressed;							
					else
					{
						mKeys[i].state = eKeyState::Down;
						mKeys[i].Time = mKeys[i].TakenPressedTime;
						mKeys[i].TakenPressedTime = 0.0f;		// 처음 눌린경우 눌린시간 0.0f로 초기화
					}						

					mKeys[i].bPrevPressed = true;
				}
				// 해당키가 안눌러져 있다.
				else
				{
					// 이전 프레임에 눌러져 있었다
					if (mKeys[i].bPrevPressed == true)
						mKeys[i].state = eKeyState::Up;								
					else
						mKeys[i].state = eKeyState::None;					

					mKeys[i].bPrevPressed = false;
				}
			}

			POINT MousePos = {};
			// 현재 마우스 Pos 를 받아온다
			GetCursorPos(&MousePos);
			// 마우스 Pos 를 스크린 좌표에서 특정 클라이언트 좌표로 바꿔준다
			ScreenToClient(hWnd, &MousePos);
			mMousePos.x = (float)MousePos.x;
			mMousePos.y = (float)MousePos.y;
		}
		else // 현재 포커스중이 아니다
		{
			for (UINT i = 0; i < (UINT)eKeyCode::End; i++)
			{
				mKeys[i].bPrevPressed = false;

				if (mKeys[i].state == eKeyState::Down || mKeys[i].state == eKeyState::Pressed)
				{
					mKeys[i].state = eKeyState::Up;
				}
				else if (mKeys[i].state == eKeyState::Up)
				{
					mKeys[i].state = eKeyState::None;
				}
			}			
		}
	}
}
