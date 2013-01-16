
#include <toy3d/Toy3DCommon.h>
#include <toy3d/Toy3DPtrArray.h>

using namespace TOY3D;

#define DECIMALISM        10
#define MAX_RANK          128
#define MAX_NUM_LEN       4
#define TEST_MAX_NAME_LEN 16
#define TEST_NAME "pointer_"

typedef struct _IMG_INFO
{
    char name[TEST_MAX_NAME_LEN];
    int width;
    int height;
}IMG_INFO;


void add(TPtrArray & ptrAry, IMG_INFO **pptr, Uint n, Uint & atimes, Uint & failueTimes)
{
    Uint i, len;
    char str[MAX_NUM_LEN];
    IMG_INFO *imgInfo = *pptr;

    printf("Create pointers and append one half of them into array.\n");
    printf("And the rest will be inserted into the array.\n\n");

    len = n/2;
    for( i=0; i<n; i++)
    {
        imgInfo= (IMG_INFO *)malloc(sizeof(IMG_INFO));
        if(!imgInfo)
        {
            failueTimes++;
            printf("Malloc failed and append a null pointer.\n");
            ptrAry.append((TPointer)NULL);
            continue;
        }
        
        atimes++;
        memset(imgInfo, 0, sizeof(IMG_INFO));
        strncpy(imgInfo->name, TEST_NAME, strlen(TEST_NAME));
        memset(str, 0, MAX_NUM_LEN);
        itoa(i, str, DECIMALISM);
        strncat(imgInfo->name+strlen(TEST_NAME), str, sizeof(str));
        
        imgInfo->width = i;
        imgInfo->height = i;
        
        printf("The pointer %d with name %s is ok.\n", imgInfo, imgInfo->name);
        if(i<=len)
        {
            ptrAry.append((TPointer)imgInfo);
            continue;
        }

        ptrAry.insert((TPointer)imgInfo, ptrAry.getLength());
    }

    return;
}

void remove(TPtrArray & ptrAry, Uint & dtimes, Uint & numOfNullPtr)
{
    Bool rv;
    Uint i, len;
    IMG_INFO *imgInfo;

    printf("\n");
    printf("The next, we remove one half elements by index from array, and delete them.\n\n");
    
    len = ptrAry.getLength()/2;
    for(i=0; i<len; i++)
    {
        //removeByIndex is inefficient.
        imgInfo = (IMG_INFO *)ptrAry.removeByIndex(0);
        if(!imgInfo)
        {
            printf("Got a null pointer. Next.\n");
            numOfNullPtr++;
            continue;
        }
        
        printf("Pointer : %d, name : %s", imgInfo, imgInfo->name);
        DELETEANDNULL(imgInfo);
        printf(" deleted.\n");
        dtimes++;
    }
    
    printf("\n");
    printf("Then we remove one pointer by value.\n");
    
    imgInfo = (IMG_INFO *)ptrAry[0];
    rv = ptrAry.remove((TPointer)imgInfo);
    if( TRUE!=rv )
        printf("pointer %d doesn't exist.\n", imgInfo);
    else
    {
        printf("pointer %d is removed.\n", imgInfo);
        if(imgInfo)
        {
            DELETEANDNULL(imgInfo);
            dtimes++;
        }
        else
        {
            numOfNullPtr++;
        }
    }
    
    printf("\nThe next, we will delete the rest.\n\n");
    
    len = ptrAry.getLength();
    for(i=0; i<len; i++)
    {
        imgInfo = (IMG_INFO *)ptrAry[i];
        //imgInfo = (IMG_INFO *)ptrs.getElement(i);
        if(!imgInfo)
        {
            printf("We got a null pointer. Next.\n");
            numOfNullPtr++;
            continue;
        }
        
        printf("Pointer : %d, name : %s", imgInfo, imgInfo->name);
        DELETEANDNULL(imgInfo);
        printf("  deleted.\n");
        dtimes++;
    }

    return;
}

void statistics(Uint total, Uint mallocTimes, Uint failureTimes, Uint deleteTimes, Uint numOfNullPtr)
{
    printf("\n");
    printf("************************************************************\n");
    printf("The Statistical Result:\n");
    printf("Mallocing times : %u \n", mallocTimes);
    printf("Deleting times  : %u \n", deleteTimes);
    printf("Failure Times while mallocing : %u \n", failureTimes);
    printf("NULL PointerS while deleteing : %u \n", numOfNullPtr);
    printf("\n");

    if( (mallocTimes==deleteTimes)
        &&(failureTimes==numOfNullPtr)
        &&(total==(mallocTimes+numOfNullPtr)) )
    {
        printf("********************It's ok.********************\n");
    }
    else
    {
        printf("********************Error.********************\n");
    }

    printf("\n");
    printf("************************************************************\n");

    return;
}

void init(unsigned int n)
{
    Uint i;
    Uint len;
    Uint alloc_time, delete_time, atime_0, dtime_0;
    IMG_INFO *imgInfo = NULL;
    TPtrArray ptrAry;

    ptrAry.create();
    printf("create an pointer array with length %u.\n", ptrAry.getLength());

    printf("We use struct IMG_INFO for testing, \n");
    printf("and the names follow the rule as follow: %s_x, and the x is number.\n", TEST_NAME);

    alloc_time = 0;
    delete_time = 0;
    atime_0 = 0;
    dtime_0 = 0;
 
    add(ptrAry, &imgInfo, n, alloc_time, atime_0);

    printf("The length of array is %d, and the elements is as follows.\n", ptrAry.getLength() );
    len = ptrAry.getLength();
    for(i=0; i<len; i++)
    {
        printf("Pointer : %d.\n", ptrAry.getElement(i));
    }

    remove(ptrAry, delete_time, dtime_0);
    statistics(n, alloc_time, atime_0, delete_time, dtime_0);

    printf("At the end, we destroy the pointer array.\n");
    ptrAry.destroy();

    return;
}

int main(int argc, char** argv)
{
    char ans;
    unsigned int n;

    do 
    {
        n = 0;
        while(1)
        {
            printf("Please input an positive integer(less than %d): \n", MAX_RANK);
            scanf("%u", &n);
            fflush(stdin);
            if( n>0 && n<MAX_RANK)
                break;
            printf("Out of bound, again please.\n");
        }

        init(n);

        printf("Go on?(y/n)\n");
        scanf("%c", &ans);
        fflush(stdin);
    } while(ans=='y'||ans=='Y');

  	return 0;
}


