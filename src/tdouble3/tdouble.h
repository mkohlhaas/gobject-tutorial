#pragma once

#include <glib-object.h>

G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, GObject)

static char *signal_name = "div-by-zero";

TDouble *t_double_new (double value);
double   t_double_get (TDouble *self);
gboolean t_double_get_value (TDouble *self, double *value);
void     t_double_set (TDouble *self, double value);
void     t_double_set_value (TDouble *self, double value);
TDouble *t_double_add (TDouble *self, TDouble *other);
TDouble *t_double_sub (TDouble *self, TDouble *other);
TDouble *t_double_mul (TDouble *self, TDouble *other);
TDouble *t_double_div (TDouble *self, TDouble *other);
TDouble *t_double_uminus (TDouble *self);
