#include <stdio.h>

int main ()
{
	FILE * f = fopen("origin_sudoku", "r");
    FILE * fp = fopen("formula_sudoku", "w") ;

	int x, y;
    int n[9][9];

    for (y = 1; y <= 9; y++)
        for(x=1; x<=9; x++)
            fscanf(f, "%d", a[x][y]);
        
    //비움
	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(declare-const a%d%d Int)\n", y, x) ;

    //숫자 넣기
    for (y = 1; y <= 9; y++) {
        for(x = 1; x <= 9; x++) {
            fscanf(f, "%d", n);
            fprintf(fp, "(assert (= (select a%d%d) %d))", y,x,n);
        }
        fscanf(f, "%d", n);
    }

    //한 칸은 1이상 9이하
	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(assert (and (<= a%d%d 9) (<= 1 a%d%d)))\n", y, x, y, x) ;


    //한 행 더하면 45
	for (x = 1 ; x <= 9 ; x++) {
		int i_y ;
		fprintf(fp, "(assert(<= (+ ") ;
		for (i_y = 1 ; i_y <= 9 ; i_y++)
			fprintf(fp, "a%d%d ", i_y, x) ;
		fprintf(fp, ") 45))\n") ;
	}

    //한 열 더하면 45
	for (y = 1 ; y <= 9 ; y++) {
		int i_x ;
		fprintf(fp, "(assert(<= (+ ") ;
		for (i_x = 1 ; i_x <= 9 ; i_x++)
			fprintf(fp, "a%d%d ", y, i_x) ;
		fprintf(fp, ") 45))\n") ;
	}

    //한 박스 더하면 45
    for(int s = 0; s <= 2; s++) {
        for(int r = 0; r <= 2; r++) {
            fprintf(fp, "(assert(<= (+ ");
            for(y = 1; y <= 3; y++) {
                for(x = 1; x <= 3; x++) {
                    fprintf(fp, "a%d%d ", 3*s+y, 3*r+x);
                }
            }
            fprintf(fp, ") 45))\n");
        }
    }

    
	fprintf(fp, "(check-sat)\n(get-model)\n") ;

	fclose(fp) ;

	FILE * fin = popen("z3 formula", "r") ; //FIXME
	char buf[128] ;
	fscanf(fin, "%s %s", buf, buf) ;
	while (!feof(fin)) {
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s ", buf) ;
		fscanf(fin, "%s", buf) ; printf("%s\n", buf) ;
	}
	pclose(fin) ;
}