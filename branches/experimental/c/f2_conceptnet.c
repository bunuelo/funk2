// 
// Copyright (c) 2007-2009 Bo Morgan.
// All rights reserved.
// 
// Author: Bo Morgan
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

#include "funk2.h"

// conceptnet_relation primobject definition

defprimobject__static_slot(conceptnet_relation__type,          0);
defprimobject__static_slot(conceptnet_relation__left_concept,  1);
defprimobject__static_slot(conceptnet_relation__right_concept, 2);

f2ptr __conceptnet_relation__symbol = -1;

f2ptr f2conceptnet_relation__new(f2ptr cause, f2ptr type, f2ptr left_concept, f2ptr right_concept) {
  if (__conceptnet_relation__symbol == -1) {__conceptnet_relation__symbol = f2symbol__new(cause, strlen("conceptnet_relation"), (u8*)"conceptnet_relation");}
  f2ptr this = f2__primobject__new(cause, __conceptnet_relation__symbol, 3, nil);
  f2conceptnet_relation__type__set(         this, cause, type);
  f2conceptnet_relation__left_concept__set( this, cause, left_concept);
  f2conceptnet_relation__right_concept__set(this, cause, right_concept);
  return this;
}

boolean_t raw__conceptnet_relationp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__conceptnet_relation(this, cause));}
f2ptr f2__conceptnet_relationp(f2ptr this, f2ptr cause) {return f2bool__new(raw__conceptnet_relationp(this, cause));}


// conceptnet_graph primobject definition

defprimobject__static_slot(conceptnet_graph__relations, 0);

f2ptr __conceptnet_graph__symbol = -1;

f2ptr f2conceptnet_graph__new(f2ptr cause, f2ptr relations) {
  if (__conceptnet_graph__symbol == -1) {__conceptnet_graph__symbol = f2symbol__new(cause, strlen("conceptnet_graph"), (u8*)"conceptnet_graph");}
  f2ptr this = f2__primobject__new(cause, __conceptnet_graph__symbol, 1, nil);
  f2conceptnet_graph__relations__set( this, cause, relations);
  return this;
}

boolean_t raw__conceptnet_graphp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__conceptnet_graph(this, cause));}
f2ptr f2__conceptnet_graphp(f2ptr this, f2ptr cause) {return f2bool__new(raw__conceptnet_graphp(this, cause));}

//<http://conceptnet.media.mit.edu/assertion/1112793> conceptnet:LeftConcept <http://conceptnet.media.mit.edu/concept/1003777>;
// conceptnet:RelationType <http://conceptnet.media.mit.edu/reltype/IsA>;
// conceptnet:RightConcept <http://conceptnet.media.mit.edu/concept/1003230>;
// conceptnet:LeftText "Hockey";
// conceptnet:RightText "a sport";
// conceptnet:FrameId <http://conceptnet.media.mit.edu/frame/1385>;
// conceptnet:Language <http://conceptnet.media.mit.edu/language/en>;
// conceptnet:Creator <http://conceptnet.media.mit.edu/user/8362>;
// conceptnet:Score 66; conceptnet:Sentence "Hockey is a sport played in an arena".

#define max_concept_line_len 4096

// this is a quick hack to load the conceptnet r3 file format into conceptnet1 format triples: [relation-type left-concept right-concept]

f2ptr raw__conceptnet_relation__new_read_from_file_descriptor(f2ptr cause, int fd) {
  s64 line_len = 0;
  u8  read_buffer[max_concept_line_len];
  {
    boolean_t done = boolean__false;
    s64 index = 0;
    do {
      char ch;
      size_t read_num = read(fd, &ch, 1);
      if (read_num != 1 || ch == '\r' || ch == '\n') {
	done = boolean__true;
      } else {
	if (index < max_concept_line_len) {
	  read_buffer[index] = ch;
	}
	index ++;
      }
    } while (! done);
    if (index == 0) {
      return nil;
    }
    if (index >= max_concept_line_len) {
      return nil;
    }
    read_buffer[index] = 0;
    line_len = index;
  }
  if (line_len == 0) {
    return nil;
  }
  
  f2ptr type          = nil;
  f2ptr left_concept  = nil;
  f2ptr right_concept = nil;
  
  {
    boolean_t done = boolean__false;
    int       semicolon_count = 0;
    s64 index = 0;
    while (! done) {
      if (read_buffer[index] == ';') {
	semicolon_count ++;
	if (semicolon_count == 2) {
	  boolean_t find_type_done = boolean__false;
	  s64 find_type_index = index;
	  while (! find_type_done) {
	    if (read_buffer[find_type_index] == '/') {
	      s64 type_start_index = find_type_index + 1;
	      s64 type_end_index   = index - 1;
	      s64 type_len = type_end_index - type_start_index;
	      type = f2symbol__new(cause, type_len, read_buffer + type_start_index);
	      find_type_done = boolean__true;
	    } else if (find_type_index == 0) {
	      return nil;
	    } else {
	      find_type_index --;
	    }
	  }
	} else if (semicolon_count == 4) {
	  boolean_t find_left_done = boolean__false;
	  s64 find_left_index = index - 2;
	  while (! find_left_done) {
	    if (read_buffer[find_left_index] == '\"') {
	      s64 left_start_index = find_left_index + 1;
	      s64 left_end_index   = index - 1;
	      s64 left_len = left_end_index - left_start_index;
	      left_concept = f2symbol__new(cause, left_len, read_buffer + left_start_index);
	      find_left_done = boolean__true;
	    } else if (find_left_index == 0) {
	      return nil;
	    } else {
	      find_left_index --;
	    }
	  }
	} else if (semicolon_count == 5) {
	  boolean_t find_right_done = boolean__false;
	  s64 find_right_index = index - 2;
	  while (! find_right_done) {
	    if (read_buffer[find_right_index] == '\"') {
	      s64 right_start_index = find_right_index + 1;
	      s64 right_end_index   = index - 1;
	      s64 right_len = right_end_index - right_start_index;
	      right_concept = f2symbol__new(cause, right_len, read_buffer + right_start_index);
	      find_right_done = boolean__true;
	    } else if (find_right_index == 0) {
	      return nil;
	    } else {
	      find_right_index --;
	    }
	  }
	}
      }
      
      if (index >= line_len) {
	done = boolean__true;
      } else {
	index ++;
      }
    }
  }
  
  f2ptr conceptnet_relation = f2conceptnet_relation__new(cause, type, left_concept, right_concept);
  return conceptnet_relation;
}

