// #include <Python.h>
#include "/usr/include/python3.10/numpy/arrayobject.h"
#include "python3.10/Python.h"

#include "chap1.c"
#include <stddef.h>

// Function to compute the sum of elements in a NumPy array
static PyObject *mean_list(PyObject *self, PyObject *args, PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"array", NULL};

  PyObject *input_obj = NULL;

  PyArrayObject *array = NULL;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &input_obj)) {
    return NULL; // Signal an error
  }

  // Interpret the input object as a NumPy array
  array = (PyArrayObject *)PyArray_FROM_OTF(input_obj, NPY_FLOAT64,
                                            NPY_ARRAY_IN_ARRAY);
  if (array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  // Get the number of elements
  npy_intp const size = PyArray_SIZE(array);
  double const *const data = (double *)PyArray_DATA(array);

  double const m = mean_double(data, (size_t)size);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}

// Function to compute the sum of elements in a NumPy array
static PyObject *trimmed_mean_list(PyObject *self, PyObject *args,
                                   PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"array", "trim", NULL};

  PyObject *input_obj = NULL;
  size_t trim = 0;

  PyArrayObject *array = NULL;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", kwlist, &input_obj,
                                   &trim)) {
    return NULL; // Signal an error
  }

  // Interpret the input object as a NumPy array
  array = (PyArrayObject *)PyArray_FROM_OTF(input_obj, NPY_FLOAT64,
                                            NPY_ARRAY_IN_ARRAY);
  if (array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  // Get the number of elements
  npy_intp const size = PyArray_SIZE(array);
  double const *const data = (double *)PyArray_DATA(array);

  double const m = trimmed_mean(data, (size_t)size, trim);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}
// Function to compute the sum of elements in a NumPy array
static PyObject *median_list(PyObject *self, PyObject *args, PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"array", NULL};

  PyObject *input_obj = NULL;

  PyArrayObject *array = NULL;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &input_obj)) {
    return NULL; // Signal an error
  }

  // Interpret the input object as a NumPy array
  array = (PyArrayObject *)PyArray_FROM_OTF(input_obj, NPY_FLOAT64,
                                            NPY_ARRAY_IN_ARRAY);
  if (array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  // Get the number of elements
  npy_intp const size = PyArray_SIZE(array);
  double const *const data = (double *)PyArray_DATA(array);

  double const m = median_double(data, (size_t)size);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}

// Method definitions
static PyMethodDef MyMethods[] = {
    {"mean_list", (PyCFunction)mean_list, METH_VARARGS | METH_KEYWORDS,
     "Return mean of a NumPy array."},
    {"median_list", (PyCFunction)median_list, METH_VARARGS | METH_KEYWORDS,
     "Return median of a NumPy array."},
    {"trimmed_mean", (PyCFunction)trimmed_mean_list,
     METH_VARARGS | METH_KEYWORDS, "Return trimmed mean of a NumPy array."},

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
