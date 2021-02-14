#pragma once

#ifndef __TEXTURE_BUNDLE_H__
#define __TEXTURE_BUNDLE_H__

#include "Nalmak_Include.h"
#include "ResourceManager.h"

class NALMAK_DLL TextureBundle
{
public:
	TextureBundle(wstring _name, Vector4 _color = Vector4(1, 1, 1, 1), Vector2 _uvScale = Vector2(1, 1));
	~TextureBundle();
private:
	PDIRECT3DTEXTURE9 m_tex;
	Vector4 m_color;
	Vector2 m_uvScaling;
};

#endif // !__TEXTURE_BUNDLE_H__
