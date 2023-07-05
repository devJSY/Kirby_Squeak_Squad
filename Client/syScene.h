#pragma once
#include "syEntity.h"
#include "syLayer.h"

namespace sy
{
	using namespace sy::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		std::vector<Layer> mLayers;
	};
}
