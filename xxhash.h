#pragma once
#if defined(XXHASH_IMPLEMENTATION) || defined(XXH_IMPLEMENTATION)
#include "xxhash.c"
#include "xxh_x86dispatch.h"
#include "xxh_x86dispatch.c"
#else
#include "xxhash.h"
#include "xxh_x86dispatch.h"
#endif
