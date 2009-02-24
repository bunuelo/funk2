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

#ifndef F2__PACKET__H
#define F2__PACKET__H

#include "f2_funk2_node.h"
#include "f2_buffered_socket.h"
#include "f2_ptypes_memory.h"
#include "f2_scheduler.h"

#define funk2_start_of_packet_byte ((u8)'f')
#define funk2_channel_byte         ((u8)'2')
#define funk2_end_of_packet_byte0  ((u8)0x0d)
#define funk2_end_of_packet_byte1  ((u8)0x0a)

typedef enum funk2_packet_type_e {
  funk2_packet_type__pcs_request__register_peer                             = 0x01,
  funk2_packet_type__pcs_request__remote_computer_id_to_node_id             ,
  funk2_packet_type__pcs_respond__remote_computer_id_to_node_id             ,
  // end p2p network layer abstraction packets
  
  // causal event packets
  funk2_packet_type__pcs_request__know_of_event                              ,
  
  // begin funk2 accessible packets
  funk2_packet_type__pcs_request__client_request_received                    , // internal router packet wrapper packet
  funk2_packet_type__pcs_request__system__environment                        ,
  funk2_packet_type__pcs_respond__system__environment                        ,
  funk2_packet_type__pcs_request__memblock__creation_microseconds_since_1970 , //u64              (f2ptr this);
  funk2_packet_type__pcs_respond__memblock__creation_microseconds_since_1970 ,
  funk2_packet_type__pcs_request__f2ptype__raw                               , //ptype_t          (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2ptype__raw                               ,
  funk2_packet_type__pcs_request__f2ptype__cause                             , //f2ptr            (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2ptype__cause                             ,
  funk2_packet_type__pcs_request__f2ptype__cause__set                        , //f2ptr            (f2ptr cause, f2ptr this, f2ptr value);
  funk2_packet_type__pcs_respond__f2ptype__cause__set                        ,
  funk2_packet_type__pcs_request__f2integer__new                             , //f2ptr            (f2ptr cause, s64 i);
  funk2_packet_type__pcs_respond__f2integer__new                             ,
  funk2_packet_type__pcs_request__f2integer__i                               , //s64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2integer__i                               ,
  funk2_packet_type__pcs_request__f2double__new                              , //f2ptr            (f2ptr cause, double d);
  funk2_packet_type__pcs_respond__f2double__new                              ,
  funk2_packet_type__pcs_request__f2double__d                                , //double           (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2double__d                                ,
  funk2_packet_type__pcs_request__f2float__new                               , //f2ptr            (f2ptr cause, float f);
  funk2_packet_type__pcs_respond__f2float__new                               ,
  funk2_packet_type__pcs_request__f2float__f                                 , //float            (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2float__f                                 ,
  funk2_packet_type__pcs_request__f2pointer__new                             , //f2ptr            (f2ptr cause, ptr p);
  funk2_packet_type__pcs_respond__f2pointer__new                             ,
  funk2_packet_type__pcs_request__f2pointer__p                               , //ptr              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2pointer__p                               ,
  funk2_packet_type__pcs_request__f2gfunkptr__new                            , //f2ptr            (f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);
  funk2_packet_type__pcs_respond__f2gfunkptr__new                            ,
  funk2_packet_type__pcs_request__f2gfunkptr__new_from_f2ptr                 , //f2ptr            (f2ptr cause, f2ptr f2p);
  funk2_packet_type__pcs_respond__f2gfunkptr__new_from_f2ptr                 ,
  funk2_packet_type__pcs_request__f2gfunkptr__gfunkptr                       , //f2ptr            (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2gfunkptr__gfunkptr                       ,
  funk2_packet_type__pcs_request__f2gfunkptr__computer_id                    , //computer_id_t    (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2gfunkptr__computer_id                    ,
  funk2_packet_type__pcs_request__f2gfunkptr__pool_index                     , //pool_index_t     (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2gfunkptr__pool_index                     ,
  funk2_packet_type__pcs_request__f2gfunkptr__pool_address                   , //pool_address_t   (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2gfunkptr__pool_address                   ,
  funk2_packet_type__pcs_request__f2mutex__new                               , //f2ptr            (f2ptr cause);
  funk2_packet_type__pcs_respond__f2mutex__new                               ,
  funk2_packet_type__pcs_request__f2mutex__lock                              , //void             (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2mutex__lock                              ,
  funk2_packet_type__pcs_request__f2mutex__unlock                            , //void             (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2mutex__unlock                            ,
  funk2_packet_type__pcs_request__f2mutex__trylock                           , //int              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2mutex__trylock                           ,
  funk2_packet_type__pcs_request__f2char__new                                , //f2ptr            (f2ptr cause, char ch);
  funk2_packet_type__pcs_respond__f2char__new                                ,
  funk2_packet_type__pcs_request__f2char__ch                                 , //char             (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2char__ch                                 ,
  funk2_packet_type__pcs_request__f2string__new                              , //f2ptr            (f2ptr cause, u64 length, u8* init);
  funk2_packet_type__pcs_respond__f2string__new                              ,
  funk2_packet_type__pcs_request__f2string__length                           , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2string__length                           ,
  funk2_packet_type__pcs_request__f2string__elt                              , //u8               (f2ptr cause, f2ptr this, int index);
  funk2_packet_type__pcs_respond__f2string__elt                              ,
  funk2_packet_type__pcs_request__f2string__str_copy                         , //void             (f2ptr cause, f2ptr this, u8* str);
  funk2_packet_type__pcs_respond__f2string__str_copy                         ,
  funk2_packet_type__pcs_request__f2string__hash_value                       , //int              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2string__hash_value                       ,
  funk2_packet_type__pcs_request__f2symbol__new                              , //f2ptr            (f2ptr cause, u64 length, u8* init);
  funk2_packet_type__pcs_respond__f2symbol__new                              ,
  funk2_packet_type__pcs_request__f2symbol__length                           , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2symbol__length                           ,
  funk2_packet_type__pcs_request__f2symbol__hash_value                       , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2symbol__hash_value                       ,
  funk2_packet_type__pcs_request__f2symbol__elt                              , //u8               (f2ptr cause, f2ptr this, int index);
  funk2_packet_type__pcs_respond__f2symbol__elt                              ,
  funk2_packet_type__pcs_request__f2symbol__str_copy                         , //void             (f2ptr cause, f2ptr this, u8* str);
  funk2_packet_type__pcs_respond__f2symbol__str_copy                         ,
  funk2_packet_type__pcs_request__f2chunk__new                               , //f2ptr            (f2ptr cause, u64 length, byte* bytes);
  funk2_packet_type__pcs_respond__f2chunk__new                               ,
  funk2_packet_type__pcs_request__f2chunk__new_copy                          , //f2ptr            (f2ptr cause, f2ptr init_chunk);
  funk2_packet_type__pcs_respond__f2chunk__new_copy                          ,
  funk2_packet_type__pcs_request__f2chunk__length                            , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2chunk__length                            ,
  funk2_packet_type__pcs_request__f2chunk__bit8__elt                         , //u8               (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2chunk__bit8__elt                         ,
  funk2_packet_type__pcs_request__f2chunk__bit8__elt__set                    , //void             (f2ptr cause, f2ptr this, u64 index, u8 value);
  funk2_packet_type__pcs_respond__f2chunk__bit8__elt__set                    ,
  funk2_packet_type__pcs_request__f2chunk__bit16__elt                        , //u16              (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2chunk__bit16__elt                        ,
  funk2_packet_type__pcs_request__f2chunk__bit16__elt__set                   , //void             (f2ptr cause, f2ptr this, u64 index, u16 value);
  funk2_packet_type__pcs_respond__f2chunk__bit16__elt__set                   ,
  funk2_packet_type__pcs_request__f2chunk__bit32__elt                        , //u32              (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2chunk__bit32__elt                        ,
  funk2_packet_type__pcs_request__f2chunk__bit32__elt__set                   , //void             (f2ptr cause, f2ptr this, u64 index, u32 value);
  funk2_packet_type__pcs_respond__f2chunk__bit32__elt__set                   ,
  funk2_packet_type__pcs_request__f2chunk__bit64__elt                        , //u64              (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2chunk__bit64__elt                        ,
  funk2_packet_type__pcs_request__f2chunk__bit64__elt__set                   , //void             (f2ptr cause, f2ptr this, u64 index, u64 value);
  funk2_packet_type__pcs_respond__f2chunk__bit64__elt__set                   ,
  funk2_packet_type__pcs_request__f2chunk__cfunk_jump                        , //f2ptr            (f2ptr cause, f2ptr this, f2ptr thread, f2ptr env, f2ptr args);
  funk2_packet_type__pcs_respond__f2chunk__cfunk_jump                        ,
  funk2_packet_type__pcs_request__f2chunk__bytecode_jump                     , //int              (f2ptr cause, f2ptr this, f2ptr thread);
  funk2_packet_type__pcs_respond__f2chunk__bytecode_jump                     ,
  funk2_packet_type__pcs_request__f2chunk__send                              , //f2ptr            (f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
  funk2_packet_type__pcs_respond__f2chunk__send                              ,
  funk2_packet_type__pcs_request__f2chunk__recv                              , //f2ptr            (f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
  funk2_packet_type__pcs_respond__f2chunk__recv                              ,
  funk2_packet_type__pcs_request__f2simple_array__new                        , //f2ptr            (f2ptr cause, u64 length, ptr dptr_ptr);
  funk2_packet_type__pcs_respond__f2simple_array__new                        ,
  funk2_packet_type__pcs_request__f2simple_array__new_copy                   , //f2ptr            (f2ptr cause, u64 length, f2ptr init_array);
  funk2_packet_type__pcs_respond__f2simple_array__new_copy                   ,
  funk2_packet_type__pcs_request__f2simple_array__immutable                  , //u8               (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2simple_array__immutable                  ,
  funk2_packet_type__pcs_request__f2simple_array__immutable__set             , //void             (f2ptr cause, f2ptr this, u8 value);
  funk2_packet_type__pcs_respond__f2simple_array__immutable__set             ,
  funk2_packet_type__pcs_request__f2simple_array__length                     , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2simple_array__length                     ,
  funk2_packet_type__pcs_request__f2simple_array__elt                        , //f2ptr            (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2simple_array__elt                        ,
  funk2_packet_type__pcs_request__f2simple_array__elt__set                   , //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);
  funk2_packet_type__pcs_respond__f2simple_array__elt__set                   ,
  funk2_packet_type__pcs_request__f2traced_array__new                        , //f2ptr            (f2ptr cause, u64 length, ptr dptr_ptr);
  funk2_packet_type__pcs_respond__f2traced_array__new                        ,
  funk2_packet_type__pcs_request__f2traced_array__new_copy                   , //f2ptr            (f2ptr cause, u64 length, f2ptr init_array);
  funk2_packet_type__pcs_respond__f2traced_array__new_copy                   ,
  funk2_packet_type__pcs_request__f2traced_array__immutable                  , //u8               (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2traced_array__immutable                  ,
  funk2_packet_type__pcs_request__f2traced_array__immutable__set             , //void             (f2ptr cause, f2ptr this, u8 value);
  funk2_packet_type__pcs_respond__f2traced_array__immutable__set             ,
  funk2_packet_type__pcs_request__f2traced_array__length                     , //u64              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2traced_array__length                     ,
  funk2_packet_type__pcs_request__f2traced_array__elt                        , //f2ptr            (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2traced_array__elt                        ,
  funk2_packet_type__pcs_request__f2traced_array__elt__set__trace_depth      , //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
  funk2_packet_type__pcs_respond__f2traced_array__elt__set__trace_depth      ,
  funk2_packet_type__pcs_request__f2traced_array__elt__set                   , //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);
  funk2_packet_type__pcs_respond__f2traced_array__elt__set                   ,
  funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on            , //f2ptr            (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on            ,
  funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on__set       , //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);
  funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on__set       ,
  funk2_packet_type__pcs_request__f2traced_array__elt__trace                 , //f2ptr            (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2traced_array__elt__trace                 ,
  funk2_packet_type__pcs_request__f2traced_array__elt__trace__set            , //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);
  funk2_packet_type__pcs_respond__f2traced_array__elt__trace__set            ,
  funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame     , //f2ptr            (f2ptr cause, f2ptr this, u64 index);
  funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame     ,
  funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame__set, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);
  funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame__set,
  funk2_packet_type__pcs_request__f2larva__new                               , //f2ptr            (f2ptr cause, u32 type);
  funk2_packet_type__pcs_respond__f2larva__new                               ,
  funk2_packet_type__pcs_request__f2larva__type                              , //u32              (f2ptr cause, f2ptr this);
  funk2_packet_type__pcs_respond__f2larva__type                              ,
} funk2_packet_type_t;

// todo: event rate data queries, all network average

typedef u8 stream_iter_t;

struct funk2_packet_header_s {
  u8            start_of_packet_byte; // funk2_sop_byte     (always the same)
  u8            channel;              // funk2_channel_byte (always the same)
  stream_iter_t stream_iter;          // increments for each unique packet sent to node (used to remove duplicated sent packets during disconnect/reconnect)
  u16           payload_length;
} __attribute__((__packed__));
typedef struct funk2_packet_header_s funk2_packet_header_t;

struct funk2_packet_payload_header_s {
  u8 type;
  u8 data[0];
} __attribute__((__packed__));
typedef struct funk2_packet_payload_header_s funk2_packet_payload_header_t;

