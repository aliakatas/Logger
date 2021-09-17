#include "create_timestamp.h"

# include <stdio.h>
# include <stdlib.h>
#include <string>
# include <time.h>

// Info on the format for strftime
// https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm

// Functions adapted from 
// https://people.sc.fsu.edu/~jburkardt/c_src/timestamp/timestamp.html

/******************************************************************************/

void time_numbers(int* value)
/* 
  Output:

    int TIME_NUMBERS[6], the year, month, day, hour, minute and second.
*/
{
    tm* tm_ptr = (tm*)malloc(sizeof(tm));
    time_t now;
    
    now = time(0);
    localtime_s(tm_ptr, &now);

    value[0] = 1900 + tm_ptr->tm_year;
    value[1] = 1 + tm_ptr->tm_mon;
    value[2] = tm_ptr->tm_mday;
    value[3] = tm_ptr->tm_hour;
    value[4] = tm_ptr->tm_min;
    value[5] = tm_ptr->tm_sec;

    free(tm_ptr);
}
/******************************************************************************/

void timestamp() {
# define TIME_SIZE 40

    static char time_buffer[TIME_SIZE];
    tm* tm_ptr = (tm*)malloc(sizeof(tm));
    time_t now;

    now = time(NULL);
    localtime_s(tm_ptr, &now);

    //strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    strftime(time_buffer, TIME_SIZE, "%Y-%m-%d %H:%M:%S", tm_ptr);

    printf("%s\n", time_buffer);

    free(tm_ptr);
    return;
# undef TIME_SIZE
}
/******************************************************************************/

char* timestring()
/*
  Output:

    char *TIMESTRING, a string containing the current YMDHMS date.
*/
{
# define TIME_SIZE 40

    tm* tm_ptr = (tm*)malloc(sizeof(tm));
    time_t now;
    char* s;

    now = time(NULL);
    localtime_s(tm_ptr, &now);

    s = (char*)malloc(TIME_SIZE * sizeof(char));

    //strftime(s, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);
    strftime(s, TIME_SIZE, "%Y-%m-%d %H:%M:%S", tm_ptr);

    free(tm_ptr);
    return s;
# undef TIME_SIZE
}
/******************************************************************************/

void get_timestamp_now(char* time_buffer, const int buff_size) {
    memset(time_buffer, 0, buff_size);

    tm* tm_ptr = (tm*)malloc(sizeof(tm));
    time_t now;

    now = time(NULL);
    localtime_s(tm_ptr, &now);

    strftime(time_buffer, buff_size, "%Y-%m-%d %H:%M:%S", tm_ptr);
    free(tm_ptr);
}
