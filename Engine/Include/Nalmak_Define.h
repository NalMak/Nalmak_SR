#pragma once
#ifndef __NALMAK_DEFINE_H__
#define __NALMAK_DEFINE_H__

#ifdef NALMAK_ENGINE
#define  NALMAK_DLL _declspec(dllexport)
#else
#define NALMAK_DLL _declspec(dllexport)
#endif // NALMAK_ENGINE



const float EPSILON = 0.0001f;

#define Deg2Rad  0.01745329251f
#define Rad2Deg  57.2957795131f
#define PI  3.14159265f
#define PI_DIV2  1.57079632679f

#define BEGIN(name) //namespace name {
#define END //}
#define USING(name) //using namespace name;



#ifdef NALMAK_ENGINE
#define dTime TimeManager::GetInstance()->GetdeltaTime()
#else
#define dTime g_time->GetdeltaTime()
#endif // NALMAK_ENGINE


#define DECLARE_SINGLETON(T)						\
private:											\
	T(const T&) = delete;							\
	T& operator=(const T&) = delete;				\
public:												\
	static T* GetInstance();						\
	static void DestroyInstance();					\
private:											\
	static T* m_instance;							


#define IMPLEMENT_SINGLETON(T)						\
T* T::m_instance = nullptr;							\
T* T::GetInstance()									\
{													\
	if(!m_instance)									\
	{												\
		m_instance = new T();						\
	};												\
	return m_instance;								\
}													\
void T::DestroyInstance()							\
{													\
	if (m_instance)									\
	{												\
		delete m_instance;							\
		m_instance = nullptr;						\
	}												\
}


#define COLOR_RGB(r,g,b) RGB((BYTE)(r * 255),(BYTE)(g * 255),(BYTE)(b * 255))


#define SAFE_DELETE(p) if(p){ delete p; p = nullptr; }
#define SAFE_DELETE_ARR(p) if(p){ delete[]p; p = nullptr; }		
#define SAFE_RELEASE(p) if(p){ p->Release(); p = nullptr; }


#define RENDER_QUEUE_BACKGROUND 1000
#define RENDER_QUEUE_GEOMETRY 2000
#define RENDER_QUEUE_TRANSPARENT 3000
#define RENDER_QUEUE_OVERLAY 4000


#endif