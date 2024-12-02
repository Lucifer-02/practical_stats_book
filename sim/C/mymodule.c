// #include <Python.h>
#include "/usr/include/python3.10/numpy/arrayobject.h"
#include "chap1.c"
#include "python3.10/Python.h"
#include <assert.h>
#include <stdbool.h>

// Function to compute the sum of elements in a NumPy array
static PyObject *mean_list(PyObject *self, PyObject *args) {
  PyObject *input_obj = NULL;
  PyArrayObject *array = NULL;

  // Parse the input tuple. "O" expects a Python object.
  if (!PyArg_ParseTuple(args, "O", &input_obj)) {
    return NULL;
  }

  // Interpret the input object as a NumPy array
  array = (PyArrayObject *)PyArray_FROM_OTF(input_obj, NPY_FLOAT64,
                                            NPY_ARRAY_IN_ARRAY);
  if (array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  // Ensure the array is contiguous
  if (!PyArray_ISCONTIGUOUS(array)) {
    PyErr_SetString(PyExc_ValueError, "Array must be contiguous.");
    Py_DECREF(array);
    return NULL;
  }
  // Get the number of elements
  npy_intp size = (size_t)PyArray_SIZE(array);
  double *data = (double *)PyArray_DATA(array);

  double m = mean_double(data, size);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}

// Method definitions
static PyMethodDef MyMethods[] = {
    {"mean_list", mean_list, METH_VARARGS, "mean elements of a NumPy array."},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "mymodule",         // Module name
    "Example C module", // Module documentation
    -1,                 // Module state (-1 for global state)
    MyMethods           // Methods
};

// Module initialization
PyMODINIT_FUNC PyInit_mymodule(void) {
  // Initialize NumPy
  import_array(); // Required for NumPy C API
  return PyModule_Create(&mymodule);
}