struct funk2_packet_s {
  funk2_packet_header_t         header;
  funk2_packet_payload_header_t payload_header;
} __attribute__((__packed__));
typedef struct funk2_packet_s funk2_packet_t;



// packet payload definitions and initialization functions


//  funk2_packet_type__pcs_request__register_peer

// request register_peer

struct pcs_packet_payload_request__register_peer_s {
  funk2_packet_payload_header_t payload_header;
  node_id_t                     node_id;
  u8                            ip_addr[4];
  u16                           port_num;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__register_peer_s pcs_packet_payload_request__register_peer_t;

struct pcs_request__register_peer_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__register_peer_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__register_peer_s pcs_request__register_peer_t;

void                   send_packet__request__register_peer(f2ptr cause, funk2_node_t* funk2_node, node_id_t node_id, u8* ip_addr, u16 port_num);
void rpc_socket_layer__send_packet__request__register_peer(             funk2_node_t* funk2_node, node_id_t node_id, u8* ip_addr, u16 port_num);


//  funk2_packet_type__pcs_request__remote_computer_id_to_node_id

struct pcs_packet_payload_request__remote_computer_id_to_node_id_s {
  funk2_packet_payload_header_t payload_header;
  computer_id_t                 computer_id;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__remote_computer_id_to_node_id_s pcs_packet_payload_request__remote_computer_id_to_node_id_t;

struct pcs_request__remote_computer_id_to_node_id_s {
  funk2_packet_header_t                                       header;
  pcs_packet_payload_request__remote_computer_id_to_node_id_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__remote_computer_id_to_node_id_s pcs_request__remote_computer_id_to_node_id_t;


struct pcs_packet_payload_respond__remote_computer_id_to_node_id_s {
  funk2_packet_payload_header_t payload_header;
  node_id_t                     node_id;
  computer_id_t                 computer_id;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__remote_computer_id_to_node_id_s pcs_packet_payload_respond__remote_computer_id_to_node_id_t;

struct pcs_respond__remote_computer_id_to_node_id_s {
  funk2_packet_header_t                                       header;
  pcs_packet_payload_respond__remote_computer_id_to_node_id_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__remote_computer_id_to_node_id_s pcs_respond__remote_computer_id_to_node_id_t;

void send_packet__request__remote_computer_id_to_node_id(funk2_node_t* funk2_node, computer_id_t computer_id);
void send_packet__respond__remote_computer_id_to_node_id(funk2_node_t* funk2_node, node_id_t node_id, computer_id_t requester_computer_id);


//  funk2_packet_type__pcs_request__know_of_event

// request know_of_event

struct pcs_packet_payload_request__know_of_event_s {
  funk2_packet_payload_header_t payload_header;
  f2ptr                         event_cause;
  node_id_t                     node_id;
  event_id_t                    event_id;
  f2ptr                         type;
  f2ptr                         data;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__know_of_event_s pcs_packet_payload_request__know_of_event_t;

struct pcs_request__know_of_event_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__know_of_event_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__know_of_event_s pcs_request__know_of_event_t;

void                   send_packet__request__know_of_event(f2ptr cause, funk2_node_t* funk2_node, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data);
void rpc_socket_layer__send_packet__request__know_of_event(             funk2_node_t* funk2_node, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data);


// client_request_received (internal router packet wrapper packet)

struct pcs_packet_payload_client_request_received_s {
  funk2_packet_payload_header_t payload_header;
  client_id_t                   client_id;
  u64                           microseconds_since_1970;
  funk2_packet_t                request;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_client_request_received_s pcs_packet_payload_client_request_received_t;

struct pcs_client_request_received_packet_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_client_request_received_t payload;
} __attribute__((__packed__));
typedef struct pcs_client_request_received_packet_s pcs_client_request_received_packet_t;




struct pcs_packet_payload_header__action_payload_header_s {
  funk2_packet_payload_header_t payload_header;
  f2ptr                         cause;
  f2ptr                         thread;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_header__action_payload_header_s pcs_packet_payload_header__action_payload_header_t;

struct pcs_action_packet_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_action_packet_s pcs_action_packet_t;


void            funk2_packet_header__init(funk2_packet_header_t* this, u16 payload_length);
u32             funk2_packet__sizeof(funk2_packet_t* this);
funk2_packet_t* funk2_packet__copy(funk2_packet_t* this);
funk2_packet_t* funk2_packet__peek_read_new_from_circular_buffer(circular_buffer_t* buffer, u32* peek_byte_num, bool* invalid_packet_found);
funk2_packet_t* funk2_packet__read_valid_new_from_circular_buffer(circular_buffer_t* buffer);
funk2_packet_t* funk2_packet__peek_recv_new_from_buffered_socket(buffered_socket_t* socket, u32* peek_byte_num, bool* invalid_packet_found);
funk2_packet_t* funk2_packet__recv_new_valid_from_buffered_socket(buffered_socket_t* socket);
funk2_packet_t* funk2_packet__peek_read_new_from_buffered_file(buffered_file_t* file, u32* peek_byte_num, bool* invalid_packet_found);
funk2_packet_t* funk2_packet__read_new_valid_from_buffered_file(buffered_file_t* file);
void            socket_rpc_layer__funk2_packet__send_to_socket(funk2_packet_t* packet, buffered_socket_t* socket);
void            funk2_packet__send_to_socket(f2ptr cause, funk2_packet_t* packet, buffered_socket_t* socket);
void            funk2_packet__receive(funk2_node_t* funk2_node, pcs_action_packet_t* packet);



//  funk2_packet_type__pcs_request__system__environment                              , //u64              (f2ptr cause, funk2_packet_payload_header_t payload_header)

// request system__environment

struct pcs_packet_payload_request__system__environment_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__system__environment_s pcs_packet_payload_request__system__environment_t;

struct pcs_request__system__environment_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__system__environment_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__system__environment_s pcs_request__system__environment_t;

// respond system__environment

struct pcs_packet_payload_respond__system__environment_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              environment;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__system__environment_s pcs_packet_payload_respond__system__environment_t;

struct pcs_respond__system__environment_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__system__environment_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__system__environment_s pcs_respond__system__environment_t;

void send_packet__request__system__environment(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__request__system__environment(funk2_node_t* funk2_node, pcs_request__system__environment_t* packet);
void send_packet__respond__system__environment(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr environment);
void recv_packet__respond__system__environment(funk2_node_t* funk2_node, pcs_respond__system__environment_t* packet);

f2ptr funk2_node__system__environment(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
f2ptr funk2__system__environment(f2ptr cause, node_id_t node_id);


//  funk2_packet_type__pcs_request__memblock__creation_microseconds_since_1970 = 0x05, //u64              (f2ptr cause, f2ptr this);

// request memblock__creation_microseconds_since_1970

struct pcs_packet_payload_request__memblock__creation_microseconds_since_1970_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__memblock__creation_microseconds_since_1970_s pcs_packet_payload_request__memblock__creation_microseconds_since_1970_t;

struct pcs_request__memblock__creation_microseconds_since_1970_s {
  funk2_packet_header_t                                                    header;
  pcs_packet_payload_request__memblock__creation_microseconds_since_1970_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__memblock__creation_microseconds_since_1970_s pcs_request__memblock__creation_microseconds_since_1970_t;

// respond memblock__creation_microseconds_since_1970

struct pcs_packet_payload_respond__memblock__creation_microseconds_since_1970_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                creation_microseconds_since_1970;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__memblock__creation_microseconds_since_1970_s pcs_packet_payload_respond__memblock__creation_microseconds_since_1970_t;

struct pcs_respond__memblock__creation_microseconds_since_1970_s {
  funk2_packet_header_t                     header;
  pcs_packet_payload_respond__memblock__creation_microseconds_since_1970_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__memblock__creation_microseconds_since_1970_s pcs_respond__memblock__creation_microseconds_since_1970_t;

void send_packet__request__memblock__creation_microseconds_since_1970(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__memblock__creation_microseconds_since_1970(funk2_node_t* funk2_node, pcs_request__memblock__creation_microseconds_since_1970_t* packet);
void send_packet__respond__memblock__creation_microseconds_since_1970(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 creation_microseconds_since_1970);
void recv_packet__respond__memblock__creation_microseconds_since_1970(funk2_node_t* funk2_node, pcs_respond__memblock__creation_microseconds_since_1970_t* packet);

u64 funk2_node__memblock__creation_microseconds_since_1970(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__memblock__creation_microseconds_since_1970(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2ptype__raw                                 = 0x06, //ptype_t          (f2ptr cause, f2ptr this);

// request f2ptype__raw

struct pcs_packet_payload_request__f2ptype__raw_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2ptype__raw_s pcs_packet_payload_request__f2ptype__raw_t;

struct pcs_request__f2ptype__raw_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_request__f2ptype__raw_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2ptype__raw_s pcs_request__f2ptype__raw_t;

// respond f2ptype__raw

struct pcs_packet_payload_respond__f2ptype__raw_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  ptype_t                                            raw;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2ptype__raw_s pcs_packet_payload_respond__f2ptype__raw_t;

struct pcs_respond__f2ptype__raw_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_respond__f2ptype__raw_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2ptype__raw_s pcs_respond__f2ptype__raw_t;

void send_packet__request__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2ptype__raw(funk2_node_t* funk2_node, pcs_request__f2ptype__raw_t* packet);
void send_packet__respond__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, ptype_t raw);
void recv_packet__respond__f2ptype__raw(funk2_node_t* funk2_node, pcs_respond__f2ptype__raw_t* packet);

ptype_t funk2_node__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
ptype_t funk2__f2ptype__raw(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2ptype__cause                               = 0x07, //f2ptr            (f2ptr cause, f2ptr this);

// request f2ptype__cause

struct pcs_packet_payload_request__f2ptype__cause_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2ptype__cause_s pcs_packet_payload_request__f2ptype__cause_t;

struct pcs_request__f2ptype__cause_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2ptype__cause_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2ptype__cause_s pcs_request__f2ptype__cause_t;

// respond f2ptype__cause

struct pcs_packet_payload_respond__f2ptype__cause_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              ptype__cause;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2ptype__cause_s pcs_packet_payload_respond__f2ptype__cause_t;

struct pcs_respond__f2ptype__cause_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_respond__f2ptype__cause_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2ptype__cause_s pcs_respond__f2ptype__cause_t;

void send_packet__request__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2ptype__cause(funk2_node_t* funk2_node, pcs_request__f2ptype__cause_t* packet);
void send_packet__respond__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr ptype__cause);
void recv_packet__respond__f2ptype__cause(funk2_node_t* funk2_node, pcs_respond__f2ptype__cause_t* packet);

f2ptr funk2_node__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
f2ptr funk2__f2ptype__cause(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2ptype__cause__set                          = 0x08, //f2ptr            (f2ptr cause, f2ptr this, f2ptr value);

// request f2ptype__cause__set

struct pcs_packet_payload_request__f2ptype__cause__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2ptype__cause__set_s pcs_packet_payload_request__f2ptype__cause__set_t;

struct pcs_request__f2ptype__cause__set_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2ptype__cause__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2ptype__cause__set_s pcs_request__f2ptype__cause__set_t;

// respond f2ptype__cause__set

struct pcs_packet_payload_respond__f2ptype__cause__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2ptype__cause__set_s pcs_packet_payload_respond__f2ptype__cause__set_t;

struct pcs_respond__f2ptype__cause__set_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2ptype__cause__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2ptype__cause__set_s pcs_respond__f2ptype__cause__set_t;

void send_packet__request__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr value);
void recv_packet__request__f2ptype__cause__set(funk2_node_t* funk2_node, pcs_request__f2ptype__cause__set_t* packet);
void send_packet__respond__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2ptype__cause__set(funk2_node_t* funk2_node, pcs_respond__f2ptype__cause__set_t* packet);

void funk2_node__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr value);
void funk2__f2ptype__cause__set(f2ptr cause, f2ptr this, f2ptr value);


//  funk2_packet_type__pcs_request__f2integer__new                             = 0x09, //f2ptr            (f2ptr cause, s64 i);

// request f2integer__new

struct pcs_packet_payload_request__f2integer__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                i;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2integer__new_s pcs_packet_payload_request__f2integer__new_t;

struct pcs_request__f2integer__new_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_request__f2integer__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2integer__new_s pcs_request__f2integer__new_t;

// respond f2integer__new

struct pcs_packet_payload_respond__f2integer__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2integer__new_s pcs_packet_payload_respond__f2integer__new_t;

struct pcs_respond__f2integer__new_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_respond__f2integer__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2integer__new_s pcs_respond__f2integer__new_t;

void send_packet__request__f2integer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 i);
void recv_packet__request__f2integer__new(funk2_node_t* funk2_node, pcs_request__f2integer__new_t* packet);
void send_packet__respond__f2integer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2integer__new(funk2_node_t* funk2_node, pcs_respond__f2integer__new_t* packet);

f2ptr funk2_node__f2integer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 i);
f2ptr funk2__f2integer__new(f2ptr cause, u64 i);


//  funk2_packet_type__pcs_request__f2integer__i                               = 0x0A, //s64              (f2ptr cause, f2ptr this);

// request f2integer__i

struct pcs_packet_payload_request__f2integer__i_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2integer__i_s pcs_packet_payload_request__f2integer__i_t;

struct pcs_request__f2integer__i_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2integer__i_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2integer__i_s pcs_request__f2integer__i_t;

// respond f2integer__i

struct pcs_packet_payload_respond__f2integer__i_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  s64                                                i;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2integer__i_s pcs_packet_payload_respond__f2integer__i_t;

struct pcs_respond__f2integer__i_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2integer__i_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2integer__i_s pcs_respond__f2integer__i_t;

void send_packet__request__f2integer__i(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2integer__i(funk2_node_t* funk2_node, pcs_request__f2integer__i_t* packet);
void send_packet__respond__f2integer__i(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, s64 i);
void recv_packet__respond__f2integer__i(funk2_node_t* funk2_node, pcs_respond__f2integer__i_t* packet);

s64 funk2_node__f2integer__i(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
s64 funk2__f2integer__i(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2double__new                              = 0x0B, //f2ptr            (f2ptr cause, double d);

// request f2double__new

struct pcs_packet_payload_request__f2double__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  double                                             d;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2double__new_s pcs_packet_payload_request__f2double__new_t;

struct pcs_request__f2double__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2double__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2double__new_s pcs_request__f2double__new_t;

// respond f2double__new

struct pcs_packet_payload_respond__f2double__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2double__new_s pcs_packet_payload_respond__f2double__new_t;

struct pcs_respond__f2double__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2double__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2double__new_s pcs_respond__f2double__new_t;

void send_packet__request__f2double__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, double d);
void recv_packet__request__f2double__new(funk2_node_t* funk2_node, pcs_request__f2double__new_t* packet);
void send_packet__respond__f2double__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2double__new(funk2_node_t* funk2_node, pcs_respond__f2double__new_t* packet);

f2ptr funk2_node__f2double__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, double d);
f2ptr funk2__f2double__new(f2ptr cause, double d);


//  funk2_packet_type__pcs_request__f2double__d                                = 0x0C, //double           (f2ptr cause, f2ptr this);

// request f2double__d

struct pcs_packet_payload_request__f2double__d_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2double__d_s pcs_packet_payload_request__f2double__d_t;

struct pcs_request__f2double__d_s {
  funk2_packet_header_t                     header;
  pcs_packet_payload_request__f2double__d_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2double__d_s pcs_request__f2double__d_t;

// respond f2double__d

struct pcs_packet_payload_respond__f2double__d_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  double                                             d;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2double__d_s pcs_packet_payload_respond__f2double__d_t;

struct pcs_respond__f2double__d_s {
  funk2_packet_header_t                     header;
  pcs_packet_payload_respond__f2double__d_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2double__d_s pcs_respond__f2double__d_t;

void send_packet__request__f2double__d(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2double__d(funk2_node_t* funk2_node, pcs_request__f2double__d_t* packet);
void send_packet__respond__f2double__d(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, double d);
void recv_packet__respond__f2double__d(funk2_node_t* funk2_node, pcs_respond__f2double__d_t* packet);

double funk2_node__f2double__d(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
double funk2__f2double__d(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2float__new                               = 0x0D, //f2ptr            (f2ptr cause, float f);

// request f2float__new

struct pcs_packet_payload_request__f2float__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  float                                              f;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2float__new_s pcs_packet_payload_request__f2float__new_t;

struct pcs_request__f2float__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2float__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2float__new_s pcs_request__f2float__new_t;

// respond f2float__new

struct pcs_packet_payload_respond__f2float__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2float__new_s pcs_packet_payload_respond__f2float__new_t;

struct pcs_respond__f2float__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2float__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2float__new_s pcs_respond__f2float__new_t;

void send_packet__request__f2float__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, float f);
void recv_packet__request__f2float__new(funk2_node_t* funk2_node, pcs_request__f2float__new_t* packet);
void send_packet__respond__f2float__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2float__new(funk2_node_t* funk2_node, pcs_respond__f2float__new_t* packet);

f2ptr funk2_node__f2float__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, float f);
f2ptr funk2__f2float__new(f2ptr cause, float f);


//  funk2_packet_type__pcs_request__f2float__f                                 = 0x0E, //float            (f2ptr cause, f2ptr this);

// request f2float__f

struct pcs_packet_payload_request__f2float__f_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2float__f_s pcs_packet_payload_request__f2float__f_t;

struct pcs_request__f2float__f_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_request__f2float__f_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2float__f_s pcs_request__f2float__f_t;

// respond f2float__f

struct pcs_packet_payload_respond__f2float__f_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  float                                              f;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2float__f_s pcs_packet_payload_respond__f2float__f_t;

struct pcs_respond__f2float__f_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_respond__f2float__f_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2float__f_s pcs_respond__f2float__f_t;

void send_packet__request__f2float__f(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2float__f(funk2_node_t* funk2_node, pcs_request__f2float__f_t* packet);
void send_packet__respond__f2float__f(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, float f);
void recv_packet__respond__f2float__f(funk2_node_t* funk2_node, pcs_respond__f2float__f_t* packet);

float funk2_node__f2float__f(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
float funk2__f2float__f(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2pointer__new                             = 0x0F, //f2ptr            (f2ptr cause, ptr p);

// request f2pointer__new

struct pcs_packet_payload_request__f2pointer__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  ptr                                                p;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2pointer__new_s pcs_packet_payload_request__f2pointer__new_t;

struct pcs_request__f2pointer__new_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_request__f2pointer__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2pointer__new_s pcs_request__f2pointer__new_t;

struct pcs_packet_payload_respond__f2pointer__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2pointer__new_s pcs_packet_payload_respond__f2pointer__new_t;

struct pcs_respond__f2pointer__new_s {
  funk2_packet_header_t                        header;
  pcs_packet_payload_respond__f2pointer__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2pointer__new_s pcs_respond__f2pointer__new_t;

void send_packet__request__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, ptr p);
void recv_packet__request__f2pointer__new(funk2_node_t* funk2_node, pcs_request__f2pointer__new_t* packet);
void send_packet__respond__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2pointer__new(funk2_node_t* funk2_node, pcs_respond__f2pointer__new_t* packet);

f2ptr funk2_node__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, ptr p);
f2ptr funk2__f2pointer__new(f2ptr cause, ptr p);


//  funk2_packet_type__pcs_request__f2pointer__p                               = 0x10, //ptr              (f2ptr cause, f2ptr this);

// request f2pointer__p

struct pcs_packet_payload_request__f2pointer__p_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2pointer__p_s pcs_packet_payload_request__f2pointer__p_t;

struct pcs_request__f2pointer__p_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2pointer__p_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2pointer__p_s pcs_request__f2pointer__p_t;

// respond f2pointer__p

struct pcs_packet_payload_respond__f2pointer__p_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  ptr                                                p;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2pointer__p_s pcs_packet_payload_respond__f2pointer__p_t;

struct pcs_respond__f2pointer__p_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2pointer__p_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2pointer__p_s pcs_respond__f2pointer__p_t;

void send_packet__request__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2pointer__p(funk2_node_t* funk2_node, pcs_request__f2pointer__p_t* packet);
void send_packet__respond__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, ptr p);
void recv_packet__respond__f2pointer__p(funk2_node_t* funk2_node, pcs_respond__f2pointer__p_t* packet);

ptr funk2_node__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
ptr funk2__f2pointer__p(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2gfunkptr__new                            = 0x11, //f2ptr            (f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);

// request f2gfunkptr__new

struct pcs_packet_payload_request__f2gfunkptr__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  computer_id_t                                      computer_id;
  pool_index_t                                       pool_index;
  pool_address_t                                     pool_address;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__new_s pcs_packet_payload_request__f2gfunkptr__new_t;

struct pcs_request__f2gfunkptr__new_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_request__f2gfunkptr__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__new_s pcs_request__f2gfunkptr__new_t;

// respond f2gfunkptr__new

struct pcs_packet_payload_respond__f2gfunkptr__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__new_s pcs_packet_payload_respond__f2gfunkptr__new_t;

struct pcs_respond__f2gfunkptr__new_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_respond__f2gfunkptr__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__new_s pcs_respond__f2gfunkptr__new_t;

void send_packet__request__f2gfunkptr__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);
void recv_packet__request__f2gfunkptr__new(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__new_t* packet);
void send_packet__respond__f2gfunkptr__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2gfunkptr__new(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__new_t* packet);

f2ptr funk2_node__f2gfunkptr__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);
f2ptr funk2__f2gfunkptr__new(f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);


//  funk2_packet_type__pcs_request__f2gfunkptr__new_from_f2ptr                 = 0x12, //f2ptr            (f2ptr cause, f2ptr f2p);

// request f2gfunkptr__new_from_f2ptr

struct pcs_packet_payload_request__f2gfunkptr__new_from_f2ptr_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              f2p;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__new_from_f2ptr_s pcs_packet_payload_request__f2gfunkptr__new_from_f2ptr_t;

struct pcs_request__f2gfunkptr__new_from_f2ptr_s {
  funk2_packet_header_t                                    header;
  pcs_packet_payload_request__f2gfunkptr__new_from_f2ptr_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__new_from_f2ptr_s pcs_request__f2gfunkptr__new_from_f2ptr_t;

// respond f2gfunkptr__new_from_f2ptr

struct pcs_packet_payload_respond__f2gfunkptr__new_from_f2ptr_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new_from_f2ptr;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__new_from_f2ptr_s pcs_packet_payload_respond__f2gfunkptr__new_from_f2ptr_t;

struct pcs_respond__f2gfunkptr__new_from_f2ptr_s {
  funk2_packet_header_t                                    header;
  pcs_packet_payload_respond__f2gfunkptr__new_from_f2ptr_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__new_from_f2ptr_s pcs_respond__f2gfunkptr__new_from_f2ptr_t;

void send_packet__request__f2gfunkptr__new_from_f2ptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr f2p);
void recv_packet__request__f2gfunkptr__new_from_f2ptr(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__new_from_f2ptr_t* packet);
void send_packet__respond__f2gfunkptr__new_from_f2ptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new_from_f2ptr);
void recv_packet__respond__f2gfunkptr__new_from_f2ptr(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__new_from_f2ptr_t* packet);

f2ptr funk2_node__f2gfunkptr__new_from_f2ptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr f2p);
f2ptr funk2__f2gfunkptr__new_from_f2ptr(f2ptr cause, f2ptr f2p);


//  funk2_packet_type__pcs_request__f2gfunkptr__gfunkptr                       = 0x13, //f2ptr            (f2ptr cause, f2ptr this);

// request f2gfunkptr__gfunkptr

struct pcs_packet_payload_request__f2gfunkptr__gfunkptr_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__gfunkptr_s pcs_packet_payload_request__f2gfunkptr__gfunkptr_t;

struct pcs_request__f2gfunkptr__gfunkptr_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_request__f2gfunkptr__gfunkptr_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__gfunkptr_s pcs_request__f2gfunkptr__gfunkptr_t;

// respond f2gfunkptr__gfunkptr

struct pcs_packet_payload_respond__f2gfunkptr__gfunkptr_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              gfunkptr;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__gfunkptr_s pcs_packet_payload_respond__f2gfunkptr__gfunkptr_t;

struct pcs_respond__f2gfunkptr__gfunkptr_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_respond__f2gfunkptr__gfunkptr_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__gfunkptr_s pcs_respond__f2gfunkptr__gfunkptr_t;

void send_packet__request__f2gfunkptr__gfunkptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2gfunkptr__gfunkptr(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__gfunkptr_t* packet);
void send_packet__respond__f2gfunkptr__gfunkptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr gfunkptr);
void recv_packet__respond__f2gfunkptr__gfunkptr(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__gfunkptr_t* packet);

f2ptr funk2_node__f2gfunkptr__gfunkptr(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
f2ptr funk2__f2gfunkptr__gfunkptr(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2gfunkptr__computer_id                    = 0x14, //computer_id_t    (f2ptr cause, f2ptr this);

// request f2gfunkptr__computer_id

struct pcs_packet_payload_request__f2gfunkptr__computer_id_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__computer_id_s pcs_packet_payload_request__f2gfunkptr__computer_id_t;

struct pcs_request__f2gfunkptr__computer_id_s {
  funk2_packet_header_t                                 header;
  pcs_packet_payload_request__f2gfunkptr__computer_id_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__computer_id_s pcs_request__f2gfunkptr__computer_id_t;

// respond f2gfunkptr__computer_id

struct pcs_packet_payload_respond__f2gfunkptr__computer_id_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  computer_id_t                                      computer_id;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__computer_id_s pcs_packet_payload_respond__f2gfunkptr__computer_id_t;

struct pcs_respond__f2gfunkptr__computer_id_s {
  funk2_packet_header_t                                 header;
  pcs_packet_payload_respond__f2gfunkptr__computer_id_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__computer_id_s pcs_respond__f2gfunkptr__computer_id_t;

void send_packet__request__f2gfunkptr__computer_id(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2gfunkptr__computer_id(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__computer_id_t* packet);
void send_packet__respond__f2gfunkptr__computer_id(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, computer_id_t computer_id);
void recv_packet__respond__f2gfunkptr__computer_id(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__computer_id_t* packet);

computer_id_t funk2_node__f2gfunkptr__computer_id(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
computer_id_t funk2__f2gfunkptr__computer_id(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2gfunkptr__pool_index                     = 0x15, //pool_index_t     (f2ptr cause, f2ptr this);

// request f2gfunkptr__pool_index

struct pcs_packet_payload_request__f2gfunkptr__pool_index_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__pool_index_s pcs_packet_payload_request__f2gfunkptr__pool_index_t;

struct pcs_request__f2gfunkptr__pool_index_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_request__f2gfunkptr__pool_index_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__pool_index_s pcs_request__f2gfunkptr__pool_index_t;

// respond f2gfunkptr__pool_index

struct pcs_packet_payload_respond__f2gfunkptr__pool_index_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  pool_index_t                                       pool_index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__pool_index_s pcs_packet_payload_respond__f2gfunkptr__pool_index_t;

struct pcs_respond__f2gfunkptr__pool_index_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_respond__f2gfunkptr__pool_index_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__pool_index_s pcs_respond__f2gfunkptr__pool_index_t;

void send_packet__request__f2gfunkptr__pool_index(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2gfunkptr__pool_index(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__pool_index_t* packet);
void send_packet__respond__f2gfunkptr__pool_index(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, pool_index_t pool_index);
void recv_packet__respond__f2gfunkptr__pool_index(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__pool_index_t* packet);

pool_index_t funk2_node__f2gfunkptr__pool_index(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
pool_index_t funk2__f2gfunkptr__pool_index(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2gfunkptr__pool_address                   = 0x16, //pool_address_t   (f2ptr cause, f2ptr this);

// request f2gfunkptr__pool_address

struct pcs_packet_payload_request__f2gfunkptr__pool_address_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2gfunkptr__pool_address_s pcs_packet_payload_request__f2gfunkptr__pool_address_t;

struct pcs_request__f2gfunkptr__pool_address_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2gfunkptr__pool_address_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2gfunkptr__pool_address_s pcs_request__f2gfunkptr__pool_address_t;

// respond f2gfunkptr__pool_address

struct pcs_packet_payload_respond__f2gfunkptr__pool_address_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  pool_address_t                                     pool_address;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2gfunkptr__pool_address_s pcs_packet_payload_respond__f2gfunkptr__pool_address_t;

struct pcs_respond__f2gfunkptr__pool_address_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2gfunkptr__pool_address_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2gfunkptr__pool_address_s pcs_respond__f2gfunkptr__pool_address_t;

void send_packet__request__f2gfunkptr__pool_address(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2gfunkptr__pool_address(funk2_node_t* funk2_node, pcs_request__f2gfunkptr__pool_address_t* packet);
void send_packet__respond__f2gfunkptr__pool_address(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, pool_address_t pool_address);
void recv_packet__respond__f2gfunkptr__pool_address(funk2_node_t* funk2_node, pcs_respond__f2gfunkptr__pool_address_t* packet);

pool_address_t funk2_node__f2gfunkptr__pool_address(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
pool_address_t funk2__f2gfunkptr__pool_address(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2mutex__new                               = 0x17, //f2ptr            (f2ptr cause);

// request f2mutex__new

struct pcs_packet_payload_request__f2mutex__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2mutex__new_s pcs_packet_payload_request__f2mutex__new_t;

struct pcs_request__f2mutex__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2mutex__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2mutex__new_s pcs_request__f2mutex__new_t;

// respond f2mutex__new

struct pcs_packet_payload_respond__f2mutex__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2mutex__new_s pcs_packet_payload_respond__f2mutex__new_t;

struct pcs_respond__f2mutex__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2mutex__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2mutex__new_s pcs_respond__f2mutex__new_t;

void send_packet__request__f2mutex__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__request__f2mutex__new(funk2_node_t* funk2_node, pcs_request__f2mutex__new_t* packet);
void send_packet__respond__f2mutex__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2mutex__new(funk2_node_t* funk2_node, pcs_respond__f2mutex__new_t* packet);

f2ptr funk2_node__f2mutex__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
f2ptr funk2__f2mutex__new(f2ptr cause);


//  funk2_packet_type__pcs_request__f2mutex__lock                              = 0x18, //void             (f2ptr cause, f2ptr this);

// request f2mutex__lock

struct pcs_packet_payload_request__f2mutex__lock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2mutex__lock_s pcs_packet_payload_request__f2mutex__lock_t;

struct pcs_request__f2mutex__lock_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2mutex__lock_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2mutex__lock_s pcs_request__f2mutex__lock_t;

// respond f2mutex__lock

struct pcs_packet_payload_respond__f2mutex__lock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2mutex__lock_s pcs_packet_payload_respond__f2mutex__lock_t;

struct pcs_respond__f2mutex__lock_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2mutex__lock_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2mutex__lock_s pcs_respond__f2mutex__lock_t;

void send_packet__request__f2mutex__lock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2mutex__lock(funk2_node_t* funk2_node, pcs_request__f2mutex__lock_t* packet);
void send_packet__respond__f2mutex__lock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2mutex__lock(funk2_node_t* funk2_node, pcs_respond__f2mutex__lock_t* packet);

void funk2_node__f2mutex__lock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void funk2__f2mutex__lock(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2mutex__unlock                            = 0x19, //void             (f2ptr cause, f2ptr this);

// request f2mutex__unlock

struct pcs_packet_payload_request__f2mutex__unlock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2mutex__unlock_s pcs_packet_payload_request__f2mutex__unlock_t;

struct pcs_request__f2mutex__unlock_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_request__f2mutex__unlock_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2mutex__unlock_s pcs_request__f2mutex__unlock_t;

// respond f2mutex__unlock

struct pcs_packet_payload_respond__f2mutex__unlock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2mutex__unlock_s pcs_packet_payload_respond__f2mutex__unlock_t;

struct pcs_respond__f2mutex__unlock_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_respond__f2mutex__unlock_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2mutex__unlock_s pcs_respond__f2mutex__unlock_t;

void send_packet__request__f2mutex__unlock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2mutex__unlock(funk2_node_t* funk2_node, pcs_request__f2mutex__unlock_t* packet);
void send_packet__respond__f2mutex__unlock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2mutex__unlock(funk2_node_t* funk2_node, pcs_respond__f2mutex__unlock_t* packet);

void funk2_node__f2mutex__unlock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void funk2__f2mutex__unlock(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2mutex__trylock                           = 0x1A, //int              (f2ptr cause, f2ptr this);

// request f2mutex__trylock

struct pcs_packet_payload_request__f2mutex__trylock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2mutex__trylock_s pcs_packet_payload_request__f2mutex__trylock_t;

struct pcs_request__f2mutex__trylock_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_request__f2mutex__trylock_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2mutex__trylock_s pcs_request__f2mutex__trylock_t;

// respond f2mutex__trylock

struct pcs_packet_payload_respond__f2mutex__trylock_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  int                                                trylock;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2mutex__trylock_s pcs_packet_payload_respond__f2mutex__trylock_t;

struct pcs_respond__f2mutex__trylock_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_respond__f2mutex__trylock_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2mutex__trylock_s pcs_respond__f2mutex__trylock_t;

void send_packet__request__f2mutex__trylock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2mutex__trylock(funk2_node_t* funk2_node, pcs_request__f2mutex__trylock_t* packet);
void send_packet__respond__f2mutex__trylock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, int trylock);
void recv_packet__respond__f2mutex__trylock(funk2_node_t* funk2_node, pcs_respond__f2mutex__trylock_t* packet);

int funk2_node__f2mutex__trylock(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
int funk2__f2mutex__trylock(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2char__new                                = 0x1B, //f2ptr            (f2ptr cause, u64 ch);

// request f2char__new

struct pcs_packet_payload_request__f2char__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                ch;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2char__new_s pcs_packet_payload_request__f2char__new_t;

struct pcs_request__f2char__new_s {
  funk2_packet_header_t                     header;
  pcs_packet_payload_request__f2char__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2char__new_s pcs_request__f2char__new_t;

// respond f2char__new

struct pcs_packet_payload_respond__f2char__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2char__new_s pcs_packet_payload_respond__f2char__new_t;

struct pcs_respond__f2char__new_s {
  funk2_packet_header_t                     header;
  pcs_packet_payload_respond__f2char__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2char__new_s pcs_respond__f2char__new_t;

void send_packet__request__f2char__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 ch);
void recv_packet__request__f2char__new(funk2_node_t* funk2_node, pcs_request__f2char__new_t* packet);
void send_packet__respond__f2char__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2char__new(funk2_node_t* funk2_node, pcs_respond__f2char__new_t* packet);

f2ptr funk2_node__f2char__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 ch);
f2ptr funk2__f2char__new(f2ptr cause, u64 ch);


//  funk2_packet_type__pcs_request__f2char__ch                                 = 0x1C, //u64             (f2ptr cause, f2ptr this);

// request f2char__ch

struct pcs_packet_payload_request__f2char__ch_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2char__ch_s pcs_packet_payload_request__f2char__ch_t;

struct pcs_request__f2char__ch_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_request__f2char__ch_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2char__ch_s pcs_request__f2char__ch_t;

// respond f2char__ch

struct pcs_packet_payload_respond__f2char__ch_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  char                                               ch;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2char__ch_s pcs_packet_payload_respond__f2char__ch_t;

struct pcs_respond__f2char__ch_s {
  funk2_packet_header_t                    header;
  pcs_packet_payload_respond__f2char__ch_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2char__ch_s pcs_respond__f2char__ch_t;

void send_packet__request__f2char__ch(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2char__ch(funk2_node_t* funk2_node, pcs_request__f2char__ch_t* packet);
void send_packet__respond__f2char__ch(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 ch);
void recv_packet__respond__f2char__ch(funk2_node_t* funk2_node, pcs_respond__f2char__ch_t* packet);

u64 funk2_node__f2char__ch(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2char__ch(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2string__new                              = 0x1D, //f2ptr            (f2ptr cause, u64 length, u8* init);

// request f2string__new

struct pcs_packet_payload_request__f2string__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  u8                                                 init[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2string__new_s pcs_packet_payload_request__f2string__new_t;

struct pcs_request__f2string__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2string__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2string__new_s pcs_request__f2string__new_t;

// respond f2string__new

struct pcs_packet_payload_respond__f2string__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2string__new_s pcs_packet_payload_respond__f2string__new_t;

struct pcs_respond__f2string__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2string__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2string__new_s pcs_respond__f2string__new_t;

void send_packet__request__f2string__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, u8* init);
void recv_packet__request__f2string__new(funk2_node_t* funk2_node, pcs_request__f2string__new_t* packet);
void send_packet__respond__f2string__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2string__new(funk2_node_t* funk2_node, pcs_respond__f2string__new_t* packet);

f2ptr funk2_node__f2string__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, u8* init);
f2ptr funk2__f2string__new(f2ptr cause, u64 length, u8* init);


//  funk2_packet_type__pcs_request__f2string__length                           = 0x1E, //u64              (f2ptr cause, f2ptr this);

// request f2string__length

struct pcs_packet_payload_request__f2string__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2string__length_s pcs_packet_payload_request__f2string__length_t;

struct pcs_request__f2string__length_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_request__f2string__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2string__length_s pcs_request__f2string__length_t;

// respond f2string__length

struct pcs_packet_payload_respond__f2string__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2string__length_s pcs_packet_payload_respond__f2string__length_t;

struct pcs_respond__f2string__length_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_respond__f2string__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2string__length_s pcs_respond__f2string__length_t;

void send_packet__request__f2string__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2string__length(funk2_node_t* funk2_node, pcs_request__f2string__length_t* packet);
void send_packet__respond__f2string__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length);
void recv_packet__respond__f2string__length(funk2_node_t* funk2_node, pcs_respond__f2string__length_t* packet);

u64 funk2_node__f2string__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2string__length(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2string__elt                              = 0x1F, //u8               (f2ptr cause, f2ptr this, int index);

// request f2string__elt

struct pcs_packet_payload_request__f2string__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  int                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2string__elt_s pcs_packet_payload_request__f2string__elt_t;

struct pcs_request__f2string__elt_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2string__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2string__elt_s pcs_request__f2string__elt_t;
// respond f2string__elt

struct pcs_packet_payload_respond__f2string__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2string__elt_s pcs_packet_payload_respond__f2string__elt_t;

struct pcs_respond__f2string__elt_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2string__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2string__elt_s pcs_respond__f2string__elt_t;

void send_packet__request__f2string__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int index);
void recv_packet__request__f2string__elt(funk2_node_t* funk2_node, pcs_request__f2string__elt_t* packet);
void send_packet__respond__f2string__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8 elt);
void recv_packet__respond__f2string__elt(funk2_node_t* funk2_node, pcs_respond__f2string__elt_t* packet);

u8 funk2_node__f2string__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int index);
u8 funk2__f2string__elt(f2ptr this, int index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2string__str_copy                         = 0x21, //void             (f2ptr this, f2ptr cause, u8* str);

// request f2string__str_copy

struct pcs_packet_payload_request__f2string__str_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2string__str_copy_s pcs_packet_payload_request__f2string__str_copy_t;

struct pcs_request__f2string__str_copy_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_request__f2string__str_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2string__str_copy_s pcs_request__f2string__str_copy_t;

// respond f2string__str_copy

struct pcs_packet_payload_respond__f2string__str_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 str[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2string__str_copy_s pcs_packet_payload_respond__f2string__str_copy_t;

struct pcs_respond__f2string__str_copy_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_respond__f2string__str_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2string__str_copy_s pcs_respond__f2string__str_copy_t;

void send_packet__request__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2string__str_copy(funk2_node_t* funk2_node, pcs_request__f2string__str_copy_t* packet);
void send_packet__respond__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8* str);
void recv_packet__respond__f2string__str_copy(funk2_node_t* funk2_node, pcs_respond__f2string__str_copy_t* packet);

void funk2_node__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8* str);
void funk2__f2string__str_copy(f2ptr this, f2ptr cause, u8* str);


//  funk2_packet_type__pcs_request__f2string__hash_value                       = 0x22, //int              (f2ptr cause, f2ptr this);

// request f2string__hash_value

struct pcs_packet_payload_request__f2string__hash_value_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2string__hash_value_s pcs_packet_payload_request__f2string__hash_value_t;

struct pcs_request__f2string__hash_value_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_request__f2string__hash_value_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2string__hash_value_s pcs_request__f2string__hash_value_t;

// respond f2string__hash_value

struct pcs_packet_payload_respond__f2string__hash_value_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  int                                                hash_value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2string__hash_value_s pcs_packet_payload_respond__f2string__hash_value_t;

struct pcs_respond__f2string__hash_value_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_respond__f2string__hash_value_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2string__hash_value_s pcs_respond__f2string__hash_value_t;

void send_packet__request__f2string__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2string__hash_value(funk2_node_t* funk2_node, pcs_request__f2string__hash_value_t* packet);
void send_packet__respond__f2string__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, int hash_value);
void recv_packet__respond__f2string__hash_value(funk2_node_t* funk2_node, pcs_respond__f2string__hash_value_t* packet);

int funk2_node__f2string__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
int funk2__f2string__hash_value(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2symbol__new                              = 0x23, //f2ptr            (f2ptr cause, u64 length, u8* init);

// request f2symbol__new

struct pcs_packet_payload_request__f2symbol__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  u8                                                 init[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2symbol__new_s pcs_packet_payload_request__f2symbol__new_t;

struct pcs_request__f2symbol__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2symbol__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2symbol__new_s pcs_request__f2symbol__new_t;

// respond f2symbol__new

struct pcs_packet_payload_respond__f2symbol__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2symbol__new_s pcs_packet_payload_respond__f2symbol__new_t;

struct pcs_respond__f2symbol__new_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2symbol__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2symbol__new_s pcs_respond__f2symbol__new_t;

void send_packet__request__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, u8* init);
void recv_packet__request__f2symbol__new(funk2_node_t* funk2_node, pcs_request__f2symbol__new_t* packet);
void send_packet__respond__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2symbol__new(funk2_node_t* funk2_node, pcs_respond__f2symbol__new_t* packet);

f2ptr funk2_node__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, u8* init);
f2ptr funk2__f2symbol__new(f2ptr cause, u64 length, u8* init);


//  funk2_packet_type__pcs_request__f2symbol__length                           = 0x24, //u64              (f2ptr cause, f2ptr this);

// request f2symbol__length

struct pcs_packet_payload_request__f2symbol__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2symbol__length_s pcs_packet_payload_request__f2symbol__length_t;

struct pcs_request__f2symbol__length_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_request__f2symbol__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2symbol__length_s pcs_request__f2symbol__length_t;

// respond f2symbol__length

struct pcs_packet_payload_respond__f2symbol__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2symbol__length_s pcs_packet_payload_respond__f2symbol__length_t;

struct pcs_respond__f2symbol__length_s {
  funk2_packet_header_t                          header;
  pcs_packet_payload_respond__f2symbol__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2symbol__length_s pcs_respond__f2symbol__length_t;

void send_packet__request__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2symbol__length(funk2_node_t* funk2_node, pcs_request__f2symbol__length_t* packet);
void send_packet__respond__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length);
void recv_packet__respond__f2symbol__length(funk2_node_t* funk2_node, pcs_respond__f2symbol__length_t* packet);

u64 funk2_node__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2symbol__length(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2symbol__hash_value                           = 0x24, //u64              (f2ptr cause, f2ptr this);

// request f2symbol__hash_value

struct pcs_packet_payload_request__f2symbol__hash_value_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2symbol__hash_value_s pcs_packet_payload_request__f2symbol__hash_value_t;

struct pcs_request__f2symbol__hash_value_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_request__f2symbol__hash_value_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2symbol__hash_value_s pcs_request__f2symbol__hash_value_t;

// respond f2symbol__hash_value

struct pcs_packet_payload_respond__f2symbol__hash_value_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                hash_value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2symbol__hash_value_s pcs_packet_payload_respond__f2symbol__hash_value_t;

struct pcs_respond__f2symbol__hash_value_s {
  funk2_packet_header_t                              header;
  pcs_packet_payload_respond__f2symbol__hash_value_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2symbol__hash_value_s pcs_respond__f2symbol__hash_value_t;

void send_packet__request__f2symbol__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2symbol__hash_value(funk2_node_t* funk2_node, pcs_request__f2symbol__hash_value_t* packet);
void send_packet__respond__f2symbol__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 hash_value);
void recv_packet__respond__f2symbol__hash_value(funk2_node_t* funk2_node, pcs_respond__f2symbol__hash_value_t* packet);

u64 funk2_node__f2symbol__hash_value(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2symbol__hash_value(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2symbol__elt                              = 0x25, //u8               (f2ptr this, int index, f2ptr cause);

// request f2symbol__elt

struct pcs_packet_payload_request__f2symbol__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  int                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2symbol__elt_s pcs_packet_payload_request__f2symbol__elt_t;

struct pcs_request__f2symbol__elt_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2symbol__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2symbol__elt_s pcs_request__f2symbol__elt_t;

// respond f2symbol__elt

struct pcs_packet_payload_respond__f2symbol__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2symbol__elt_s pcs_packet_payload_respond__f2symbol__elt_t;

struct pcs_respond__f2symbol__elt_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2symbol__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2symbol__elt_s pcs_respond__f2symbol__elt_t;

void send_packet__request__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int index);
void recv_packet__request__f2symbol__elt(funk2_node_t* funk2_node, pcs_request__f2symbol__elt_t* packet);
void send_packet__respond__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8 elt);
void recv_packet__respond__f2symbol__elt(funk2_node_t* funk2_node, pcs_respond__f2symbol__elt_t* packet);

u8 funk2_node__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int index);
u8 funk2__f2symbol__elt(f2ptr this, int index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2symbol__str_copy                         = 0x27, //void             (f2ptr this, f2ptr cause, u8* str);

// request f2symbol__str_copy

struct pcs_packet_payload_request__f2symbol__str_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2symbol__str_copy_s pcs_packet_payload_request__f2symbol__str_copy_t;

struct pcs_request__f2symbol__str_copy_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_request__f2symbol__str_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2symbol__str_copy_s pcs_request__f2symbol__str_copy_t;

// respond f2symbol__str_copy

struct pcs_packet_payload_respond__f2symbol__str_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 str[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2symbol__str_copy_s pcs_packet_payload_respond__f2symbol__str_copy_t;

struct pcs_respond__f2symbol__str_copy_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_respond__f2symbol__str_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2symbol__str_copy_s pcs_respond__f2symbol__str_copy_t;

void send_packet__request__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2symbol__str_copy(funk2_node_t* funk2_node, pcs_request__f2symbol__str_copy_t* packet);
void send_packet__respond__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8* str);
void recv_packet__respond__f2symbol__str_copy(funk2_node_t* funk2_node, pcs_respond__f2symbol__str_copy_t* packet);

void funk2_node__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8* str);
void funk2__f2symbol__str_copy(f2ptr cause, f2ptr this, u8* str);


//  funk2_packet_type__pcs_request__f2chunk__new                               = 0x28, //f2ptr            (f2ptr cause, u64 length, byte* bytes);

// request f2chunk__new

struct pcs_packet_payload_request__f2chunk__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  byte                                               bytes[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__new_s pcs_packet_payload_request__f2chunk__new_t;

struct pcs_request__f2chunk__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2chunk__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__new_s pcs_request__f2chunk__new_t;

// respond f2chunk__new

struct pcs_packet_payload_respond__f2chunk__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__new_s pcs_packet_payload_respond__f2chunk__new_t;

struct pcs_respond__f2chunk__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2chunk__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__new_s pcs_respond__f2chunk__new_t;

void send_packet__request__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, byte* bytes);
void recv_packet__request__f2chunk__new(funk2_node_t* funk2_node, pcs_request__f2chunk__new_t* packet);
void send_packet__respond__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2chunk__new(funk2_node_t* funk2_node, pcs_respond__f2chunk__new_t* packet);

f2ptr funk2_node__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, byte* bytes);
f2ptr funk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes);


//  funk2_packet_type__pcs_request__f2chunk__new_copy                          = 0x29, //f2ptr            (f2ptr cause, f2ptr init_chunk);

// request f2chunk__new_copy

struct pcs_packet_payload_request__f2chunk__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              init_chunk;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__new_copy_s pcs_packet_payload_request__f2chunk__new_copy_t;

struct pcs_request__f2chunk__new_copy_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_request__f2chunk__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__new_copy_s pcs_request__f2chunk__new_copy_t;

// respond f2chunk__new_copy

struct pcs_packet_payload_respond__f2chunk__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new_copy;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__new_copy_s pcs_packet_payload_respond__f2chunk__new_copy_t;

struct pcs_respond__f2chunk__new_copy_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_respond__f2chunk__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__new_copy_s pcs_respond__f2chunk__new_copy_t;

void send_packet__request__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr init_chunk);
void recv_packet__request__f2chunk__new_copy(funk2_node_t* funk2_node, pcs_request__f2chunk__new_copy_t* packet);
void send_packet__respond__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new_copy);
void recv_packet__respond__f2chunk__new_copy(funk2_node_t* funk2_node, pcs_respond__f2chunk__new_copy_t* packet);

f2ptr funk2_node__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr init_chunk);
f2ptr funk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk);


//  funk2_packet_type__pcs_request__f2chunk__length                            = 0x2A, //u64              (f2ptr cause, f2ptr this);

// request f2chunk__length

struct pcs_packet_payload_request__f2chunk__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__length_s pcs_packet_payload_request__f2chunk__length_t;

struct pcs_request__f2chunk__length_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_request__f2chunk__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__length_s pcs_request__f2chunk__length_t;

// respond f2chunk__length

struct pcs_packet_payload_respond__f2chunk__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__length_s pcs_packet_payload_respond__f2chunk__length_t;

struct pcs_respond__f2chunk__length_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_respond__f2chunk__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__length_s pcs_respond__f2chunk__length_t;

void send_packet__request__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2chunk__length(funk2_node_t* funk2_node, pcs_request__f2chunk__length_t* packet);
void send_packet__respond__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length);
void recv_packet__respond__f2chunk__length(funk2_node_t* funk2_node, pcs_respond__f2chunk__length_t* packet);

u64 funk2_node__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2chunk__length(f2ptr cause, f2ptr this);


//  funk2_packet_type__pcs_request__f2chunk__bit8__elt                         = 0x2C, //u8               (f2ptr cause, f2ptr this, u64 index);

// request f2chunk__bit8__elt

struct pcs_packet_payload_request__f2chunk__bit8__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit8__elt_s pcs_packet_payload_request__f2chunk__bit8__elt_t;

struct pcs_request__f2chunk__bit8__elt_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_request__f2chunk__bit8__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit8__elt_s pcs_request__f2chunk__bit8__elt_t;

// respond f2chunk__bit8__elt

struct pcs_packet_payload_respond__f2chunk__bit8__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit8__elt_s pcs_packet_payload_respond__f2chunk__bit8__elt_t;

struct pcs_respond__f2chunk__bit8__elt_s {
  funk2_packet_header_t                            header;
  pcs_packet_payload_respond__f2chunk__bit8__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit8__elt_s pcs_respond__f2chunk__bit8__elt_t;

void send_packet__request__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2chunk__bit8__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit8__elt_t* packet);
void send_packet__respond__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8 elt);
void recv_packet__respond__f2chunk__bit8__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit8__elt_t* packet);

u8 funk2_node__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
u8 funk2__f2chunk__bit8__elt(f2ptr cause, f2ptr this, u64 index);


//  funk2_packet_type__pcs_request__f2chunk__bit8__elt__set                    = 0x2D, //void             (f2ptr this, u64 index, f2ptr cause, u8 value);

// request f2chunk__bit8__elt__set

struct pcs_packet_payload_request__f2chunk__bit8__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  u8                                                 value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit8__elt__set_s pcs_packet_payload_request__f2chunk__bit8__elt__set_t;

struct pcs_request__f2chunk__bit8__elt__set_s {
  funk2_packet_header_t                                 header;
  pcs_packet_payload_request__f2chunk__bit8__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit8__elt__set_s pcs_request__f2chunk__bit8__elt__set_t;

// respond f2chunk__bit8__elt__set

struct pcs_packet_payload_respond__f2chunk__bit8__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit8__elt__set_s pcs_packet_payload_respond__f2chunk__bit8__elt__set_t;

struct pcs_respond__f2chunk__bit8__elt__set_s {
  funk2_packet_header_t                                 header;
  pcs_packet_payload_respond__f2chunk__bit8__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit8__elt__set_s pcs_respond__f2chunk__bit8__elt__set_t;

void send_packet__request__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u8 value);
void recv_packet__request__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit8__elt__set_t* packet);
void send_packet__respond__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit8__elt__set_t* packet);

void funk2_node__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u8 value);
void funk2__f2chunk__bit8__elt__set(f2ptr cause, f2ptr this, u64 index, u8 value);


//  funk2_packet_type__pcs_request__f2chunk__bit16__elt                        = 0x2E, //u16              (f2ptr cause, f2ptr this, u64 index);

// request f2chunk__bit16__elt

struct pcs_packet_payload_request__f2chunk__bit16__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit16__elt_s pcs_packet_payload_request__f2chunk__bit16__elt_t;

struct pcs_request__f2chunk__bit16__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2chunk__bit16__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit16__elt_s pcs_request__f2chunk__bit16__elt_t;

// respond f2chunk__bit16__elt

struct pcs_packet_payload_respond__f2chunk__bit16__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u16                                                elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit16__elt_s pcs_packet_payload_respond__f2chunk__bit16__elt_t;

struct pcs_respond__f2chunk__bit16__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2chunk__bit16__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit16__elt_s pcs_respond__f2chunk__bit16__elt_t;

void send_packet__request__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2chunk__bit16__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit16__elt_t* packet);
void send_packet__respond__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u16 elt);
void recv_packet__respond__f2chunk__bit16__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit16__elt_t* packet);

u16 funk2_node__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
u16 funk2__f2chunk__bit16__elt(f2ptr cause, f2ptr this, u64 index);


//  funk2_packet_type__pcs_request__f2chunk__bit16__elt__set                   = 0x2F, //void             (f2ptr cause, f2ptr this, u64 index, u16 value);

// request f2chunk__bit16__elt__set

struct pcs_packet_payload_request__f2chunk__bit16__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  u16                                                value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit16__elt__set_s pcs_packet_payload_request__f2chunk__bit16__elt__set_t;

struct pcs_request__f2chunk__bit16__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2chunk__bit16__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit16__elt__set_s pcs_request__f2chunk__bit16__elt__set_t;

// respond f2chunk__bit16__elt__set

struct pcs_packet_payload_respond__f2chunk__bit16__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit16__elt__set_s pcs_packet_payload_respond__f2chunk__bit16__elt__set_t;

struct pcs_respond__f2chunk__bit16__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2chunk__bit16__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit16__elt__set_s pcs_respond__f2chunk__bit16__elt__set_t;

void send_packet__request__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u16 value);
void recv_packet__request__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit16__elt__set_t* packet);
void send_packet__respond__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit16__elt__set_t* packet);

void funk2_node__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u16 value);
void funk2__f2chunk__bit16__elt__set(f2ptr cause, f2ptr this, u64 index, u16 value);


//  funk2_packet_type__pcs_request__f2chunk__bit32__elt                        = 0x30, //u32              (f2ptr this, u64 index, f2ptr cause);

// request f2chunk__bit32__elt

struct pcs_packet_payload_request__f2chunk__bit32__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit32__elt_s pcs_packet_payload_request__f2chunk__bit32__elt_t;

struct pcs_request__f2chunk__bit32__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2chunk__bit32__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit32__elt_s pcs_request__f2chunk__bit32__elt_t;

// respond f2chunk__bit32__elt

struct pcs_packet_payload_respond__f2chunk__bit32__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u32                                                elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit32__elt_s pcs_packet_payload_respond__f2chunk__bit32__elt_t;

struct pcs_respond__f2chunk__bit32__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2chunk__bit32__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit32__elt_s pcs_respond__f2chunk__bit32__elt_t;

void send_packet__request__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2chunk__bit32__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit32__elt_t* packet);
void send_packet__respond__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u32 elt);
void recv_packet__respond__f2chunk__bit32__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit32__elt_t* packet);

u32 funk2_node__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
u32 funk2__f2chunk__bit32__elt(f2ptr cause, f2ptr this, u64 index);


//  funk2_packet_type__pcs_request__f2chunk__bit32__elt__set                   = 0x31, //void             (f2ptr cause, f2ptr this, u64 index, u32 value);

// request f2chunk__bit32__elt__set

struct pcs_packet_payload_request__f2chunk__bit32__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  u32                                                value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit32__elt__set_s pcs_packet_payload_request__f2chunk__bit32__elt__set_t;

struct pcs_request__f2chunk__bit32__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2chunk__bit32__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit32__elt__set_s pcs_request__f2chunk__bit32__elt__set_t;

// respond f2chunk__bit32__elt__set

struct pcs_packet_payload_respond__f2chunk__bit32__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit32__elt__set_s pcs_packet_payload_respond__f2chunk__bit32__elt__set_t;

struct pcs_respond__f2chunk__bit32__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2chunk__bit32__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit32__elt__set_s pcs_respond__f2chunk__bit32__elt__set_t;

void send_packet__request__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u32 value);
void recv_packet__request__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit32__elt__set_t* packet);
void send_packet__respond__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit32__elt__set_t* packet);

void funk2_node__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u32 value);
void funk2__f2chunk__bit32__elt__set(f2ptr cause, f2ptr this, u64 index, u32 value);


//  funk2_packet_type__pcs_request__f2chunk__bit64__elt                        = 0x32, //u64              (f2ptr this, u64 index, f2ptr cause);

// request f2chunk__bit64__elt

struct pcs_packet_payload_request__f2chunk__bit64__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit64__elt_s pcs_packet_payload_request__f2chunk__bit64__elt_t;

struct pcs_request__f2chunk__bit64__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2chunk__bit64__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit64__elt_s pcs_request__f2chunk__bit64__elt_t;

// respond f2chunk__bit64__elt

struct pcs_packet_payload_respond__f2chunk__bit64__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit64__elt_s pcs_packet_payload_respond__f2chunk__bit64__elt_t;

struct pcs_respond__f2chunk__bit64__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2chunk__bit64__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit64__elt_s pcs_respond__f2chunk__bit64__elt_t;

void send_packet__request__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2chunk__bit64__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit64__elt_t* packet);
void send_packet__respond__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 elt);
void recv_packet__respond__f2chunk__bit64__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit64__elt_t* packet);

