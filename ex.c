#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct kdt
{
    int *data;
    struct kdt *left,*right;
} kdt;


int k=-1;
double min_dis=INFINITY;
double min_dis_inef=INFINITY;

kdt* near_point=NULL;
kdt* near_point_inef=NULL;

double distance_parameter(int *arr1 , int *arr2)
{
    double interspace = 0;
    int i;
    for (i=0;i<k;i++)
        interspace += (arr1[i] - arr2[i])*(arr1[i] - arr2[i]);
    return sqrt(interspace);
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


void nearestneighbour(kdt* root,int source[],int depth)
{
    if(root==NULL) 
        return;
    
    else if(distance_parameter(root->data,source) < min_dis)
    {
        if(distance_parameter(root->data,source)!=0)
        {
            min_dis=distance_parameter(root->data,source);
            near_point=root;
        }
        
        nearestneighbour(root->left,source,depth+1);
        nearestneighbour(root->right,source,depth+1); 
    }
    else if (min_dis < fabs(root->data[depth%k]-source[depth%k]))
    {
        if ((root->data[depth%k]<source[depth%k]))
        {
            nearestneighbour(root->right,source,depth+1);
        }
        
        else
        {
            nearestneighbour(root->left,source,depth+1);
        }     
    }
    
    else
    {
        nearestneighbour(root->left,source,depth+1);
        nearestneighbour(root->right,source,depth+1);
    }
}


void inefficient_NN(kdt* root,int source[])//Inefficient way of finding the nearest neighbour (doing a inorder traversal and updating the nearest data)
{
     if(root==NULL)
    return;

    inefficient_NN(root->left,source);

    if((min_dis_inef > distance_parameter(root->data,source)) && ((distance_parameter(root->data,source))!=0))
    {
        min_dis_inef = distance_parameter(root->data,source);
        near_point_inef = root;
    }

    inefficient_NN(root->right,source);
    
    return;

}


int main()
{
    return 0;    
}
