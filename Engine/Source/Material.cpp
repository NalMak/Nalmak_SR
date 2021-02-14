#include "Material.h"
#include "ResourceManager.h"
#include "Shader.h"

#include <fstream>

USING(Nalmak)


Material::Material()
{
	/*SetShader(L"default");
	m_renderQueue = 0;
	m_renderingMode = RENDERING_MODE_OPAQUE;
	m_blendingMode = BLENDING_MODE_DEFAULT;
	m_fillMode = FILL_MODE_SOLID;
	m_alphaTest = 0;*/
}


Material::~Material()
{
	Release();
}

void Material::Initialize(wstring _fp)
{
	// _fp ���� ��ΰ� ������
	// �տ� ��� �� ���� ���� �̸��� ����
	// Ȯ���ڵ� ���� �װ� Ű���� �� -> �̰� AddResource key������ ����ϸ� ��
	// �Ľ��� �ϸ� �˴ϴ�?
	//{
	//	Material particle;
	//	particle.SetShader(L"particle");
	//	particle.SetBledingMode(BLENDING_MODE_ADDITIVE);
	//	particle.SetTexture("g_mainTex", L"particleDefault");
	//	particle.SetRenderingMode(RENDERING_MODE_TRANSPARENT);
	//	particle.SetRenderQueue(RENDER_QUEUE_TRANSPARENT);

	//	//ResourceManager::GetInstance()->AddResource(L"particle", particle);
	//}

	string path;
	path.assign(_fp.begin(), _fp.end());

	ifstream file(path.c_str());

	string buffer;
	size_t length = 0;

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

		// 1. shader
		if (strcmp(memberName.c_str(), "shader") == 0)
		{
			// shader name
			size_t valueEnd;
			for (valueEnd = firstWordEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string shaderName = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			wstring name;
			name.assign(shaderName.begin(), shaderName.end());
			SetShader(name);
		}
		// 2. texture
		if (strcmp(memberName.c_str(), "texture") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// texture name
			size_t nameEnd;
			for (nameEnd = handleNameEnd; nameEnd < buffer.size(); ++nameEnd)
			{
				if ('\"' == buffer[nameEnd])
					break;
			}

			string textureName = buffer.substr(handleNameEnd, nameEnd - handleNameEnd);

			wstring name;
			name.assign(textureName.begin(), textureName.end());

			SetTexture(handleName, name);
		}
		if (strcmp(memberName.c_str(), "textureRT") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// texture name
			size_t nameEnd;
			for (nameEnd = handleNameEnd; nameEnd < buffer.size(); ++nameEnd)
			{
				if ('\"' == buffer[nameEnd])
					break;
			}

			string textureName = buffer.substr(handleNameEnd, nameEnd - handleNameEnd);

			wstring name;
			name.assign(textureName.begin(), textureName.end());
			auto rt = ResourceManager::GetInstance()->GetResource<RenderTarget>(name);
			SetTexture(handleName, rt->GetTexture());
		}
#pragma region shaderMember
		//bool      "handle"   "true"
		if (strcmp(memberName.c_str(), "bool") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			size_t valueEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string subBuffer = buffer.substr(handleNameEnd, valueEnd - handleNameEnd);

			if (strcmp(subBuffer.c_str(), "true") == 0)
				SetBool(handleName, true);
			else
				SetBool(handleName, false);
		}
		//int         "handle"   "x"
		if (strcmp(memberName.c_str(), "int") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			size_t valueEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string subBuffer = buffer.substr(handleNameEnd, valueEnd - handleNameEnd);

			int value = atoi(subBuffer.c_str());
			SetInt(handleName, value);
		}
		//float      "handle"   "x"
		if (strcmp(memberName.c_str(), "float") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			size_t valueEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string subBuffer = buffer.substr(handleNameEnd, valueEnd - handleNameEnd);

			float value = (float)atof(subBuffer.c_str());
			SetFloat(handleName, value);
		}
		//matrix   "handle"   "x,x,x,x,  x,x,x,x,  x,x,x,x,  x,x,x,x"
		if (strcmp(memberName.c_str(), "matrix") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - handleNameEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			Matrix mat;
			int row = 0;
			int col = 0;
			size_t valueStart = handleNameEnd;
			size_t valueEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if (',' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					mat.m[row][col] = value;

					++col;
					if (col == 4)
					{
						++row;
						col = 0;
					}
					valueStart = valueEnd + 1;
				}
				else if ('\"' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					mat.m[row][col] = value;

					break;
				}
			}
			SetMatrix(handleName, mat);
		}
		//vector4 "handle"   "x,x,x,x"
		if (strcmp(memberName.c_str(), "vector4") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			Vector4 vec;
			int vecIndex = 0;
			size_t valueStart = handleNameEnd;
			size_t valueEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if (',' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					++vecIndex;
					valueStart = valueEnd + 1;
				}
				else if ('\"' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					break;
				}
			}

			SetVector(handleName, vec);
		}
		//vector2 "handle"   "x,x"
		if (strcmp(memberName.c_str(), "vector2") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			// ���� " ã��
			++handleNameEnd;
			while ('\"' != buffer[handleNameEnd])
			{
				++handleNameEnd;
			}
			++handleNameEnd;

			// value
			Vector2 vec;
			int vecIndex = 0;
			size_t valueEnd;
			size_t valueStart = handleNameEnd;
			for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if (',' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					++vecIndex;
					valueStart = valueEnd + 1;
				}
				else if ('\"' == buffer[valueEnd])
				{
					string subBuffer = buffer.substr(valueStart, valueEnd - valueStart);
					float value = (float)atof(subBuffer.c_str());
					vec[vecIndex] = value;

					break;
				}
			}

			SetVector(handleName, vec);
		}
