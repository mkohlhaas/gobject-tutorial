#pragma once

#include <glib-object.h>

G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, GObject)

TDouble *t_double_new (double value);
TDouble *t_double_add (TDouble *self, TDouble *other);
TDouble *t_double_sub (TDouble *self, TDouble *other);
TDouble *t_double_mul (TDouble *self, TDouble *other);
TDouble *t_double_div (TDouble *self, TDouble *other);
TDouble *t_double_uminus (TDouble *self);
