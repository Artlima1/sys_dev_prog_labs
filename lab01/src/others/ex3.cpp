#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * In total there will be 9 processes, the expected output will be
                i=0
                i=1
                i=1
                i=i
                i=1
                i=i
                i=i
                i=i
    But it can happen in different execution orders
 */

int main () {
    int i;
    setbuf (stdout,0);
    for (i=0; i<2; i++) {
        printf ("i=%d\n", i);
        if (fork())             // Call # 1
            fork ();              // Call # 2
        else
            system ("echo i=i");  // Call # 3
    }
    return (1);
}