f2ptr raw__conceptnet_graph__load_r3_format(f2ptr cause, u8* filename) {
  int fd = open((char*)filename, O_RDONLY);
  if (fd == -1) {
    return nil;
  }
  boolean_t done = boolean__false;
  f2ptr relations     = nil;
  f2ptr relation_iter = nil;
  do {
    f2ptr relation = raw__conceptnet_relation__new_read_from_file_descriptor(cause, fd);
    if (! relation) {
      done = boolean__true;
    } else {
      f2ptr new_cons = f2cons__new(cause, relation, nil);
      if (! relation_iter) {
	relation_iter = new_cons;
	relations     = relation_iter;
      } else {
	f2cons__cdr__set(relation_iter, cause, new_cons);
	relation_iter = new_cons;
      }
    }
  } while (! done);
  f2ptr conceptnet = f2conceptnet_graph__new(cause, relations);
  close(fd);
  return conceptnet;
}

f2ptr f2__conceptnet_graph__load_r3_format(f2ptr cause, f2ptr filename) {
  if (! raw__stringp(filename, cause)) {
    return f2larva__new(cause, 1);
  }
  s64   filename_length = f2string__length(filename, cause);
  u8* filename_str = (u8*)alloca(filename_length + 1);
  f2string__str_copy(filename, cause, filename_str);
  filename_str[filename_length] = 0;
  return raw__conceptnet_graph__load_r3_format(cause, filename_str);
}
def_pcfunk1(conceptnet_graph__load_r3_format, filename, return f2__conceptnet_graph__load_r3_format(this_cause, filename));

f2ptr f2__conceptnet_graph__new_left_concept_relations_hash(f2ptr cause, f2ptr this) {
  if (! raw__conceptnet_graphp(this, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr concept_relations_hash = f2__hashtable__new(cause, 20);
  f2ptr relation_iter = f2conceptnet_graph__relations(this, cause);
  while (relation_iter) {
    f2ptr relation       = f2cons__car(relation_iter, cause);
    f2ptr left_concept   = f2conceptnet_relation__left_concept(relation, cause);
    f2ptr old_hash_value = f2hashtable__lookup_value(concept_relations_hash, cause, left_concept);
    f2ptr new_hash_value = f2cons__new(cause, relation, old_hash_value);
    f2__hashtable__add_keyvalue_pair(cause, concept_relations_hash, left_concept, new_hash_value);
  }
  return concept_relations_hash;
}
def_pcfunk1(conceptnet_graph__new_left_concept_relations_hash, this, return f2__conceptnet_graph__new_left_concept_relations_hash(this_cause, this));

f2ptr f2__conceptnet_graph__new_right_concept_relations_hash(f2ptr cause, f2ptr this) {
  if (! raw__conceptnet_graphp(this, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr concept_relations_hash = f2__hashtable__new(cause, 20);
  f2ptr relation_iter = f2conceptnew_graph__relations(this, cause);
  while (relation_iter) {
    f2ptr relation       = f2cons__car(relation_iter, cause);
    f2ptr right_concept  = f2conceptnet_relation__right_concept(relation, cause);
    f2ptr old_hash_value = f2hashtable__lookup_value(concept_relations_hash, cause, right_concept);
    f2ptr new_hash_value = f2cons__new(cause, relation, old_hash_value);
    f2__hashtable__add_keyvalue_pair(cause, concept_relations_hash, right_concept, new_hash_value);
  }
  return concept_relations_hash;
}
def_pcfunk1(conceptnet_graph__new_right_concept_relations_hash, this, return f2__conceptnet_graph__new_right_concept_relations_hash(this_cause, this));

// **

void f2__conceptnet__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __conceptnet_relation__symbol = f2symbol__new(cause, strlen("conceptnet_relation"), (u8*)"conceptnet_relation");
  __conceptnet_graph__symbol    = f2symbol__new(cause, strlen("conceptnet_graph"),    (u8*)"conceptnet_graph");
}

void f2__conceptnet__initialize() {
  pause_gc();
  f2__conceptnet__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __conceptnet_relation__symbol, nil);
  environment__add_var_value(cause, global_environment(), __conceptnet_graph__symbol, nil);
  
  f2__primcfunk__init__1(conceptnet_graph__load_r3_format,                   filename);
  f2__primcfunk__init__1(conceptnet_graph__new_left_concept_relations_hash,  this);
  f2__primcfunk__init__1(conceptnet_graph__new_right_concept_relations_hash, this);
  
  resume_gc();
  try_gc();
}

