#pragma once

#include "../tnumber/tnumber.h"
#include "tstr.h"
#include <glib-object.h>

#define T_TYPE_NUM_STR (t_num_str_get_type ())

G_DECLARE_FINAL_TYPE (TNumStr, t_num_str, T, NUM_STR, TStr)

enum
{
  t_none,
  t_int,
  t_double
};

// TNumStr can have any string, which is t_none, t_int or t_double type.
// If the type is t_none, t_num_str_get_t_number returns NULL.
// It is good idea to call t_num_str_get_string_type and check the type in advance.

int      t_num_str_get_string_type (TNumStr *self);
void     t_num_str_set_from_t_number (TNumStr *self, TNumber *num);
TNumber *t_num_str_get_t_number (TNumStr *self);
TNumStr *t_num_str_new_with_tnumber (TNumber *num);
TNumStr *t_num_str_new (void);
