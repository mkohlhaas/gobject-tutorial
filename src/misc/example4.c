#include <glib-object.h>
#include <stdlib.h>

typedef struct _TDouble
{
  GObject parent;
  double  value;
} TDouble;

typedef struct _TDoubleClass
{
  GObjectClass parent_class;
} TDoubleClass;

static void
t_double_class_init (TDoubleClass *class)
{
}

static void
t_double_init (TDouble *self)
{
}

// creates t_double_get_type, …
G_DEFINE_TYPE (TDouble, t_double, G_TYPE_OBJECT)

#define T_DOUBLE_TYPE (t_double_get_type ())

int
main (void)
{
  GType dtype = T_DOUBLE_TYPE;

  if (dtype)
    {
      g_print ("Type registration was successful!\n");
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
      g_print ("Instantiation was successful!\n");
      g_print ("The instance address is %p.\n", d);
    }
  else
    {
      g_print ("Instantiation failed.\n");
      exit (EXIT_FAILURE);
    }

  g_object_unref (d);
}
