#pragma once

#include <stdio.h>
#include <string>

#define NOFILESPECIFIED			"NONE"

/** Handles the logic for logging various kinds of messages.
* 
* It can handle both stderr and log file output internally. 
* It provides functions to write tagged messages as well as 
* lines with a user-defined guard.
*/
class Logger
{
public:
	/** Constructor - Initialises attributes with sensible values.
	*/
	Logger();

	/** Destructor - Closes log file if it is open.
	*/
	~Logger();

	/** Set the file name (including path) of the log file.
	* 
	* @param fname [in] The file name including absolute or relative path.
	*/
	void set_filename(const char* fname);

	/** Get the file name (including path) of the log file assigned to
	* the Logger object.
	* 
	* @return String of the file name including absolute or relative path.
	*/
	std::string get_filename();

	/** Open the log file assigned to this Logger object.
	* 
	* @return True if successful, false otherwise.
	*/
	bool open_file();
	
	/** Open the log file given as input and assigns it to this Logger object.
	* If there is an existing log file open, it is closed and logging resumes 
	* to the new file.
	* 
	* @param fname [in] The file name (including absolute or relative path) to write log messages to.
	* @return True if successful, false otherwise.
	*/
	bool open_file(const char* fname);
	
	/** Closes the log file associated with this Logger object, if it is open.
	* 
	* @return True if successful, false, otherwise.
	*/
	bool close_file();

	/** Writes text to the log file or stderr (depending on current object's assignment).
	* 
	* @param txt [in] The text string to write.
	* @param ending [in] The line-ending string. Default is newline character.
	* @return True if successful, false otherwise.
	*/
	bool write(const char* txt, const char* ending = "\n");
	
	/** Writes a date in particular format: [YYYY-MM-DD] 
	* to the log file or stderr (depending on current object's assignment).
	* 
	* @param yyyy [in] Year value.
	* @param mm [in] Month value.
	* @param dd [in] Day value.
	* @param ending [in] The line-ending string. Default is newline character.
	* @return True if successful, false otherwise.
	*/
	bool write_date(const int yyyy, const int mm, const int dd, const char* ending = "\n");
	
	/** Writes a date in particular format: [yyyy-mm-dd HH:MM:SS] 
	* to the log file or stderr (depending on current object's assignment).
	* 
	* @param yyyy [in] Year value.
	* @param mm [in] Month value.
	* @param dd [in] Day value.
	* @param HH [in] Hour value.
	* @param MM [in] Minutes value.
	* @param SS [in] Seconds value.
	* @param ending [in] The line-ending string. Default is newline character.
	* @return True if successful, false otherwise.
	*/
	bool write_date_time(const int yyyy, const int mm, const int dd, const int HH, const int MM, const int SS, const char* ending = "\n");

	/** Logs a message to the log file or stderr (depending on current object's assignment).
	* It may include a line guard to facilitate further processing if needed.
	* 
	* @param txt [in] The message string to write.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @param ending [in] The line-ending string. Default is newline character.
	* @return True if successful, false otherwise. 
	*/
	bool log_message(const char* txt, const char* line_guard = "", const char* ending = "\n");
	
	/** Logs an event (its description) to the log file or stderr 
	* (depending on current object's assignment).
	* It may include a line guard to facilitate further processing if needed. 
	* 
	* The current date time (timestamp) is included in the line. The output format is 
	* {line_guard}[yyyy-mm-dd HH:DD:SS] {description} \n.
	* 
	* @param description [in] The message describing the event.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @return True if successful, false otherwise. 
	*/
	bool log_event(const char* description, const char* line_guard = "");
	
	/** Logs an error (its description) to the log file or stderr 
	* (depending on current object's assignment).
	* It may include a line guard to facilitate further processing if needed. 
	* 
	* The current date time (timestamp) is included in the line. The output format is 
	* {line_guard}[yyyy-mm-dd HH:DD:SS] {error_tag}: {description} \n.
	* 
	* @param description [in] The message describing the event.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @param error_tag [in] The string-tag to define an error in the log.
	* @return True if successful, false otherwise.
	*/
	bool log_error(const char* description, const char* line_guard = "", const char* error_tag = "ERROR");
	
	/** Logs a warning (its description) to the log file or stderr 
	* (depending on current object's assignment).
	* It may include a line guard to facilitate further processing if needed. 
	* 
	* The current date time (timestamp) is included in the line. The output format is 
	* {line_guard}[yyyy-mm-dd HH:DD:SS] {warning_tag}: {description} \n.
	* 
	* @param description [in] The message describing the event.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @param warning_tag [in] The string-tag to define a warning in the log.
	* @return True if successful, false otherwise.
	*/
	bool log_warning(const char* description, const char* line_guard = "", const char* warning_tag = "WARNING");
	
	/** Logs a note (its description) to the log file or stderr 
	* (depending on current object's assignment).
	* It may include a line guard to facilitate further processing if needed. 
	* 
	* The current date time (timestamp) is included in the line. The output format is 
	* {line_guard}[yyyy-mm-dd HH:DD:SS] {note_tag}: {description} \n.
	* 
	* @param description [in] The message describing the event.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @param note_tag [in] The string-tag to define a note in the log.
	* @return True if successful, false otherwise.
	*/
	bool log_note(const char* description, const char* line_guard = "", const char* note_tag = "NOTE");
	
	/** Generic log function. Depending on current object's assignment, it can write to
	* a log file or stderr 
	* It may include a line guard to facilitate further processing if needed. 
	* 
	* The current date time (timestamp) can be included in the line. The general (full) 
	* output format is {line_guard}[yyyy-mm-dd HH:DD:SS] {tag}: {description} \n.
	* 
	* @param description [in] The message describing the event.
	* @param line_guard [in] The string to lead the line feed. Default is empty.
	* @param tag [in] The string-tag to define something particular in the log.
	* @param tstamp [in] Flag to indicate whether to include a timestamp or not.
	* @return True if successful, false otherwise.
	*/
	bool log_generic(const char* description, const char* line_guard, const char* tag, const bool tstamp);

private:

	FILE* fptr;						//!< Log file identifier.
	FILE* temp_fptr;				//!< Working identifier (can be stderr or point to where fptr points.
	std::string filename;			//!< Name of the log file (includes path).

};



