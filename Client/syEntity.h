#pragma once
#include "CommonInclude.h"

namespace sy
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;
	};
}

