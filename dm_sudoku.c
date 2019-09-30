#include <stdio.h>


int main() {
    int i, j, n;

    for (i = 1 ; i <= 9 ; i++)
		for (j = 1 ; j <= 9 ; j++)
            for(n = 1; n <= 9; n++)
			    printf("(declare-const p%d%d%d Bool)\n", i, j, n) ;

    //Q1
    printf("; Q1\n");
    printf("(assert (and ");
    for(i=1; i<=9; i++) {
        printf("(and ");
        for(n=1; n<=9; n++) {
            printf("(or ");
                for(j=1; j<=9; j++)
                    printf("p%d%d%d ", i, j, n);
        }
        printf(")");
    }
    printf(")))\n");

    //Q2
    printf("; Q2\n");
    printf("(assert (and ");
    for(j=1; j<=9; j++) {
        printf("(and ");
        for(n=1; n<=9; n++) {
            printf("(or ");
            for(i=1; i<=9; i++)
                printf("p%d%d%d ", i, j, n);
            printf(")");
        }
        printf(")");
    }
    printf("))\n");

    //Q3
    printf("; 03\n");
    printf("(assert (and ");
    for(int r = 0; r <= 2; r++) {
        printf("(and ");
        for(int s = 0; s <= 2; s++) {
            printf("(and ");
            for(n = 1; n <= 9; n++) {
                printf("(or ");
                for(i = 1; i <= 3; i++) {
                    printf("(or ");
                    for(j = 1; j <= 3; j++)
                        printf("p%d%d%d ", 3*r+i, 3*s+j, n);
                    printf(")");
                }
                printf(")");
            }
            printf(")");
        }
        printf(")");
    }
    printf("))\n");
    
    /*
    //Q4
    printf("; 04\n");
    printf("(assert (and ");
    for(n = 1; n <= 9; n++) {
        printf("(and ");
        for(int k = 1; k <= 9; k++) {
            if(k != n) {
                printf("");
                for
        }
    }
    */
    printf("(check-sat)\n(get-model)\n");
}