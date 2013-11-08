#define MAP_ENTRY_UPDATED 1
#define MAP_ENTRY_ADDED 2
#define MAP_FULL -1

struct map_item {
	int index;
	char *key;
	void *item;
};

typedef struct {
	int items_number;
	int total_items_number;
	struct map_item *items;
} map;

void map_init(map *collection, int total_items_number);
void map_free(map *collection);
void *map_get_entry(const char *key, map *collection);
int map_add_entry(const char *key, void *entry, map *collection);
int map_remove_entry(const char *key, map *collection);
