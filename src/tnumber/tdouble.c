#include "tdouble.h"
#include "tint.h"

// ------------ TDouble --------------------------------------------------------------------------------------------- //

struct _TDouble
{
  TNumber parent;
  double  value;
};

G_DEFINE_TYPE (TDouble, t_double, T_TYPE_NUMBER)

TDouble *
t_double_new_with_value (double value)
{
  TDouble *d = g_object_new (T_TYPE_DOUBLE, "value", value, NULL);
  return d;
}

TDouble *
t_double_new (void)
{
  TDouble *d = g_object_new (T_TYPE_DOUBLE, NULL);
  return d;
}

#define T_DOUBLE_BINARY_OP(op)                                                                                         \
  if (T_IS_INT (other))                                                                                                \
    {                                                                                                                  \
      int i;                                                                                                           \
      g_object_get (T_INT (other), "value", &i, NULL);                                                                 \
      return T_NUMBER (t_double_new_with_value (T_DOUBLE (self)->value op (double) i));                                \
    }                                                                                                                  \
  else                                                                                                                 \
    {                                                                                                                  \
      double d;                                                                                                        \
      g_object_get (T_DOUBLE (other), "value", &d, NULL);                                                              \
      return T_NUMBER (t_double_new_with_value (T_DOUBLE (self)->value op d));                                         \
    }

#define T_DOUBLE_OP(op_name, op)                                                                                       \
  static TNumber *t_double_##op_name (TNumber *self, TNumber *other)                                                   \
  {                                                                                                                    \
    g_return_val_if_fail (T_IS_DOUBLE (self), NULL);                                                                   \
    T_DOUBLE_BINARY_OP (+)                                                                                             \
  }

T_DOUBLE_OP (add, +)
T_DOUBLE_OP (mul, *)
T_DOUBLE_OP (sub, -)

static TNumber *
t_double_div (TNumber *self, TNumber *other)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);

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
          return T_NUMBER (t_double_new_with_value (T_DOUBLE (self)->value / (double)i));
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
          return T_NUMBER (t_double_new_with_value (T_DOUBLE (self)->value / d));
        }
    }
}

static TNumber *
t_double_uminus (TNumber *self)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);
  return T_NUMBER (t_double_new_with_value (-T_DOUBLE (self)->value));
}

static char *
t_double_to_s (TNumber *self)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);
  double d;
  g_object_get (T_DOUBLE (self), "value", &d, NULL);
  return g_strdup_printf ("%f", d);
}

// ------------ Internals ------------------------------------------------------------------------------------------- //

#define PROP_DOUBLE_ID 1

static GParamSpec *double_property = NULL;

static void
t_double_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
  TDouble *self = T_DOUBLE (object);
  if (property_id == PROP_DOUBLE_ID)
    {
      self->value = g_value_get_double (value);
    }
  else
    {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_double_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
  TDouble *self = T_DOUBLE (object);
  if (property_id == PROP_DOUBLE_ID)
    {
      g_value_set_double (value, self->value);
    }
  else
    {
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}

static void
t_double_class_init (TDoubleClass *class)
{
  /* override virtual functions */
  TNumberClass *tnumber_class = T_NUMBER_CLASS (class);
  tnumber_class->add          = t_double_add;
  tnumber_class->sub          = t_double_sub;
  tnumber_class->mul          = t_double_mul;
  tnumber_class->div          = t_double_div;
  tnumber_class->uminus       = t_double_uminus;
  tnumber_class->to_s         = t_double_to_s;

  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  gobject_class->set_property = t_double_set_property;
  gobject_class->get_property = t_double_get_property;

  const gchar *name  = "value";
  const gchar *nick  = "val";
  const gchar *blurb = "Double value";
  GParamFlags  flags = G_PARAM_READWRITE;
  double_property    = g_param_spec_double (name, nick, blurb, -G_MAXDOUBLE, G_MAXDOUBLE, 0, flags);
  g_object_class_install_property (gobject_class, PROP_DOUBLE_ID, double_property);
}

static void
t_double_init (TDouble *self)
{
}
