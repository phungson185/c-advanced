#include<stdio.h>
int main(int argc, char *argv[])
{
    int a;
    char s[1000];
    FILE* p = fopen("test.txt","r");
    while(fscanf(p,"%[^\n]s",s)!= EOF)
        {
            //printf("%d\n",a);
            puts(s);
            break;
        }
}