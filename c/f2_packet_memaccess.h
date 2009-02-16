#ifndef F2__PACKET__MEMACCESS__H
#define F2__PACKET__MEMACCESS__H

//#define F2__MEMACCESS__PTYPE

#if defined(F2__MEMACCESS__PTYPE)
#  define f2system__environment pfunk2__system__environment
#else
#  define f2system__environment funk2__system__environment
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define memblock__creation_microseconds_since_1970 pfunk2__memblock__creation_microseconds_since_1970
#else
#  define memblock__creation_microseconds_since_1970 funk2__memblock__creation_microseconds_since_1970
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2ptype__raw pfunk2__f2ptype__raw
#else
#  define f2ptype__raw funk2__f2ptype__raw
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2ptype__cause pfunk2__f2ptype__cause
#else
#  define f2ptype__cause funk2__f2ptype__cause
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2ptype__cause__set pfunk2__f2ptype__cause__set
#else
#  define f2ptype__cause__set funk2__f2ptype__cause__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2integer__new pfunk2__f2integer__new
#else
#  define f2integer__new funk2__f2integer__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2integer__i pfunk2__f2integer__i
#else
#  define f2integer__i funk2__f2integer__i
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2double__new pfunk2__f2double__new
#else
#  define f2double__new funk2__f2double__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2double__d pfunk2__f2double__d
#else
#  define f2double__d funk2__f2double__d
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2float__new pfunk2__f2float__new
#else
#  define f2float__new funk2__f2float__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2float__f pfunk2__f2float__f
#else
#  define f2float__f funk2__f2float__f
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2pointer__new pfunk2__f2pointer__new
#else
#  define f2pointer__new funk2__f2pointer__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2pointer__p pfunk2__f2pointer__p
#else
#  define f2pointer__p funk2__f2pointer__p
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__new pfunk2__f2gfunkptr__new
#else
#  define f2gfunkptr__new funk2__f2gfunkptr__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__new_from_f2ptr pfunk2__f2gfunkptr__new_from_f2ptr
#else
#  define f2gfunkptr__new_from_f2ptr funk2__f2gfunkptr__new_from_f2ptr
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__gfunkptr pfunk2__f2gfunkptr__gfunkptr
#else
#  define f2gfunkptr__gfunkptr funk2__f2gfunkptr__gfunkptr
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__computer_id pfunk2__f2gfunkptr__computer_id
#else
#  define f2gfunkptr__computer_id funk2__f2gfunkptr__computer_id
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__pool_index pfunk2__f2gfunkptr__pool_index
#else
#  define f2gfunkptr__pool_index funk2__f2gfunkptr__pool_index
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2gfunkptr__pool_address pfunk2__f2gfunkptr__pool_address
#else
#  define f2gfunkptr__pool_address funk2__f2gfunkptr__pool_address
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2mutex__new pfunk2__f2mutex__new
#else
#  define f2mutex__new funk2__f2mutex__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2mutex__lock pfunk2__f2mutex__lock
#else
#  define f2mutex__lock funk2__f2mutex__lock
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2mutex__unlock pfunk2__f2mutex__unlock
#else
#  define f2mutex__unlock funk2__f2mutex__unlock
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2mutex__trylock pfunk2__f2mutex__trylock
#else
#  define f2mutex__trylock funk2__f2mutex__trylock
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2char__new pfunk2__f2char__new
#else
#  define f2char__new funk2__f2char__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2char__ch pfunk2__f2char__ch
#else
#  define f2char__ch funk2__f2char__ch
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2string__new pfunk2__f2string__new
#else
#  define f2string__new funk2__f2string__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2string__length pfunk2__f2string__length
#else
#  define f2string__length funk2__f2string__length
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2string__elt pfunk2__f2string__elt
#else
#  define f2string__elt funk2__f2string__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2string__str_copy pfunk2__f2string__str_copy
#else
#  define f2string__str_copy funk2__f2string__str_copy
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2string__hash_value pfunk2__f2string__hash_value
#else
#  define f2string__hash_value funk2__f2string__hash_value
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2symbol__new pfunk2__f2symbol__new
#else
#  define f2symbol__new funk2__f2symbol__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2symbol__length pfunk2__f2symbol__length
#else
#  define f2symbol__length funk2__f2symbol__length
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2symbol__hash_value pfunk2__f2symbol__hash_value
#else
#  define f2symbol__hash_value funk2__f2symbol__hash_value
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2symbol__elt pfunk2__f2symbol__elt
#else
#  define f2symbol__elt funk2__f2symbol__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2symbol__str_copy pfunk2__f2symbol__str_copy
#else
#  define f2symbol__str_copy funk2__f2symbol__str_copy
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__new pfunk2__f2chunk__new
#else
#  define f2chunk__new funk2__f2chunk__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__new_copy pfunk2__f2chunk__new_copy
#else
#  define f2chunk__new_copy funk2__f2chunk__new_copy
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__length pfunk2__f2chunk__length
#else
#  define f2chunk__length funk2__f2chunk__length
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit8__elt pfunk2__f2chunk__bit8__elt
#else
#  define f2chunk__bit8__elt funk2__f2chunk__bit8__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit8__elt__set pfunk2__f2chunk__bit8__elt__set
#else
#  define f2chunk__bit8__elt__set funk2__f2chunk__bit8__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit16__elt pfunk2__f2chunk__bit16__elt
#else
#  define f2chunk__bit16__elt funk2__f2chunk__bit16__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit16__elt__set pfunk2__f2chunk__bit16__elt__set
#else
#  define f2chunk__bit16__elt__set funk2__f2chunk__bit16__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit32__elt pfunk2__f2chunk__bit32__elt
#else
#  define f2chunk__bit32__elt funk2__f2chunk__bit32__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit32__elt__set pfunk2__f2chunk__bit32__elt__set
#else
#  define f2chunk__bit32__elt__set funk2__f2chunk__bit32__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit64__elt pfunk2__f2chunk__bit64__elt
#else
#  define f2chunk__bit64__elt funk2__f2chunk__bit64__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bit64__elt__set pfunk2__f2chunk__bit64__elt__set
#else
#  define f2chunk__bit64__elt__set funk2__f2chunk__bit64__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__cfunk_jump pfunk2__f2chunk__cfunk_jump
#else
#  define f2chunk__cfunk_jump funk2__f2chunk__cfunk_jump
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__bytecode_jump pfunk2__f2chunk__bytecode_jump
#else
#  define f2chunk__bytecode_jump funk2__f2chunk__bytecode_jump
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__send pfunk2__f2chunk__send
#else
#  define f2chunk__send funk2__f2chunk__send
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2chunk__recv pfunk2__f2chunk__recv
#else
#  define f2chunk__recv funk2__f2chunk__recv
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2simple_array__new pfunk2__f2simple_array__new
#else
#  define f2simple_array__new funk2__f2simple_array__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2simple_array__new_copy pfunk2__f2simple_array__new_copy
#else
#  define f2simple_array__new_copy funk2__f2simple_array__new_copy
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2simple_array__length pfunk2__f2simple_array__length
#else
#  define f2simple_array__length funk2__f2simple_array__length
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2simple_array__elt pfunk2__f2simple_array__elt
#else
#  define f2simple_array__elt funk2__f2simple_array__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2simple_array__elt__set pfunk2__f2simple_array__elt__set
#else
#  define f2simple_array__elt__set funk2__f2simple_array__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__new pfunk2__f2traced_array__new
#else
#  define f2traced_array__new funk2__f2traced_array__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__new_copy pfunk2__f2traced_array__new_copy
#else
#  define f2traced_array__new_copy funk2__f2traced_array__new_copy
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__length pfunk2__f2traced_array__length
#else
#  define f2traced_array__length funk2__f2traced_array__length
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt pfunk2__f2traced_array__elt
#else
#  define f2traced_array__elt funk2__f2traced_array__elt
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__set__trace_depth pfunk2__f2traced_array__elt__set__trace_depth
#else
#  define f2traced_array__elt__set__trace_depth funk2__f2traced_array__elt__set__trace_depth
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__set pfunk2__f2traced_array__elt__set
#else
#  define f2traced_array__elt__set funk2__f2traced_array__elt__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__tracing_on pfunk2__f2traced_array__elt__tracing_on
#else
#  define f2traced_array__elt__tracing_on funk2__f2traced_array__elt__tracing_on
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__tracing_on__set pfunk2__f2traced_array__elt__tracing_on__set
#else
#  define f2traced_array__elt__tracing_on__set funk2__f2traced_array__elt__tracing_on__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__trace pfunk2__f2traced_array__elt__trace
#else
#  define f2traced_array__elt__trace funk2__f2traced_array__elt__trace
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__trace__set pfunk2__f2traced_array__elt__trace__set
#else
#  define f2traced_array__elt__trace__set funk2__f2traced_array__elt__trace__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__imagination_frame pfunk2__f2traced_array__elt__imagination_frame
#else
#  define f2traced_array__elt__imagination_frame funk2__f2traced_array__elt__imagination_frame
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2traced_array__elt__imagination_frame__set pfunk2__f2traced_array__elt__imagination_frame__set
#else
#  define f2traced_array__elt__imagination_frame__set funk2__f2traced_array__elt__imagination_frame__set
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2larva__new pfunk2__f2larva__new
#else
#  define f2larva__new funk2__f2larva__new
#endif

#if defined(F2__MEMACCESS__PTYPE)
#  define f2larva__type pfunk2__f2larva__type
#else
#  define f2larva__type funk2__f2larva__type
#endif


#endif // F2__PACKET__MEMACCESS__H
