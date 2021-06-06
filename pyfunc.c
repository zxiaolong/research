#include <Python.h>

int test_function_from_python(int a) {
    int res;
    PyObject *pModule,*pFunc;
    PyObject *pArgs, *pValue;
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    /* import */
    pModule = PyImport_Import(PyString_FromString("test_module"));
    if(NULL == pModule) {
        printf("Import failed\n");
        return 1;
    }

    /* great_module.great_function */
    pFunc = PyObject_GetAttrString(pModule, "test_function"); 
    if(NULL == pFunc) {
        printf("get function failed\n");
        return 1;
    }
    
    /* build args */
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs,0, PyInt_FromLong(a));
      
    /* call */
    pValue = PyObject_CallObject(pFunc, pArgs);
    
    res = PyInt_AsLong(pValue);
    return res;
}

int main(int argc, char *argv[]) {
    Py_Initialize();
    printf("result: %d\n", test_function_from_python(2));
    Py_Finalize();
}
