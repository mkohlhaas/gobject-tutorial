project('tstr', 'c')

gobjdep = dependency('gobject-2.0')

test1files = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'test1.c',
  'tstr.c',
)
executable('test1', test1files, dependencies: gobjdep, install: false)

test2files = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'test2.c',
  'tnumstr.c',
  'tstr.c',
)
executable('test2', test2files, dependencies: gobjdep, install: false)

sourcefiles = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'main.c',
  'tnumstr.c',
  'tstr.c',
)
executable('tnumstr', sourcefiles, dependencies: gobjdep, install: false)
