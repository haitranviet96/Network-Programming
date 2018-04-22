
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Generate a random number from nr_min to nr_max
int randomNumber(int nr_min, int nr_max)
{
    // Initialize the random number generator with the current time
    // be sure that it is initialized only once
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }
    // generate the random number
    return rand() % nr_max + nr_min;
}

// Generate a random color from 0 to 255
int randomColor()
{
    return randomNumber(0, 255);
}
