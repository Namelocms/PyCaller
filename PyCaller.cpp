#include "PyCaller.h"

// Convert a string to a char*[]
char* PyCaller::sTOc(string aString) {
	char* converted = new char[aString.length() + 1];	// Initialize correct size of character array
	std::strcpy(converted, aString.c_str());			// copy string to 'converted' char array as characters

	return converted;
}

/*

Calls a Python Function with any type and amount of arguments > 0
The 'const char* fmt...' argument represents the format string followed by variable arguments.
Format string example: "cdfs" -> 'c'(char), 'd'(int), 'f'(double), 's'(string) -> expected arg input: doSomething("cdfs", 'A', 3, 2.5, "test");

'c': Represents a character argument.
'd': Represents an integer (decimal) argument.
'f': Represents a floating-point (double) argument.
's': Represents a string argument (a const char* pointer).
'/0': Represents the end of a null-terminated string in C and C++

*/
PyObject* PyCaller::CallPyFunc(string pyFileName, string pyFuncName, const char* fmt...) {
	/*
 	PyObject* Descriptions:
	 	pArgs: Python tuple of arguments to pass to Python function
	  	pValue: C++ type converted to Python type
	   	pResult: Python type result returned from Python Function
		pModule: Holds imported Python file
	 	pFunc: Holds reference to Python Function from pModule
  	*/
	PyObject* pArgs = nullptr, * pValue = nullptr, * pResult = nullptr, * pModule = nullptr, * pFunc = nullptr;
	
	char* fileName;			// Name of Python File
	char* funcName;			// Name of Python function
	
	int numArgs;			// Number of arguments to pass to Python function
	char argType;			// Argument Type (c, s, f, d)
	char argC;				// character argument
	int argD;				// integer argument
	double argF;			// double argument
	const char* argS;		// string argument

	fileName = sTOc(pyFileName);									// Convert file name string to char*[]
	funcName = sTOc(pyFuncName);									// Convert func name string to char*[]

	pModule = PyImport_ImportModule(fileName);							// Import Python Module
	if (pModule == nullptr) {
		std::cout << "ERROR Importing Python file!" << std::endl;
		PyErr_Print();
		PyErr_Clear();

	}

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, funcName);				// Get a reference to the Python function

		if (pFunc && PyCallable_Check(pFunc)) {
			va_list args;								// Initialize a variable argument list
			va_start(args, fmt);

			numArgs = std::strlen(fmt);						// Determine the number of arguments based on the format string
			pArgs = PyTuple_New(numArgs);						// Create a tuple to hold Python argument objects

			for (int i = 0; i < numArgs; i++) {					// Loop through the format string and process each argument
				argType = fmt[i];						// Get the type specifier from the format string

				switch (argType) {
				case 'c':
					argC = va_arg(args, char);                          	// Extract a character argument
					pValue = PyUnicode_DecodeUTF8(&argC, 1, NULL);     	// Convert the character to a Python Unicode string object
					PyTuple_SetItem(pArgs, i, pValue);                  	// Add the Python object to the tuple
					break;

				case 'd':
					argD = va_arg(args, int);                           	// Extract an integer argument
					pValue = PyLong_FromLong(argD);                     	// Convert the integer to a Python long object
					PyTuple_SetItem(pArgs, i, pValue);                  	// Add the Python object to the tuple
					break;

				case 'f':
					argF = va_arg(args, double);                        // Extract a double argument
					pValue = PyFloat_FromDouble(argF);                  // Convert the double to a Python float object
					PyTuple_SetItem(pArgs, i, pValue);                  // Add the Python object to the tuple
					break;

				case 's':
					argS = va_arg(args, const char*);                   // Extract a string argument
					pValue = PyUnicode_DecodeFSDefault(argS);           // Convert the C string to a Python Unicode string object
					PyTuple_SetItem(pArgs, i, pValue);                  // Add the Python object to the tuple
					break;

				case '/0':												// End of fmt string
					// Do nothing here
					break;
				}
			}

			va_end(args);													// Clean up the variable argument list
			try {
				pResult = PyObject_CallObject(pFunc, pArgs);					// Call the Python function with the constructed tuple of arguments

			}
			catch (std::exception& e) {
				std::cerr << "Error with Python function call: " << pyFuncName << ": " << e.what() << std::endl;
			}
			Py_DECREF(pArgs);												// Release the tuple and its contents
		}
		else {
			PyErr_Print();
		}
	}
	else {
		PyErr_Print();
	}

	Py_XDECREF(pFunc);												// Clean up
	Py_DECREF(pModule);												// 											
	Py_DECREF(pArgs);												//
	Py_DECREF(pValue);												// 
	delete[] fileName;												// 
	delete[] funcName;												// 

	return pResult;													// Return the result of the Python function call
}

