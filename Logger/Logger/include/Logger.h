#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#define NOFILESPECIFIED			"NONE"

class Logger
{
public:
	Logger();
	~Logger();

	void set_filename(const char* fname);
	std::string get_filename();

	bool open_file();
	bool open_file(const char* fname);
	bool close_file();

	bool write(const char* txt, const char* ending = "\n");
	bool write(const float flt, const char* ending = "\n");
	bool write_date(const int yyyy, const int mm, const int dd, const char* ending = "\n");
	bool write_date_time(const int yyyy, const int mm, const int dd, const int HH, const int MM, const int SS, const char* ending = "\n");

	bool log_message(const char* txt, const char* line_guard = "", const char* ending = "\n");
	bool log_event(const char* description, const char* line_guard = "");
	bool log_error(const char* description, const char* line_guard = "", const char* error_tag = "ERROR");
	bool log_warning(const char* description, const char* line_guard = "", const char* warning_tag = "WARNING");
	bool log_note(const char* description, const char* line_guard = "", const char* note_tag = "NOTE");

private:

	FILE* fptr;
	std::string filename;

	bool log_generic(const char* description, const char* line_guard, const char* tag, const bool tstamp);
};

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

