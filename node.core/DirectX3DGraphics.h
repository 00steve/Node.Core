#pragma once

#define NOMINMAX

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

// STL Headers
#include <algorithm>
#include <cassert>
#include <chrono>


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

	bool CheckTearingSupport();

	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);

	ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter);

	HANDLE CreateEventHandle();

	ComPtr<ID3D12Fence> CreateFence(ComPtr<ID3D12Device2> device);

	ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);

	ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);

	uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue);

	void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);

	void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration);
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

