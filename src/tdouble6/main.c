#include "glib.h"
#include "tdouble.h"
#include <glib-object.h>

static double
get_value (TDouble *d)
{
  double v;
  g_object_get (d, "value", &v, NULL);
  return v;
}

void
set_value (TDouble *d, double value)
{
  g_object_set (d, "value", value, NULL);
}

static void
t_print (char *op, TDouble *d1, TDouble *d2, TDouble *d3)
{
  g_print ("%lf %s %lf = %lf\n", get_value (d1), op, get_value (d2), get_value (d3));
}

#define T_PRN_UNREF(op, d1, d2, d3)                                                                                    \
  if (d3)                                                                                                              \
    {                                                                                                                  \
      t_print (op, d1, d2, d3);                                                                                        \
      g_object_unref (d3);                                                                                             \
    }                                                                                                                  \
  else                                                                                                                 \
    {                                                                                                                  \
      g_print ("Operation %s failed!\n", op);                                                                          \
    }

static void
notify_cb (GObject *gobject, GParamSpec *pspec, gpointer user_data)
{
  const char *name = g_param_spec_get_name (pspec);
  if (T_IS_DOUBLE (gobject) && strcmp (name, "value") == 0)
    {
      double v;
      g_object_get (T_DOUBLE (gobject), "value", &v, NULL);
      g_print ("Property \"%s\" is set to %lf.\n", name, v);
    }
}

void
connect_signal (TDouble *d)
{
  g_signal_connect (G_OBJECT (d), "notify::value", G_CALLBACK (notify_cb), NULL);
}

int
main (void)
{
  TDouble *d1 = t_double_new (10.0);
  TDouble *d2 = t_double_new (20.0);

  connect_signal (d1);
  connect_signal (d2);

  TDouble *d3 = t_double_add (d1, d2);
  T_PRN_UNREF ("+", d1, d2, d3);

  d3 = t_double_sub (d1, d2);
  T_PRN_UNREF ("-", d1, d2, d3);

  d3 = t_double_mul (d1, d2);
  T_PRN_UNREF ("*", d1, d2, d3);

  d3 = t_double_div (d1, d2);
  T_PRN_UNREF ("/", d1, d2, d3);

  set_value (d2, 0.0);
  d3 = t_double_div (d1, d2);

  set_value (d1, -20.0);
  d3 = t_double_uminus (d1);
  g_print ("-(%.2f)     = %.2f\n", get_value (d1), get_value (d3));
  g_object_unref (d3);

  g_object_unref (d1);
  g_object_unref (d2);
}
