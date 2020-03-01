#pragma once
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_Keys
{
	// declares balck board keys
	TCHAR const * const TargetLocation = TEXT("TargetLocation");

	TCHAR const * const bCanSeePlayer = TEXT("CanSeePlayer");

	TCHAR const * const patrol_path_vector = TEXT("PatrolPathVector");

	TCHAR const * const patrol_path_index = TEXT("PatrolPathIndex");

	TCHAR const * const bPlayerIsInMeleeRange = TEXT("PlayerIsInMeleeRange");

	TCHAR const * const PlayerRef = TEXT("PlayerRef");
}
