#include <stdio.h>

int main (void)
{
    int i;
    int num[100];

    for (i = 0; i < 100; i++) {

        //何も入力せずEnterキーが押されるとforループを抜けるようにしたい
        char buff[100];
        fgets(buff, sizeof(buff), stdin);
        printf("buff %s \n",buff);
        if (sscanf(buff, "%d", &num[i]) != 1){}
        printf("%d\n",num[i]);
    break;
    }

    printf("Hello, world\n");
    return 0;
}