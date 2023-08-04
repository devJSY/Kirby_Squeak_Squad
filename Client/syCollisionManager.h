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
			static void Update(); // Lyaer ���� �浹�������� üũ�ϴ� �Լ�
			static void Render(HDC hdc);
			static void Release();

			// Scene ����� ���� Layer�浹üũ���� �����ϴ� �Լ�
			static void Clear(); 
			// ���ڷ� �־��� Layer ���� �浹üũ�ϵ��� ���� ���ִ� �Լ�
			static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);

		private:
			// Layer ���� Object���� �浹�������� üũ�ϴ� �Լ�
			static void LayerCollision(class Scene* scene, eLayerType left, eLayerType rigth);
			// Collider ���� � �浹�������� üũ�ϴ� �Լ�
			static void ColliderCollision(Collider* left, Collider* right);
			// Collider�� ������ �浹������ üũ�ϴ� �Լ�
			static bool Intersect(Collider* left, Collider* right);

			static bool IsPointInCircle(float cx, float cy, float cr, float px, float py);

		private:
			static std::map<UINT64, bool> mCollisionMap;	// Collider ������ �浹���¸�
			static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX]; //���̾����ŭ�� ��Ʈ����� ���̾����ŭ�� �迭
	};
}
