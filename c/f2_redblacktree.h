// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
// 
// Permission to use, copy, modify and distribute this software and its
// documentation is hereby granted, provided that both the copyright
// notice and this permission notice appear in all copies of the
// software, derivative works or modified versions, and any portions
// thereof, and that both notices appear in supporting documentation.
// 
// BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
// BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
// WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
// 
// Bo Morgan requests users of this software to return to bo@mit.edu any
// improvements or extensions that they make and grant Bo Morgan the
// rights to redistribute these changes.
// 

#ifndef F2__REDBLACKTREE__H
#define F2__REDBLACKTREE__H

#include "f2_archconfig.h"
#include "f2_global.h"

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
  ptr         memorypool_beginning;
  rbt_node_t* head;
} rbt_tree_t;

void        rbt_node__print(rbt_node_t* node);
void        rbt_tree__init(rbt_tree_t* tree, rbt_node_t* head, ptr memorypool_beginning);
void        rbt_tree__reinit(rbt_tree_t* tree, ptr new_memorypool_beginning);
void        rbt_tree__free_all_nodes(rbt_tree_t* tree);
boolean_t   rbt_tree__empty(rbt_tree_t* tree);
void        rbt_tree__print(rbt_tree_t* tree);
void        rbt_tree__insert(rbt_tree_t* tree, rbt_node_t* node);
void        rbt_tree__remove(rbt_tree_t* tree, rbt_node_t* node);
rbt_node_t* rbt_tree__minimum(rbt_tree_t* tree);
rbt_node_t* rbt_tree__maximum(rbt_tree_t* tree);
rbt_node_t* rbt_tree__minimum_not_less_than(rbt_tree_t* tree, f2size_t size);
int         rbt_tree__size(rbt_tree_t* tree);
rbt_node_t* rbt_node__next(rbt_node_t* node);
rbt_node_t* rbt_node__prev(rbt_node_t* node);
int         rbt_node__is_valid(rbt_node_t* node);
int         rbt_tree__is_valid(rbt_tree_t* tree);
void        rbt_tree__load_from_stream(rbt_tree_t* tree, int fd);
void        rbt_tree__save_to_stream(rbt_tree_t* tree, int fd);

extern void f2__redblacktree__initialize();

#endif // F2__REDBLACKTREE__H

