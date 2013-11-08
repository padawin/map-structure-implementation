#include "map.h"
#include <string.h>

/**
 * Library to use map structures acting as associative arrays.
 *
 * The current features are:
 * - search an item from a key
 * - insert an item
 * - update an item
 * - delete an item
 */


char _map_search_sub_collection(map *collection, const char *key, const size_t key_len, int *item_index, int start_index, int end_index);

/**
 * Function to search an entry from a given key in a collection
 *
 * @param const char *key The key to search
 * @param map *collection The collection
 * @return void * The entry corresponding to the key in the collection, NULL if
 * 		does not exist
 */
void *map_get_entry(const char *key, map *collection)
{
	void *item;
	int index;
	char found;

	found = _map_search_sub_collection(collection, key, strlen(key), &index, 0, collection->items_number - 1);

	if (!found) {
		item = NULL;
	}
	else {
		item = collection->items[index].item;
	}

	return item;
}

/**
 * Function to add or update an entry from a given key.
 * If an entry already exist with the given key, it will be replaced with
 * the new value.
 *
 * @param const char *key Key to update or insert
 * @param void *entry Entry which must be stored for the given key
 * @param map *collection Collection to update
 * @return int MAP_ENTRY_UPDATED if a value has been updated, MAP_ENTRY_ADDED if
 * 		no entry existed for the given key
 */
int map_add_entry(
	const char *key,
	void *entry,
	map *collection
)
{
	// find index where entry must be inserted
	int index, ret, right_bound;
	char found;

	right_bound = collection->items_number - 1;
	// empty collection
	if (right_bound == -1) {
		right_bound = 0;
	}

	found = _map_search_sub_collection(
		collection,
		key,
		strlen(key),
		&index,
		0,
		right_bound
	);

	if (!found) {
		if (collection->items_number == collection->total_items_number) {
			return MAP_FULL;
		}

		map_item item;
		item.key = (char *) key;
		item.index = index;
		item.item = entry;

		if (collection->items_number == 0) {
			collection->items[0] = item;
		}
		else {
			int i;
			for (i = collection->items_number; i > index + 1; i--) {
				collection->items[i] = collection->items[i - 1];
			}
			collection->items[index + 1] = item;
		}
		collection->items_number++;
		index++;
		ret = MAP_ENTRY_ADDED;
	}
	else {
		// delete the previous item ?
		// set the new one
		collection->items[index].item = entry;
		ret = MAP_ENTRY_UPDATED;
	}

	// return entry's index
	return ret;
}

/**
 * Function to delete an entry.
 * Not implemented
 */
int map_remove_entry(const char *key, map *collection)
{
	return 1;
}

/**
 * Function to search an entry in a sub section of the collection.
 * The element is searched with a dichotomic search algorithm.
 * The function return a boolean value depending on if the key is found
 * in the collection or not. In any case, the index parameter will be updated.
 * If the key is found, the index value will be the item's index, else it'll be
 * the index of the left sibling of the searched key. Which means that if the
 * key is inserted, it's index will be the left sibling's +1
 *
 * @param map *collection The collection
 * @param const char *key The key to search
 * @param const size_t key_len The key's length
 * @param int *item_index The index of the searched item, modified by the
 * 		function
 * @param int start_index Left bound of the sub collection where the item is
 * 		searched
 * @param int end_index Right bound of the sub collection where the item is
 * 		searched
 * @return 1 if the key is found in the collection, 0 else
 */
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
	int middle_index;
	int comp_start, comp_end;

	if (collection->items_number == 0) {
		*item_index = -1;
		return 0;
	}
	// check the boundaries
	else if (start_index == 0 && end_index == collection->items_number - 1) {
		comp_start = strncmp(key, collection->items[start_index].key, key_len);
		comp_end = strncmp(collection->items[end_index].key, key, key_len);
		// key must be placed before the first => not found
		if (comp_start < 0) {
			*item_index = -1;
			return 0;
		}
		else if (comp_start == 0) {
			*item_index = 0;
			return 1;
		}
		// key must be placed after the last => not found
		else if (comp_end <= 0) {
			*item_index = end_index;
			return comp_end == 0;
		}
	}

	// take middle index, rounded on low value
	middle_index = (start_index + end_index) / 2;

	int keys_comp = strncmp(collection->items[middle_index].key, key, key_len);

	// the key is found or the search is finished and the key is not found
	if (keys_comp == 0 || start_index == end_index - 1) {
		*item_index = middle_index;
		ret = (keys_comp == 0);
	}
	else if (keys_comp > 0) {
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
