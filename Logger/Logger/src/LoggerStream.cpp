#include "LoggerStream.h"

LoggerStream::LoggerStream() {
	filename = NOFILESPECIFIED;
}

LoggerStream::~LoggerStream() {
	close_file();
}

void LoggerStream::set_filename(const char* fname) {
	filename = fname;
}

std::string LoggerStream::get_filename() {
	return filename;
}

bool LoggerStream::open_file() {
	if (filename.compare(NOFILESPECIFIED) == 0)
		return false;

	fptr.open(filename.c_str(), std::ios::out);

	if (fptr.fail()) {
		fprintf_s(stderr, "Failed to open file: \n    %s \n", filename.c_str());
		return false;
	}
	else {
		fprintf_s(stderr, "File opened:\n   %s \n", filename.c_str());
	}

	return true;
}

bool LoggerStream::close_file() {
	if (!fptr.fail()) {
		fptr.close();
	}
	else
		return false;

	return true;
}

bool LoggerStream::write(const char* txt, const char* ending) {
	if (!fptr.fail()) {
		fptr << txt << ending;
		return !fptr.fail();
	}

	return false;
}

bool LoggerStream::write(const float flt, const char* ending) {
	if (!fptr.fail()) {
		fptr << "Numbers: " << flt << ending;
		return !fptr.fail();
	}

	return false;
}

bool LoggerStream::write(const int yyyy, const int mm, const int dd, const char* ending) {
	if (!fptr.fail()) {
		fptr << "[" << yyyy << "-" << mm << "-" << dd << "]" << ending;
		return !fptr.fail();
	}
	return false;
}

