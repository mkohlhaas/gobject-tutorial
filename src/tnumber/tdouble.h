#pragma once

#include "tnumber.h"
#include <glib-object.h>

#define T_TYPE_DOUBLE (t_double_get_type ())
G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, TNumber)

TDouble *t_double_new_with_value (double value);
TDouble *t_double_new (void);
