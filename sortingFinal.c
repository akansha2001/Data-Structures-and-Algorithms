

# include <stdio.h>
# include <stdlib.h>
#include <time.h>


//bubble sort
void bubble_sort(int *arr,int n)
{
    /*
    Bubble sort: larger elements "bubble" to the top for each pass through the array

    Time complexity (worst case): O(n^2) [worst case: array sorted in reverse order]
    Best case: O(n) [array is already sorted]
    */

    int t=0;//swapping variable

    for(int i=0;i<n-1;i++)//outer loop for number of passes
    {
        for(int j=0;j<n-i-1;j++)//inner loop for comparisons in each pass
        {
            if(arr[j]>arr[j+1])//swap so that the larger element can 'bubble' to the top
            {
                t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
            }
        }
        //at the end of each pass, the (n-i-1)th and higher locations hold the correct elements for final sorted array
    }

}

//selection sort
void selection_sort(int *arr,int n)
{
    /*
    Selection sort: for each pass, finds the next minimum element and places it in correct position. One swap per pass.

    Time complexity (all cases): O(n^2)
    */

    int t=0;//swapping variable
    int min=arr[0],p=0;

    for(int i=0;i<n-1;i++)//outer loop for number of passes
    {
        min=arr[i];//present minimum
        p=i;//position of minimum
        for(int j=i+1;j<n;j++)//inner loop to find the minimum element in the unsorted (i+1 to n-1) portion of the array
        {
            if(arr[j]<min)//comparison, but no swapping until the inner loop completes its iterations
            {
                //reassign minimum element to new minimum and note it's position for sswapping
                min=arr[j];
                p=j;
            }
        }
        //swap once per iteration
        t=arr[i];
        arr[i]=arr[p];
        arr[p]=t;

        //at the end of (i)th iteration, the sub-array from index 0 to index i is sorted
    }

}

//insertion sort
void insert_sort(int *arr,int n)
{
    /*
    Insertion sort: a portion of the array is sorted at each iteration and compared against the next item in the array which
    is inserted at the correct position in the sub-array at the end of each iteration

    Time complexity (worst/average cases): O(n^2)
    Best case: O(n) [array is already sorted]
    */

    int t=0;//swap variable

    int p=0;


    for(int i=0;i<n-1;i++)//outer loop for number of passes; i represents length of sorted sublist
    {

        t=arr[i+1];// element to be compared against every element of the sublist

        p=i+1;//to keep track of the position where (i+1)th element will be inserted in the sorted sub-array to maintain sorted
        //property while increasing length of sub-array by 1 per pass

        for(int j=0;j<=i;j++)//checking against sublist elements
        {
            if(t<arr[j])//insertion location found
            {
                p=j;

                break;
            }
        }
        //shifting the higher elements to the right by one position to accomodate the (i+1)th element
        for(int k=i+1;k>p;k--)
        {
            arr[k]=arr[k-1];
        }

        arr[p]=t;

        //at the end of (i)th iteration we have a sorted sub-array in the front of the array
        //however, unlike selection sort and bubble sort, the positions of elements in the sorted sub-array are not
        //necessarily their final positions in the sorted array
    }

}

//quick sort
void quick_sort(int *arr,int l, int h)//divide and conquer
{
    /*
    Quick sort: picks an element as pivot and partitions the given array around the picked pivot
    Recursively sorts the remaining portions to the left and right of the pivot element until the entire array is sorted

    Time complexity (best/average cases): O(nlog(n))
    Worst case: O(n) [all elements are equal]
    */

    if (l<h)//there remains some portion of the array to sort [lower bound of portion to be sorted<upper bound]
    {

        int pi=part(arr,l,h);//index of the pivot element
        //after part() is called, the pivot element is at it's correct location in the final sorted array
        //the portion of the array above and below pivot (at index pi) remain to be sorted

        quick_sort(arr,l,(pi-1));//recursive call on lower part

        quick_sort(arr,(pi+1),h);//recursive call on upper part

    }

    //base case: array has been sorted. No statements to execute in this case

}

