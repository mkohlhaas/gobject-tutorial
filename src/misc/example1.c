#include <glib-object.h>

int
main (void)
{
  GObject *instance1 = g_object_new (G_TYPE_OBJECT, NULL);
  GObject *instance2 = g_object_new (G_TYPE_OBJECT, NULL);
  g_print ("The address of instance1 is %p\n", instance1);
  g_print ("The address of instance2 is %p\n", instance2);

  GObjectClass *class1 = G_OBJECT_GET_CLASS (instance1);
  GObjectClass *class2 = G_OBJECT_GET_CLASS (instance2);

  g_print ("The address of the class of instance1 is %p\n", class1);
  g_print ("The address of the class of instance2 is %p\n", class2);
  g_print ("Class Name: %s\n", G_OBJECT_CLASS_NAME (class1));

  g_object_unref (instance1);
  g_object_unref (instance2);
}
