#include <string.h>

// This file should be either linked with a C program directly, or
// compiled into a shared library and loaded via LD_PRELOAD.
//
// It overrides malloc/realloc/free, calling the real ones while recording
// all currenly allocated memory in the heap_contents linked list.

extern void* __libc_malloc(size_t);
extern void* __libc_realloc(void*, size_t);
extern void* __libc_calloc(size_t, size_t);
extern void* __libc_free(void*);


// list management //////////////////////////////////////////////////////////////

// List to store all heap pointers created by malloc
typedef struct heap_node {
	void* pointer;
	size_t size;
	char source;			// m: malloc, c: callor, r: realloc
	struct heap_node* next;
} heap_node;
heap_node heap_contents = { .next = NULL };		// dummy node of a linked list of heap_node

static void insert_or_update_pointer(void* pointer, int size, char source, void* old_pointer) {
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

	heap_node* node = __libc_malloc(sizeof(*node));
	node->pointer = pointer;
	node->size = size;
	node->source = source;
	node->next = NULL;
	prev->next = node;
}

static void remove_pointer(void* pointer) {
	// remove from the heap_contents list
	for(heap_node* prev = &heap_contents; prev != NULL; prev = prev->next) {
		heap_node* node = prev->next;
		if(node != NULL && node->pointer == pointer) {
			prev->next = node->next;
			__libc_free(node);
			break;
		}
	}
}


// wrappers ////////////////

void* malloc(size_t size) {
	void* pointer = __libc_malloc(size);

	// libc seems to allocte 1024 bytes on start for its own use. Ignore it.
	if(!(heap_contents.next == NULL && size == 1024))
		insert_or_update_pointer(pointer, size, 'm', NULL);

	return pointer;
}

void* realloc(void* old_pointer, size_t size) {
	void* pointer = __libc_realloc(old_pointer, size);
	insert_or_update_pointer(pointer, size, 'r', old_pointer);
	return pointer;
}

void* calloc(size_t n, size_t size) {
	void* pointer = __libc_calloc(n, size);
	insert_or_update_pointer(pointer, n * size, 'c', NULL);
	return pointer;
}

void free(void* pointer) {
	remove_pointer(pointer);
	__libc_free(pointer);
}
