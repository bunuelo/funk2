#include <Python.h>
#include "../../../c/funk2.h"

PyObject* raw__exp__as__python_object(f2ptr cause, f2ptr exp) {
  if (exp == nil) {
    return Py_BuildValue("[]");
  }
  if (raw__larva__is_type(cause, exp)) {
    f2ptr larva = exp;
    return Py_BuildValue("(s,i)", "larva", raw__larva__larva_type(cause, larva));
  }
  if (raw__string__is_type(cause, exp)) {
    f2ptr string         = exp;
    u64   string__length = raw__string__length(cause, string);
    u8*   string__str    = (u8*)alloca(string__length + 1);
    raw__string__str_copy(cause, string, string__str);
    string__str[string__length] = 0;
    return Py_BuildValue("s", (char*)string__str);
  }
  if (raw__integer__is_type(cause, exp)) {
    f2ptr integer = exp;
    return Py_BuildValue("i", f2integer__i(integer, cause));
  }
  printf("\nPython Funk2 warning: not handling type conversion of object.");
  return NULL;
}

static PyObject* funk2_read(PyObject* self, PyObject* args) {
  const char *raw_string;
  
  if (!PyArg_ParseTuple(args, "s", &raw_string)) {
    return NULL;
  }
  
  PyObject* result;
  
  f2ptr cause = nil;
  {
    pause_gc();
    f2ptr string = f2string__new(cause, strlen(raw_string), (u8*)raw_string);
    result       = raw__exp__as__python_object(cause, f2__string__read(cause, string));
    resume_gc();
  }
  
  return result;
}

static PyMethodDef Funk2Methods[] = {
  {"read",  funk2_read, METH_VARARGS, "Read a string in Funk2, returning the result as a Python object."},
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

static PyObject *Funk2Error;

// **

PyMODINIT_FUNC initfunk2(void) {
  PyObject *m;
  
  funk2__start_main_in_separate_thread();
  
  m = Py_InitModule("funk2", Funk2Methods);
  if (m == NULL)
    return;
  
  Funk2Error = PyErr_NewException("funk2.error", NULL, NULL);
  Py_INCREF(Funk2Error);
  PyModule_AddObject(m, "error", Funk2Error);
}

