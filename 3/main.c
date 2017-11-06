#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void get_bag_result(int weight[], int value[], int size);
static int get_max(int a, int b);

int main(int argc, char * argv[])
{
    int weight[] = {2, 2, 6, 5, 4};
    int value[] = {6, 3, 5, 4, 6};

    get_bag_result(weight, value, 5);
    return 0;
}

/*
V(i, 0) = V(0, j) = 0 

V(i, j) = V(i - 1, j)  j < wi  

V(i, j) = max{V(i - 1, j), V(i - 1, j - wi) + vi) } j > wi
*/
static void get_bag_result(int weight[], int value[], int size)
{
    int bag_weight = 1;
    int num = 1;
    int temp[size][11];
    
    if(weight == NULL || value == NULL || size < 1)
    {
        return;
    }

    memset(temp, 0, size * 11 * sizeof(int));
    /*
    for(num = 0; num < size; num++)
    {
        for(bag_weight = 0; bag_weight < 11; bag_weight ++)
        {
            temp[num][bag_weight] = 0;
        }
    }*/
    
    for(bag_weight = 1; bag_weight <= 10; bag_weight++)
    {
        for(num = size - 1; num >= 0; num--)
        {
            if(num == size - 1)
            {
                temp[num][bag_weight] = weight[num] > bag_weight ? 0 : value[num];
            }
            else
            {
                temp[num][bag_weight] = weight[num] > bag_weight ? temp[num + 1][bag_weight] : get_max(temp[num + 1][bag_weight], temp[num + 1][bag_weight - weight[num]] + value[num]);
            }
        }
    }

    for(num = 0; num < size; num++)
    {
        for(bag_weight = 1; bag_weight < 11; bag_weight ++)
        {
            printf("%d ", temp[num][bag_weight]);
        }
        
        printf("\n");
    }
}

static int get_max(int a, int b)
{
    return a > b ? a : b;
}

