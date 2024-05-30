#include "tdouble.h"
#include <stdlib.h>

int
main (void)
{
  double value;
  double initial_val = 10.0;
  double updated_val = -20.0;

  g_print ("Initialising d to %.2f.\n", initial_val);
  TDouble *d = t_double_new (initial_val);
  if (t_double_get_value (d, &value))
    {
      g_print ("Succesfully read value from d and assigned its value %.2f to another variable.\n", value);
    }
  else
    {
      g_print ("t_double_get_value call failed.\n");
      exit (EXIT_FAILURE);
    }

  t_double_set_value (d, updated_val);
  g_print ("Setting d to %.2f.\n", updated_val);
  if (t_double_get_value (d, &value))
    {
      g_print ("Succesfully read value from d and assigned its value %.2f to another variable.\n", value);
    }
  else
    {
      g_print ("t_double_get_value call failed.\n");
      exit (EXIT_FAILURE);
    }

  g_object_unref (d);
}
