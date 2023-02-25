#include <stdio.h>

int main(void){
    int in;
    double store;
    double calc;
    double count;
    int max = 0;
    while(1)
    {
        scanf("%d", in);
        if(in < 0)
        {
            break;
        }
        if(in >= max)
        {
            max = in;
        }
        store += in;
        count++;
    }
    calc = store / count;
    print("%d", max);
    printf("0.2%lf\n", calc);
}