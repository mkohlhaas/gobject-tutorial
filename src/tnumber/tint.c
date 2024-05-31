#include "tint.h"
#include "tdouble.h"

// ------------ TInt ------------------------------------------------------------------------------------------------ //

struct _TInt
{
  TNumber parent;
  int     value;
};

G_DEFINE_TYPE (TInt, t_int, T_TYPE_NUMBER)

TInt *
t_int_new_with_value (int value)
{
  TInt *i = g_object_new (T_TYPE_INT, "value", value, NULL);
  return i;
}

TInt *
t_int_new (void)
{
  TInt *i = g_object_new (T_TYPE_INT, NULL);
  return i;
}

#define T_INT_BINARY_OP(op)                                                                                            \
  int    i;                                                                                                            \
  double d;                                                                                                            \
  if (T_IS_INT (other))                                                                                                \
    {                                                                                                                  \
      g_object_get (T_INT (other), "value", &i, NULL);                                                                 \
      return T_NUMBER (t_int_new_with_value (T_INT (self)->value op i));                                               \
    }                                                                                                                  \
  else                                                                                                                 \
    {                                                                                                                  \
      g_object_get (T_DOUBLE (other), "value", &d, NULL);                                                              \
      return T_NUMBER (t_int_new_with_value (T_INT (self)->value op (int) d));                                         \
    }

#define T_INT_OP(op_name, op)                                                                                          \
  static TNumber *t_int_##op_name (TNumber *self, TNumber *other)                                                      \
  {                                                                                                                    \
    g_return_val_if_fail (T_IS_INT (self), NULL);                                                                      \
    T_INT_BINARY_OP (+)                                                                                                \
  }

T_INT_OP (add, +)
T_INT_OP (mul, *)
T_INT_OP (sub, -)

static TNumber *
t_int_div (TNumber *self, TNumber *other)
{
  g_return_val_if_fail (T_IS_INT (self), NULL);

  if (T_IS_INT (other))
    {
      int i;
      g_object_get (T_INT (other), "value", &i, NULL);
      if (i == 0)
        {
          g_signal_emit_by_name (self, "div-by-zero");
          return NULL;
        }
      else
        {
          return T_NUMBER (t_int_new_with_value (T_INT (self)->value / i));
        }
    }
  else
    {
      double d;
      g_object_get (T_DOUBLE (other), "value", &d, NULL);
      if (d == 0)
        {
          g_signal_emit_by_name (self, "div-by-zero");
          return NULL;
        }
      else
        {
          return T_NUMBER (t_int_new_with_value (T_INT (self)->value / (int)d));
        }
    }
}

static TNumber *
t_int_uminus (TNumber *self)
{
  g_return_val_if_fail (T_IS_INT (self), NULL);
  return T_NUMBER (t_int_new_with_value (-T_INT (self)->value));
}

static char *
t_int_to_s (TNumber *self)
{
  g_return_val_if_fail (T_IS_INT (self), NULL);
  int i;
  g_object_get (T_INT (self), "value", &i, NULL);
  return g_strdup_printf ("%d", i);
}

// ------------ Internals ------------------------------------------------------------------------------------------- //

#define PROP_INT_ID 1

static GParamSpec *int_property = NULL;

static void
t_int_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
  TInt *self = T_INT (object);
  if (property_id == PROP_INT_ID)
    {
      self->value = g_value_get_int (value);
    }
  else
    {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_int_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
  TInt *self = T_INT (object);
  if (property_id == PROP_INT_ID)
    {
      g_value_set_int (value, self->value);
    }
  else
    {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_int_class_init (TIntClass *class)
{
  /* override virtual functions */
  TNumberClass *tnumber_class = T_NUMBER_CLASS (class);
  tnumber_class->add          = t_int_add;
  tnumber_class->sub          = t_int_sub;
  tnumber_class->mul          = t_int_mul;
  tnumber_class->div          = t_int_div;
  tnumber_class->uminus       = t_int_uminus;
  tnumber_class->to_s         = t_int_to_s;

  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  gobject_class->set_property = t_int_set_property;
  gobject_class->get_property = t_int_get_property;

  const gchar *name  = "value";
  const gchar *nick  = "val";
  const gchar *blurb = "Integer value";
  GParamFlags  flags = G_PARAM_READWRITE;
  int_property       = g_param_spec_int (name, nick, blurb, G_MININT, G_MAXINT, 0, flags);
  g_object_class_install_property (gobject_class, PROP_INT_ID, int_property);
}

static void
t_int_init (TInt *self)
{
}
