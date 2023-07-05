#pragma once
#include "syEntity.h"
#include "syGameObject.h"

namespace sy
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject()
		{
			GameObject* obj = new GameObject();
			mGameObjects.push_back(obj);		
		}

	private:
		std::vector<GameObject*> mGameObjects;
	};
}


