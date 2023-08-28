#include "PyCaller.h"
#include <typeinfo>

int main() {
	PyCaller py;

	Py_Initialize();		// Needed for Python Interpereter Initialization

	PyObject* iPy;
	PyObject* dPy;
	PyObject* sPy;
	PyObject* cPy;
	PyObject* nPy;

	string pyFileName = "PyFile";
	
	string testInt = "testInt";
	string testDouble = "testDouble";
	string testString = "testString";
	string testChar = "testChar";
	string testNoArgs = "testNoArgs";
	
	int intResult;
	double doubleResult;
	string stringResult;
	char charResult;
	string noArgsResult;

	iPy = py.CallPyFunc(pyFileName, testInt, "ddd", 121, 22, 4433);
	intResult = py.PyObjToDouble(iPy);	// int expected
	std::cout << "Result: " << intResult << ":" << typeid(intResult).name() << std::endl;
	Py_DECREF(iPy);

	dPy = py.CallPyFunc(pyFileName, testDouble, "fff", 12.6, 24.5, 31.4);
	doubleResult = py.PyObjToDouble(dPy);	// double expected
	std::cout << "Result: " << doubleResult << ":" << typeid(doubleResult).name() << std::endl;
	Py_DECREF(dPy);

	sPy = py.CallPyFunc(pyFileName, testString, "sss", "String ", "Test ", "Result!");
	stringResult = py.PyObjToString(sPy);	// string expected
	std::cout << "Result: " << stringResult << ":" << typeid(stringResult).name() << std::endl;
	Py_DECREF(sPy);

	cPy = py.CallPyFunc(pyFileName, testChar, "c", 'L');
	charResult = py.PyObjToChar(cPy);	// char expected
	std::cout << "Result: " << charResult << ":" << typeid(charResult).name() << std::endl;
	Py_DECREF(cPy);

	nPy = py.CallPyFuncNoArgs(pyFileName, testNoArgs);
	noArgsResult = py.PyObjToString(nPy);	// string expected
	std::cout << "Result: " << noArgsResult << ":" << typeid(noArgsResult).name() << std::endl;
	Py_DECREF(nPy);

	Py_Finalize();		// Interpereter shutdown
	return 0;
}