u64 funk2_node__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
u64 funk2__f2chunk__bit64__elt(f2ptr cause, f2ptr this, u64 index);


//  funk2_packet_type__pcs_request__f2chunk__bit64__elt__set                   = 0x33, //void             (f2ptr this, u64 index, f2ptr cause, u64 value);

// request f2chunk__bit64__elt__set

struct pcs_packet_payload_request__f2chunk__bit64__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  u64                                                value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bit64__elt__set_s pcs_packet_payload_request__f2chunk__bit64__elt__set_t;

struct pcs_request__f2chunk__bit64__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2chunk__bit64__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bit64__elt__set_s pcs_request__f2chunk__bit64__elt__set_t;

// respond f2chunk__bit64__elt__set

struct pcs_packet_payload_respond__f2chunk__bit64__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bit64__elt__set_s pcs_packet_payload_respond__f2chunk__bit64__elt__set_t;

struct pcs_respond__f2chunk__bit64__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2chunk__bit64__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bit64__elt__set_s pcs_respond__f2chunk__bit64__elt__set_t;

void send_packet__request__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u64 value);
void recv_packet__request__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit64__elt__set_t* packet);
void send_packet__respond__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit64__elt__set_t* packet);

void funk2_node__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, u64 value);
void funk2__f2chunk__bit64__elt__set(f2ptr cause, f2ptr this, u64 index, u64 value);


