#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define HEAP_CAPACITY 640


typedef struct{
    size_t  used;
    char data[HEAP_CAPACITY];
    myMemory *ptr;

}myMemory;

void init_alloc(myMemory *heap){
    memset(heap->data, 0, HEAP_CAPACITY);
    
}

void *heap_alloc(myMemory *heap, size_t requestSize){    
    assert(heap->used + requestSize <= HEAP_CAPACITY);
    void *  result = heap->data + heap->used;
    heap->used += requestSize;
    return result;
}

void free_mem(void *heap){
    (void) heap;
    asser(false && "TODO: no free_mem not implemented");
    
    
}

void heap_collect(){
    asser(false && "TODO: no heap_collect not implemented");

}

int main(){
    myMemory *myMem;

    init_alloc(myMem);
    heap_alloc(myMem, 26);

    for(int i = 0; i < 26; i++){
        myMem->data[i] = i + 'A';
    }

    return 0;
}