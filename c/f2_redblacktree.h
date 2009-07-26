#ifndef F2__REDBLACKTREE__H
#define F2__REDBLACKTREE__H

#include "f2_archconfig.h"
#include "f2_global.h"
//#include "f2_memory.h"

typedef enum rbt_color_e {
  rbt_color__black = 0,
  rbt_color__red
} rbt_color_t;

struct rbt_node_s {
  struct rbt_node_s* parent;
  struct rbt_node_s* left;
  struct rbt_node_s* right;
  rbt_color_t        color;
  f2size_t           key;
} __attribute__((__packed__));
typedef struct rbt_node_s rbt_node_t;

typedef struct rbt_tree_s {
  rbt_node_t* head;
} rbt_tree_t;

void        rbt_node__print(rbt_node_t* node);
void        rbt_tree__init(rbt_tree_t* tree, rbt_node_t* head);
void        rbt_tree__print(rbt_tree_t* tree);
void        rbt_tree__insert(rbt_tree_t* tree, rbt_node_t* node);
void        rbt_tree__remove(rbt_tree_t* tree, rbt_node_t* node);
rbt_node_t* rbt_tree__minimum(rbt_tree_t* tree);
rbt_node_t* rbt_tree__maximum(rbt_tree_t* tree);
rbt_node_t* rbt_node__next(rbt_node_t* node);
rbt_node_t* rbt_node__prev(rbt_node_t* node);
int         rbt_node__is_valid(rbt_node_t* node);
int         rbt_tree__is_valid(rbt_tree_t* tree);

extern void f2__redblacktree__initialize();

#endif // F2__REDBLACKTREE__H

