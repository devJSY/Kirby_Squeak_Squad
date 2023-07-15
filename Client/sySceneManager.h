#pragma once
#include "syScene.h"

namespace sy
{
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
			Scene->Initialize();

			return Scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		// Ʈ�� �ڷᱸ��
		// Key Value ������ �̷���� �ִ�
		// Key�� �����͸� �˻��ϴ� �뵵
		// Value �� ���� ������ ������
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;

	};
}
