#include "stdlib.h"
int cal();
int main() {
    int arv,number,ans;
    while (1) {
        printf("arv\n");
        scanf("%d",&arv);
        printf("number\n");
        scanf("%d",&number);
        ans = cal(arv,number);
        printf("ans : %d\n",ans);
    }
    return 0;
}

cal(int arv,int number){
    int digit,temp,ans,remaind,i = 1;
    ans = number%arv;
    temp = number;
    while (1) {
        i = i * 10;
        temp = temp / arv;
        printf("%d\n",temp );
        if(temp>arv){
            remaind = temp % arv;
            ans = ans + remaind*i;
        }
        else if(temp == arv){
            ans = ans +i*10;
            break;
        }

        else if(temp < arv || temp == 0){
            ans = ans + temp * i;
            break;
        }
    }
    return ans;
}
