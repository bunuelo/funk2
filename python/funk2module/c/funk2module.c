#include <Python.h>
#include "../../../c/funk2.h"

PyObject* raw__exp__as__python_object(f2ptr cause, f2ptr exp) {
  if (raw__larva__is_type(cause, exp)) {
    f2ptr larva = exp;
    return Py_BuildValue("(s,i)", "larva", raw__larva__larva_type(cause, larva));
  }
  if (raw__string__is_type(cause, exp)) {
    f2ptr string         = exp;
    u64   string__length = raw__string__length(cause, string);
    u8*   string__str    = (u8*)alloca(string__length + 1);
    raw__string__str_copy(cause, string, string__str, string__length);
    string__str[string__length] = 0;
    return Py_BuildValue("s", (char*)string__str);
  }
  if (raw__integer__is_type(cause, exp)) {
    f2ptr integer = exp;
    return Py_BuildValue("i", f2integer__i(exp, cause));
  }
  printf("\nPython Funk2 warning: not handling type conversion of object.");
  f2__print(cause, exp);
  return NULL;
}

static PyObject* funk2_eval(PyObject* self, PyObject* args) {
  const char *command;
  
  if (!PyArg_ParseTuple(args, "s", &command)) {
    return NULL;
  }
  
  f2ptr cause = nil;
  {
    pause_gc();
    PyObject* result = raw__exp__as_python_object(cause, raw__eval_string_to_string(cause, command));
    resume_gc();
  }
  
  return result;
}

static PyMethodDef Funk2Methods[] = {
  {"eval",  funk2_eval, METH_VARARGS, "Read and evaluate a string in Funk2, returning the result as a Python object."},
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

static PyObject *Funk2Error;

// **

PyMODINIT_FUNC initfunk2(void) {
  PyObject *m;
  
  m = Py_InitModule("funk2", Funk2Methods);
  if (m == NULL)
    return;
  
  Funk2Error = PyErr_NewException("funk2.error", NULL, NULL);
  Py_INCREF(Funk2Error);
  PyModule_AddObject(m, "error", Funk2Error);
}