#pragma endregion
		// 3. renderQueue
		if (strcmp(memberName.c_str(), "renderQueue") == 0)
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
			SetRenderQueue(value);
		}
		// 4. renderMode
		if (strcmp(memberName.c_str(), "renderMode") == 0)
		{
			// render mode value
			size_t valueEnd;
			for (valueEnd = firstWordEnd + 2; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string renderMode = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			int value = atoi(renderMode.c_str());
			SetRenderingMode((RENDERING_MODE)value);
		}
		// 5. blendingMode
		if (strcmp(memberName.c_str(), "blendingMode") == 0)
		{
			// blending mode value
			size_t valueEnd;
			for (valueEnd = firstWordEnd; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string blendingMode = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			int value = atoi(blendingMode.c_str());
			SetBledingMode((BLENDING_MODE)value);
		}
		// 6. fillMode
		if (strcmp(memberName.c_str(), "fillMode") == 0)
		{
			// fill mode value
			size_t valueEnd;
			for (valueEnd = firstWordEnd + 2; valueEnd < buffer.size(); ++valueEnd)
			{
				if ('\"' == buffer[valueEnd])
					break;
			}

			string fillMode = buffer.substr(firstWordEnd, valueEnd - firstWordEnd);

			int value = atoi(fillMode.c_str());
			SetFillMode((FILL_MODE)value);

			break;
		}
	}


}

void Material::Release()
{
}

void Material::SetShader(wstring _shaderName)
{
	m_shader = ResourceManager::GetInstance()->GetResource<Shader>(_shaderName);
	ThrowIfFailed(m_shader->CheckShaderInitialize()); // Please Set Shader Input Layout 
	// ���⼭ �����ٸ� ���ҽ� �Ŵ��� ���� ���̴� �ʱ�ȭ�κ� �ڵ� ����!
	assert(L"Shader is nullptr" && m_shader);
}

void Material::SetDataToShader()
{
	for (auto& value : m_boolValues)
		m_shader->SetBool(value.first, value.second);

	for (auto& value : m_intValues)
		m_shader->SetInt(value.first, value.second);

	for (auto& value : m_floatValues)
		m_shader->SetFloat(value.first, value.second);

	for (auto& value : m_matrixValues)
		m_shader->SetMatrix(value.first, value.second);

	for (auto& value : m_vector4Values)
		m_shader->SetVector(value.first, value.second);

	for (auto& value : m_vector2Values)
		m_shader->SetVector(value.first, value.second);

	for (auto& value : m_texValues)
		m_shader->SetTexture(value.first, value.second);

	for (auto& value : m_values)
		m_shader->SetValue(value.first, value.second.first, value.second.second);
}

void Material::SetBool(const string& _parameter, bool _value)
{
	for (auto& value : m_boolValues)
	{
		if (value.first == _parameter)
		{
			value.second = _value;
			return;
		}
	}
	m_boolValues.emplace_back(pair<string, bool>(_parameter, _value));
}

void Material::SetInt(const string& _parameter, int _value)
{
	for (auto& value : m_intValues)
	{
		if (value.first == _parameter)
		{
			value.second = _value;
			return;
		}

	}
	m_intValues.emplace_back(pair<string, int>(_parameter, _value));
}

void Material::SetFloat(const string& _parameter, float _value)
{
	for (auto& value : m_floatValues)
	{
		if (value.first == _parameter)
		{
			value.second = _value;
			return;
		}
	}

	m_floatValues.emplace_back(pair<string, float>(_parameter, _value));
}

void Material::SetMatrix(const string& _parameter, const Matrix & _value)
{
	for (auto& value : m_matrixValues)
	{
		if (value.first == _parameter)
		{
			value.second = _value;
			return;
		}
	}

	m_matrixValues.emplace_back(pair<string, Matrix>(_parameter, _value));
}

void Material::SetTexture(const string& _parameter, PDIRECT3DTEXTURE9 _value)
{
	for (auto& value : m_texValues)
	{
		if (value.first == _parameter)
		{
			value.second = _value;
			return;
		}
	}

	m_texValues.emplace_back(pair<string, PDIRECT3DTEXTURE9>(_parameter, _value));
}

void Material::SetTexture(const string & _parameter, const wstring & _texName)
{
	auto tex = ResourceManager::GetInstance()->GetResource<Texture>(_texName)->GetTexure(0);
	for (auto& value : m_texValues)
	{
		if (value.first == _parameter)
		{
			value.second = tex;
			return;
		}
	}

	m_texValues.emplace_back(pair<string, PDIRECT3DTEXTURE9>(_parameter, tex));
}




void Material::SetTexture(int _index, PDIRECT3DTEXTURE9 _value)
{
	assert(m_texValues.size() > _index && L"At least one texture is required");

	m_texValues[_index].second = _value;
}


void Material::SetVector(const string& _parameter, const Vector4 & _vector)
{
	for (auto& value : m_vector4Values)
	{
		if (value.first == _parameter)
		{
			value.second = _vector;
			return;
		}
	}

	m_vector4Values.emplace_back(pair<string, Vector4>(_parameter, _vector));
}

void Material::SetVector(const string& _parameter, const Vector2 & _vector)
{
	for (auto& value : m_vector2Values)
	{
		if (value.first == _parameter)
		{
			value.second = _vector;
			return;
		}
	}

	m_vector2Values.emplace_back(pair<string, Vector2>(_parameter, _vector));
}

void Material::SetValue(const string& _parameter, void* _address, UINT _size)
{
	pair<void*, UINT> value;
	value.first = _address;
	value.second = _size;
	pair<string, pair<void*, UINT>> pair2;
	pair2.first = _parameter;
	pair2.second = value;
	m_values.emplace_back(pair2);

}




