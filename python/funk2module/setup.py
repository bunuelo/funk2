from distutils.core import setup, Extension

funk2module_extension = Extension('funk2',
                                  sources      = ['c/funk2module.c'],
                                  libraries    = ['funk2'],
                                  library_dirs = ['../../lib/.libs/'])

setup(name        = 'Funk2',
      version     = '2.10',
      description = 'Funk2: a reflective programming language.',
      ext_modules = [funk2module_extension])

