#include <Python.h>

static long
hash_unicode(PyObject *obj) {
    register Py_ssize_t len;
    register long x = 0;
    register Py_UNICODE *p;
    len = PyUnicode_GET_SIZE(obj);
    if (len == 0) return 0;
    p = PyUnicode_AS_UNICODE(obj);
    x ^= *p << 7;
    while (--len >= 0) {
        x = (1000003*x) ^ *p++;
    }
    x ^= PyUnicode_GET_SIZE(obj);
    if (x == -1) return -2;
    return x;
}

static long
hash_bytes(PyObject *obj) {
    register Py_ssize_t len;
    register unsigned char *p;
    register long x = 0;
    len = Py_SIZE(obj);
    if (len == 0) return 0;
    p = (unsigned char *) ((PyBytesObject *)obj) -> ob_sval;
    x ^= *p << 7;
    while (--len >= 0)
        x = (1000003*x) ^ *p++;
    x ^= Py_SIZE(obj);
    if (x == -1) return -2;
    return x;
}


static PyObject* hash(PyObject *self, PyObject *args) {
    PyObject *object;
    if (!PyArg_ParseTuple(args, "O:obj", &object)) {
        return NULL;
    }
    if (PyBytes_Check(object)) {
        return Py_BuildValue("l", hash_bytes(object));
    } else if (PyUnicode_Check(object)) {
        return Py_BuildValue("l", hash_unicode(object));
    }
    PyErr_Format(PyExc_TypeError, "object must bytes or unicode, got %s", object->ob_type->tp_name);
    return NULL;
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
