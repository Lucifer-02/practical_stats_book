#include ".venv/lib/python3.11/site-packages/numpy/_core/include/numpy/arrayobject.h"
#include "/home/lucifer/.local/share/uv/python/cpython-3.11.11-linux-x86_64-gnu/include/python3.11/Python.h"

#include "src/chap1.c"
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
  double const *const array_data = (double *)PyArray_DATA(array);

  Slice const data = {
      .pointer = (char *)array_data, .len = size, .item_size = sizeof(double)};

  double const m = mean_double(data);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}

// Function to compute the sum of elements in a NumPy array
static PyObject *trim_mean_list(PyObject *self, PyObject *args,
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
  double const *const array_data = (double *)PyArray_DATA(array);

  Slice const data = {
      .pointer = (char *)array_data, .len = size, .item_size = sizeof(double)};
  double const m = trim_mean(data, trim);

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
  double const *const array_data = (double *)PyArray_DATA(array);
  Slice const data = {
      .pointer = (char *)array_data, .len = size, .item_size = sizeof(double)};

  double const m = median_double(data);

  // Clean up
  Py_DECREF(array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(m);
}

static PyObject *weighted_mean_list(PyObject *self, PyObject *args,
                                    PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"data_list", "weights", NULL};

  PyObject *data_list = NULL;
  PyObject *weights_list = NULL;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", kwlist, &data_list,
                                   &weights_list)) {
    return NULL; // Signal an error
  }

  PyArrayObject *data_array = (PyArrayObject *)PyArray_FROM_OTF(
      data_list, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  if (data_array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  PyArrayObject *weights_array = (PyArrayObject *)PyArray_FROM_OTF(
      weights_list, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  if (weights_array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  Slice const data = {.pointer = (char *)PyArray_DATA(data_array),
                      .len = PyArray_SIZE(data_array),
                      .item_size = sizeof(double)};
  Slice const weights = {.pointer = (char *)PyArray_DATA(weights_array),
                         .len = PyArray_SIZE(weights_array),
                         .item_size = sizeof(double)};
  double const result = weighted_mean(data, weights);

  // Clean up
  Py_DECREF(data_array);
  Py_DECREF(weights_array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(result);
}

static PyObject *var_list(PyObject *self, PyObject *args, PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"data_list", "ddof", NULL};

  PyObject *data_list = NULL;
  size_t ddof = 0;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", kwlist, &data_list,
                                   &ddof)) {
    return NULL; // Signal an error
  }

  PyArrayObject *data_array = (PyArrayObject *)PyArray_FROM_OTF(
      data_list, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  if (data_array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  Slice const data = {.pointer = (char *)PyArray_DATA(data_array),
                      .len = PyArray_SIZE(data_array),
                      .item_size = sizeof(double)};
  double const result = var(data, ddof);

  // Clean up
  Py_DECREF(data_array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(result);
}

static PyObject *std_list(PyObject *self, PyObject *args, PyObject *kwargs) {
  // Define argument names (must be NULL-terminated)
  static char *kwlist[] = {"data_list", "ddof", NULL};

  PyObject *data_list = NULL;
  size_t ddof = 0;

  // Parse positional and keyword arguments
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", kwlist, &data_list,
                                   &ddof)) {
    return NULL; // Signal an error
  }

  PyArrayObject *data_array = (PyArrayObject *)PyArray_FROM_OTF(
      data_list, NPY_FLOAT64, NPY_ARRAY_IN_ARRAY);
  if (data_array == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Input must be a NumPy array of type float64.");
    return NULL;
  }

  Slice const data = {.pointer = (char *)PyArray_DATA(data_array),
                      .len = PyArray_SIZE(data_array),
                      .item_size = sizeof(double)};
  double const result = std(data, ddof);

  // Clean up
  Py_DECREF(data_array);

  // Return the sum as a Python float
  return PyFloat_FromDouble(result);
}

// Method definitions
static PyMethodDef MyMethods[] = {
    {"mean_list", (PyCFunction)mean_list, METH_VARARGS | METH_KEYWORDS,
     "Return mean of a NumPy array."},
    {"median_list", (PyCFunction)median_list, METH_VARARGS | METH_KEYWORDS,
     "Return median of a NumPy array."},
    {"trim_mean", (PyCFunction)trim_mean_list, METH_VARARGS | METH_KEYWORDS,
     "Return trim mean of a NumPy array."},
    {"weighted_mean_list", (PyCFunction)weighted_mean_list,
     METH_VARARGS | METH_KEYWORDS,
     "Return mean with weights of a NumPy array."},
    {"var_list", (PyCFunction)var_list, METH_VARARGS | METH_KEYWORDS,
     "Return variation with degree of freedom(delta) of a NumPy array."},
    {"std_list", (PyCFunction)std_list, METH_VARARGS | METH_KEYWORDS,
     "Return standard diviation with degree of freedom(delta) of a NumPy "
     "array."},
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
