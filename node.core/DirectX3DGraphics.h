#pragma once

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// D3D12 extension library.
//#include <d3dx12.h>

#include "Graphics.h"

class DirectX3DGraphics : public Graphics {
private:

public:
	DirectX3DGraphics();
	~DirectX3DGraphics();

	void Draw();

	bool Initialize();

	void Update();
};

