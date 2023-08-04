#include "syCollisionManager.h"
#include "syScene.h"
#include "sySceneManager.h"

namespace sy
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
		Clear();
	}

	void CollisionManager::Update()
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)
				{
					LayerCollision(ActiveScene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::Release()
	{
	}

	void CollisionManager::Clear()
	{
		for (size_t i = 0; i < LAYER_MAX; i++)
		{
			mLayerMasks[i].reset();
		}

		mCollisionMap.clear(); // Collider 충돌상태 초기화
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = -1;
		int col = -1;

		// 항상 left가 크고 right가 작도록 설정
		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		mLayerMasks[row][col] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType rigth)
	{
		// finds left layer objects
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		// finds right layer Objects
		Layer& rightLayer = scene->GetLayer(rigth);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// 해당 Layer의 모든 오브젝트들을 돌면서 충돌상태인지 체크한다 
		for (GameObject* Left : lefts)
		{
			Collider* leftCol = Left->GetComponent<Collider>();
			if (leftCol == nullptr) // Collider가 존재하지않으면  continue;
				continue;

			for (GameObject* Right : rights)
			{
				Collider* RightCol = Right->GetComponent<Collider>();
				if (RightCol == nullptr) // Collider가 존재하지않으면  continue;
					continue;
				if (Left == Right) // 충돌한 객체가 자기자신이면 continue;
					continue;

				// 각 Collider끼리 충돌상태를 확인한다.
				ColliderCollision(leftCol, RightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체의 ID값으로 Map에 저장할 ID 생성
		ColliderID ID;
		ID.left = (UINT)left->GetCollisionNumber();
		ID.right = (UINT)right->GetCollisionNumber();

		// 이전 충돌체의 정보를 가져와서 확인한다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);

		// 혹시 충돌정보가 없다면 새로 생성하여 넣어준다
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		// 충돌함수 호출
		if (Intersect(left, right))
		{
			// 처음 충돌하는 상태
			if (iter->second == false)
			{
				left->OncollisionEnter(right);
				right->OncollisionEnter(left);
				iter->second = true;
			}
			else
			{
				left->OncollisionStay(right);
				right->OncollisionStay(left);
			}
		}
		else
		{
			// 충돌을 막 빠져나가는 상태
			if (iter->second == true)
			{
				left->OncollisionExit(right);
				right->OncollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPosition();
		Vector2 rightPos = right->GetPosition();

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		eColliderType leftType = left->GetColliderType();
		eColliderType rightType = right->GetColliderType();

		float leftRadius = left->GetRadius();
		float rightRadius = right->GetRadius();

		if (leftType == eColliderType::Box && rightType == eColliderType::Box)
		{
			// 두 충돌체간의 위치차이값 < Left 충돌체의 size의 절반 + Right 충돌체의 size의 절반 이라면 충돌중이다
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.f) + fabs(rightSize.x / 2.f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.f) + fabs(rightSize.y / 2.f))
			{
				return true;
			}
		}
		else if (leftType == eColliderType::Sphere && rightType == eColliderType::Sphere)
		{
			// 두 원의 충돌 판단 (피타고라스)
			float distance = (float)sqrt(pow(rightPos.x - leftPos.x, 2) + pow(rightPos.y - leftPos.y, 2));
			if (distance <= leftRadius + rightRadius)
			{
				return true;
			}
		}
		else if (leftType == eColliderType::Sphere && rightType == eColliderType::Box)
		{
			// 원의 Radius 만큼 사각형을 확장한뒤 원의 중점이 사각형 안에 들어있는지 확인 
			float Left = rightPos.x - (rightSize.x / 2.f) - leftRadius;
			float Right = rightPos.x + (rightSize.x / 2.f) + leftRadius;
			float top = rightPos.y + (rightSize.x / 2.f) + leftRadius;
			float bottom = rightPos.y - (rightSize.x / 2.f) - leftRadius;

			// 예외상황 사각형 꼭지점이 원안에 들어오면 충돌
			// 사각형의 좌상단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, top)) return true;

			// 사각형의 좌하단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, bottom)) return true;

			// 사각형의 우상단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, top)) return true;

			// 사각형의 우하단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, bottom)) return true;


			if (Left < leftPos.x
				&& leftPos.x < Right
				&& top > leftPos.y
				&& leftPos.y > bottom)
			{
				return true;
			}
		}
		else if (leftType == eColliderType::Box && rightType == eColliderType::Sphere)
		{
			// 원의 Radius 만큼 사각형을 확장한뒤 원의 중점이 사각형 안에 들어있는지 확인
			float Left = leftPos.x - (leftSize.x / 2.f) - rightRadius;
			float Right = leftPos.x + (leftSize.x / 2.f) + rightRadius;
			float top = leftPos.y + (leftSize.x / 2.f) + rightRadius;
			float bottom = leftPos.y - (leftSize.x / 2.f) - rightRadius;

			// 예외상황 사각형 꼭지점이 원안에 들어오면 충돌
			// 사각형의 좌상단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, top)) return true;

			// 사각형의 좌하단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, bottom)) return true;

			// 사각형의 우상단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, top)) return true;

			// 사각형의 우하단 포인트가 원안에 있는지 파악
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, bottom)) return true;

			if (Left < rightPos.x
				&& rightPos.x < Right
				&& top > rightPos.y
				&& rightPos.y > bottom)
			{
				return true;
			}
		}

		return false;
	}

	bool CollisionManager::IsPointInCircle(float cx, float cy, float cr, float px, float py)
	{
		// x 변위량
		float deltaX = cx - px;

		float deltaY = cy - py;

		// 원의 중심과 점과의 거리
		float length = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		if (length > cr)
			return false;

		return true;
	}
}