#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

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
		Video,			
		LevelUI,
		Enemy,
		Player,
		Effect,
		UI,			 
		Inventory,
		Item,
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
		Normal,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Collider,
		Rigidbody,
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

	enum class eLevelType
	{
		AllClear_LevelSelect
		, LevelSelect
		, Level1_Clear
		, Level1
		, Level2
		, Level3
		, Level4
		, Level5
		, Level6_Clear
		, Level6
		, Level7
		, Level8
		, Bosses
		, None
	};
}