project('tcomparable', 'c')

gobjdep = dependency('gobject-2.0')

sourcefiles = files(
  '../../tnumber/tnumber.c',
  '../../tstr/tnumstr.c',
  'main_without_macro.c',
  'tcomparable_without_macro.c',
  'tdouble_without_macro.c',
  'tint_without_macro.c',
  'tstr_without_macro.c',
)

executable(
  'tcomparable',
  sourcefiles,
  dependencies: gobjdep,
  install: false,
)
