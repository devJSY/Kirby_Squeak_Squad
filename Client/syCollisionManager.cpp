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

		mCollisionMap.clear(); // Collider �浹���� �ʱ�ȭ
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = -1;
		int col = -1;

		// �׻� left�� ũ�� right�� �۵��� ����
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

		// �ش� Layer�� ��� ������Ʈ���� ���鼭 �浹�������� üũ�Ѵ� 
		for (GameObject* Left : lefts)
		{
			Collider* leftCol = Left->GetComponent<Collider>();
			if (leftCol == nullptr) // Collider�� ��������������  continue;
				continue;

			for (GameObject* Right : rights)
			{
				Collider* RightCol = Right->GetComponent<Collider>();
				if (RightCol == nullptr) // Collider�� ��������������  continue;
					continue;
				if (Left == Right) // �浹�� ��ü�� �ڱ��ڽ��̸� continue;
					continue;

				// �� Collider���� �浹���¸� Ȯ���Ѵ�.
				ColliderCollision(leftCol, RightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// �� �浹ü�� ID������ Map�� ������ ID ����
		ColliderID ID;
		ID.left = (UINT)left->GetCollisionNumber();
		ID.right = (UINT)right->GetCollisionNumber();

		// ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);

		// Ȥ�� �浹������ ���ٸ� ���� �����Ͽ� �־��ش�
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		// �浹�Լ� ȣ��
		if (Intersect(left, right))
		{
			// ó�� �浹�ϴ� ����
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
			// �浹�� �� ���������� ����
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
			// �� �浹ü���� ��ġ���̰� < Left �浹ü�� size�� ���� + Right �浹ü�� size�� ���� �̶�� �浹���̴�
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.f) + fabs(rightSize.x / 2.f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.f) + fabs(rightSize.y / 2.f))
			{
				return true;
			}
		}
		else if (leftType == eColliderType::Sphere && rightType == eColliderType::Sphere)
		{
			// �� ���� �浹 �Ǵ� (��Ÿ���)
			float distance = (float)sqrt(pow(rightPos.x - leftPos.x, 2) + pow(rightPos.y - leftPos.y, 2));
			if (distance <= leftRadius + rightRadius)
			{
				return true;
			}
		}
		else if (leftType == eColliderType::Sphere && rightType == eColliderType::Box)
		{
			// ���� Radius ��ŭ �簢���� Ȯ���ѵ� ���� ������ �簢�� �ȿ� ����ִ��� Ȯ�� 
			float Left = rightPos.x - (rightSize.x / 2.f) - leftRadius;
			float Right = rightPos.x + (rightSize.x / 2.f) + leftRadius;
			float top = rightPos.y + (rightSize.x / 2.f) + leftRadius;
			float bottom = rightPos.y - (rightSize.x / 2.f) - leftRadius;

			// ���ܻ�Ȳ �簢�� �������� ���ȿ� ������ �浹
			// �簢���� �»�� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, top)) return true;

			// �簢���� ���ϴ� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, bottom)) return true;

			// �簢���� ���� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, top)) return true;

			// �簢���� ���ϴ� ����Ʈ�� ���ȿ� �ִ��� �ľ�
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
			// ���� Radius ��ŭ �簢���� Ȯ���ѵ� ���� ������ �簢�� �ȿ� ����ִ��� Ȯ��
			float Left = leftPos.x - (leftSize.x / 2.f) - rightRadius;
			float Right = leftPos.x + (leftSize.x / 2.f) + rightRadius;
			float top = leftPos.y + (leftSize.x / 2.f) + rightRadius;
			float bottom = leftPos.y - (leftSize.x / 2.f) - rightRadius;

			// ���ܻ�Ȳ �簢�� �������� ���ȿ� ������ �浹
			// �簢���� �»�� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, top)) return true;

			// �簢���� ���ϴ� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Left, bottom)) return true;

			// �簢���� ���� ����Ʈ�� ���ȿ� �ִ��� �ľ�
			if (IsPointInCircle(leftPos.x, leftPos.y, leftRadius, Right, top)) return true;

			// �簢���� ���ϴ� ����Ʈ�� ���ȿ� �ִ��� �ľ�
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
		// x ������
		float deltaX = cx - px;

		float deltaY = cy - py;

		// ���� �߽ɰ� ������ �Ÿ�
		float length = sqrt((deltaX * deltaX) + (deltaY * deltaY));

		if (length > cr)
			return false;

		return true;
	}
}