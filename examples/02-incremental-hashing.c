// Example 2: Incremental hashing using XXH64
#define XXHASH_IMPLEMENTATION
#include <xxhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char* chunks[] = {"Hello, ", "incremental ", "hashing!"};
    size_t num_chunks = sizeof(chunks) / sizeof(chunks[0]);
    unsigned long long seed = 0;

    // Create a hash state
    XXH64_state_t* state = XXH64_createState();
    if (state == NULL) {
        fprintf(stderr, "Failed to create hash state\n");
        return 1;
    }

    // Initialize the state
    if (XXH64_reset(state, seed) == XXH_ERROR) {
        fprintf(stderr, "Failed to reset hash state\n");
        XXH64_freeState(state);
        return 1;
    }

    // Update the hash state with chunks
    for (size_t i = 0; i < num_chunks; i++) {
        if (XXH64_update(state, chunks[i], strlen(chunks[i])) == XXH_ERROR) {
            fprintf(stderr, "Failed to update hash state\n");
            XXH64_freeState(state);
            return 1;
        }
    }

    // Finalize the hash
    XXH64_hash_t hash = XXH64_digest(state);

    // Print the hash
    printf("XXH64 incremental hash: %llu\n", hash);

    // Free the state
    XXH64_freeState(state);

    return 0;
}
