project('tstr', 'c')

gobjdep = dependency('gobject-2.0')

test1files = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'test1.c',
  'tstr.c',
)
test1 = executable('test1', test1files, dependencies: gobjdep, install: false)
test('test1', test1)

test2files = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'test2.c',
  'tnumstr.c',
  'tstr.c',
)
test2 = executable('test2', test2files, dependencies: gobjdep, install: false)
test('test2', test2)

sourcefiles = files(
  '../tnumber/tdouble.c',
  '../tnumber/tint.c',
  '../tnumber/tnumber.c',
  'main.c',
  'tnumstr.c',
  'tstr.c',
)
executable('tnumstr', sourcefiles, dependencies: gobjdep, install: false)
