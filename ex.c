#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct kdt
{
    int *data;
    struct kdt *left,*right;
}kdt;
int k=-1;



double distance_parameter(int *arr1 , int *arr2)
{
    double interspace = 0;
    int i;
    for (i=0;i<k;i++)
        interspace += (arr1[i] - arr2[i])*(arr1[i] - arr2[i]);
    return interspace;
}



kdt* allocate()
{
    kdt *node;
    node = (kdt*)malloc(sizeof(kdt));
    if (node == NULL)
    {
        printf("MEMORY ALLOCATION FAILED !!!");
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;

    node->data = (int*)malloc(k * sizeof(int));
    if (node->data == NULL)
    {
        printf("MEMORY ALLOCATION FAILED !!!");
        return NULL;
    }

    return node;
}



kdt* insert(kdt *root, int *arr, int depth)
{
    int i;

    if(root == NULL)
    {
        kdt *temp;
        temp = allocate();
        if (temp == NULL)
        {
            printf("MEMORY ALLOCATION FAILED !!!");
            return NULL;
        }
        for(i=0;i<k;i++)
            temp->data[i] = arr[i];

        return root;
    }
    
    if (arr[depth%k] > root->data[depth%k])
        root = insert(root->right , arr , depth+1);
    else
        root = insert(root->left , arr , depth+1);

    return root;
}



kdt* search(kdt* root,int arr[],int depth){
    if(root==NULL)
    {
        return NULL;
    }

    if(root->data[depth%k] == arr[depth%k])
    {
        int flag=1;
        for(int i=0;i<k;i++)
        {
            if(root->data[i]!=arr[i])
            {
                flag=0;
                break;
            }
        }
        
        if(flag)
            return root;
        else 
            return search(root->left,arr,depth+1);
        
    }

    else if(root->data[depth%k] > arr[depth%k])
    {
        return search(root->left,arr,depth+1);
    }
    else
    {
        return search(root->right,arr,depth+1);
    }
}



int main()
{
    return 0;    
}
