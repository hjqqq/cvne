#include "data.h"

struct Item* build_first_item(void* val)
{
	struct Item* new = malloc(sizeof(struct Item));
	new->next = NULL;
	new->prev = NULL;
	new->val = val;
	return new;
}

void add_after(struct Item* item, void* val)
{
	struct Item* new = malloc(sizeof(struct Item));
	new->next = item->next;
	new->prev = item;
	item->next = new;
	new->val = val;
}

void add_before(struct Item* item, void* val)
{
	struct Item* new = malloc(sizeof(struct Item));
	new->prev = item->prev;
	new->next = item;
	item->prev = new;
	new->val = val;
}

void del_item(struct Item* item)
{
	if(item->next)
		item->next->prev = item->prev;
	if(item->prev)
		item->prev->next = item->next;
	free(item);
}

void free_item(struct Item* item, void (*free_func)(void*))
{
	free_func(item->val);
	del_item(item);
}

void iterate_list(struct Item* item, void (*func)(void*))
{
	struct Item* cur = item->next;
	func(item);
	while(cur)
	{
		func(cur->val);
		cur = cur->next;
	}
	cur = item->prev;
	while(cur)
	{
		func(cur->val);
		cur = cur->prev;
	}
}

void del_list(struct Item* item)
{
	while(item->next)
		del_item(item->next);
	while(item->prev)
		del_item(item->prev);
	del_item(item);
}

void free_list(struct Item* item, void (*free_func)(void*))
{
	while(item->next)
		free_item(item->next, free_func);
	while(item->prev)
		free_item(item->prev, free_func);
	free_item(item, free_func);
}