//  funk2_packet_type__pcs_request__f2chunk__cfunk_jump                        = 0x34, //f2ptr            (f2ptr cause, f2ptr this, f2ptr thread, f2ptr env, f2ptr args);

// request f2chunk__cfunk_jump

struct pcs_packet_payload_request__f2chunk__cfunk_jump_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  f2ptr                                              thread;
  f2ptr                                              env;
  f2ptr                                              args;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__cfunk_jump_s pcs_packet_payload_request__f2chunk__cfunk_jump_t;

struct pcs_request__f2chunk__cfunk_jump_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2chunk__cfunk_jump_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__cfunk_jump_s pcs_request__f2chunk__cfunk_jump_t;

// respond f2chunk__cfunk_jump

struct pcs_packet_payload_respond__f2chunk__cfunk_jump_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              cfunk_jump_return;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__cfunk_jump_s pcs_packet_payload_respond__f2chunk__cfunk_jump_t;

struct pcs_respond__f2chunk__cfunk_jump_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2chunk__cfunk_jump_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__cfunk_jump_s pcs_respond__f2chunk__cfunk_jump_t;

void send_packet__request__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr thread, f2ptr env, f2ptr args);
void recv_packet__request__f2chunk__cfunk_jump(funk2_node_t* funk2_node, pcs_request__f2chunk__cfunk_jump_t* packet);
void send_packet__respond__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr cfunk_jump_return);
void recv_packet__respond__f2chunk__cfunk_jump(funk2_node_t* funk2_node, pcs_respond__f2chunk__cfunk_jump_t* packet);

