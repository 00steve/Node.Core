#include "DirectX3DGraphics.h"



DirectX3DGraphics::DirectX3DGraphics(){
}


DirectX3DGraphics::~DirectX3DGraphics(){
}


void DirectX3DGraphics::Draw() {
}

void DirectX3DGraphics::EnableDebugLayer(){
	#if defined(_DEBUG)
		// Always enable the debug layer before doing anything DX12 related
		// so all possible errors generated while creating DX12 objects
		// are caught by the debug layer.
		ComPtr<ID3D12Debug> debugInterface;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
		debugInterface->EnableDebugLayer();
	#endif
}


bool DirectX3DGraphics::Initialize() {
	HWND g_hWnd;
	// Window rectangle (used to toggle fullscreen state).
	RECT g_WindowRect;

	// The number of swap chain back buffers.
	const uint8_t g_NumFrames = 3;

	// DirectX 12 Objects
	ComPtr<ID3D12Device2> g_Device;
	ComPtr<ID3D12CommandQueue> g_CommandQueue;
	ComPtr<IDXGISwapChain4> g_SwapChain;
	ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
	ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
	ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;


	EnableDebugLayer();




	isInitialized = true;
	DBOUT("-  Initialized dx3d graphics\n");
	return true;
}


bool DirectX3DGraphics::IsInitialized() {
	return isInitialized;
}


void DirectX3DGraphics::ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		// Set a breakpoint on this line to catch DirectX API errors
		throw std::exception();
	}
}

void DirectX3DGraphics::Update() {
	HandleMessages();
}