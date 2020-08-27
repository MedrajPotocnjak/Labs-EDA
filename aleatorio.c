#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i=0,j=0;
    int m[15][15];
    srand(time(NULL));

    for(i=0;i<12;i++){
        for(j=0;j<12;j++){
            m[i][j]=rand()%51;
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    return 0;
}