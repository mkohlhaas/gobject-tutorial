#include "tdouble.h"
#include "tint.h"
#include "tnumber.h"
#include <glib-object.h>

static void
notify_cb (GObject *gobject, GParamSpec *pspec, gpointer user_data)
{
  const char *name = g_param_spec_get_name (pspec);
  if (T_IS_INT (gobject) && strcmp (name, "value") == 0)
    {
      int i;
      g_object_get (T_INT (gobject), "value", &i, NULL);
      g_print ("Property \"%s\" is set to %d.\n", name, i);
    }
  else if (T_IS_DOUBLE (gobject) && strcmp (name, "value") == 0)
    {
      double d;
      g_object_get (T_DOUBLE (gobject), "value", &d, NULL);
      g_print ("Property \"%s\" is set to %lf.\n", name, d);
    }
}

void
connect_signal (TNumber *n)
{
  g_signal_connect (G_OBJECT (n), "notify::value", G_CALLBACK (notify_cb), NULL);
}

int
main (void)
{
  TNumber *i = T_NUMBER (t_int_new ());
  TNumber *d = T_NUMBER (t_double_new ());

  connect_signal (i);
  connect_signal (d);

  g_object_set (T_INT (i), "value", 100, NULL);
  g_object_set (T_DOUBLE (d), "value", 12.345, NULL);

  TNumber *num  = t_number_add (i, d);
  char    *si   = t_number_to_s (i);
  char    *sd   = t_number_to_s (d);
  char    *snum = t_number_to_s (num);
  g_print ("%s + %s is %s.\n", si, sd, snum);

  g_object_unref (num);
  g_free (snum);

  num  = t_number_add (d, i);
  snum = t_number_to_s (num);
  g_print ("%s + %s is %s.\n", sd, si, snum);

  g_object_unref (num);
  g_free (sd);
  g_free (snum);

  g_object_set (T_DOUBLE (d), "value", 0.0, NULL);
  sd = t_number_to_s (d);
  if ((num = t_number_div (i, d)) != NULL)
    {
      snum = t_number_to_s (num);
      g_print ("%s / %s is %s.\n", si, sd, snum);
      g_object_unref (num);
      g_free (snum);
    }

  g_object_unref (i);
  g_object_unref (d);

  g_free (si);
  g_free (sd);
}