f2ptr funk2_node__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr thread, f2ptr env, f2ptr args);
f2ptr funk2__f2chunk__cfunk_jump(f2ptr cause, f2ptr this, f2ptr thread, f2ptr env, f2ptr args);


//  funk2_packet_type__pcs_request__f2chunk__bytecode_jump                     = 0x35, //int              (f2ptr cause, f2ptr this, f2ptr thread);

// request f2chunk__bytecode_jump

struct pcs_packet_payload_request__f2chunk__bytecode_jump_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  f2ptr                                              thread;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__bytecode_jump_s pcs_packet_payload_request__f2chunk__bytecode_jump_t;

struct pcs_request__f2chunk__bytecode_jump_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_request__f2chunk__bytecode_jump_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__bytecode_jump_s pcs_request__f2chunk__bytecode_jump_t;

// respond f2chunk__bytecode_jump

struct pcs_packet_payload_respond__f2chunk__bytecode_jump_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  int                                                bytecode_jump_return;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__bytecode_jump_s pcs_packet_payload_respond__f2chunk__bytecode_jump_t;

struct pcs_respond__f2chunk__bytecode_jump_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_respond__f2chunk__bytecode_jump_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__bytecode_jump_s pcs_respond__f2chunk__bytecode_jump_t;

void send_packet__request__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr thread);
void recv_packet__request__f2chunk__bytecode_jump(funk2_node_t* funk2_node, pcs_request__f2chunk__bytecode_jump_t* packet);
void send_packet__respond__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, int bytecode_jump_return);
void recv_packet__respond__f2chunk__bytecode_jump(funk2_node_t* funk2_node, pcs_respond__f2chunk__bytecode_jump_t* packet);

