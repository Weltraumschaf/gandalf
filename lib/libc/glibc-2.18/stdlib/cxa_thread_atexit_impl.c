/* Register destructors for C++ TLS variables declared with thread_local.
   Copyright (C) 2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <stdlib.h>
#include <ldsodefs.h>

typedef void (*dtor_func) (void *);

struct dtor_list
{
  dtor_func func;
  void *obj;
  struct link_map *map;
  struct dtor_list *next;
};

static __thread struct dtor_list *tls_dtor_list;
static __thread void *dso_symbol_cache;
static __thread struct link_map *lm_cache;

/* Register a destructor for TLS variables declared with the 'thread_local'
   keyword.  This function is only called from code generated by the C++
   compiler.  FUNC is the destructor function and OBJ is the object to be
   passed to the destructor.  DSO_SYMBOL is the __dso_handle symbol that each
   DSO has at a unique address in its map, added from crtbegin.o during the
   linking phase.  */
int
__cxa_thread_atexit_impl (dtor_func func, void *obj, void *dso_symbol)
{
  /* Prepend.  */
  struct dtor_list *new = calloc (1, sizeof (struct dtor_list));
  new->func = func;
  new->obj = obj;
  new->next = tls_dtor_list;
  tls_dtor_list = new;

  /* See if we already encountered the DSO.  */
  __rtld_lock_lock_recursive (GL(dl_load_lock));

  if (__builtin_expect (dso_symbol_cache != dso_symbol, 0))
    {
      ElfW(Addr) caller = (ElfW(Addr)) dso_symbol;

      struct link_map *l = _dl_find_dso_for_object (caller);

      /* If the address is not recognized the call comes from the main
         program (we hope).  */
      lm_cache = l ? l : GL(dl_ns)[LM_ID_BASE]._ns_loaded;
    }
  /* A destructor could result in a thread_local construction and the former
     could have cleared the flag.  */
  if (lm_cache->l_type == lt_loaded && lm_cache->l_tls_dtor_count == 0)
    lm_cache->l_flags_1 |= DF_1_NODELETE;

  new->map = lm_cache;
  new->map->l_tls_dtor_count++;

  __rtld_lock_unlock_recursive (GL(dl_load_lock));

  return 0;
}

/* Call the destructors.  This is called either when a thread returns from the
   initial function or when the process exits via the exit function.  */
void
__call_tls_dtors (void)
{
  while (tls_dtor_list)
    {
      struct dtor_list *cur = tls_dtor_list;
      tls_dtor_list = tls_dtor_list->next;

      cur->func (cur->obj);

      __rtld_lock_lock_recursive (GL(dl_load_lock));

      /* Allow DSO unload if count drops to zero.  */
      cur->map->l_tls_dtor_count--;
      if (cur->map->l_tls_dtor_count == 0 && cur->map->l_type == lt_loaded)
        cur->map->l_flags_1 &= ~DF_1_NODELETE;

      __rtld_lock_unlock_recursive (GL(dl_load_lock));

      free (cur);
    }
}
libc_hidden_def (__call_tls_dtors)
