#include "tdouble.h"

// ---------- TDouble --------------------------------- //

#define T_DOUBLE_TYPE (t_double_get_type ())

static guint t_double_signal_div_by_zero;

struct _TDouble
{
  GObject parent;
  double  value;
};

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT)

static void
t_double_class_init (TDoubleClass *class)
{
  GSignalFlags signal_flags = G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS;
  t_double_signal_div_by_zero
      = g_signal_new (signal_name, G_TYPE_FROM_CLASS (class), signal_flags, 0, NULL, NULL, NULL, G_TYPE_NONE, 0);
}

static void
t_double_init (TDouble *d)
{
}

// ---------- API ------------------------------------- //

// constructor
TDouble *
t_double_new (double value)
{
  TDouble *d = g_object_new (T_DOUBLE_TYPE, NULL);
  d->value   = value;
  return d;
}

// getter
gboolean
t_double_get_value (TDouble *self, double *value)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), FALSE);
  *value = self->value;
  return TRUE;
}

double
t_double_get (TDouble *self)
{
  return self->value;
}

// setter
void
t_double_set_value (TDouble *self, double value)
{
  g_return_if_fail (T_IS_DOUBLE (self));
  self->value = value;
}

void
t_double_set (TDouble *self, double value)
{
  self->value = value;
}

// arithmetic operations
#define T_DOUBLE_OP(op_name, op)                                                                                       \
  TDouble *t_double_##op_name (TDouble *self, TDouble *other)                                                          \
  {                                                                                                                    \
    g_return_val_if_fail (T_IS_DOUBLE (self), NULL);                                                                   \
    g_return_val_if_fail (T_IS_DOUBLE (other), NULL);                                                                  \
    return t_double_new (self->value op other->value);                                                                 \
  }

T_DOUBLE_OP (add, +);
T_DOUBLE_OP (mul, *);
T_DOUBLE_OP (sub, -);

TDouble *
t_double_div (TDouble *self, TDouble *other)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);
  g_return_val_if_fail (T_IS_DOUBLE (other), NULL);
  double value;

  if ((!t_double_get_value (other, &value)))
    {
      return NULL;
    }
  else if (value == 0)
    {
      g_signal_emit (other, t_double_signal_div_by_zero, 0);
      return NULL;
    }
  return t_double_new (self->value / value);
}

// unary minus
TDouble *
t_double_uminus (TDouble *self)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);

  return t_double_new (-self->value);
}
