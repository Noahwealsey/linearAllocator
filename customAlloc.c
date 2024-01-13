#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define UNIMPLEMENTED do{\
    fprintf(stderr, "%s:%d: %s is not implemented yet", __FILE__, __LINE__, __func__);\
    abort();\
    }while(0)

#define HEAP_ALLOC_CAP 64000
#define CHUNK_LIST_CAP 1024


typedef struct {
    size_t size;
    void* ptr;
}Chunk;

typedef struct{
    size_t count;
    Chunk chunks[CHUNK_LIST_CAP ];
}Chunk_list;

char heap[HEAP_ALLOC_CAP] = {0};
size_t used = 0;

Chunk_list freed_chunks[CHUNK_LIST_CAP ] = {0};
Chunk_list alloced_chunks[CHUNK_LIST_CAP ] = {0};

void heap_dump_alloced_chunk(Chunk_list * list){
    printf("Status report: \nNO. of allocation %ld, address of first allocation\t%p\n", list->count, list->chunks[0].ptr);
    for (size_t i = 0; i < list->count; i++)
    {printf("Start: %p, size: %zu\n", 
        list->chunks[i].ptr,
        list->chunks[i].size
            );
    }    
}

int Chunk_insert(Chunk_list *list, void *start, size_t size){

    assert(size < CHUNK_LIST_CAP);
    list->chunks[list->count].ptr = start;
    list->chunks[list->count].size= size;

    for (int i = list->count; i > 0 && list->chunks[i].ptr< list->chunks[i - 1].ptr ; --i)   //sorting the memchunks
    {
        Chunk t = list->chunks[i];
        list->chunks[i]  =  list->chunks[i- 1];
        list->chunks[i - 1] = t;
    }

    list->count++;  

    return list->count;
}
 

void *heap_alloc(size_t requestSize){    

    if(requestSize > 0)
    {
        assert(used + requestSize < HEAP_ALLOC_CAP);
        void *  ptr = heap + used;
        used += requestSize;
        Chunk_insert(alloced_chunks, ptr, requestSize);
        return ptr;
    }
    else{
        return NULL;
    }
}


void Chunk_remove(Chunk_list *list, size_t index){
    (void) list;
    (void) index;
    UNIMPLEMENTED;
}

int Chunk_find(Chunk_list *list, void *ptr){
    (void) list;
    (void)ptr;
    UNIMPLEMENTED;
}

void free_mem(void *heap){
    int index = Chunk_find(alloced_chunks, heap);
    assert(index >= 0);
    Chunk_remove(alloced_chunks, (size_t) index);
    Chunk_insert(freed_chunks, alloced_chunks->chunks[index].ptr, alloced_chunks->chunks[index].size);

}

void heap_collect(){
    UNIMPLEMENTED;
}

int main(){
 
    for (size_t i = 0; i < 100; i++)
    {
        void *p = heap_alloc(i);
    }
    
    heap_dump_alloced_chunk(alloced_chunks);

    return 0;


}
