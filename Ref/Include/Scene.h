#pragma once

#ifndef  __SCENE_H__
#define __SCENE_H__

#include "Nalmak_Include.h"
class NALMAK_DLL Scene
{
	friend class SceneManager;
protected:
	Scene() = default;
	virtual ~Scene() = default;
public:
	template <typename T>
	static Scene* Instantiate()
	{
		return new T;
	}
protected:
	virtual void Initialize() = 0;
};

#endif // ! __SCENE_H__
