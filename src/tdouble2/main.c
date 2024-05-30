#include <glib-object.h>
#include "tdouble.h"

static void
t_print (char *op, TDouble *d1, TDouble *d2, TDouble *d3) {
  double v1, v2, v3;

  if (! t_double_get_value (d1, &v1))
    return;
  if (! t_double_get_value (d2, &v2))
    return;
  if (! t_double_get_value (d3, &v3))
    return;

  g_print ("%lf %s %lf = %lf\n", v1, op, v2, v3);
}

int
main (int argc, char **argv) {
  TDouble *d1, *d2, *d3;
  double v1, v3;

  d1 = t_double_new (10.0);
  d2 = t_double_new (20.0);
  if ((d3 = t_double_add (d1, d2)) != NULL) {
    t_print ("+", d1, d2, d3);
    g_object_unref (d3);
  }

  if ((d3 = t_double_sub (d1, d2)) != NULL) {
    t_print ("-", d1, d2, d3);
    g_object_unref (d3);
  }

  if ((d3 = t_double_mul (d1, d2)) != NULL) {
    t_print ("*", d1, d2, d3);
    g_object_unref (d3);
  }

  if ((d3 = t_double_div (d1, d2)) != NULL) {
    t_print ("/", d1, d2, d3);
    g_object_unref (d3);
  }

  if ((d3 = t_double_uminus (d1)) != NULL && (t_double_get_value (d1, &v1)) && (t_double_get_value (d3, &v3))) {
    g_print ("-(%lf) = %lf\n", v1, v3);
    g_object_unref (d3);
  }

  g_object_unref (d1);
  g_object_unref (d2);

  return 0;
}
