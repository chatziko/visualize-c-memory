#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list_node {
	int value;
	struct list_node* next;
} ListNode;

typedef struct {
	int field1;
	float field2;
} MyStruct;



void local_vars_example() {
	int my_int = 1;
	float my_float = 2.0;
	int my_array[3] = {3, 4, 5};
	MyStruct my_struct = {.field1 = 1, .field2 = 2.0};

	if(1) {
		int block_scope = 1;
		printf("local_vars_example: %d\n", block_scope);
	}

	printf("local_vars_example: %d %f %d %d\n", my_int, my_float, my_array[0], my_struct.field1);
}

void pointer_example() {
	int foo = 1;
	int bar = 2;

	int* pointer = &foo;
	*pointer = 3;

	int** double_pointer = &pointer;
	*double_pointer = &bar;
	**double_pointer = 4;
}

void malloc_example() {
	int* my_int = malloc(sizeof(*my_int));
	*my_int = 1;

	float* my_float = malloc(sizeof(*my_float));
	*my_float = 2.0;

	int* my_int_array = malloc(3 * sizeof(*my_int_array));
	my_int_array[0] = 1;
	my_int_array[1] = 2;
	my_int_array[2] = 3;

	MyStruct* my_struct = malloc(sizeof(*my_struct));
	my_struct->field1 = 1;
	my_struct->field2 = 2;

	free(my_int);
	free(my_float);
	free(my_int_array);
	free(my_struct);
}

void string_example() {
	char string1[5];
	strcpy(string1, "foo");

	char* string2 = malloc(5);
	strcpy(string2, "bar");
	free(string2);
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap_example() {
	int foo = 1;
	int bar = 2;
	swap(&foo, &bar);
}

ListNode* create_node(int value) {
	ListNode* node = malloc(sizeof(*node));
	node->value = value;
	node->next = NULL;
	return node;
}

void list_example() {
	ListNode* first = create_node(0);
	first->next = create_node(1);
	first->next->next = create_node(2);

	free(first->next->next);
	free(first->next);
	free(first);
}

int recursive_function(int n) {
	int temp = 0;
	if(n > 0)
		temp = recursive_function(n - 1);

	return n + temp;
}

void recursion_example() {
	int result = recursive_function(3);
	printf("recursion_example: %d\n", result);
}

void memory_leak_example() {
	int* my_int;
	
	my_int = malloc(sizeof(*my_int));
	my_int = malloc(sizeof(*my_int));
	my_int = malloc(sizeof(*my_int));

	free(my_int);
}

	

int main() {
	local_vars_example();
	pointer_example();
	swap_example();
	malloc_example();
	string_example();
	recursion_example();
	list_example();
	memory_leak_example();

	printf("\nVisualization examples. To display them, start debugging (F5),\n");
	printf("open Debug Visualizer and type \"memory\" in the window that opens.\n\n");

	return 0;
}
