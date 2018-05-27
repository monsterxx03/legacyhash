#include <Python.h>

static PyObject* hash(PyObject *self, PyObject *args) {
    PyObject *object;
    register Py_ssize_t len;
    register Py_UNICODE *p;
    register long x = 0;
    if (!PyArg_ParseTuple(args, "O:obj", &object)) {
        return NULL;
    }
    len = PyUnicode_GET_SIZE(object);
    p = PyUnicode_AS_UNICODE(object);
    x ^= *p << 7;
    while (--len >= 0) {
        x = (1000003*x) ^ *p++;
    }
    x ^= PyUnicode_GET_SIZE(object);
    return Py_BuildValue("l", x);
}

PyDoc_STRVAR(pydoc_hash,
        "hash(object) -> integer\n"
        "\n"
        "Return the hash value for the given object."
);

static PyMethodDef hash_methods[] = {
    {"hash", (PyCFunction)hash, METH_VARARGS, pydoc_hash},
    {NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(module_doc,
        "legacy hash in python2.7\n");

static struct PyModuleDef moduleref ={
    PyModuleDef_HEAD_INIT,
    "legacyhash",                 /* m_name */
    module_doc,                   /* m_doc */
    -1, 
    hash_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};


PyMODINIT_FUNC
PyInit_legacyhash() {
    return PyModule_Create(&moduleref);
}
