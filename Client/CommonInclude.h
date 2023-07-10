#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
//#include <gdiplus.h>
//
//#pragma comment(lib, "Gdiplus.lib")

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
		Player,
		Monster,
		Effect,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		End,
	};
}