#pragma once

/** Returns the current date+time as array of integers.
* 
* Returns year, month, day, hour, minutes, seconds.
* 
* @param value [out] Integer array of size 6. YYYY, MM, DD, hh, mm, ss
*/
void time_numbers(int *value);

/** Prints the current date+time to stderr.
*/
void timestamp();

/** Returns the current date+time in ISO 8061 format.
* 
* It can be inefficient in memory usage - each call creates a new string.
* 
* @return String with ISO 8061 date-time format.
*/
char* timestring();

/** Returns the current date+time as a string in ISO 8061 format.
* 
* Efficient in memory usage as it only writes to the prescribed buffer.
* 
* @param time_buffer [inout] The buffer where the timestamp is written.
* @param buff_size [in] The size of the buffer. Must be at least 21 characters long.
*/
void get_timestamp_now(char* time_buffer, const int buff_size);

