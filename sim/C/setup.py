from setuptools import setup, Extension
import numpy

module = Extension(
    "mymodule",
    sources=["mymodule.c"],
    undef_macros=["NDEBUG"],
    include_dirs=[numpy.get_include()],  # Include NumPy headers
)


setup(
    name="mymodule",
    version="0.1",
    description="Example C module for Python",
    ext_modules=[module],
)
