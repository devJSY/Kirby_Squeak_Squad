#pragma once
#include "CommonInclude.h"

namespace sy
{
#define LAYER_MAX (UINT)eLayerType::End

	union COlliderID
	{
		struct
		{
			UINT left;	// 4Byte
			UINT right;	// 4Byte
		};
		UINT64 id; // 8Byte
	};

	using namespace enums;
	class CollisionManager
	{
		//public:
		//	static void Initialize();
		//	static void Update();
		//	static void Render(HDC hdc);
		//	static void Release();

		//private:
		//	static std::map<UINT64, bool> mCollisionMap;
		//	static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX]; //레이어갯수만큼의 비트요소의 레이어갯수만큼의 배열
	};
}
