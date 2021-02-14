#include "RenderTarget.h"
#include <fstream>

USING(Nalmak)


RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
	Release();
}

RenderTarget::RenderTarget(UINT _width, UINT _height, D3DFORMAT _format, DWORD _color)
{
	m_color = _color;
	// D3DPOOL_DEFAULT �� ���� , D3DPOOL_MANAGED ���Ұ�
	ThrowIfFailed(D3DXCreateTexture(m_device, _width, _height, 1, D3DUSAGE_RENDERTARGET, _format, D3DPOOL_DEFAULT, &m_texture));
	//ThrowIfFailed(m_device->CreateRenderTarget(_width, _height, _format, 0, 0, TRUE, &m_captureSurface, NULL));

	ThrowIfFailed(m_texture->GetSurfaceLevel(0, &m_captureSurface));
}




void RenderTarget::Initialize(wstring _fp)
{

	string path;
	path.assign(_fp.begin(), _fp.end());

	ifstream file(path.c_str());

	string buffer;
	size_t length = 0;

	UINT width = 0;
	UINT height = 0;
	Vector4 color;
	TEXTURE_FORMAT format = TEXTURE_FORMAT::TEXTURE_FORMAT_A8R8G8B8;

	while (true)
	{
		getline(file, buffer);
		if ('#' == buffer[0] || "" == buffer)
			continue;

		// �׸� Ȯ��
		size_t firstWordEnd;
		for (firstWordEnd = 0; firstWordEnd < buffer.size(); ++firstWordEnd)
		{
			if (' ' == buffer[firstWordEnd])
				break;
		}

		string memberName = buffer.substr(0, firstWordEnd);

		// ���� " ã��
		while ('\"' != buffer[firstWordEnd])
		{
			++firstWordEnd;
		}
		++firstWordEnd;

		// 1. width
		if (strcmp(memberName.c_str(), "width") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			width = (UINT)atoi(handleName.c_str());
		}
		// 2. height
		if (strcmp(memberName.c_str(), "height") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			height = (UINT)atoi(handleName.c_str());
		}
		//vector4 "handle"   "x,x,x,x"
		if (strcmp(memberName.c_str(), "color") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// value
			Vector4 vec;
			int vecIndex = 0;
			size_t valueStart = 0;
			size_t valueEnd;
			handleNameEnd = handleName.size();

			for (valueEnd = 0; valueEnd < handleNameEnd + 1; ++valueEnd)
			{
				if (',' == handleName[valueEnd])
				{
					string subBuffer = handleName.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					++vecIndex;
					valueStart = valueEnd + 1;
				}
				else if (handleNameEnd == valueEnd)
				{
					string subBuffer = handleName.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					break;
				}
			}

			color = vec;
		}
	
#pragma endregion
		// 3. renderQueue
		if (strcmp(memberName.c_str(), "format") == 0)
		{
			// render queue value
			size_t valueEnd;
			for (valueEnd = firstWordEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string renderQueue = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			int value = atoi(renderQueue.c_str());
			format = (TEXTURE_FORMAT)value;

			break;
		}
	}

	// D3DPOOL_DEFAULT �� ���� , D3DPOOL_MANAGED ���Ұ�
	D3DFORMAT d3dformat;
    m_color = RGB((DWORD)(color.x * 255), (DWORD)(color.x * 255), (DWORD)(color.x * 255));
	switch (format)
	{
	case TEXTURE_FORMAT_A8R8G8B8:
		d3dformat = D3DFORMAT::D3DFMT_A8R8G8B8;
		break;
	case TEXTURE_FORMAT_D24S8:
		d3dformat = D3DFORMAT::D3DFMT_D24S8;
		break;
	case TEXTURE_FORMAT_A16B16G16R16:
		d3dformat = D3DFORMAT::D3DFMT_A16B16G16R16;
		break;
	case TEXTURE_FORMAT_A32B32G32R32:
		d3dformat = D3DFORMAT::D3DFMT_A32B32G32R32F;
		break;
	default:
		break;
	}
	ThrowIfFailed(D3DXCreateTexture(m_device, width, height, 1, D3DUSAGE_RENDERTARGET, d3dformat, D3DPOOL_DEFAULT, &m_texture));
	ThrowIfFailed(m_texture->GetSurfaceLevel(0, &m_captureSurface));


}

void RenderTarget::Release()
{
	SAFE_RELEASE(m_originSurface);
	SAFE_RELEASE(m_captureSurface);
	SAFE_RELEASE(m_texture);
}

void RenderTarget::StartRecord(UINT _index)
{
	m_device->GetRenderTarget(_index, &m_originSurface);
	ThrowIfFailed(m_device->SetRenderTarget(_index, m_captureSurface));
	ThrowIfFailed(m_device->Clear(0, nullptr, D3DCLEAR_TARGET, m_color, 1.f, 0));
	m_targetIndex = _index;
}

void RenderTarget::EndRecord()
{
	ThrowIfFailed(m_device->SetRenderTarget(m_targetIndex, m_originSurface));
}
