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
int num=0;






void swap(double *a,double *b) 
{
    double temp = *a;
    *a = *b;
    *b = temp;
}



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
        num++;
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



void func(kdt* x, int source[], int d , int K , double* k_distances , kdt** k_nearest){
    double dist_x = distance_parameter(x->data, source);
    for (int i = 0;i<K;i++) {
        if (dist_x < k_distances[i]) {
            for (int j=K-1;j>i;j--) {
                k_distances[j] = k_distances[j - 1];
                k_nearest[j] = k_nearest[j - 1];
            }
            k_distances[i] = dist_x;
            k_nearest[i] = x;
            break;
        }
    }

}






void nearestn(kdt *root, int source[], int d, int K, int* num_neighbors , double* k_distances , kdt** k_nearest)
{
    if (root==NULL) return;
    kdt *nextbranch = NULL;
    kdt *otherbranch = NULL;
    if (source[d%k] < root->data[d%k])
    {
        nextbranch = root->left;
        otherbranch = root->right;
    }
    else
    {
        nextbranch = root->right;
        otherbranch = root->left;
    }
    
    nearestn(nextbranch,source,d+1,K,num_neighbors,k_distances,k_nearest);
    func(root,source,d,K,k_distances,k_nearest);

    double dist_x = distance_parameter(root->data, source);
    double dist = fabs(root->data[d%k] - source[d%k]);

    if (dist < dist_x)
    {
        nearestn(otherbranch,source,d+1,K,num_neighbors,k_distances,k_nearest);
    }
}






void printKDTree(kdt* root, int depth) {
    if (root == NULL)
        return;

    int spacing = 4;
    printKDTree(root->right, depth + 1);
    for (int i = 0; i < depth * spacing; i++) {
        printf(" ");
    }
    for (int i=0;i<k;i++)
        printf("%d ", root->data[i]);
    printf("\n");

    printKDTree(root->left, depth+1);
}









int main()
{
    char choice;
    kdt *root=NULL;
    int count=1;

    loop:
    printf("\n*********************************************");
    printf("\nI: Insert a point\nF: Insert using file\nD: Display KD-Tree\nS: Search\nN: Finding k_nearest neighbour(Using K-D Tree)\nT: Inorder Traversal\nQ: Quit\n");
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

            int K;
            printf("Enter the number of k nearest neighbours to find : ");
            scanf("%d",&K);
            kdt* k_nearest[K];     // Array to store the k-k_nearest neighbor nodes
            double k_distances[K];  // Array to store the distances to k-k_nearest neighbors
            int num_neighbors = 0;
            for(int i=0;i<K;i++)
            {
                k_nearest[i]=NULL;
                k_distances[i]=INFINITY;
            }

            nearestn(root,s,0,K,&num_neighbors,k_distances,k_nearest);

            printf("The %d-k nearest neighbors are:\n", K);
            
            for (int i = 0; i < K; i++)
            {
                    if(k_nearest[i]!=NULL)
                    {
                        printf("(");
                        for(int j = 0; j < k; j++)
                            printf("%d%s",k_nearest[i]->data[j] , (j<k-1)? "," : "");
                        printf(")\n");
                    }
                    else 
                        break; 
            }
            goto loop;
        }
    break;

    case 'F':
        {
            FILE * file = fopen ("C:\\Users\\devan\\Downloads\\Example.txt","r");

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
            printf("The number of nodes are %d\n",num);
            inorder(root);
            printf("\n");
            goto loop;            
        }
    break;

    case 'D':
        {
            printKDTree(root,0);
            printf("\n\n");
            goto loop;            
        }
    break;

    case 'Q':
        {
            return 0;         
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














