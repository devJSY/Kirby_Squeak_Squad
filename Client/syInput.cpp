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
				// ��Key ����� �ð� ����
				mKeys[i].TakenPressedTime += Time::DeltaTime();

				// �ش�Ű�� ��������.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// ���� �����ӿ��� ������ �־���.
					if (mKeys[i].bPrevPressed == true)
						mKeys[i].state = eKeyState::Pressed;							
					else
					{
						mKeys[i].state = eKeyState::Down;
						mKeys[i].Time = mKeys[i].TakenPressedTime;
						mKeys[i].TakenPressedTime = 0.0f;		// ó�� ������� �����ð� 0.0f�� �ʱ�ȭ
					}						

					mKeys[i].bPrevPressed = true;
				}
				// �ش�Ű�� �ȴ����� �ִ�.
				else
				{
					// ���� �����ӿ� ������ �־���
					if (mKeys[i].bPrevPressed == true)
						mKeys[i].state = eKeyState::Up;								
					else
						mKeys[i].state = eKeyState::None;					

					mKeys[i].bPrevPressed = false;
				}
			}

			POINT MousePos = {};
			// ���� ���콺 Pos �� �޾ƿ´�
			GetCursorPos(&MousePos);
			// ���콺 Pos �� ��ũ�� ��ǥ���� Ư�� Ŭ���̾�Ʈ ��ǥ�� �ٲ��ش�
			ScreenToClient(hWnd, &MousePos);
			mMousePos.x = (float)MousePos.x;
			mMousePos.y = (float)MousePos.y;
		}
		else // ���� ��Ŀ������ �ƴϴ�
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
