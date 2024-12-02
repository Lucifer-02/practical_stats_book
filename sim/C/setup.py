from setuptools import setup, Extension

module = Extension("mymodule", sources=["mymodule.c"], undef_macros=["NDEBUG"])

setup(
    name="mymodule",
    version="0.1",
    description="Example C module for Python",
    ext_modules=[module],
)
