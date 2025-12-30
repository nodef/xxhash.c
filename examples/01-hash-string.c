// Example 1: Hashing a string using XXH64
#define XXHASH_IMPLEMENTATION
#include <xxhash.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char* input = "Hello, xxHash!";
    size_t length = strlen(input);
    unsigned long long seed = 0; // Seed can be any value

    // Compute the hash
    XXH64_hash_t hash = XXH64(input, length, seed);

    // Print the hash
    printf("XXH64 hash of '%s': %llu\n", input, hash);

    return 0;
}
