#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define if_null_return_ret(a, b) do{ if(a == NULL) return b;}while(0)
#define if_null_return(a) do{ if(a == NULL) return;}while(0)

typedef struct NODE_STACK
{
    int item;
    struct NODE_STACK * next;
}node;

typedef struct STACK_TAG
{
    node * top;
    int size;
}stack_t;

static int is_right(int input[], int output[], int size);
static void free_stack(stack_t * stack);
static int top(stack_t * stack);
static void push(stack_t * stack, int item);
static int pop(stack_t * stack);

static int pop(stack_t * stack)
{
    int ret = -1;
    node * temp = NULL;
    
    if_null_return_ret(stack, ret);

    if(stack->size > 0)
    {
        temp = stack->top;
        stack->top = temp->next;
        
        ret = temp->item;
        stack->size -= 1;

        free(temp);
        temp = NULL;

        return ret;
    }

    return ret;
}

static void push(stack_t * stack, int item)
{
    node * temp = NULL;
    if_null_return(stack);

    temp = (node *)malloc(sizeof(node));
    if(temp == NULL)
    {
        return;
    }

    memset(temp, 0, sizeof(temp));
    temp->item = item;
    temp->next = stack->top;
    stack->top = temp;
    stack->size++;
}


static int top(stack_t * stack)
{
    int ret = 0;
    
    if_null_return_ret(stack, ret);

    if(stack->size > 0)
    {
        ret = stack->top->item;
    }

    return ret;
}

static void free_stack(stack_t * stack)
{
    int i = 0;
    node * temp = NULL;
    
    if_null_return(stack);

    for(i = 0; i < stack->size; i++)
    {
        temp = stack->top;
        
        if(temp != NULL)
        {
            stack->top = temp->next;
            free(temp);
            temp = NULL;
        }
    }

    free(stack);
    stack = NULL;
}

static void print_stack(stack_t * stack)
{
    int i = 0;
    node * temp = NULL;

    temp = stack->top;
    for(i = 0; i < stack->size; i++)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }

    printf("\n");
}

int main(int argc, char * argv[])
{
    int ret = -1;
    int input[]  = {1, 2, 3, 4};
    int output[] = {3, 4, 2, 1};

    ret = is_right(input, output, sizeof(input) / sizeof(int));

    printf("ret: %d\n", ret);
    
    return 0;
}

static int is_right(int input[], int output[], int size)
{
    int i = 0;
    int j = 0;
    int ret = -1;
    stack_t * stack = NULL;
    
    if(input == NULL || output == NULL || size < 1)
    {
        return ret;
    }
    
    stack = (stack_t *)malloc(sizeof(stack_t));
    if(stack == NULL)
    {
        printf("Malloc error.\n");
        return ret;
    }

    memset(stack, 0, sizeof(stack_t));
    for(i = 0, j = 0; i < size;)
    {
        if(output[i] == top(stack))
        {
            pop(stack);
            i++;
        }
        else if(j < size)
        {
            push(stack, input[j]);
            j++;
        }
        else
        {
            break;
        }
        
        print_stack(stack);
    }

    if(stack->size == 0)
    {
        ret = 0;
    }

    free_stack(stack);
    
    return ret;
}
