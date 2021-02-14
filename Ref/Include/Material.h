#pragma once

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "IResource.h"

class Shader;
class Texture;

BEGIN(Nalmak)
class NALMAK_DLL Material :
	public IResource
{
	friend class ResourceManager;
public:
	struct Desc
	{

	};
public:
	explicit Material();
	~Material();

private:
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

public:
	void SetShader(wstring _shaderName);
	Shader* GetShader()const { return m_shader; }
private:
	Shader* m_shader;

	char* tex;

public:
	void SetDataToShader();

	void SetBool(const string& _parameter, bool _value);
	void SetInt(const string& _parameter, int _value);
	void SetFloat(const string& _parameter, float _value);
	void SetMatrix(const string& _parameter, const Matrix& _value);
	void SetTexture(const string& _parameter, PDIRECT3DTEXTURE9 _value);
	void SetTexture(const string& _parameter, const wstring& _texName);
	void SetTexture(int _index, PDIRECT3DTEXTURE9 _value);

	void SetVector(const string& _parameter, const Vector4& _vector);
	void SetVector(const string& _parameter, const Vector2& _vector);
	void SetValue(const string& _parameter, void* _address, UINT _size);

private:
	vector<pair<string, bool>> m_boolValues;
	vector<pair<string, float>> m_floatValues;
	vector<pair<string, int>> m_intValues;
	vector<pair<string, Matrix>> m_matrixValues;
	vector<pair<string, Vector2>> m_vector2Values;
	vector<pair<string, Vector4>> m_vector4Values;
	vector<pair<string, PDIRECT3DTEXTURE9>> m_texValues;
	vector<pair<string, pair<void*, UINT>>> m_values;

private:
	_RENDER_QUEUE m_renderQueue = RENDER_QUEUE_GEOMETRY;

public:
	void SetRenderQueue(_RENDER_QUEUE _renderQueue) { m_renderQueue = _renderQueue; }
	_RENDER_QUEUE GetRenderQueue() { return m_renderQueue; }

public:
	void SetFillMode(FILL_MODE _fillMode) { m_fillMode = _fillMode; }
	void SetRenderingMode(RENDERING_MODE _renderingMode, float _alphaTest = 0) { m_renderingMode = _renderingMode; }
	void SetBledingMode(BLENDING_MODE _bledingMode) { m_blendingMode = _bledingMode; }
public:
	RENDERING_MODE GetRenderingMode() { return m_renderingMode; }
	BLENDING_MODE GetBlendingMode() { return m_blendingMode; }
	FILL_MODE GetFillMode() { return m_fillMode; }

	int GetAlphaTest() { return m_alphaTest; }
private:
	RENDERING_MODE m_renderingMode;
	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

	int m_alphaTest;
};

END
#endif // !__MATERIAL_H__
