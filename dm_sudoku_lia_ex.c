#include <stdio.h>

int main ()
{
	FILE * f = fopen("origin_sudoku", "r");
    FILE * fp = fopen("formula_sudoku", "w") ;

	int x, y;
    char input[9][9];
    int star_addr[9];
    int num[81];
    int num_addr[81];
    int count_num=0;
    int count_star=0;

    //원본 파일에서 줄로 읽어오기
    for (int i = 0; i<9; i++)
        fscanf(f, "%s", input[i]);

    //변수 만들기
	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(declare-const a%d%d Int)\n", y, x) ;
    
    //월본에서 별과 숫자 위치 저장
    for(y=1; y<=9; y++) {
        for(x=1; x<=9; x++) {               
            if(input[x][y]=='*') {
                star_addr[count_star] = (x+1)*10+(y+1);
                count_star++;
            }
            else if(input[x][y] == '?') {}
            else {
                num[count_num] = input[x][y]-0;
                num_addr[count_num] = (x+1)*10 +(y+1);
            }
        }
    }

    //숫자 초기화
    for(int i = 0; i < count_num; i++) {
        fprintf(fp, "(assert (= (select a%d%d) %d))", num_addr[i]%10, num_addr[i]-num_addr[i]%10, num[i]);
    }

    //한 칸은 1이상 9이하
	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(assert (and (<= a%d%d 9) (<= 1 a%d%d)))\n", y, x, y, x) ;


    //한 행 다 달라야 한다
	for (x = 1 ; x <= 9 ; x++) {
        for(y = 1; y <= 9; y++) {
            for(int i_y = y+1; i_y<=9; i_y++)
                fprintf(fp, "(assert (distinct a%d%d a%d%d))\n", y, x, i_y, x);
        }
	}

    //한 열 다 달라야 한다
	for (y = 1 ; y <= 9 ; y++) {
		for( x = 1; x<= 9; x++) {
            for(int i_x = x+1; i_x <= 9; i_x++)
                fprintf(fp, "(assert (distinct a%d%d a%d%d))\n", y, x, y, i_x);
        }
	}

    //한 박스 다 달라야 한다
    for(int s = 0; s <= 2; s++) {
        for(int r = 0; r <= 2; r++) {
            for(y = 1; y<=3; y++) {
                for(x = 1; x <= 3; x++) {
                    for(int i_x = x; i_x <= 3; i_x++)
                        fprinf(fp, "(assert (distinct a%d%d a%d%d))\n", 3*s+y, 3*r+x, 3*s+y, 3*r+i_x);
                    for(int i_y = y+1; i_y <= 3; i_y++)
                        for(int i_x = 1; i_x <= 3; i_x++)
                            fprintf(fp, "(assert (distinct a%d%d a%d%d))\n", 3*s+y, 3*r+x, 3*s+i_y, 3*r+i_x);
                }
            }
        }
    }

    //별끼리 달라야함
    for(int i = 0; i < count_star; i++) {
        for(int j = i+1; j < count_star; j++)
            fprintf(fp, "(assert (distinct a%d%d a%d%d))", star_addr[i]%10, star_addr[i]-(star_addr[i]%10), star_addr[j]%10, star_addr[j]-(star_addr[j]%10));
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