int funk2_node__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, f2ptr thread);
int funk2__f2chunk__bytecode_jump(f2ptr cause, f2ptr this, f2ptr thread);


//  funk2_packet_type__pcs_request__f2chunk__send                              = 0x36, //f2ptr            (f2ptr cause, f2ptr this, int start, int length, int fd, int flags);

// request f2chunk__send

struct pcs_packet_payload_request__f2chunk__send_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  int                                                start;
  int                                                length;
  int                                                fd;
  int                                                flags;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__send_s pcs_packet_payload_request__f2chunk__send_t;

struct pcs_request__f2chunk__send_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2chunk__send_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__send_s pcs_request__f2chunk__send_t;

// respond f2chunk__send

struct pcs_packet_payload_respond__f2chunk__send_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              send_return;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__send_s pcs_packet_payload_respond__f2chunk__send_t;

struct pcs_respond__f2chunk__send_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2chunk__send_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__send_s pcs_respond__f2chunk__send_t;

void send_packet__request__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
void recv_packet__request__f2chunk__send(funk2_node_t* funk2_node, pcs_request__f2chunk__send_t* packet);
void send_packet__respond__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr send_return);
void recv_packet__respond__f2chunk__send(funk2_node_t* funk2_node, pcs_respond__f2chunk__send_t* packet);

f2ptr funk2_node__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
f2ptr funk2__f2chunk__send(f2ptr cause, f2ptr this, int start, int length, int fd, int flags);


//  funk2_packet_type__pcs_request__f2chunk__recv                              = 0x37, //f2ptr            (f2ptr cause, f2ptr this, int start, int length, int fd, int flags);

// request f2chunk__recv

struct pcs_packet_payload_request__f2chunk__recv_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  int                                                start;
  int                                                length;
  int                                                fd;
  int                                                flags;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2chunk__recv_s pcs_packet_payload_request__f2chunk__recv_t;

struct pcs_request__f2chunk__recv_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2chunk__recv_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2chunk__recv_s pcs_request__f2chunk__recv_t;

// respond f2chunk__recv

struct pcs_packet_payload_respond__f2chunk__recv_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  int                                                recv_return;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2chunk__recv_s pcs_packet_payload_respond__f2chunk__recv_t;

struct pcs_respond__f2chunk__recv_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2chunk__recv_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2chunk__recv_s pcs_respond__f2chunk__recv_t;

void send_packet__request__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
void recv_packet__request__f2chunk__recv(funk2_node_t* funk2_node, pcs_request__f2chunk__recv_t* packet);
void send_packet__respond__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr recv_return);
void recv_packet__respond__f2chunk__recv(funk2_node_t* funk2_node, pcs_respond__f2chunk__recv_t* packet);

f2ptr funk2_node__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, int start, int length, int fd, int flags);
f2ptr funk2__f2chunk__recv(f2ptr cause, f2ptr this, int start, int length, int fd, int flags);


//  funk2_packet_type__pcs_request__f2simple_array__new                               = 0x38, //f2ptr            (f2ptr cause, u64 length, f2ptr* f2ptr_array);

// request f2simple_array__new

struct pcs_packet_payload_request__f2simple_array__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  bool                                               f2ptr_array__defined;
  f2ptr                                              f2ptr_array[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__new_s pcs_packet_payload_request__f2simple_array__new_t;

struct pcs_request__f2simple_array__new_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2simple_array__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__new_s pcs_request__f2simple_array__new_t;

// respond f2simple_array__new

struct pcs_packet_payload_respond__f2simple_array__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__new_s pcs_packet_payload_respond__f2simple_array__new_t;

struct pcs_respond__f2simple_array__new_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2simple_array__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__new_s pcs_respond__f2simple_array__new_t;

void send_packet__request__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, ptr f2ptr_array);
void recv_packet__request__f2simple_array__new(funk2_node_t* funk2_node, pcs_request__f2simple_array__new_t* packet);
void send_packet__respond__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2simple_array__new(funk2_node_t* funk2_node, pcs_respond__f2simple_array__new_t* packet);

f2ptr funk2_node__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, ptr f2ptr_array);
f2ptr funk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_array);


