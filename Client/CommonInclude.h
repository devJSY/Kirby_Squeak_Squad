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