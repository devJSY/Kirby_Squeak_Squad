#pragma once
#include "syGameObject.h"

namespace sy
{
	class Video : public GameObject
	{
	public:
		Video();
		virtual ~Video();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetSpeed(float speed) { mSpeed = speed; }
		float GetSpeed() { return mSpeed; }

	private:
		float mSpeed;

	};
}