// Call Python fuction with no arguments to pass
PyObject* PyCaller::CallPyFuncNoArgs(string pyFileName, string pyFuncName) {
	PyObject* pModule, * pFunc = nullptr, * pResult = nullptr;
	char* fileName, * funcName;

	fileName = sTOc(pyFileName);
	funcName = sTOc(pyFuncName);

	pModule = PyImport_ImportModule(fileName);						// Import the Python module
	if (pModule == nullptr) {
		std::cout << "ERROR Importing Python file!" << std::endl;
		PyErr_Print();
		PyErr_Clear();

	}

	else {
		pFunc = PyObject_GetAttrString(pModule, funcName);			// Get a reference to the Python function
		try {
			pResult = PyObject_CallObject(pFunc, NULL);				// Call the Python function with NULL arguments

		}
		catch (std::exception& e) {
			std::cerr << "Error with Python function call: " << pyFuncName << ": " << e.what() << std::endl;
		}
	}

	Py_XDECREF(pFunc);												// Clean up
	Py_DECREF(pModule);												// 											
	delete[] fileName;												// 
	delete[] funcName;												// 

	return pResult;													// Return the result of the Python function call
}


// Convert PyObject result to C++ string
string PyCaller::PyObjToString(PyObject* sPyObj) {
	const char* result = nullptr;  // Initialize result to nullptr

	if (sPyObj != nullptr && PyUnicode_Check(sPyObj)) {
		result = PyUnicode_AsUTF8(sPyObj);
		if (result == nullptr) {
			PyErr_Print();  // Handle error if conversion fails
		}
	}

	if (result != nullptr) {
		return std::string(result);  // Return the string if conversion succeeded
	}
	else {
		return "";  // Return an empty string if conversion fails or input is not a Python string
	}
}

// Convert PyObject result to C++ char
char PyCaller::PyObjToChar(PyObject* cPyObj) {
	char charResult = '?';  // Default value if conversion fails
	string stringResult;

	if (cPyObj != nullptr && PyUnicode_Check(cPyObj)) {
		stringResult = PyObjToString(cPyObj);
		if (!stringResult.empty() && stringResult.length() == 1) {
			charResult = stringResult[0];
		}
		else {
			std::cerr << "ERROR: Python returned an unexpected string length" << std::endl;
		}
	}
	else {
		std::cerr << "ERROR: Invalid or null Python object" << std::endl;
	}

	return charResult;
}

// Convert PyObject result to C++ int
int PyCaller::PyObjToInt(PyObject* dPyObj) {
	int result;

	if (dPyObj != NULL) {
		try {
			result = PyLong_AsLong(dPyObj);
		}
		catch (std::exception& e) {
			std::cerr << "Error converting Python Obj to int: " << PyObjToString(dPyObj) << ": " << e.what() << std::endl;
			result = NULL;
		}
	}
	else {
		result = NULL;
	}

	return result;
}

// Convert PyObject result to C++ double
double PyCaller::PyObjToDouble(PyObject* fPyObj) {
	double result;

	if (fPyObj != NULL) {
		try {
			result = PyFloat_AsDouble(fPyObj);
		}
		catch (std::exception& e) {
			std::cerr << "Error converting Python Obj to double: " << PyObjToString(fPyObj) << ": " << e.what() << std::endl;
			result = NULL;
		}
	}
	else {
		result = NULL;
	}

	return result;
}

// Convert PyObject result to C++ char*
char* PyCaller::PyObjToCharArray(PyObject* caPyObj) {
	string cppString;
	char* result;
	
	cppString = PyObjToString(caPyObj);

	result = sTOc(cppString);

	return result;
}
