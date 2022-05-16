#include <stdio.h>


int CountSetBits(int N){
    int cnt = 0, k = N;

    while(k > 0){
        if(k % 2 != 0){
            cnt++;
        }
        k /= 2;
    }
    return cnt;
}

int main(){
    int n = 6;
    int x = CountSetBits(n);
    printf("N: %d\nCount: %d\n", n, x);
}
