project('tcomparable', 'c')

gobjdep = dependency('gobject-2.0')

sourcefiles = files(
  '../../tnumber/tnumber.c',
  '../../tstr/tnumstr.c',
  'main.c',
  'tcomparable.c',
  'tdouble.c',
  'tint.c',
  'tstr.c',
)

executable('tcomparable', sourcefiles, dependencies: gobjdep, install: false)
