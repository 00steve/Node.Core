#include "DirectX3DGraphics.h"



DirectX3DGraphics::DirectX3DGraphics(){
}


DirectX3DGraphics::~DirectX3DGraphics(){
}


void DirectX3DGraphics::Draw() {
}

bool DirectX3DGraphics::Initialize() {
	HWND g_hWnd;
	// Window rectangle (used to toggle fullscreen state).
	RECT g_WindowRect;

	// DirectX 12 Objects
	//ComPtr<ID3D12Device2> g_Device;
	//ComPtr<ID3D12CommandQueue> g_CommandQueue;
	//ComPtr<IDXGISwapChain4> g_SwapChain;
	//ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
	//ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	//ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
	//ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;
	//UINT g_RTVDescriptorSize;
	//UINT g_CurrentBackBufferIndex;








	DBOUT("-  Initialized dx3d graphics\n");
	return true;
}

void DirectX3DGraphics::Update() {
	HandleMessages();
}