//  funk2_packet_type__pcs_request__f2simple_array__new_copy                          = 0x39, //f2ptr            (f2ptr cause, u64 length, f2ptr init_array);

// request f2simple_array__new_copy

struct pcs_packet_payload_request__f2simple_array__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  f2ptr                                              init_array;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__new_copy_s pcs_packet_payload_request__f2simple_array__new_copy_t;

struct pcs_request__f2simple_array__new_copy_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2simple_array__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__new_copy_s pcs_request__f2simple_array__new_copy_t;

// respond f2simple_array__new_copy

struct pcs_packet_payload_respond__f2simple_array__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new_copy;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__new_copy_s pcs_packet_payload_respond__f2simple_array__new_copy_t;

struct pcs_respond__f2simple_array__new_copy_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2simple_array__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__new_copy_s pcs_respond__f2simple_array__new_copy_t;

void send_packet__request__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, f2ptr init_array);
void recv_packet__request__f2simple_array__new_copy(funk2_node_t* funk2_node, pcs_request__f2simple_array__new_copy_t* packet);
void send_packet__respond__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new_copy);
void recv_packet__respond__f2simple_array__new_copy(funk2_node_t* funk2_node, pcs_respond__f2simple_array__new_copy_t* packet);

f2ptr funk2_node__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, f2ptr init_array);
f2ptr funk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array);


//  funk2_packet_type__pcs_request__f2simple_array__immutable                               = 0x3B, //u8            (f2ptr this, f2ptr cause);

// request f2simple_array__immutable

struct pcs_packet_payload_request__f2simple_array__immutable_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__immutable_s pcs_packet_payload_request__f2simple_array__immutable_t;

struct pcs_request__f2simple_array__immutable_s {
  funk2_packet_header_t                                   header;
  pcs_packet_payload_request__f2simple_array__immutable_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__immutable_s pcs_request__f2simple_array__immutable_t;

// respond f2simple_array__immutable

struct pcs_packet_payload_respond__f2simple_array__immutable_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 immutable;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__immutable_s pcs_packet_payload_respond__f2simple_array__immutable_t;

struct pcs_respond__f2simple_array__immutable_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2simple_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__immutable_s pcs_respond__f2simple_array__immutable_t;

void send_packet__request__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2simple_array__immutable(funk2_node_t* funk2_node, pcs_request__f2simple_array__immutable_t* packet);
void send_packet__respond__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8 immutable);
void recv_packet__respond__f2simple_array__immutable(funk2_node_t* funk2_node, pcs_respond__f2simple_array__immutable_t* packet);

f2ptr funk2_node__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
f2ptr funk2__f2simple_array__immutable(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2simple_array__immutable__set                          = 0x3D, //void            (f2ptr cause, f2ptr this, u8 value);

// request f2simple_array__immutable__set

struct pcs_packet_payload_request__f2simple_array__immutable__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u8                                                 value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__immutable__set_s pcs_packet_payload_request__f2simple_array__immutable__set_t;

struct pcs_request__f2simple_array__immutable__set_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_request__f2simple_array__immutable__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__immutable__set_s pcs_request__f2simple_array__immutable__set_t;

// respond f2simple_array__immutable__set

struct pcs_packet_payload_respond__f2simple_array__immutable__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__immutable__set_s pcs_packet_payload_respond__f2simple_array__immutable__set_t;

struct pcs_respond__f2simple_array__immutable__set_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_respond__f2simple_array__immutable__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__immutable__set_s pcs_respond__f2simple_array__immutable__set_t;

void send_packet__request__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8 value);
void recv_packet__request__f2simple_array__immutable__set(funk2_node_t* funk2_node, pcs_request__f2simple_array__elt__set_t* packet);
void send_packet__respond__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2simple_array__immutable__set(funk2_node_t* funk2_node, pcs_respond__f2simple_array__elt__set_t* packet);

void funk2_node__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8 value);
void funk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value);


//  funk2_packet_type__pcs_request__f2simple_array__length                            = 0x3A, //u64              (f2ptr cause, f2ptr this);

// request f2simple_array__length

struct pcs_packet_payload_request__f2simple_array__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__length_s pcs_packet_payload_request__f2simple_array__length_t;

struct pcs_request__f2simple_array__length_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_request__f2simple_array__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__length_s pcs_request__f2simple_array__length_t;

// respond f2simple_array__length

struct pcs_packet_payload_respond__f2simple_array__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__length_s pcs_packet_payload_respond__f2simple_array__length_t;

struct pcs_respond__f2simple_array__length_s {
  funk2_packet_header_t                                header;
  pcs_packet_payload_respond__f2simple_array__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__length_s pcs_respond__f2simple_array__length_t;

void send_packet__request__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2simple_array__length(funk2_node_t* funk2_node, pcs_request__f2simple_array__length_t* packet);
void send_packet__respond__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length);
void recv_packet__respond__f2simple_array__length(funk2_node_t* funk2_node, pcs_respond__f2simple_array__length_t* packet);

u64 funk2_node__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2simple_array__length(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2simple_array__elt                               = 0x3B, //f2ptr            (f2ptr this, u64 index, f2ptr cause);

// request f2simple_array__elt

struct pcs_packet_payload_request__f2simple_array__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__elt_s pcs_packet_payload_request__f2simple_array__elt_t;

struct pcs_request__f2simple_array__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2simple_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__elt_s pcs_request__f2simple_array__elt_t;

// respond f2simple_array__elt

struct pcs_packet_payload_respond__f2simple_array__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__elt_s pcs_packet_payload_respond__f2simple_array__elt_t;

struct pcs_respond__f2simple_array__elt_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2simple_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__elt_s pcs_respond__f2simple_array__elt_t;

void send_packet__request__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2simple_array__elt(funk2_node_t* funk2_node, pcs_request__f2simple_array__elt_t* packet);
void send_packet__respond__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr elt);
void recv_packet__respond__f2simple_array__elt(funk2_node_t* funk2_node, pcs_respond__f2simple_array__elt_t* packet);

f2ptr funk2_node__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
f2ptr funk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2simple_array__elt__set                          = 0x3D, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);

// request f2simple_array__elt__set

struct pcs_packet_payload_request__f2simple_array__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2simple_array__elt__set_s pcs_packet_payload_request__f2simple_array__elt__set_t;

struct pcs_request__f2simple_array__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2simple_array__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2simple_array__elt__set_s pcs_request__f2simple_array__elt__set_t;

// respond f2simple_array__elt__set

struct pcs_packet_payload_respond__f2simple_array__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2simple_array__elt__set_s pcs_packet_payload_respond__f2simple_array__elt__set_t;

struct pcs_respond__f2simple_array__elt__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2simple_array__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2simple_array__elt__set_s pcs_respond__f2simple_array__elt__set_t;

void send_packet__request__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void recv_packet__request__f2simple_array__elt__set(funk2_node_t* funk2_node, pcs_request__f2simple_array__elt__set_t* packet);
void send_packet__respond__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2simple_array__elt__set(funk2_node_t* funk2_node, pcs_respond__f2simple_array__elt__set_t* packet);

void funk2_node__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void funk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);


//  funk2_packet_type__pcs_request__f2traced_array__new                               = 0x38, //f2ptr            (f2ptr cause, u64 length, dptr_t* dptr_array);

// request f2traced_array__new

struct pcs_packet_payload_request__f2traced_array__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  bool                                               dptr_array__defined;
  dptr_t                                             dptr_array[0];
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__new_s pcs_packet_payload_request__f2traced_array__new_t;

struct pcs_request__f2traced_array__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2traced_array__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__new_s pcs_request__f2traced_array__new_t;

// respond f2traced_array__new

struct pcs_packet_payload_respond__f2traced_array__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__new_s pcs_packet_payload_respond__f2traced_array__new_t;

struct pcs_respond__f2traced_array__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2traced_array__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__new_s pcs_respond__f2traced_array__new_t;

void send_packet__request__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, ptr dptr_array);
void recv_packet__request__f2traced_array__new(funk2_node_t* funk2_node, pcs_request__f2traced_array__new_t* packet);
void send_packet__respond__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2traced_array__new(funk2_node_t* funk2_node, pcs_respond__f2traced_array__new_t* packet);

f2ptr funk2_node__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, ptr dptr_array);
f2ptr funk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_array);


//  funk2_packet_type__pcs_request__f2traced_array__new_copy                          = 0x39, //f2ptr            (f2ptr cause, u64 length, f2ptr init_array);

// request f2traced_array__new_copy

struct pcs_packet_payload_request__f2traced_array__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
  f2ptr                                              init_array;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__new_copy_s pcs_packet_payload_request__f2traced_array__new_copy_t;

struct pcs_request__f2traced_array__new_copy_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_request__f2traced_array__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__new_copy_s pcs_request__f2traced_array__new_copy_t;

// respond f2traced_array__new_copy

struct pcs_packet_payload_respond__f2traced_array__new_copy_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new_copy;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__new_copy_s pcs_packet_payload_respond__f2traced_array__new_copy_t;

struct pcs_respond__f2traced_array__new_copy_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_respond__f2traced_array__new_copy_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__new_copy_s pcs_respond__f2traced_array__new_copy_t;

void send_packet__request__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, f2ptr init_array);
void recv_packet__request__f2traced_array__new_copy(funk2_node_t* funk2_node, pcs_request__f2traced_array__new_copy_t* packet);
void send_packet__respond__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new_copy);
void recv_packet__respond__f2traced_array__new_copy(funk2_node_t* funk2_node, pcs_respond__f2traced_array__new_copy_t* packet);

f2ptr funk2_node__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length, f2ptr init_array);
f2ptr funk2__f2traced_array__new_copy(f2ptr cause, u64 length, f2ptr init_array);


//  funk2_packet_type__pcs_request__f2traced_array__immutable                               = 0x3B, //u8            (f2ptr this, f2ptr cause);

// request f2traced_array__immutable

struct pcs_packet_payload_request__f2traced_array__immutable_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__immutable_s pcs_packet_payload_request__f2traced_array__immutable_t;

struct pcs_request__f2traced_array__immutable_s {
  funk2_packet_header_t                                   header;
  pcs_packet_payload_request__f2traced_array__immutable_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__immutable_s pcs_request__f2traced_array__immutable_t;

// respond f2traced_array__immutable

struct pcs_packet_payload_respond__f2traced_array__immutable_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u8                                                 immutable;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__immutable_s pcs_packet_payload_respond__f2traced_array__immutable_t;

struct pcs_respond__f2traced_array__immutable_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2traced_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__immutable_s pcs_respond__f2traced_array__immutable_t;

void send_packet__request__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2traced_array__immutable(funk2_node_t* funk2_node, pcs_request__f2traced_array__immutable_t* packet);
void send_packet__respond__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u8 immutable);
void recv_packet__respond__f2traced_array__immutable(funk2_node_t* funk2_node, pcs_respond__f2traced_array__immutable_t* packet);

f2ptr funk2_node__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
f2ptr funk2__f2traced_array__immutable(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__immutable__set                          = 0x3D, //void            (f2ptr cause, f2ptr this, u8 value);

// request f2traced_array__immutable__set

struct pcs_packet_payload_request__f2traced_array__immutable__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u8                                                 value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__immutable__set_s pcs_packet_payload_request__f2traced_array__immutable__set_t;

struct pcs_request__f2traced_array__immutable__set_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_request__f2traced_array__immutable__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__immutable__set_s pcs_request__f2traced_array__immutable__set_t;

// respond f2traced_array__immutable__set

struct pcs_packet_payload_respond__f2traced_array__immutable__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__immutable__set_s pcs_packet_payload_respond__f2traced_array__immutable__set_t;

struct pcs_respond__f2traced_array__immutable__set_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_respond__f2traced_array__immutable__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__immutable__set_s pcs_respond__f2traced_array__immutable__set_t;

void send_packet__request__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8 value);
void recv_packet__request__f2traced_array__immutable__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__set_t* packet);
void send_packet__respond__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__immutable__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__set_t* packet);

void funk2_node__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u8 value);
void funk2__f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value);


//  funk2_packet_type__pcs_request__f2traced_array__length                            = 0x3A, //u64              (f2ptr cause, f2ptr this);

// request f2traced_array__length

struct pcs_packet_payload_request__f2traced_array__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__length_s pcs_packet_payload_request__f2traced_array__length_t;

struct pcs_request__f2traced_array__length_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_request__f2traced_array__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__length_s pcs_request__f2traced_array__length_t;

// respond f2traced_array__length

struct pcs_packet_payload_respond__f2traced_array__length_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u64                                                length;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__length_s pcs_packet_payload_respond__f2traced_array__length_t;

struct pcs_respond__f2traced_array__length_s {
  funk2_packet_header_t                         header;
  pcs_packet_payload_respond__f2traced_array__length_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__length_s pcs_respond__f2traced_array__length_t;

void send_packet__request__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2traced_array__length(funk2_node_t* funk2_node, pcs_request__f2traced_array__length_t* packet);
void send_packet__respond__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u64 length);
void recv_packet__respond__f2traced_array__length(funk2_node_t* funk2_node, pcs_respond__f2traced_array__length_t* packet);

u64 funk2_node__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u64 funk2__f2traced_array__length(f2ptr this, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__elt                               = 0x3B, //f2ptr            (f2ptr this, u64 index, f2ptr cause);

// request f2traced_array__elt

struct pcs_packet_payload_request__f2traced_array__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt_s pcs_packet_payload_request__f2traced_array__elt_t;

struct pcs_request__f2traced_array__elt_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2traced_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt_s pcs_request__f2traced_array__elt_t;

// respond f2traced_array__elt

struct pcs_packet_payload_respond__f2traced_array__elt_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              elt;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt_s pcs_packet_payload_respond__f2traced_array__elt_t;

struct pcs_respond__f2traced_array__elt_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2traced_array__elt_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt_s pcs_respond__f2traced_array__elt_t;

void send_packet__request__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2traced_array__elt(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt_t* packet);
void send_packet__respond__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr elt);
void recv_packet__respond__f2traced_array__elt(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt_t* packet);

