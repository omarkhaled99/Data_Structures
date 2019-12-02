#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
    char* cName;
    double balance;
    int order;
} Item;
/*
 * Heapify index i in array of Items with size n
 */
void swap(Item*a,Item*b)
{
    Item temp;
    temp = *a;
    *a=*b;
    *b =temp;
}

void max_heapify(Item *arr, int n, int i)
{
    if(2*i>n)
    {
        return;
    }
    //handle the case of triple equal
    if(arr[2*i].balance>arr[i].balance&&arr[2*i].balance>=arr[2*i+1].balance)
    {
        swap(&arr[2*i],&arr[i]);
        max_heapify(arr,n,2*i);
    }
    else if(arr[2*i+1].balance>arr[i].balance&&arr[2*i].balance<=arr[2*i+1].balance)
    {
        swap(&arr[2*i+1],&arr[i]);
        max_heapify(arr,n,2*i+1);
    }
    else if(arr[2*i].balance==arr[i].balance)
    {
        if(arr[2*i].order<arr[i].order)

     {
         swap(&arr[2*i],&arr[i]);
        max_heapify(arr,n,2*i);
     }

    }
     if(arr[2*i+1].balance==arr[i].balance)
    {
        if(arr[2*i+1].order<arr[i].order){
            swap(&arr[2*i+1],&arr[i]);
        max_heapify(arr,n,2*i+1);
        }

    }

}

/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
    int i;
    for(i=n; i>0; i--)
        max_heapify(arr,n,i);
}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    int i=1;
    Item maximum = arr[1];
    arr[1]=arr[n];
    construct_PQ(arr,n-1);
    return maximum;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)

{
    int i = 1;
    FILE * fp = fopen(fname,"r");
    if(fp==NULL)
        printf("error opening file");
    while(!feof(fp))
    {
        char*name=malloc(sizeof(char)*50);
        double balance;
        fscanf(fp,"%s %lf\n",name,&balance);
        arr[i].cName=name;
        arr[i].balance=balance;
        arr[i].order=i;
        name = NULL;
        i++;
    }
    fclose(fp);
    return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    Item customer;
    int i;
    for(i=n-1; i>0; i--)
    {
        customer = extract_maximum(arr,i);
        printf("\n%s\t\t%lf\t\t%d",customer.cName,customer.balance,customer.order);
    }
}
/*
 *
 */
int main(int argc, char**argv)
{

    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
