#include <glib-object.h>

typedef struct _TDouble
{
  GObject parent;
  double  value;
} TDouble;

typedef struct _TDoubleClass
{
  GObjectClass parent;
} TDoubleClass;

static void
t_double_class_init (TDoubleClass *class)
{
}

static void
t_double_init (TDouble *self)
{
}

GType
t_double_get_type (void)
{
  static GType type;

  if (!type)
    {
      GTypeInfo info = {
        .class_size    = sizeof (TDoubleClass),
        .class_init    = (GClassInitFunc)t_double_class_init,
        .instance_size = sizeof (TDouble),
        .instance_init = (GInstanceInitFunc)t_double_init,
      };
      type = g_type_register_static (G_TYPE_OBJECT, "TDouble", &info, G_TYPE_FLAG_NONE);
    }
  return type;
}

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
