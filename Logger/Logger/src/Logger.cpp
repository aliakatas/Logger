#include "Logger.h"
#include "create_timestamp.h"
#include <time.h>

#define PRINT_MESSAGE(e) {char temp_message[256]; \
	memset(temp_message, 0, 256); \
	strerror_s(temp_message, 256, e); \
	fprintf_s(stderr, "%s\n", temp_message); }

#define NO_BYTES_WRITTEN() {fprintf_s(stderr, "No bytes written \n"); }

Logger::Logger() {
	fptr = nullptr;
	filename = NOFILESPECIFIED;
}

Logger::~Logger() {
	fflush(fptr);
	close_file();
}

void Logger::set_filename(const char* fname) {
	filename = fname;
}

std::string Logger::get_filename() {
	return filename;
}

bool Logger::open_file() {
	if (filename.compare(NOFILESPECIFIED) == 0)
		return false;

	errno_t err = fopen_s(&fptr, filename.c_str(), "w");
	if (err == 0) 
		fprintf_s(stderr, "File opened:\n   %s \n", filename.c_str());
	else {
		PRINT_MESSAGE(err);
		return false;
	}

	return true;
}

bool Logger::open_file(const char* fname) {
	if (filename.compare(NOFILESPECIFIED) != 0) 
		fprintf_s(stderr, "WARNING: Opening \n     %s \nInstead of \n     %s \n", fname, filename.c_str());

	set_filename(fname);
	return open_file();
}

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

bool Logger::write(const char* txt, const char* ending) {
	if (strlen(txt) > 0 || strlen(ending) > 0) {
		if (fptr) {
			int err = fprintf_s(fptr, "%s%s", txt, ending);
			if (err == 0) {
				NO_BYTES_WRITTEN();
				return false;
			}
		}
		else
			return false;
	}
	return true;
}

bool Logger::write(const float flt, const char* ending) {
	if (fptr) {
		int err = fprintf_s(fptr, "Numbers: %f%s", flt, ending);
		if (err == 0) {
			NO_BYTES_WRITTEN();
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Logger::write_date(const int yyyy, const int mm, const int dd, const char* ending) {
	if (fptr) {
		int err = fprintf_s(fptr, "[%04d-%02d-%02d]%s", yyyy, mm, dd, ending);
		if (err == 0) {
			NO_BYTES_WRITTEN();
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Logger::write_date_time(const int yyyy, const int mm, const int dd, const int HH, const int MM, const int SS, const char* ending) {
	if (fptr) {
		int err = fprintf_s(fptr, "[%04d-%02d-%02d %02d:%02d:%02d]%s", yyyy, mm, dd, HH, MM, SS, ending);
		if (err == 0) {
			NO_BYTES_WRITTEN();
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Logger::log_message(const char* txt, const char* line_guard, const char* ending) {
	if (fptr) {
		int err = fprintf_s(fptr, "%s %s%s", line_guard, txt, ending);
		if (err == 0) {
			NO_BYTES_WRITTEN();
			return false;
		}
	}
	else
		return false;
	return true;
}

bool Logger::log_event(const char* description, const char* line_guard) {
	if (fptr) {
		if (!write(line_guard, ""))
			return false;
		int timestamp[6];
		time_numbers(timestamp);

		if (!write_date_time(timestamp[0], timestamp[1], timestamp[2], timestamp[3], timestamp[4], timestamp[5], " "))
			return false;

		if (!write(description))
			return false;
	}
	else
		return false;
	return true;
}

bool Logger::log_error(const char* description, const char* line_guard, const char* error_tag) {
	return log_generic(description, line_guard, error_tag, true);
}

bool Logger::log_warning(const char* description, const char* line_guard, const char* warning_tag) {
	return log_generic(description, line_guard, warning_tag, true);
}

bool Logger::log_note(const char* description, const char* line_guard, const char* note_tag) {
	return log_generic(description, line_guard, note_tag, true);
}

bool Logger::log_generic(const char* description, const char* line_guard, const char* tag, const bool tstamp) {
	if (fptr) {
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
	}
	else
		return false;
	return true;
}

//**************************************************************************************

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


