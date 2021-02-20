
#include <stdlib.h>

// malloc/free wrapper
// It simply calls the real malloc/free while recording all
// currenly allocated memory in the heap_contents linked list.


// List to store all heap pointers created by malloc
typedef struct heap_node {
	void* pointer;
	size_t size;
	struct heap_node* next;
} heap_node;
heap_node heap_contents = { .next = NULL };		// dummy node of a linked list of heap_node


void* __real_malloc(size_t);
void __real_free(void*);

void* __wrap_malloc(size_t size) {
	void* pointer = __real_malloc(size);

	// add to the end of the heap_contents list
	heap_node* prev = &heap_contents;
	for(prev = &heap_contents; prev->next != NULL; prev = prev->next)
		;
	heap_node* node = __real_malloc(sizeof(*node));
	node->pointer = pointer;
	node->size = size;
	node->next = NULL;
	prev->next = node;

	return pointer;
}

void __wrap_free(void* ptr) {
	__real_free(ptr);

	// remove from the heap_contents list
	for(heap_node* prev = &heap_contents; prev != NULL; prev = prev->next) {
		heap_node* node = prev->next;
		if(node->pointer == ptr) {
			prev->next = node->next;
			__real_free(node);
			break;
		}
	}
}



