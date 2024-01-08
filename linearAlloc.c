#include <stdio.h>

typedef struct {
    size_t size;
    size_t used;
    unsigned char *heapPtr;

}myLinearHeap;

void linear_alloc_init(size_t size, myLinearHeap *ptr){
    ptr->size = size;
    ptr->used = 0;
    ptr->heapPtr = (unsigned char *)malloc(size);   
    if(ptr->heapPtr == NULL){
        printf("Sorry but we cannot service your request, due to some fatal machine error");

    }
}

void *linear_alloc(myLinearHeap *heap,size_t requestSize){
    if(heap->size > requestSize + heap->used){
        printf("your request is to large for us to handle");
    }

    void *requestPtr = heap->used + heap->heapPtr;
    heap->used += requestSize;
    return requestPtr;

}

void reset_alloc(myLinearHeap * heap){
    heap->used = 0;
}

void destroy_alloc(myLinearHeap *ptr){
    free(ptr->heapPtr); 
    ptr->used  = 0;
    ptr->size  = 0;
    free(ptr);
}


int main()
{
    myLinearHeap myHeap;
    linear_alloc_init(&myHeap, 100);

    int *myArray = (int *)linear_alloc(&myHeap, 5);

    if(myArray != NULL)
    {
        for(int i = 0; i < 5; i++){
            myArray[i] = i;
        }
    }
    reset_alloc(&myHeap);   
    destroy_alloc(&myHeap);
}