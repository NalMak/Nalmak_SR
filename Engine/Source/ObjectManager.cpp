#include "..\Include\ObjectManager.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(ObjectManager)
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Release();
}



void ObjectManager::Initialize(_OBJECT_TAG _ObjectTag)
{
	m_gameObjectLists.assign(_ObjectTag, list<GameObject*>());
}

void ObjectManager::Update()
{
	MergeObjectList();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end();)
		{
			if (!(*iter)->IsAlive())
			{
				(*iter)->Release();
				delete *iter;
				iter = objList.erase(iter);
				continue;
			}
			if ((*iter)->m_active)
			{
				(*iter)->Update();
			}

			++iter;
		}
	}
}

void ObjectManager::LateUpdate()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->LateUpdate();
			}
		}
	}
}

void ObjectManager::PreRender()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->PreRender();
			}
		}
	}
}

void ObjectManager::PostRender()
{
	for (auto& objList : m_gameObjectLists)
	{
		for (auto& obj : objList)
		{
			if (obj->m_active)
			{
				obj->PostRender();
			}
		}
	}
}

void ObjectManager::Release()
{
	MergeObjectList();

	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			(*iter)->Release();
		}
	}
	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		objList.clear();
	}
}

void ObjectManager::ReleaseScene()
{
	MergeObjectList();
	list<GameObject*> dontDestroyNonActivedList;
	list<GameObject*> dontDestroyObjectList;


	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end();)
		{
			if ((*iter)->m_dontDestroy)
			{
				dontDestroyObjectList.emplace_back(*iter);
				iter = objList.erase(iter);
			}
			else
			{
				(*iter)->Release();
				++iter;
			}
		}
	}


	for (auto& objList : m_gameObjectLists)
	{
		for (auto iter = objList.begin(); iter != objList.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		objList.clear();
	}
	for (auto& obj : dontDestroyObjectList)
	{
		m_gameObjectLists[obj->m_tag].emplace_back(obj);
	}
}

void ObjectManager::DeleteList(_OBJECT_TAG _tag)
{
	for (auto& obj : m_gameObjectLists[_tag])
	{
		GameObject::Destroy(obj);
	}
}



void ObjectManager::AddObject(GameObject * _obj)
{
	assert("Object is nullptr" && _obj);

	

	m_newGameObjectList.emplace_back(_obj);
}

void ObjectManager::ChangeTag(_OBJECT_TAG _tag, GameObject * _obj)
{
	auto iter_begin = m_gameObjectLists[_obj->GetTag()].begin();
	for (; iter_begin != m_gameObjectLists[_obj->GetTag()].end(); ++iter_begin)
	{
		if (*iter_begin == _obj)
		{
			iter_begin = m_gameObjectLists[_obj->GetTag()].erase(iter_begin);
			break;
		}
		if (iter_begin == m_gameObjectLists[_obj->GetTag()].end())
			assert("List in Object null" && 0);
	}

	m_gameObjectLists[_tag].emplace_back(_obj);
}

const list<GameObject*>& ObjectManager::GetObjectList(_OBJECT_TAG _tag)
{
	return m_gameObjectLists[_tag];
}

GameObject * ObjectManager::Find(const wstring& _name)
{
	GameObject* object = nullptr;
	for (auto& objlist : m_gameObjectLists)
	{
		for (auto& obj : objlist)
		{
			if (obj->GetName() == _name)
			{
				object = obj;
				return object;
			}
		}
	}
	assert("Can't find object using that name!" && object);
	return object;
}

GameObject * ObjectManager::Find(_OBJECT_TAG _tag, const wstring& _name)
{
	if (m_gameObjectLists[_tag].empty())
		return nullptr;

	for (auto& obj : m_gameObjectLists[_tag])
	{
		if (obj->GetName() == _name)
		{
			return obj;
		}
	}
	return nullptr;
}

GameObject * ObjectManager::FindFirstObjectbyTag(_OBJECT_TAG _tag)
{
	if (m_gameObjectLists[_tag].empty())
		return nullptr;

	return m_gameObjectLists[_tag].front();
}

void ObjectManager::MergeObjectList()
{
	for (auto& newObj : m_newGameObjectList)
	{
		m_gameObjectLists[newObj->GetTag()].emplace_back(newObj);
	}
	m_newGameObjectList.clear();
}
