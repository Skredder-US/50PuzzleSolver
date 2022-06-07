/*
 * Attempts every possible arrangement of the SafeCracker Puzzle to find solutions!
 * The puzzle has 65,536 arrangements of 4 rotatable rings atop a fixed, 5th ring.
 * The columns of each ring must add to 50 to solve the puzzle! (see picture)
 * 
 * Found only 1 solution: "7       13      6       0" with current input (see code for more)
 * This solution was found (seemingly) instantly after running!
 * 
 * 6/7/2022 Taylor Juve
 */

#include <stdio.h>
#include <stdbool.h>

#define LEN 16
#define NUM_RINGS 5
#define GAP -1
#define KEY 50 // all columns must add to this to be a solution

struct ring {
    int inner[LEN];
    int outer[LEN];
    int rotation; // values 0 to LEN-1
};

bool isSolved(struct ring rings[NUM_RINGS]);

int main() {
    // See picture of puzzle 
    struct ring rings[NUM_RINGS] = {
        {   // top ring
            {}, // None
            {8, GAP, 17, GAP, 6, GAP, 6, GAP, 8, GAP, 8, GAP, 16, GAP, 19, GAP},
            0
        },
        {
            {6, 18, 8, 17, 4, 20, 4, 14, 4, 5, 1, 14, 10, 17, 10, 5},
            {10, GAP, 14, GAP, 11, GAP, 8, GAP, 12, GAP, 11, GAP, 3, GAP, 8, GAP},
            0
        },
        {
            {0, 22, 19, 10, 0, 5, 20, 8, 19, 10, 15, 20, 12, 20, 13, 13},
            {10, GAP, 11, GAP, 10, GAP, 0, GAP, 11, GAP, 8, GAP, 8, GAP, 8, GAP},
            0
        },
        {
            {12, 1, 10, 12, 22, 0, 5, 8, 5, 1, 24, 8, 10, 20, 7, 20},
            {9, GAP, 8, GAP, 8, GAP, 9, GAP, 6, GAP, 10, GAP, 8, GAP, 10, GAP},
            0
        },
        {   // bottom ring
            {10, 18, 10, 10, 10, 10, 15, 7, 19, 18, 2, 9, 27, 13, 11, 13},
            {4, 15, 7, 10, 1, 10, 4, 5, 3, 15, 16, 4, 7, 0, 16, 8},
            0
        }
    };

    // Test every possible combination of ring rotations for solutions, printing solutions
    for (rings[0].rotation = 0; rings[0].rotation < LEN; rings[0].rotation++) {
        for (rings[1].rotation = 0; rings[1].rotation < LEN; rings[1].rotation++) {
            for (rings[2].rotation = 0; rings[2].rotation < LEN; rings[2].rotation++) {
                for (rings[3].rotation = 0; rings[3].rotation < LEN; rings[3].rotation++) {
                    if (isSolved(rings)) {
                        printf("%d\t%d\t%d\t%d\n", rings[0].rotation, rings[1].rotation, 
                            rings[2].rotation, rings[3].rotation);
                    }
                }
            }
        }
    }

    return 0;
}

// Test current configuration to see if solved
bool isSolved(struct ring rings[NUM_RINGS]) {
    // Check the sum of the numbers in each column against KEY
    for (int col = 0; col < LEN; col++) {
        int sum = 0;

        for (int ring = 0; ring < NUM_RINGS; ring++) {
            // Get the value from the current ring
            int rotatedCol = (rings[ring].rotation + col) % LEN;
            int value = rings[ring].outer[rotatedCol];
            
            // if current ring has a gap here, get the value in the gap from the ring beneath
            if (value == GAP) {
                rotatedCol = (rings[ring + 1].rotation + col) % LEN;
                value = rings[ring + 1].inner[rotatedCol];
            }

            sum += value;
        }

        if (sum != KEY) {
            return false;
        }
    }
    return true;
}
