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

#ifndef F2__GMODULE__H
#define F2__GMODULE__H

/*
                    GModule;
gboolean            g_module_supported                  (void);
gchar*              g_module_build_path                 (const gchar *directory,
                                                         const gchar *module_name);
GModule*            g_module_open                       (const gchar *file_name,
                                                         GModuleFlags flags);
enum                GModuleFlags;
gboolean            g_module_symbol                     (GModule *module,
                                                         const gchar *symbol_name,
                                                         gpointer *symbol);
const gchar*        g_module_name                       (GModule *module);
void                g_module_make_resident              (GModule *module);
gboolean            g_module_close                      (GModule *module);
const gchar*        g_module_error                      (void);

const gchar*        (*GModuleCheckInit)                 (GModule *module);
void                (*GModuleUnload)                    (GModule *module);
#define             G_MODULE_SUFFIX
#define             G_MODULE_EXPORT
#define             G_MODULE_IMPORT
*/

#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_compile.h"
#include "f2_time.h"

f2ptr f2__g_module_supported    ();
f2ptr f2__g_module_build_path   (f2ptr cause, f2ptr directory, f2ptr module_name);
f2ptr f2__g_module_open         (f2ptr cause, f2ptr file_name, f2ptr flags);
f2ptr f2__g_module_symbol       (f2ptr cause, f2ptr module, f2ptr symbol_name);
f2ptr f2__g_module_name         (f2ptr cause, f2ptr module);
void  f2__g_module_make_resident(f2ptr cause, f2ptr module);
f2ptr f2__g_module_close        (f2ptr cause, f2ptr module);
f2ptr f2__g_module_error        (f2ptr cause);

#endif // F2__GMODULE__H

