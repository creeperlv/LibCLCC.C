#include "../Headers/simple_dictionary.h"
#include <stdio.h>
#include <string.h>
int main()
{
    simple_dict *dict = LibCLCC_CreateSimpleDictionary();
    {
        int K = 0;
        int V = 12345;
        LibCLCC_SetValue(dict, &K, &V);
    }
    {
        int K = 34;
        int V = 54321;
        LibCLCC_SetValue(dict, &K, &V);
    }
    {
        int K = 0;
        printf("K:0, V=%d\n", *(int *)LibCLCC_GetValue(dict, &K));
    }
    {
        int K = 34;
        printf("K:0, V=%d\n", *(int *)LibCLCC_GetValue(dict, &K));
    }
    {
        int K = 35;
        printf("K:0, IsNull=%d\n", (int *)LibCLCC_GetValue(dict, &K) == NULL);
    }
    return 0;
}