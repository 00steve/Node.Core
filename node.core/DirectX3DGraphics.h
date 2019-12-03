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



//headers for tutorial 2
#include <DirectXMath.h>
using namespace DirectX;
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif



/*so much of this class is ripped right from :
https://www.3dgep.com/learning-directx12-1/#DirectX_12_Demo
*/

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

	static uint64_t frameCounter;
	static double elapsedSeconds;
	static std::chrono::high_resolution_clock clock;
	static std::chrono::steady_clock::time_point t0;


	bool CheckTearingSupport();

	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);

	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);

	ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter);

	HANDLE CreateEventHandle();

	ComPtr<ID3D12Fence> CreateFence(ComPtr<ID3D12Device2> device);

	ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);

	void Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent);

	ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);

	virtual void Resize(uint32_t width, uint32_t height);

	void SetFullscreen(bool fullscreen);

	uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue);

	void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);

	void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent);



	//tutorial 2 functions and properties

	uint64_t m_FenceValues[3] = {};

	// Vertex buffer for the cube.
	Microsoft::WRL::ComPtr<ID3D12Resource> m_VertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;
	// Index buffer for the cube.
	Microsoft::WRL::ComPtr<ID3D12Resource> m_IndexBuffer;
	D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;

	// Depth buffer.
	Microsoft::WRL::ComPtr<ID3D12Resource> m_DepthBuffer;
	// Descriptor heap for depth buffer.
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_DSVHeap;

	// Root signature
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_RootSignature;

	// Pipeline state object.
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_PipelineState;

	D3D12_VIEWPORT m_Viewport;
	D3D12_RECT m_ScissorRect;

	float m_FoV;

	DirectX::XMMATRIX m_ModelMatrix;
	DirectX::XMMATRIX m_ViewMatrix;
	DirectX::XMMATRIX m_ProjectionMatrix;

	bool m_ContentLoaded;
   
	// Clamp a value between a min and max range.
	template<typename T>
	constexpr const T& clamp(const T& val, const T& min, const T& max)
	{
		return val < min ? min : val > max ? max : val;
	}

	// Vertex data for a colored cube.
	struct VertexPosColor
	{
		XMFLOAT3 Position;
		XMFLOAT3 Color;
	};
	
	// Helper functions
	// Transition a resource
	void TransitionResource(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		Microsoft::WRL::ComPtr<ID3D12Resource> resource,
		D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	// Clear a render target view.
	void ClearRTV(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		D3D12_CPU_DESCRIPTOR_HANDLE rtv, FLOAT* clearColor);

	// Clear the depth of a depth-stencil view.
	void ClearDepth(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		D3D12_CPU_DESCRIPTOR_HANDLE dsv, FLOAT depth = 1.0f);

	// Create a GPU buffer.
	void UpdateBufferResource(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> commandList,
		ID3D12Resource** pDestinationResource, ID3D12Resource** pIntermediateResource,
		size_t numElements, size_t elementSize, const void* bufferData,
		D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE);

	// Resize the depth buffer to match the size of the client area.
	void ResizeDepthBuffer(int width, int height);



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

