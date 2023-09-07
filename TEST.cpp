#include "PyCaller.h"
#include <typeinfo>

int main() {
	PyCaller py;

	Py_Initialize();		// Needed for Python Interpereter Initialization

	// Python Results
	PyObject* iPy;
	PyObject* dPy;
	PyObject* sPy;
	PyObject* cPy;
	PyObject* nPy;
	PyObject* mPy;
	PyObject* caPy;

	// Python File name
	string pyFileName = "PyFile";

	// Python Function Names
	string testInt = "testInt";
	string testDouble = "testDouble";
	string testString = "testString";
	string testChar = "testChar";
	string testNoArgs = "testNoArgs";

	// C++ Results
	int intResult;
	double doubleResult;
	string stringResult;
	char charResult;
	string noArgsResult;
	double mixedDoubleResult;
	char* charArrayResult;

	// TESTING
	iPy = py.CallPyFunc(pyFileName, testInt, "ddd", 121, 22, 4433);
	intResult = py.PyObjToInt(iPy);	// int expected
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

	mPy = py.CallPyFunc(pyFileName, testDouble, "dff", 1, 2.4, 3.7);
	mixedDoubleResult = py.PyObjToDouble(mPy);
	std::cout << "Result: " << mixedDoubleResult << ":" << typeid(mixedDoubleResult).name() << std::endl << std::endl;
	Py_DECREF(mPy);

	caPy = py.CallPyFunc(pyFileName, testString, "ssc", "Char* ", "Test ", 'x');
	charArrayResult = py.PyObjToCharArray(caPy);	// char* expected
	std::cout << "Result: " << charArrayResult << " : " << typeid(charArrayResult).name() << std::endl << std::endl;
	Py_DECREF(caPy);

	Py_Finalize();		// Interpereter shutdown
	return 0;
}
