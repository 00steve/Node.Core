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


ComPtr<IDXGIAdapter4> DirectX3DGraphics::GetAdapter(bool useWarp) {

	ComPtr<IDXGIFactory4> dxgiFactory;
	UINT createFactoryFlags = 0;
	#if defined(_DEBUG)
		createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
	#endif

	ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));
	ComPtr<IDXGIAdapter1> dxgiAdapter1;
	ComPtr<IDXGIAdapter4> dxgiAdapter4;

	//if (useWarp)
	//{
	//	ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
	//	ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
	//}
	//else
	//{
	//	SIZE_T maxDedicatedVideoMemory = 0;
	//	for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
	//	{
	//		DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
	//		dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

	//		// Check to see if the adapter can create a D3D12 device without actually 
	//		// creating it. The adapter with the largest dedicated video memory
	//		// is favored.
	//		if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
	//			SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
	//				D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
	//			dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
	//		{
	//			maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
	//			ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
	//		}
	//	}
	//}

	return dxgiAdapter4;
}







bool DirectX3DGraphics::Initialize() {



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