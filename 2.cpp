#include <iostream>

using namespace std;

 
int main() {
    int i;
    int v[10];
    int min, k;

    for(i =0; i < 10; i++) 
        scanf("%d", &v[i]);

    min = v[0];
    for(i = 1; i < 10; i++)
        if(min > v[i]) {
            min = v[i];
            k = i;
        }
    printf("%d => %d", k, min);

    return 0;
}