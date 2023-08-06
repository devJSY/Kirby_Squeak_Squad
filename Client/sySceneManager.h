#pragma once
#include "syScene.h"

namespace sy
{
	class Player;
	class Inventory;
	class AbilityUI;
	class HPbarUI;
	class LifeUI;

	class SceneManager
	{
	private:
		// ��ü ���� ����
		SceneManager();
		~SceneManager() {};

	public:
		static void Release();
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		template <typename T>
		static T* CreateScene(const std::wstring& name)
		{
			T* Scene = new T();
			Scene->SetName(name);
			mScenes.insert(std::make_pair(name, Scene));
			mActiveScene = Scene;

			return Scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(const std::wstring& name);

		static Player* GetPlayer() { return mPlayer; }
		static Inventory* GetInventory() { return mInventory; }

	private:
		// Ʈ�� �ڷᱸ��
		// Key Value ������ �̷���� �ִ�
		// Key�� �����͸� �˻��ϴ� �뵵
		// Value �� ���� ������ ������
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;

		static Player* mPlayer;

		// UI ��ü�� ���ӿ� 1���� �����ϱ⶧���� SceneManager���� ����
		static Inventory* mInventory;
		static AbilityUI* mAbilityUI;
		static HPbarUI* mHPbarUI;
		static LifeUI* mLifeUI;
	};
}
