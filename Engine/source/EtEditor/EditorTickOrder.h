#pragma once
#include <Engine/Base/TickOrder.h>

//---------------------------------
// E_TickOrder
//
// Order in which order various modules should be ticked
//
enum class E_EditorTickOrder : uint32
{
	TICK_SceneSelection = static_cast<E_EditorTickOrder>(E_TickOrder::COUNT),

	COUNT
};
