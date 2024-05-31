#include "tnumber.h"

static guint t_number_signal;

G_DEFINE_ABSTRACT_TYPE (TNumber, t_number, G_TYPE_OBJECT)

static void
div_by_zero_default_cb (TNumber *self)
{
  g_printerr ("Error: division by zero.\n");
}

static void
t_number_class_init (TNumberClass *class)
{
  /* virtual functions */
  class->add         = NULL;
  class->sub         = NULL;
  class->mul         = NULL;
  class->div         = NULL;
  class->uminus      = NULL;
  class->to_s        = NULL;
  class->div_by_zero = div_by_zero_default_cb;

  GSignalFlags signal_flags = G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS;
  GType        itype        = G_TYPE_FROM_CLASS (class);
  guint        class_offset = G_STRUCT_OFFSET (TNumberClass, div_by_zero);
  t_number_signal = g_signal_new ("div-by-zero", itype, signal_flags, class_offset, NULL, NULL, NULL, G_TYPE_NONE, 0);
}

static void
t_number_init (TNumber *self)
{
}

#define T_NUMBER_BIN_OP(op)                                                                                            \
  TNumber *t_number_##op (TNumber *self, TNumber *other)                                                               \
  {                                                                                                                    \
    g_return_val_if_fail (T_IS_NUMBER (self), NULL);                                                                   \
    g_return_val_if_fail (T_IS_NUMBER (other), NULL);                                                                  \
    TNumberClass *class = T_NUMBER_GET_CLASS (self);                                                                   \
    return class->op ? class->op (self, other) : NULL;                                                                 \
  }

#define T_NUMBER_UNI_OP(op, type)                                                                                      \
  type *t_number_##op (TNumber *self)                                                                                  \
  {                                                                                                                    \
    g_return_val_if_fail (T_IS_NUMBER (self), NULL);                                                                   \
    TNumberClass *class = T_NUMBER_GET_CLASS (self);                                                                   \
    return class->op ? class->op (self) : NULL;                                                                        \
  }

T_NUMBER_BIN_OP (add)
T_NUMBER_BIN_OP (sub)
T_NUMBER_BIN_OP (mul)
T_NUMBER_BIN_OP (div)
T_NUMBER_UNI_OP (uminus, TNumber)
T_NUMBER_UNI_OP (to_s, char)
