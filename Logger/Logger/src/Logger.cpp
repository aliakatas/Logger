#include "Logger.h"
#include "create_timestamp.h"
#include <time.h>

#define PRINT_MESSAGE(e) {char temp_message[256]; \
	memset(temp_message, 0, 256); \
	strerror_s(temp_message, 256, e); \
	fprintf_s(stderr, "%s\n", temp_message); }

#define NO_BYTES_WRITTEN() {fprintf_s(stderr, "No bytes written \n"); }

//************************************
Logger::Logger() {
	fptr = nullptr;
	temp_fptr = stderr;
	filename = NOFILESPECIFIED;
}

//************************************
Logger::~Logger() {
	close_file();
}

//************************************
void Logger::set_filename(const char* fname) {
	filename = fname;
}

//************************************
std::string Logger::get_filename() {
	return filename;
}

//************************************
void Logger::set_error_tag(const char* tag) {
	error_tag = tag;
}

//************************************
std::string Logger::get_error_tag() {
	return error_tag;
}

//************************************
void Logger::set_warning_tag(const char* tag) {
	warning_tag = tag;
}

//************************************
std::string Logger::get_warning_tag() {
	return warning_tag;
}

//************************************
void Logger::set_note_tag(const char* tag) {
	note_tag = tag;
}

//************************************
std::string Logger::get_note_tag() {
	return note_tag;
}

//************************************
bool Logger::open_file() {
	if (filename.compare(NOFILESPECIFIED) == 0)
		return false;

	errno_t err = fopen_s(&fptr, filename.c_str(), "w");
	if (err == 0) {
		fprintf_s(stderr, "File opened:\n   %s \n", filename.c_str());
		temp_fptr = fptr;
	}
	else {
		PRINT_MESSAGE(err);
		return false;
	}

	return true;
}

//************************************
bool Logger::open_file(const char* fname) {
	if (filename.compare(NOFILESPECIFIED) != 0) {
		fprintf_s(stderr, "WARNING: Opening \n     %s \nInstead of \n     %s \n", fname, filename.c_str());
		close_file();
	}

	set_filename(fname);
	return open_file();
}

//************************************
bool Logger::close_file() {
	if (fptr) {
		errno_t err = fclose(fptr);
		if (err == 0) {
			fprintf_s(stderr, "Logger file closed\n");
			fptr = nullptr;
		}
		else {
			PRINT_MESSAGE(err);
			return false;
		}
	}
	else
		return false;

	return true;
}

//************************************
bool Logger::write(const char* txt, const char* ending) {
	if (strlen(txt) > 0 || strlen(ending) > 0) {
		int err = fprintf_s(temp_fptr, "%s%s", txt, ending);
		if (err == 0) {
			NO_BYTES_WRITTEN();
			return false;
		}
	}
	return true;
}

//************************************
bool Logger::write_date(const int yyyy, const int mm, const int dd, const char* ending) {
	int err = fprintf_s(temp_fptr, "[%04d-%02d-%02d]%s", yyyy, mm, dd, ending);
	if (err == 0) {
		NO_BYTES_WRITTEN();
		return false;
	}
	return true;
}

//************************************
bool Logger::write_date_time(const int yyyy, const int mm, const int dd, const int HH, const int MM, const int SS, const char* ending) {
	int err = fprintf_s(temp_fptr, "[%04d-%02d-%02d %02d:%02d:%02d]%s", yyyy, mm, dd, HH, MM, SS, ending);
	if (err == 0) {
		NO_BYTES_WRITTEN();
		return false;
	}
	return true;
}

//************************************
bool Logger::log_message(const char* txt, const char* line_guard, const char* ending) {
	int err = fprintf_s(temp_fptr, "%s %s%s", line_guard, txt, ending);
	if (err == 0) {
		NO_BYTES_WRITTEN();
		return false;
	}
	return true;
}

//************************************
bool Logger::log_event(const char* description, const char* line_guard) {
	if (!write(line_guard, ""))
		return false;
	int timestamp[6] = { 1, 2, 3, 4, 5, 6 };
	time_numbers(timestamp);

	if (!write_date_time(timestamp[0], timestamp[1], timestamp[2], timestamp[3], timestamp[4], timestamp[5], " "))
		return false;

	if (!write(description))
		return false;
	return true;
}

//************************************
bool Logger::log_error(const char* description, const char* line_guard) {
	return log_generic(description, line_guard, error_tag.c_str(), true);
}

//************************************
bool Logger::log_warning(const char* description, const char* line_guard) {
	return log_generic(description, line_guard, warning_tag.c_str(), true);
}

//************************************
bool Logger::log_note(const char* description, const char* line_guard) {
	return log_generic(description, line_guard, note_tag.c_str(), true);
}

//************************************
bool Logger::log_generic(const char* description, const char* line_guard, const char* tag, const bool tstamp) {
	if (!write(line_guard, ""))
		return false;
		
	if (tstamp) {
		int timestamp[6];
		time_numbers(timestamp);

		if (!write_date_time(timestamp[0], timestamp[1], timestamp[2], timestamp[3], timestamp[4], timestamp[5], " "))
			return false;
	}

	if (!write(tag, ": "))
		return false;

	if (!write(description))
		return false;

	return true;
}



