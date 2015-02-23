#pragma once

#include <functional>
#include "GameStructures.h"

typedef std::function<void(GamePositionOnBoard)> DetailCleaner;
typedef std::function<void(GamePositionOnBoard)> OperationWithPosition;

