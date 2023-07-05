#include "syInput.h"

namespace sy
{
	std::vector<Input::Key> Input::mKeys = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (size_t)eKeyCode::End; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPrevPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0; i < (size_t)eKeyCode::End; i++)
		{
			// �ش�Ű�� ��������.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ������ �־���.
				if (mKeys[i].bPrevPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

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
	}
}
