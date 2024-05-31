#include "tdouble.h"

#define T_DOUBLE_TYPE  (t_double_get_type ())
#define PROP_DOUBLE_ID 1

// -- Internals ----------------------------------------------------------------------------------------------------- //

struct _TDouble
{
  GObject parent;
  double  value;
};

static guint       t_double_signal_div_by_zero;
static GParamSpec *double_property = NULL;

G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT)

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
div_by_zero_default_cb (TDouble *self, gpointer user_data)
{
  g_printerr ("Error in %s: Division by Zero.\n", __FILE__);
}

static void
t_double_class_init (TDoubleClass *class)
{
  const gchar *signal_name    = "div-by-zero";
  GSignalFlags signal_flags   = G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS;
  GType        class_type     = G_TYPE_FROM_CLASS (class);
  GCallback    default_cb     = G_CALLBACK (div_by_zero_default_cb);
  t_double_signal_div_by_zero = g_signal_new_class_handler (signal_name, class_type, signal_flags, default_cb, NULL,
                                                            NULL, NULL, G_TYPE_NONE, 0);

  // register property "value"
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  gobject_class->set_property = t_double_set_property;
  gobject_class->get_property = t_double_get_property;
  double_property
      = g_param_spec_double ("value", "val", "Double value", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_READWRITE);
  g_object_class_install_property (gobject_class, PROP_DOUBLE_ID, double_property);
}

static void
t_double_init (TDouble *d)
{
}

// ---------- API --------------------------------------------------------------------------------------------------- //

// constructor
TDouble *
t_double_new (double value)
{
  TDouble *d = g_object_new (T_DOUBLE_TYPE, "value", value, NULL);
  // d->value   = value;
  return d;
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

  double right_val = other->value;
  if (!right_val)
    {
      g_signal_emit (other, t_double_signal_div_by_zero, 0);
      return NULL;
    }

  double left_val = self->value;
  return t_double_new (left_val / right_val);
}

// unary minus
TDouble *
t_double_uminus (TDouble *self)
{
  g_return_val_if_fail (T_IS_DOUBLE (self), NULL);
  return t_double_new (-self->value);
}
