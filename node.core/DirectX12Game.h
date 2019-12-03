#pragma once

#include "Game.h"
#include "DirectX3DGraphics.h"
#include <DirectXMath.h>

class DirectX12Game : public Game{
public:

	virtual bool Initialize();

	DirectX12Game();
	~DirectX12Game();
};

