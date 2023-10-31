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


int main()
{
    return 0;    
}