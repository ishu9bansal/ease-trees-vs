#ifndef size_exception_h
#define size_exception_h

#include <iostream>
#include <string>
#include <exception>


class SizeNotMatchException : public exception{
	string msg;
public:
	SizeNotMatchException() : msg("") {
	}
	SizeNotMatchException(string imsg) : msg(imsg) {
	}

	virtual const char* what() const throw() {
		string newMsg = "Size of the provided data don't match;\n" + msg;
		return newMsg.c_str();
	}

	~SizeNotMatchException() throw() {
	}
};

#endif // !size_exception_h

