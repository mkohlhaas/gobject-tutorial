#include <glib-object.h>

struct _TDouble
{
  GObject parent;
  double  value;
};

// creates TDouble, TDoubleClass, T_IS_DOUBLE, …
G_DECLARE_FINAL_TYPE (TDouble, t_double, T, DOUBLE, GObject)

// creates t_double_get_type, …
// G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT)
G_DEFINE_FINAL_TYPE (TDouble, t_double, G_TYPE_OBJECT)

static void
t_double_class_init (TDoubleClass *class)
{
}

static void
t_double_init (TDouble *self)
{
}

#define T_DOUBLE_TYPE (t_double_get_type ())

int
main (void)
{
  GType dtype = T_DOUBLE_TYPE;

  if (dtype)
    {
      g_print ("Type registration was successful.\n");
      g_print ("The type ID is %lx.\n", dtype);
    }
  else
    {
      g_print ("Type registration failed.\n");
      exit (EXIT_FAILURE);
    }

  TDouble *d = g_object_new (T_DOUBLE_TYPE, NULL);
  if (d)
    {
      g_print ("Instantiation was successful.\n");
      g_print ("The instance address is %p.\n", d);
    }
  else
    {
      g_print ("Instantiation failed!\n");
      exit (EXIT_FAILURE);
    }

  if (T_IS_DOUBLE (d))
    {
      g_print ("d is a TDouble instance.\n");
    }
  else
    {
      g_print ("d is not a TDouble instance.\n");
    }

  if (G_IS_OBJECT (d))
    {
      g_print ("d is a GObject instance.\n");
    }
  else
    {
      g_print ("d is not a GObject instance.\n");
    }

  g_object_unref (d);
}
