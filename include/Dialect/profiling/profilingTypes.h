#ifndef PROFILING_TYPES_H
#define PROFILING_TYPES_H

#include "mlir/IR/Types.h"
#include "mlir/Interfaces/DataLayoutInterfaces.h"
#include "mlir/Interfaces/MemorySlotInterfaces.h"
#include <optional>


#define GET_TYPEDEF_CLASSES
#include "profiling/profilingTypes.h.inc"

#endif