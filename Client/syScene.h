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

		void AddGameObject(eLayerType type, GameObject* gameObj)
		{
			mLayers[(int)type].AddGameObject(gameObj);
		}

		void RemoveGameObject(eLayerType type, GameObject* gameObj)
		{
			mLayers[(int)type].RemoveGameObject(gameObj);
		}

		void PassGameObject(const std::wstring& name, eLayerType type, GameObject* gameObj);

		void DeleteLayer(eLayerType type);
		void DeleteAllLayer();

		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		// Scene 진입과 Scene 변경시 해야할일들을 여기서 처리
		virtual void Enter() = 0;
		virtual void Exit() = 0;

	private:
		std::vector<Layer> mLayers;
	};
}
