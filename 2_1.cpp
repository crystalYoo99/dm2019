void main() {
    int i, sum, begin, end;
    
    for(i=0; i < 5; i++){
        scanf(“%d, %d”, &begin, &end);
        sum = accum_range(begin, end);
        printf(“sum[%d: %d] = %d\n”, begin, end, sum);
    }

int accum_range(int a, int b){
    return accum (b) - accum(a);
}

int accum(int final) {
    int sum = 0;

    for (int I = 1; I <= final; I = I +1)
        sum = sum + I;
    return sum;
}