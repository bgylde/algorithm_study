#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

static int get_lcs(char * str1, char * str2, int len1, int len2);

int main(int argc, char * argv[])
{
#if 0
    char * str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char * str2 = "ABCDEFGHIJKL";
#else
    char * str1 = "ABCBDAB";
    char * str2 = "BDCABA";
#endif
    get_lcs(str1, str2, strlen(str1), strlen(str2));
    
    return 0;
}

static int get_lcs(char * str1, char * str2, int len1, int len2)
{
    int ret = -1;
    int i = 0;
    int j = 0;
    int stack_cont = 0;
    char * str_stack = NULL;
    int max_len[len1 + 1][len2 + 1];
    
    if(str1 == NULL || str2 == NULL)
    {
        return ret;
    }

    if(len1 == 0 || len2 == 0)
    {
        return ret;
    }

    memset(max_len, 0, sizeof(int) * (len1 + 1) * (len2 + 1));
    for(i = 0; i <= len1; i++)
    {
        for(j = 0; j <= len2; j++)
        {
            if(i == 0 || j == 0)
            {
                max_len[i][j] = 0;
            }
            else
            {
                if(str1[i - 1] == str2[j - 1])
                {
                    max_len[i][j] = max_len[i - 1][j - 1] + 1;
                }
                else
                {
                    max_len[i][j] = MAX(max_len[i - 1][j], max_len[i][j - 1]);
                }
            }

            printf("%2d ", max_len[i][j]);
            ret = max_len[i][j];
        }

        printf("\n");
    }

    i = len1;
    j = len2;
    stack_cont = max_len[i][j];
    str_stack = (char *)malloc(max_len[i][j] + 1);
    if(NULL == str_stack)
    {
        printf("malloc error: %s\n", strerror(errno));
        return ret;
    }
    
    while(i != 0 && j != 0)
    {
        if(str1[i - 1] == str2[j - 1])
        {
            //printf("%c ", str1[i - 1]);
            *(str_stack + (--stack_cont)) = str1[i - 1];
            i--;
            j--;
        }
        else
        {
            if(max_len[i - 1][j] < max_len[i][j - 1])
            {
                j--;
            }
            else
            {
                i--;
            }
        }
    }

    printf("the max string is: %s\n", str_stack);
    
    return ret;
}

