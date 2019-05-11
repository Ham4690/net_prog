#include        <stdio.h>
#include        <string.h>

int main(void)
{
        char str[] = "https://www.google.com";
        char *tp;
        int count = 0;
        /* /を区切りに文字列を抽出 */   
        tp = strtok( str, "/" );
        printf("%d",count++);
//        puts( tp );
        while ( count < 2 ) {
                tp = strtok( NULL,"/" );
                printf("%d",count++);
                if ( tp != NULL ) puts( tp );
        }
        
        return 0;
}