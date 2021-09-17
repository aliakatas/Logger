#pragma once

#include <string>
#include <fstream>

#define NOFILESPECIFIED			"NONE"


class LoggerStream
{
public:
	LoggerStream();
	~LoggerStream();

	void set_filename(const char* fname);
	std::string get_filename();

	bool open_file();
	bool close_file();

	bool write(const char* txt, const char* ending = "\n");
	bool write(const float flt, const char* ending = "\n");
	bool write(const int yyyy, const int mm, const int dd, const char* ending = "\n");

private:

	std::ofstream fptr;
	std::string filename;

};