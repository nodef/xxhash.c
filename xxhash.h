#pragma once
#if defined(XXHASH_IMPLEMENTATION) || defined(XXH_IMPLEMENTATION)
#include "xxhash/xxhash.c"
// #include "xxhash/xxh_x86dispatch.h"
// #include "xxhash/xxh_x86dispatch.c"
#else
#include "xxhash/xxhash.h"
// #include "xxhash/xxh_x86dispatch.h"
#endif
