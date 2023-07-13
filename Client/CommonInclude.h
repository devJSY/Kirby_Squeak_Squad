#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>

#include "framework.h"
#include "syMath.h"

// Assert() �Լ�
#include <cassert>

#pragma comment(lib, "Msimg32.lib")

namespace sy::enums
{
	enum class eLayerType
	{
		BackGround,
		Stage,
		Inventory,
		Player,
		Monster,
		Effect,
		Item,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		End,
	};

	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};
}