#pragma once
#include "syScene.h"

namespace sy
{
	class OpeningScene : public Scene
	{
	public:
		OpeningScene();
		virtual ~OpeningScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:

	};
}

