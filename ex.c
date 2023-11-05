#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


typedef struct kdt
{
    int *data;
    struct kdt *left,*right;
} kdt;


int k=-1;
int K;
double min_dis_inef=INFINITY;


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
        root=temp;
        return root;
    }
    
    if (arr[depth%k] < root->data[depth%k])
        root->left = insert(root->left, arr , depth+1);
    else
        root->right = insert(root->right , arr , depth+1);

    return root;
}






kdt* search(kdt* root,int arr[],int depth)
{
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
        else if(root->data[(depth+1)%k] > arr[(depth+1)%k])
        {
            return search(root->left,arr,depth+1);
        }
        else
        {
            return search(root->right,arr,depth+1);
        }
        
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







void inorder(kdt* root)//Print the inorder traversal of the tree
{
    if(root==NULL)
        return;

    inorder(root->left);
    {
        printf("(");

        for (int i = 0; i < k; i++)
        {
            printf("%d%s",root->data[i] , (i<k-1)? "," : "");
        }

        printf(") ");
    }

    inorder(root->right);

    return;
}








void nearestneighbour(kdt* root, int source[], int depth, kdt* nearest[], double nearestDist[])
{
    if(root==NULL) 
        return;

    
    double dist = distance_parameter(root->data,source);

    for(int i=0;i<K;i++)
    {
        if(dist<nearestDist[i])
        {
            for(int j=K-1;j>i;j--)
            {
                nearestDist[j] = nearestDist[j-1];
                nearest[j] = nearest[j-1];
            }
            nearestDist[i] = dist;
            nearest[i] = root;
            break;
        }
    }

    if(source[depth%k] < root->data[depth%k])
    {
        nearestneighbour(root->left,source,depth+1,nearest,nearestDist);
    }
    else
    {
        nearestneighbour(root->right,source,depth+1,nearest,nearestDist);
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
    char choice;
    kdt *root=NULL;
    int count=1;

    loop:
    printf("\n*********************************************");
    printf("\nI: Insert a point\nF: Insert using file\nS: Search\nN: Finding nearest neighbour(Using K-D Tree)\nT: Inorder Traversal\nE: Finding Nearest neighbour(Using a naive approach)\nQ: Quit\n");
    fflush(stdin);
    scanf(" %c", &choice);
    
    switch (toupper(choice))
    {
    case 'I':
        {
            if (count)
            {
                 printf("Enter the value of K: ");
                 scanf("%d",&k);
                 count=0;
            }

            printf("Enter the element: ");
            int s[k];
            
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            root = insert(root,s,0);
            goto loop;
        }
    break;

    case 'S':
        {
            printf("Enter the search element : ");
            int s[k];

            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            if((search(root,s,0))!=NULL)
            printf("Found");

            else printf("Not found");
            goto loop;

        }
    break;

    case 'N':
        {
            
            printf("Enter the coordinates : ");
            int s[k];
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }
            printf("Enter the number of nearest neighbours to find : ");
            scanf("%d",&K);

            kdt** nearest = (kdt**)malloc(K*sizeof(kdt*));
            double* nearestDist = (double*)malloc(K*sizeof(double));

            for (int i = 0; i < K; i++) {
                nearest[i] = NULL;
                nearestDist[i] = INFINITY;
            }

            nearestneighbour(root,s,0,nearest,nearestDist);
            
            if (nearest[0]==NULL)
            {
                printf("Can't find nearest neighbour\n");
            }
            else
            {
                
                for (int i = 0; i < K; i++)
                {
                    if(nearest[i]!=NULL)
                    {
                        printf("(");
                        for(int j = 0; j < k; j++)
                        {
                            printf("%d%s",nearest[i]->data[j] , (j<k-1)? "," : "");
                        }
                        printf(")\n");
                    }
                    else 
                        break; 
                }       
            }
            
            free(nearest);
            free(nearestDist);
            goto loop;
        }
    break;

    case 'F':
        {
            FILE * file = fopen ("Example.txt","r");//opening the file in read mode

            if(file==NULL)
            {
                printf("File can't be open.");
                goto loop;
            }

            int N;

            fscanf(file,"%d",&N);
            
            if(count)
            {
                fscanf(file,"%d",&k);
                count = 0 ;
            }

            else 
            {
                int temp;
                fscanf(file,"%d",&temp);

                if(temp!=k)
                {
                    printf("Dimension of file is different with the dimension of the tree");
                    goto loop;
                }
            }

            int s[k];

            for (int  i = 0; i < N; i++)
            {
            
                for (int i = 0; i < k; i++)
                {
                    fscanf(file,"%d",&s[i]);
                }

                root = insert(root,s,0);

                
            }

            goto loop;
            
        }
    break;
    
    case 'T':
        {
            inorder(root);
            printf("\n");
            goto loop;            
        }
    break;

    case 'Q':
        {
            return 0;         
        }
    break;

    case 'E':
    {
         printf("Enter the coordinates : ");
            int s[k];
            for (int i = 0; i < k; i++)
            {
                scanf("%d",&s[i]);
            }

            inefficient_NN(root,s);
            
            if (near_point_inef==NULL)
            {
                printf("Can't find nearest neighbour\n");
            }
            else
            {
                printf("{");
                for (int i = 0; i < k; i++)
                {
                    printf("%d%s",near_point_inef->data[i] , (i<k-1)? "," : "");
                }
                printf("}\n");
            }
            
            min_dis_inef=INFINITY;
            near_point_inef=NULL;
            goto loop;

    }
    
    break;


    default:
    {
        printf("Invalid input");
        goto loop;
    }
        break;
    }

    
    return 0;
}















