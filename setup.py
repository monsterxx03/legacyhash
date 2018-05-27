from distutils.core import  setup, Extension

setup(
        name="legacyhash", version='1.0',
        ext_modules=[Extension("legacyhash", ["hash.c"])]
)

