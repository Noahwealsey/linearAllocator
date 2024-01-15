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
    char* ptr;
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

void *show_current_index(){
    UNIMPLEMENTED;
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
    assert(index < list->count);
    for (size_t i = index; i < list->count - 1; i++)
    {
        list->chunks[i] = list->chunks[i+1];
    }
    list->count--;
}

int chunk_compar(const void *a, const void *b){
    const Chunk *a_ptr = a;
    const Chunk *b_ptr = b;
    printf("%s", __func__);
    return a_ptr->ptr - b_ptr->ptr;

}

int Chunk_find(Chunk_list *list, void *ptr){

    Chunk key = {
        .ptr = ptr
    };

    Chunk *desire = bsearch(&key, list->chunks,
            list->count, sizeof(list->chunks[0]),
            chunk_compar);
    
    printf("%d\n: %s", desire, __func__);

    if(desire != 0){
        assert(desire > 0);
        return (desire - list->chunks)/sizeof(list->chunks[0]);
    }
    else{
        return -1;
    }
}

void free_mem(void *heap){

    if(heap != NULL){
        const int index = Chunk_find(alloced_chunks, heap);

        printf("%d\n: %s", index, __func__);

        assert(index >= 0);
        Chunk_remove(alloced_chunks, (size_t) index);
        Chunk_insert(freed_chunks, alloced_chunks->chunks[index].ptr, alloced_chunks->chunks[index].size);
    }
}

void heap_collect(){
    UNIMPLEMENTED;
}

int main(){
 
    for (size_t i = 0; i < 10; i++)
    {
        void *p = heap_alloc(i);
        if(i%2 == 0){
            printf(free_mem(i));
        }
    }
    
    heap_dump_alloced_chunk(alloced_chunks);
    heap_dump_alloced_chunk(freed_chunks);

    return 0;


}