//function to place the pivot index in the correct position and return it's index
int part(int *arr, int l, int h)
{
    int pivot, down, up, t=0;

    pivot=arr[l];//pivot set to element at beginning position of sub-array
    down=l;//left marker
    up=h;//right marker

    while(down<up)//while left marker and right markers do not cross
    //crossing of markers indicates that the higher elements have already been shifted to the right and lower ones to the left
    //of final pivot index. A final swap remains between pivot and element at index 'up'
    {
        while(down<h && arr[down]<=pivot)
        //sub-array from (l+1) to h is scanned sequentially to locate an element > pivot
        //this element being > pivot must be to the right of pivot
            down++;

        while (arr[up]>pivot)
        //sub-array from h to (l+1) is scanned sequentially (reverse direction) to locate an element < pivot
        //this element being < pivot must be to the left of pivot
            up--;


        //swapping the next higher and lower elements found by searching the sub-array sequentially
        if (down<up)//swap only if the markers have not crossed
        {
            t=arr[down];
            arr[down]=arr[up];
            arr[up]=t;
        }
    }

    //while loop is terminated when markers have crossed. a final swap places pivot at proper location in array
    arr[l]=arr[up];
    arr[up]=pivot;

    //pivot index to be returned to calling function
    return up;
}

//merge sort
void merge_sort(int *arr,int l, int r)//divide and conquer
{

    /*
    Merge sort: splits the array in 2 parts recursively until sub-arrays of length 1 are obtained. Then "builds back"
    the final sorted array piece by piece, by comparing the elements of the arrays

    splits the input array into two halves, calls itself for the two halves, and then merges the two sorted halves.
    The merge() function is used for merging two halves.

    Time complexity (all cases): O(nlog(n)) [preferable for larger values of n]

    */

    if (r>l)//there remains some portion of the array to sort [lower bound of portion to be sorted<upper bound]
    {
        int m=(l+r)/2;//split at the middle

        merge_sort(arr,l,m);//recursive call to sort the left half
        merge_sort(arr,m+1,r);//recursive call to sort the right half

        merge(arr, l, r);//to combine two sorted halves

    }
    //base case: array has been sorted. No statements to execute in this case

}

