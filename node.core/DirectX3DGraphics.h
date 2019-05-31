#pragma once

#include <wrl.h>
using namespace Microsoft::WRL;

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// D3D12 extension library.
#include "d3dx12.h"
#include <exception>


//include project headers
#include "Graphics.h"

class DirectX3DGraphics : public Graphics {
private:


	// Use WARP adapter
	bool useWarp = true;
	uint32_t g_ClientWidth = 1280;
	uint32_t g_ClientHeight = 720;
	// Set to true once the DX12 objects have been initialized.
	bool isInitialized = false;

	UINT g_RTVDescriptorSize;
	UINT g_CurrentBackBufferIndex;

	// Synchronization objects
	ComPtr<ID3D12Fence> g_Fence;
	uint64_t g_FenceValue = 0;
	uint64_t g_FrameFenceValues[3] = {};
	HANDLE g_FenceEvent;

	// By default, enable V-Sync.
	// Can be toggled with the V key.
	bool g_VSync = true;
	bool g_TearingSupported = false;
	// By default, use windowed mode.
	// Can be toggled with the Alt+Enter or F11
	bool g_Fullscreen = false;

	ComPtr<IDXGIAdapter4> dxgiAdapter4;
	ComPtr<ID3D12Device2> device;
	ComPtr<ID3D12CommandQueue> commandQueue;

protected:
	bool CheckTearingSupport();

public:
	DirectX3DGraphics();
	~DirectX3DGraphics();

	void Draw();

	void EnableDebugLayer();

	bool Initialize();

	bool IsInitialized();

	void ThrowIfFailed(HRESULT hr);

	void Update();
};

