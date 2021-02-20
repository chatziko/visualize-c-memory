#include <stdlib.h>

// malloc/free wrapper
// It simply calls the real malloc/free while recording all
// currenly allocated memory in the heap_contents linked list.

void* __real_malloc(size_t);
void* __real_calloc(size_t, size_t);
void* __real_realloc(void*, size_t);
void __real_free(void*);


// list management //////////////////////////////////////////////////////////////

// List to store all heap pointers created by malloc
typedef struct heap_node {
	void* pointer;
	size_t size;
	struct heap_node* next;
} heap_node;
heap_node heap_contents = { .next = NULL };		// dummy node of a linked list of heap_node

static void insert_or_update_pointer(void* pointer, int size, void* old_pointer) {
	// add to the end of the heap_contents list
	heap_node* prev = &heap_contents;
	for(prev = &heap_contents; prev->next != NULL; prev = prev->next) {
		// for realloc, update the existing entry (to remain in the same position)
		if(prev->next->pointer == old_pointer) {
			prev->next->pointer = pointer;
			prev->next->size = size;
			return;
		}
	}

	heap_node* node = __real_malloc(sizeof(*node));
	node->pointer = pointer;
	node->size = size;
	node->next = NULL;
	prev->next = node;
}

static void remove_pointer(void* pointer) {
	// remove from the heap_contents list
	for(heap_node* prev = &heap_contents; prev != NULL; prev = prev->next) {
		heap_node* node = prev->next;
		if(node != NULL && node->pointer == pointer) {
			prev->next = node->next;
			__real_free(node);
			break;
		}
	}
}


// wrappers ////////////////

void* __wrap_malloc(size_t size) {
	void* pointer = __real_malloc(size);
	insert_or_update_pointer(pointer, size, NULL);
	return pointer;
}

void* __wrap_calloc(size_t n, size_t size) {
	void* pointer = __real_calloc(n, size);
	insert_or_update_pointer(pointer, n * size, NULL);
	return pointer;
}

void* __wrap_realloc(void* old_pointer, size_t size) {
	void* pointer = __real_realloc(old_pointer, size);
	insert_or_update_pointer(pointer, size, old_pointer);
	return pointer;
}

void __wrap_free(void* pointer) {
	remove_pointer(pointer);
	__real_free(pointer);
}



