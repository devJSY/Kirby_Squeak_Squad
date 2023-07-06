#pragma once
#include "syScene.h"

namespace sy
{
	class WorldTunnelScene : public Scene
	{
	public:
		WorldTunnelScene();
		virtual ~WorldTunnelScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}


