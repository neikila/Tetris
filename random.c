#include <stdio.h>
#include "time.h"

int main()
{
    srand(time(NULL));
    int count = 2500000;
    while ( count-- )
        printf("%d ", rand());
    return 0;
}