void merge(int *arr, int l, int r)//to merge the 2 sorted halves of the array
{


    int m=(l+r)/2;//the mid point need not be passed explicitly and can be determined from the lower and upper bounds

    //we assume the sub-arrays from (l to m) and (m+1 to r) are sorted
    //they must be combined to produce a sorted sub-array from (l to r)

    int nl= m-l+1;//length of left temporary array
    int nr= r-m;//length of right temporary array

    int i,j;//indices for scanning the temporary arrays

    //arrays to copy the elements of arr
    int L[nl], R[nr];

    //copying

    for(i=0;i<nl;i++)
    {
        L[i]=arr[i+l];
    }

    for(j=0;j<nr;j++)
    {
        R[j]=arr[j+m+1];
    }

    //merging

    i=0;//initial index of left array
    j=0;//initial index of right array
    int k=l;//initial index of arr

    while(i<nl && j<nr)//if either temporary array is exhausted, while loop must be terminated as array index will
    //be out of bounds for the exhausted temporary array
    {

        if(L[i]<R[j])
        {
            arr[k]=L[i];
            //as we insert an element from R into arr, it's scanning index (j) must be incremented for the next comparison
            i++;
        }
        else
        {
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    //copying the remaining elements of L and R, if any. Either R or L will have been exhausted at this point
    while(i<nl)
    {
        arr[k]=L[i];
        k++;
        i++;
    }

    while(j<nr)
    {
        arr[k]=R[j];
        k++;
        j++;
    }
}


//display
void display(int *arr,int n)
{

    for(int i=0;i<n-1;i++)
        printf("%d, ",arr[i]);
    printf("%d\n",arr[n-1]);
    printf("*******************************\n");
}


//main to call the functions
void main()
{
    clock_t tb,ts,ti,tq,tm;//to compare the time taken to search for an element by either algorithm

    int *arr, *bub, *sel, *ins, *quik, *merg;
    int n;

    int ch;

    printf("Enter your choice\n");
    printf("*******************************\n");
    printf("1. Array of your choice\n");
    printf("2. Random array (average case)\n");
    printf("3. Sorted array\n");
    printf("4. Nearly sorted array\n");
    printf("5. Reverse sorted array\n");
    printf("*******************************\n");

    scanf("%d",&ch);


    switch(ch)
    {
    case 1:
        printf("Enter number of elements:");
        scanf("%d",&n);

        // Dynamically allocate memory using calloc()
        arr = bub = sel = ins = quik = merg = (int*)calloc(n,sizeof(int));

        for(int i=0;i<n;i++)
        {
            printf("Enter element %d for array \n",(i+1));
            scanf("%d",&arr[i]);
            bub[i]=sel[i]=ins[i]=quik[i]=merg[i]=arr[i];
        }

        printf("Displaying unsorted array\n");
        display(arr,n);

        //bubble sort

        bubble_sort(bub,n);

        printf("Displaying bubble sorted array\n");
        display(bub,n);

        //selection sort

        selection_sort(sel,n);

        printf("Displaying selection sorted array\n");
        display(sel,n);

        //insertion sort

        insert_sort(ins,n);

        printf("Displaying insertion sorted array\n");
        display(ins,n);

        //quick sort

        quick_sort(quik,0,n-1);

        printf("Displaying quick sorted array\n");
        display(quik,n);

        //merge sort

        merge_sort(merg,0,n-1);

        printf("Displaying merge sorted array\n");
        display(merg,n);

        break;

    case 2://unsorted
        printf("Enter number of elements:");
        scanf("%d",&n);

        // Dynamically allocate memory using calloc()
        arr = bub = sel = ins = quik = merg = (int*)calloc(n,sizeof(int));

        //create an unsorted array
        for(int i=0;i<n;i++)
        {
            bub[i]=sel[i]=ins[i]=quik[i]=merg[i]=rand();
        }
        printf("For unsorted input array\n");


        break;
    case 3://sorted
        printf("Enter number of elements:");
        scanf("%d",&n);

        // Dynamically allocate memory using calloc()
        arr = bub = sel = ins = quik = merg = (int*)calloc(n,sizeof(int));

        //create a sorted array
        for(int i=0;i<n;i++)
        {
            bub[i]=sel[i]=ins[i]=quik[i]=merg[i]=i;
        }
        printf("For sorted input array\n");

        break;
    case 4://nearly sorted
        printf("Enter number of elements:");
        scanf("%d",&n);

        // Dynamically allocate memory using calloc()
        arr = bub = sel = ins = quik = merg = (int*)calloc(n,sizeof(int));


        for(int i=0;i<n;i++)
        {
            bub[i]=sel[i]=ins[i]=quik[i]=merg[i]=i;
        }

        //making the array nearly sorted
        for(int k=0;k<n/10;k++)
        {
            bub[10*k]=sel[10*k]=ins[10*k]=quik[10*k]=merg[10*k]=k;
        }

        printf("For nearly sorted input array\n");

        break;
    case 5://reverse sorted
        printf("Enter number of elements:");
        scanf("%d",&n);

        // Dynamically allocate memory using calloc()
        arr = bub = sel = ins = quik = merg = (int*)calloc(n,sizeof(int));

        //create reverse sorted array
        for(int i=0;i<n;i++)
        {
            bub[i]=sel[i]=ins[i]=quik[i]=merg[i]=n-i;
        }

        printf("For reverse sorted input array\n");

        break;

    default: printf("Invalid input\n");
        break;

    }
    if(ch==2||ch==3||ch==4||ch==5)//cases for inputs not from the user
    {
        //bubble sort
        tb=clock();
        bubble_sort(bub,n);
        tb=clock()-tb;
        //selection sort
        ts=clock();
        selection_sort(sel,n);
        ts=clock()-ts;
        //insertion sort
        ti=clock();
        insert_sort(ins,n);
        ti=clock()-ti;
        //quick sort
        tq=clock();
        quick_sort(quik,0,n-1);
        tq=clock()-tq;
        //merge sort
        tm=clock();
        merge_sort(merg,0,n-1);
        tm=clock()-tm;

        printf("\nTime taken to sort array:\n\n");
        printf("Bubble sort: %.2f milliseconds\n",1000*(float)tb/(float)CLOCKS_PER_SEC);
        printf("Selection sort: %.2f milliseconds\n",1000*(float)ts/(float)CLOCKS_PER_SEC);
        printf("Insertion sort:%.2f milliseconds\n",1000*(float)ti/(float)CLOCKS_PER_SEC);
        printf("Quick sort:%.2f milliseconds\n",1000*(float)tq/(float)CLOCKS_PER_SEC);
        printf("Merge sort:%.2f milliseconds\n",1000*(float)tm/(float)CLOCKS_PER_SEC);

    }
}
