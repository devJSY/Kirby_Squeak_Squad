#pragma once
#include "syGameObject.h"

namespace sy
{
	class ForeGround :	public GameObject
	{
	public:
		ForeGround();
		virtual ~ForeGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}

