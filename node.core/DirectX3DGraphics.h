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
	HWND g_hWnd;
	// Window rectangle (used to toggle fullscreen state).
	RECT g_WindowRect;

	// The number of swap chain back buffers.
	const uint8_t g_NumFrames = 3;

	// DirectX 12 Objects
	ComPtr<ID3D12Device2> g_Device;
	ComPtr<ID3D12CommandQueue> g_CommandQueue;
	ComPtr<IDXGISwapChain4> g_SwapChain;
	ComPtr<ID3D12Resource> g_BackBuffers[3];
	ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	ComPtr<ID3D12CommandAllocator> g_CommandAllocators[3];
	ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;

	// Use WARP adapter
	bool g_UseWarp = false;
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

	ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);


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

