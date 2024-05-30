#pragma once

#include <glib-object.h>

G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, GObject)

gboolean t_double_get_value (TDouble *self, double *value);
void     t_double_set_value (TDouble *self, double value);
TDouble *t_double_new (double value);
