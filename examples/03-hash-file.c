// Example 3: Hashing a file using XXH3
#define XXHASH_IMPLEMENTATION
#include <xxhash.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    unsigned long long seed = 0;

    // Create a hash state
    XXH3_state_t* state = XXH3_createState();
    if (state == NULL) {
        fprintf(stderr, "Failed to create hash state\n");
        fclose(file);
        return 1;
    }

    // Initialize the state
    if (XXH3_64bits_reset_withSeed(state, seed) == XXH_ERROR) {
        fprintf(stderr, "Failed to reset hash state\n");
        XXH3_freeState(state);
        fclose(file);
        return 1;
    }

    // Read the file and update the hash state
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (XXH3_64bits_update(state, buffer, bytes_read) == XXH_ERROR) {
            fprintf(stderr, "Failed to update hash state\n");
            XXH3_freeState(state);
            fclose(file);
            return 1;
        }
    }

    if (ferror(file)) {
        perror("Error reading file");
        XXH3_freeState(state);
        fclose(file);
        return 1;
    }

    // Finalize the hash
    XXH64_hash_t hash = XXH3_64bits_digest(state);

    // Print the hash
    printf("XXH3 hash of file '%s': %llu\n", file_path, hash);

    // Free the state and close the file
    XXH3_freeState(state);
    fclose(file);

    return 0;
}
