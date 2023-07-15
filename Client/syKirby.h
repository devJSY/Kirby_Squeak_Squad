#pragma once
#include "syGameObject.h"

namespace sy
{
	class Kirby : public GameObject
	{
	public:
		Kirby();
		virtual ~Kirby();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}


