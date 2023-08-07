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

// Assert() �Լ�
#include <cassert>

#pragma comment(lib, "Msimg32.lib")

// Sound 
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace sy::enums
{
	enum class eLayerType
	{
		BackGround,
		ForeGround,
		Pixel,
		Portal,
		Video,			
		AbilityItem,
		LevelUI,
		Enemy,
		Player,
		Effect,
		UI,			 
		Zoom,
		Inventory,
		InventoryItem,
		End,
	};

	enum class eAbilityType
	{
		Fire,
		Ice,
		Cutter,
		Tornado,
		Ninja,
		Hammer,
		Metal,
		Sleep,
		Spark,
		Sword,
		Throw,
		TripleStar,
		Wheel,		
		Normal,
		End,
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
		RIGHT,
		LEFT,
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

	enum class eStageState
	{
		StageExit,
		Ex,
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5,
		Boss,
	};
}