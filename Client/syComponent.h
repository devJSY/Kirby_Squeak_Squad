#pragma once
#include "syEntity.h"

namespace sy
{
	using namespace sy::enums;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
		void SetOwner(class GameObject* owner) { mOwner = owner; }
		class GameObject* GetOwner() const { return mOwner; }

	public:
		enums::eComponentType GetCompType() const { return mType; }

	private:
		const eComponentType mType;
		class GameObject* mOwner;
	};
}