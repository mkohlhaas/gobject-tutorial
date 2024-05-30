#include "glib.h"
#include "tdouble.h"
#include <glib-object.h>

static void
t_print (char *op, TDouble *d1, TDouble *d2, TDouble *d3)
{
  double v1, v2, v3;

  if (!t_double_get_value (d1, &v1))
    {
      return;
    }
  if (!t_double_get_value (d2, &v2))
    {
      return;
    }
  if (!t_double_get_value (d3, &v3))
    {
      return;
    }

  g_print ("%.2f %s %.2f = %.2f\n", v1, op, v2, v3);
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
div_by_zero_cb (TDouble *self, gpointer user_data)
{
  g_printerr ("Error in %s: Division by Zero before message.\n", __FILE__);
}

static void
div_by_zero_after_cb (TDouble *self, gpointer user_data)
{
  g_printerr ("Error in %s: Division by Zero after message.\n", __FILE__);
}

int
main (int argc, char **argv)
{
  TDouble *d1 = t_double_new (20.0);
  TDouble *d2 = t_double_new (10.0);

  TDouble *d3 = t_double_add (d1, d2);
  T_PRN_UNREF ("+", d1, d2, d3);

  d3 = t_double_sub (d1, d2);
  T_PRN_UNREF ("-", d1, d2, d3);

  d3 = t_double_mul (d1, d2);
  T_PRN_UNREF ("*", d1, d2, d3);

  d3 = t_double_div (d1, d2);
  T_PRN_UNREF ("/", d1, d2, d3);

  t_double_set (d2, 0.0);
  g_signal_connect (d2, signal_name, G_CALLBACK (div_by_zero_cb), NULL);
  g_signal_connect_after (d2, signal_name, G_CALLBACK (div_by_zero_after_cb), NULL);
  d3 = t_double_div (d1, d2);

  t_double_set (d1, -20.0);
  d3 = t_double_uminus (d1);
  if (d3)
    {
      g_print ("-(%.2f)     = %.2f\n", t_double_get (d1), t_double_get (d3));
      g_object_unref (d3);
    }

  g_object_unref (d1);
  g_object_unref (d2);
}
