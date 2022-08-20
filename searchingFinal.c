
# include <stdio.h>
# include <stdlib.h>
# include <time.h>


//binary search
int bin_search(int *arr, int l, int h, int n)
/*function for recursive binary search which returns index of item 'n' if found.
Else returns -1
We assume the array is sorted in ascending order*/
{

    /*
    Binary Search: array is split in two parts recursively until desired item is found or length of array is exhausted

    Time complexity (worst/average case): O(log(n)) [worst case: item not found in array or at either extremity]
    Best case: O(1) [match on middle element]
    */

    if (l<=h)//if the front pointer has not exceeded the rear pointer
    {
        int mid=(l+h)/2;//middle index at which the array (or it's sub-array) will be split

        if(arr[mid]==n)//item 'n' has been found
            return mid;

        if(arr[mid]>n)
            //item to be found must be in lower half of array, if present: recursive call on lower half
            return bin_search(arr,l,mid-1,n);

        if(arr[mid]<n)
            //item to be found must be in upper half of array, if present: recursive call on upper half
            return bin_search(arr,mid+1,h,n);
    }

    return -1;//base case of recursion (if item 'n' is not found)
}

//linear search
int lin_search(int *arr, int num, int n)
/*function for linear search which returns index of item 'num' if found.
Else returns -1
For comparison with binary sort, in this program we take a sorted array. However, it works for unsorted arrays as well*/
{

    /*
    Linear Search: array is scanned sequentially until item is found or length of array is  exhausted

    Time complexity (worst/average case): O(n) [worst case: element not found in array]
    Best case: O(1) [match on first element]
    */

    int i=0;//index for scanning the array

    while(i<n)//sequentially scanning the array to locate the desired element
    {
        if(arr[i]==num)//item has been located
            return i;//return the index to the calling function
        i++;//if item has not been located, move on to the next item
    }
    return -1;//item not found
}


//display function to print the array
void display(int *arr,int n)
{

    for(int i=0;i<n-1;i++)
        printf("%d, ",arr[i]);
    printf("%d\n",arr[n-1]);
    printf("*******************************\n");
}


//main function for function calls
void main()
{
    int *arr;
    int n;

    printf("Enter number of elements:");
    scanf("%d",&n);

    // Dynamically allocate memory using calloc()
    arr = (int*)calloc(n,sizeof(int));

    if(arr == NULL)//failure to allocate memory. array cannot be used
    {
        printf("memory cannot be allocated\n");
    }

    else//memory allocated successfully
    {
        //creating sorted array
        printf("Creating sorted array from 1 to %d \n\n",n);
        for(int i=0;i<n;i++)
        {
            arr[i]=i+1;
        }

        int num;//element to be found. input from user

        printf("Enter item to search for\n");
        scanf("%d",&num);

        clock_t t_bin, t_lin;//to compare the time taken to search for an element by either algorithm

        t_bin=clock();

        int pos1=bin_search(arr,0,n-1,num);

        t_bin=clock()-t_bin;

        t_lin=clock();

        int pos2=lin_search(arr,num,n);

        t_lin=clock()-t_lin;

        printf("\nBinary search results:\n");

        if(pos1==-1)
            printf("Item not found\n");
        else
            printf("Item found at index %d of array\n", pos1);

        printf("\nLinear search results:\n");

        if(pos2==-1)
            printf("Item not found\n");
        else
            printf("Item found at index %d of array\n", pos2);

        printf("\n Time taken for binary search: %.2f microseconds \n",1000000*(float)t_bin/(float)CLOCKS_PER_SEC);

        printf("\n Time taken for linear search: %.2f microseconds \n",1000000*(float)t_lin/(float)CLOCKS_PER_SEC);

    }
}

