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
	// find index where entry must be inserted
	int index;
	char found;

	index = -1;
	found = _map_search_sub_collection(
		collection,
		key,
		strlen(key),
		&index,
		0,
		collection->items_number - 1
	);

	if (!found) {
		// make room
		// insert it
		// set entry's index
		index++;
	}
	else {
		// delete the previous item ?
		// set the new one
		collection->items[index] = *entry;
	}

	// return entry's index
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
	// check bounds ?

	char ret;
	// take middle index, rounded on low value
	int middle_index = start_index + (end_index - start_index) / 2;

	int keys_comp = strncmp(collection->items[middle_index].key, key, key_len);
	// the key is found or the search is finished and the key is not found
	if (keys_comp == 0 || start_index == end_index - 1) {
		*item_index = middle_index;
		ret = (keys_comp == 0);
	}
	else if (keys_comp > 0) {// else if collection[middle_index]->key > key
		ret = _map_search_sub_collection(
			collection,
			key,
			key_len,
			item_index,
			start_index,
			middle_index
		);
	}
	else {
		ret = _map_search_sub_collection(
			collection,
			key,
			key_len,
			item_index,
			middle_index,
			end_index
		);
	}

	return ret;
}
