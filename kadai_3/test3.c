/*
    scanfに不正入力をするとループするテスト
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int x = 0;
    char str[256];
    while(1){
        fgets(str,sizeof(str),stdin);
        str[strlen(str)-1] = '\0';
        printf("%s\n",str);
        if(x == -1) break;
    }
    return 0; 
}