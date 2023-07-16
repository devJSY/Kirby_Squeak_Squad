#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>

#include "framework.h"
#include "syMath.h"

// Assert() ÇÔ¼ö
#include <cassert>

#pragma comment(lib, "Msimg32.lib")

namespace sy::enums
{
	enum class eLayerType
	{
		BackGround,
		ForeGround,
		Inventory,
		Video,		
		Enemy,
		Player,
		Effect,
		Item,
		UI,
		End,
	};

	enum class eAbilityType
	{
		Cutter,
		Fire,
		Hammer,
		Ice,
		Metal,
		Ninja,
		Sleep,
		Spark,
		Sword,
		Throw,
		Tornado,
		TripleStar,
		Wheel,		
		None,
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

	enum class eDirection
	{
		RIGHT = 0,
		LEFT = 1,
	};
}