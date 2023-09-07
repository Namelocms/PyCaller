# PyCaller
Call a Python Function with any number of parameters > 0 and convert a Python Object to a C++ type. Also call a function with no parameters!
## How to use
### Requirements
- Python.h header file
- Python `include` folder added to VC++ Include Directories in Project Properties
- Python `libs` folder added to VC++ Library Directories in Project Properties
- Add both `python3.dll` and `python39.dll` (or equivalent for your desired Python version) to the `Release` folder
- Add any Python files (`.py`) you want to use to the `Release` folder
### Basic Walkthrough
1. Fork then clone this repository
   - `>git clone {url to clone}.git {folder-name}`
2. Make your C++ project
3. Import the PyCaller.h and PyCaller.cpp files
   - `#include "../PyCaller.h"`
   - `#include "../PyCaller.cpp"`
4. Switch to `Release x86` for the build configuration
5. Set up the properties in VC++ Directory
6. Add the 2 `.dll` files to your `Release` folder
7. Add any `.py` files to your `Release` folder
8. Initialize the PyCaller Class
   - `PyCaller py;`
9. Create a PyObject
    - `PyObject* pObj;`
10. Initialize Python Interpreter
    - `Py_Initialize();`
11. Call your Python file(DONT ADD THE `.py`) and function
    - `pObj = py.CallPyFuncNoArgs("fileName", "funcName");`
12. Convert the result to the desired C++ type
    - `int result = py.PyObjToInt(pObj);`
13. Dereference Python Objects
    - `Py_DECREF(pObj);`
14. Finalize the Python Interpreter
    - `Py_Finalize();`
### Sample Code
Check TEST.cpp for more examples!
```{C++}
#include "../PyCaller/PyCaller.h"
#include "../PyCaller/PyCaller.cpp"

int main() {
  PyCaller py;
  PyObject* pObj;
  
  Py_Initialize();
  
  pObj = py.CallPyFuncNoArgs("file", "funcName");
  int result = py.PyObjToInt(pObj);
  
  // Do something with result
  
  Py_DECREF(pObj);
  Py_Finalize();
  
  return 0;
}
```
