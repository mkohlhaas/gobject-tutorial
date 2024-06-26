#pragma once

#include <glib-object.h>

#define T_TYPE_NUMBER (t_number_get_type ())

G_DECLARE_DERIVABLE_TYPE (TNumber, t_number, T, NUMBER, GObject)

struct _TNumberClass
{
  GObjectClass parent_class;
  TNumber *(*add) (TNumber *self, TNumber *other);
  TNumber *(*sub) (TNumber *self, TNumber *other);
  TNumber *(*mul) (TNumber *self, TNumber *other);
  TNumber *(*div) (TNumber *self, TNumber *other);
  TNumber *(*uminus) (TNumber *self);
  char *(*to_s) (TNumber *self);
  void (*div_by_zero) (TNumber *self);
};

TNumber *t_number_add (TNumber *self, TNumber *other);
TNumber *t_number_sub (TNumber *self, TNumber *other);
TNumber *t_number_mul (TNumber *self, TNumber *other);
TNumber *t_number_div (TNumber *self, TNumber *other);
TNumber *t_number_uminus (TNumber *self);
char    *t_number_to_s (TNumber *self);
