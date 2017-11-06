#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREE_MEM(a) if(a) {free(a); a = NULL;}

typedef struct LinkCodeTag
{
    int num;
    struct LinkCodeTag * next;
    struct LinkCodeTag * last;
}code_t;

static void print_code_t(code_t * node);
static void free_code_t(code_t * node);
static void insert(code_t * node, int next_num);
static void add_code_t(code_t * node1, code_t * node2);

int main(int argc, char * argv[])
{
    code_t * head1 = NULL;
    code_t * head2 = NULL;

    head1 = (code_t *)malloc(sizeof(code_t));
    memset(head1, 0, sizeof(code_t));
    head2 = (code_t *)malloc(sizeof(code_t));
    memset(head2, 0, sizeof(code_t));

    insert(head1, 2);
    insert(head1, 4);
    insert(head1, 3);

    insert(head2, 5);
    insert(head2, 6);
    insert(head2, 4);

    add_code_t(head1, head2);
    
    print_code_t(head1);
    print_code_t(head2);
   
    free_code_t(head1);
    free_code_t(head2);
    
    return 0;
}

static void insert(code_t * node, int next_num)
{
    code_t * temp = NULL;

    temp = node;
    if(temp == NULL)
    {
        temp = (code_t *)malloc(sizeof(code_t));
        memset(temp, 0, sizeof(code_t));
    }
    
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = (code_t *)malloc(sizeof(code_t));

    memset(temp->next, 0, sizeof(code_t));
    temp->next->num = next_num;
    temp->next->next = NULL;
    temp->next->last = temp;
}

static void free_code_t(code_t * node)
{
    code_t * temp = NULL;
    code_t * last = NULL;

    temp = node;
    if(node == NULL)
    {
        return;
    }
        
    while(temp->next != NULL)
    {
        last = temp->next;
        FREE_MEM(temp);
        temp = last;
    }

    FREE_MEM(temp);
}

static void print_code_t(code_t * node)
{
    code_t * temp = NULL;

    temp = node;
    while(temp != NULL)
    {
        printf("%d ", temp->num);
        temp = temp->next;
    }

    printf("\n");
}

static void add_code_t(code_t * node1, code_t * node2)
{
    int result = -1;
    int inc = 0;
    
    code_t * temp1 = node1;
    code_t * temp2 = node2;

    if(temp1 == NULL || temp2 == NULL)
    {
        return;
    }

    while(temp1 != NULL || temp2 != NULL)
    {
        result = (temp1->num + temp2->num) % 10 + inc;
        inc = (temp1->num + temp2->num) / 10;

        printf("%d ", result);

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    printf("\n");
}
