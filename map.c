#include "map.h"
#include <string.h>
#include <stdio.h>

char _map_search_sub_collection(map *collection, const char *key, const size_t key_len, int *item_index, int start_index, int end_index);

void *map_get_entry(const char *key, map *collection)
{
	void *item;
	int *index;
	char found;

	found = _map_search_sub_collection(collection, key, strlen(key), index, 0, collection->items_number - 1);

	if (!found) {
		item = NULL;
	}
	else {
		item = collection->items[*index].item;
	}

	return item;
}

int map_add_entry(
	const char *key,
	map_item *entry,
	map *collection
)
{
	int index;
	return index;
}

int map_remove_entry(const char *key, map *collection)
{
	return 1;
}

char _map_search_sub_collection(
	map *collection,
	const char *key,
	const size_t key_len,
	int *item_index,
	int start_index,
	int end_index
)
{
	char ret;
	return ret;
}
