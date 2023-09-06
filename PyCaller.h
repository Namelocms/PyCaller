#pragma once
#ifndef PyCallerHeader
#define  PyCallerHeader

/*
* To include Python:
*	Config Mode = Release x86
*	Properties -> VC++ Directories
*		Include Directories: Python include folder
*		Library Directories: Python libs folder
*	Put .py files in the release folder directory
*/
#include <Python.h>
#include <iostream>
#include <string>
#include <cstdarg>		// Variable argument types using variadic functions

using std::string;

class PyCaller {
public:
	char* sTOc(string aString);
	PyObject* CallPyFunc(string pyFileName, string pyFuncName, const char* fmt...);
	PyObject* CallPyFuncNoArgs(string pyFileName, string pyFuncName);
	string PyObjToString(PyObject* sPyObj);
	char PyObjToChar(PyObject* cPyObj);
	int PyObjToInt(PyObject* dPyObj);
	double PyObjToDouble(PyObject* fPyObj);
};

#endif