f2ptr funk2_node__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
f2ptr funk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__elt__set__trace_depth             = 0x3C, //f2ptr            (f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth);

// request f2traced_array__elt__set__trace_depth

struct pcs_packet_payload_request__f2traced_array__elt__set__trace_depth_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
  int                                                trace_depth;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__set__trace_depth_s pcs_packet_payload_request__f2traced_array__elt__set__trace_depth_t;

struct pcs_request__f2traced_array__elt__set__trace_depth_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_request__f2traced_array__elt__set__trace_depth_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__set__trace_depth_s pcs_request__f2traced_array__elt__set__trace_depth_t;

// respond f2traced_array__elt__set__trace_depth

struct pcs_packet_payload_respond__f2traced_array__elt__set__trace_depth_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__set__trace_depth_s pcs_packet_payload_respond__f2traced_array__elt__set__trace_depth_t;

struct pcs_respond__f2traced_array__elt__set__trace_depth_s {
  funk2_packet_header_t                                        header;
  pcs_packet_payload_respond__f2traced_array__elt__set__trace_depth_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__set__trace_depth_s pcs_respond__f2traced_array__elt__set__trace_depth_t;

void send_packet__request__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
void recv_packet__request__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__set__trace_depth_t* packet);
void send_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__set__trace_depth_t* packet);

void funk2_node__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
void funk2__f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth);


//  funk2_packet_type__pcs_request__f2traced_array__elt__set                          = 0x3D, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);

// request f2traced_array__elt__set

struct pcs_packet_payload_request__f2traced_array__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__set_s pcs_packet_payload_request__f2traced_array__elt__set_t;

struct pcs_request__f2traced_array__elt__set_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_request__f2traced_array__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__set_s pcs_request__f2traced_array__elt__set_t;

// respond f2traced_array__elt__set

struct pcs_packet_payload_respond__f2traced_array__elt__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__set_s pcs_packet_payload_respond__f2traced_array__elt__set_t;

struct pcs_respond__f2traced_array__elt__set_s {
  funk2_packet_header_t                           header;
  pcs_packet_payload_respond__f2traced_array__elt__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__set_s pcs_respond__f2traced_array__elt__set_t;

void send_packet__request__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void recv_packet__request__f2traced_array__elt__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__set_t* packet);
void send_packet__respond__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__elt__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__set_t* packet);

void funk2_node__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void funk2__f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);


//  funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on                   = 0x3E, //f2ptr            (f2ptr this, u64 index, f2ptr cause);

// request f2traced_array__elt__tracing_on

struct pcs_packet_payload_request__f2traced_array__elt__tracing_on_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__tracing_on_s pcs_packet_payload_request__f2traced_array__elt__tracing_on_t;

struct pcs_request__f2traced_array__elt__tracing_on_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2traced_array__elt__tracing_on_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__tracing_on_s pcs_request__f2traced_array__elt__tracing_on_t;

// respond f2traced_array__elt__tracing_on

struct pcs_packet_payload_respond__f2traced_array__elt__tracing_on_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              tracing_on;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__tracing_on_s pcs_packet_payload_respond__f2traced_array__elt__tracing_on_t;

struct pcs_respond__f2traced_array__elt__tracing_on_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2traced_array__elt__tracing_on_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__tracing_on_s pcs_respond__f2traced_array__elt__tracing_on_t;

void send_packet__request__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__tracing_on_t* packet);
void send_packet__respond__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr tracing_on);
void recv_packet__respond__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__tracing_on_t* packet);

f2ptr funk2_node__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
f2ptr funk2__f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on__set              = 0x3F, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);

// request f2traced_array__elt__tracing_on__set

struct pcs_packet_payload_request__f2traced_array__elt__tracing_on__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__tracing_on__set_s pcs_packet_payload_request__f2traced_array__elt__tracing_on__set_t;

struct pcs_request__f2traced_array__elt__tracing_on__set_s {
  funk2_packet_header_t                                       header;
  pcs_packet_payload_request__f2traced_array__elt__tracing_on__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__tracing_on__set_s pcs_request__f2traced_array__elt__tracing_on__set_t;

// respond f2traced_array__elt__tracing_on__set

struct pcs_packet_payload_respond__f2traced_array__elt__tracing_on__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__tracing_on__set_s pcs_packet_payload_respond__f2traced_array__elt__tracing_on__set_t;

struct pcs_respond__f2traced_array__elt__tracing_on__set_s {
  funk2_packet_header_t                                       header;
  pcs_packet_payload_respond__f2traced_array__elt__tracing_on__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__tracing_on__set_s pcs_respond__f2traced_array__elt__tracing_on__set_t;

void send_packet__request__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void recv_packet__request__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__tracing_on__set_t* packet);
void send_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__tracing_on__set_t* packet);

void funk2_node__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void funk2__f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);


//  funk2_packet_type__pcs_request__f2traced_array__elt__trace                        = 0x40, //f2ptr            (f2ptr cause, f2ptr this, u64 index);

// request f2traced_array__elt__trace

struct pcs_packet_payload_request__f2traced_array__elt__trace_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__trace_s pcs_packet_payload_request__f2traced_array__elt__trace_t;

struct pcs_request__f2traced_array__elt__trace_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_request__f2traced_array__elt__trace_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__trace_s pcs_request__f2traced_array__elt__trace_t;

// respond f2traced_array__elt__trace

struct pcs_packet_payload_respond__f2traced_array__elt__trace_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              cause;
  f2ptr                                              trace;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__trace_s pcs_packet_payload_respond__f2traced_array__elt__trace_t;

struct pcs_respond__f2traced_array__elt__trace_s {
  funk2_packet_header_t                             header;
  pcs_packet_payload_respond__f2traced_array__elt__trace_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__trace_s pcs_respond__f2traced_array__elt__trace_t;

void send_packet__request__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2traced_array__elt__trace(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__trace_t* packet);
void send_packet__respond__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr trace);
void recv_packet__respond__f2traced_array__elt__trace(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__trace_t* packet);

f2ptr funk2_node__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
f2ptr funk2__f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__elt__trace__set                   = 0x41, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);

// request f2traced_array__elt__trace__set

struct pcs_packet_payload_request__f2traced_array__elt__trace__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__trace__set_s pcs_packet_payload_request__f2traced_array__elt__trace__set_t;

struct pcs_request__f2traced_array__elt__trace__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_request__f2traced_array__elt__trace__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__trace__set_s pcs_request__f2traced_array__elt__trace__set_t;

// respond f2traced_array__elt__trace__set

struct pcs_packet_payload_respond__f2traced_array__elt__trace__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__trace__set_s pcs_packet_payload_respond__f2traced_array__elt__trace__set_t;

struct pcs_respond__f2traced_array__elt__trace__set_s {
  funk2_packet_header_t                                  header;
  pcs_packet_payload_respond__f2traced_array__elt__trace__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__trace__set_s pcs_respond__f2traced_array__elt__trace__set_t;

void send_packet__request__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void recv_packet__request__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__trace__set_t* packet);
void send_packet__respond__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__trace__set_t* packet);

void funk2_node__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void funk2__f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);


//  funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame                        = 0x42, //f2ptr            (f2ptr cause, f2ptr this, u64 index);

// request f2traced_array__elt__imagination_frame

struct pcs_packet_payload_request__f2traced_array__elt__imagination_frame_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__imagination_frame_s pcs_packet_payload_request__f2traced_array__elt__imagination_frame_t;

struct pcs_request__f2traced_array__elt__imagination_frame_s {
  funk2_packet_header_t                                                header;
  pcs_packet_payload_request__f2traced_array__elt__imagination_frame_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__imagination_frame_s pcs_request__f2traced_array__elt__imagination_frame_t;

// respond f2traced_array__elt__imagination_frame

struct pcs_packet_payload_respond__f2traced_array__elt__imagination_frame_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              imagination_frame;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__imagination_frame_s pcs_packet_payload_respond__f2traced_array__elt__imagination_frame_t;

struct pcs_respond__f2traced_array__elt__imagination_frame_s {
  funk2_packet_header_t                                                header;
  pcs_packet_payload_respond__f2traced_array__elt__imagination_frame_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__imagination_frame_s pcs_respond__f2traced_array__elt__imagination_frame_t;

void send_packet__request__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
void recv_packet__request__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__imagination_frame_t* packet);
void send_packet__respond__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr imagination_frame);
void recv_packet__respond__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__imagination_frame_t* packet);

f2ptr funk2_node__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index);
f2ptr funk2__f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause);


//  funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame__set                   = 0x43, //f2ptr            (f2ptr cause, f2ptr this, u64 index, f2ptr value);

// request f2traced_array__elt__imagination_frame__set

struct pcs_packet_payload_request__f2traced_array__elt__imagination_frame__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
  u64                                                index;
  f2ptr                                              value;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2traced_array__elt__imagination_frame__set_s pcs_packet_payload_request__f2traced_array__elt__imagination_frame__set_t;

struct pcs_request__f2traced_array__elt__imagination_frame__set_s {
  funk2_packet_header_t                                                     header;
  pcs_packet_payload_request__f2traced_array__elt__imagination_frame__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2traced_array__elt__imagination_frame__set_s pcs_request__f2traced_array__elt__imagination_frame__set_t;

// respond f2traced_array__elt__imagination_frame__set

struct pcs_packet_payload_respond__f2traced_array__elt__imagination_frame__set_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2traced_array__elt__imagination_frame__set_s pcs_packet_payload_respond__f2traced_array__elt__imagination_frame__set_t;

struct pcs_respond__f2traced_array__elt__imagination_frame__set_s {
  funk2_packet_header_t                                                     header;
  pcs_packet_payload_respond__f2traced_array__elt__imagination_frame__set_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2traced_array__elt__imagination_frame__set_s pcs_respond__f2traced_array__elt__imagination_frame__set_t;

void send_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void recv_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__imagination_frame__set_t* packet);
void send_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause);
void recv_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__imagination_frame__set_t* packet);

void funk2_node__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this, u64 index, f2ptr value);
void funk2__f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);


//  funk2_packet_type__pcs_request__f2larva__new                               = 0x44, //f2ptr            (f2ptr cause, u32 type);

// request f2larva__new

struct pcs_packet_payload_request__f2larva__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u32                                                type;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2larva__new_s pcs_packet_payload_request__f2larva__new_t;

struct pcs_request__f2larva__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_request__f2larva__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2larva__new_s pcs_request__f2larva__new_t;

// respond f2larva__new

struct pcs_packet_payload_respond__f2larva__new_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              new;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2larva__new_s pcs_packet_payload_respond__f2larva__new_t;

struct pcs_respond__f2larva__new_s {
  funk2_packet_header_t                      header;
  pcs_packet_payload_respond__f2larva__new_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2larva__new_s pcs_respond__f2larva__new_t;

void send_packet__request__f2larva__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u32 type);
void recv_packet__request__f2larva__new(funk2_node_t* funk2_node, pcs_request__f2larva__new_t* packet);
void send_packet__respond__f2larva__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr new);
void recv_packet__respond__f2larva__new(funk2_node_t* funk2_node, pcs_respond__f2larva__new_t* packet);

f2ptr funk2_node__f2larva__new(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u32 type);
f2ptr funk2__f2larva__new(f2ptr cause, u32 type);


//  funk2_packet_type__pcs_request__f2larva__type                              = 0x45, //u32              (f2ptr cause, f2ptr this);

// request f2larva__type

struct pcs_packet_payload_request__f2larva__type_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  f2ptr                                              this;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_request__f2larva__type_s pcs_packet_payload_request__f2larva__type_t;

struct pcs_request__f2larva__type_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_request__f2larva__type_t payload;
} __attribute__((__packed__));
typedef struct pcs_request__f2larva__type_s pcs_request__f2larva__type_t;

// respond f2larva__type

struct pcs_packet_payload_respond__f2larva__type_s {
  pcs_packet_payload_header__action_payload_header_t action_payload_header;
  u32                                                type;
} __attribute__((__packed__));
typedef struct pcs_packet_payload_respond__f2larva__type_s pcs_packet_payload_respond__f2larva__type_t;

struct pcs_respond__f2larva__type_s {
  funk2_packet_header_t                       header;
  pcs_packet_payload_respond__f2larva__type_t payload;
} __attribute__((__packed__));
typedef struct pcs_respond__f2larva__type_s pcs_respond__f2larva__type_t;

void send_packet__request__f2larva__type(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
void recv_packet__request__f2larva__type(funk2_node_t* funk2_node, pcs_request__f2larva__type_t* packet);
void send_packet__respond__f2larva__type(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, u32 type);
void recv_packet__respond__f2larva__type(funk2_node_t* funk2_node, pcs_respond__f2larva__type_t* packet);

u32 funk2_node__f2larva__type(funk2_node_t* funk2_node, f2ptr this_thread, f2ptr cause, f2ptr this);
u32 funk2__f2larva__type(f2ptr this, f2ptr cause);

#define rf2_to_lf2(rf2) (funk2_node__remote_f2ptr_to_local_f2ptr(funk2_node, rf2))




#endif // SPINNERD_PACKET__H

