#pragma once
#include "CommonInclude.h"
#include "syCollider.h"

namespace sy
{
#define LAYER_MAX (UINT)eLayerType::End

	union ColliderID
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
		public:
			static void Initialize();
			static void Update(); // Lyaer 끼리 충돌상태인지 체크하는 함수
			static void Render(HDC hdc);
			static void Release();

			// Scene 변경시 기존 Layer충돌체크설정 해제하는 함수
			static void Clear(); 
			// 인자로 넣어준 Layer 끼리 충돌체크하도록 설정 해주는 함수
			static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);

		private:
			// Layer 내부 Object끼리 충돌상태인지 체크하는 함수
			static void LayerCollision(class Scene* scene, eLayerType left, eLayerType rigth);
			// Collider 끼리 어떤 충돌상태인지 체크하는 함수
			static void ColliderCollision(Collider* left, Collider* right);
			// Collider가 실제로 충돌중인지 체크하는 함수
			static bool Intersect(Collider* left, Collider* right);

			static bool IsPointInCircle(float cx, float cy, float cr, float px, float py);

		private:
			static std::map<UINT64, bool> mCollisionMap;	// Collider 끼리의 충돌상태맵
			static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX]; //레이어갯수만큼의 비트요소의 레이어갯수만큼의 배열
	};
}
