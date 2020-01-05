#include "autoengineexception.h"
#include <sstream>

AutoengineException::AutoengineException( int line, const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* AutoengineException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* AutoengineException::GetType() const noexcept {
	return "Autoengine Exception";
}

int AutoengineException::GetLine() const noexcept {
	return line;
}

const std::string& AutoengineException::GetFile() const noexcept {
	return file;
}

std::string AutoengineException::GetOriginString() const noexcept {
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}