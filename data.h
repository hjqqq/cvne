#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct Item
{
	struct Item* prev;
	struct Item* next;
	void* val;
};

struct Item* build_first_item(void* val);
void add_after(struct Item* item, void* val);
void add_before(struct Item* item, void* val);
void del_item(struct Item* item);
void free_item(struct Item* item, void (*free_func)(void*));
void iterate_list(struct Item* item, void (*func)(void*));
void del_list(struct Item* item);
void free_list(struct Item* item, void (*free_func)(void*));

#endif

