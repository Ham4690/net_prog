#include <stdio.h>
 
enum week {
  Mon,
  Tue,
  Wed,
  Thu,
  Fri,
  Sat,
  Sun
};
 
int main(void) {
    enum week wk; // enum型のオブジェクトを定義
    char *c;
    wk = Mon;
 //   printf("%s\n",c);
//    strcpy(wk,c);
//    wk = c; // enum型の定数を代入
    printf("wk=%d\n",wk); 
    switch(wk) {
        case Mon:
        case Tue:
        case Wed:
        case Thu:
        case Fri:
            printf("平日です\n");
            break;
        case Sat:
        case Sun:
            printf("休日です\n");
            break;
        default:
            printf("不正です\n");
    }
    
    return 0;
}