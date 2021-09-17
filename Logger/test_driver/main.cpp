#include "Timer.h"
#include "Logger.h"
#include "text_definitions.h"
#include <stdio.h>

#define N				10000
#define EXAMPLE_LOG		"classic_log.log"

int main(int argc, char** argv) {
	fprintf_s(stderr, "Starting Logger test driver...\n");

	Logger my_classic_logger;
	Logger cli_logger;
	Timer my_timer;

	my_timer.reset();
	my_classic_logger.set_filename(EXAMPLE_LOG);
	my_classic_logger.open_file();

	for (auto i = 0; i < N; ++i) {
		// Write to log file
		if (!my_classic_logger.log_event("*****************", "$!"))
			return -1;
		if (!my_classic_logger.log_error(LINE1_TXT, "!!"))
			return -1;
		if (!my_classic_logger.log_warning(LINE2_TXT, "$!"))
			return -1;
		if (!my_classic_logger.log_note(LINE3_TXT))
			return -1;
		if (!my_classic_logger.write(LINE4_TXT))
			return -1;
		if (!my_classic_logger.write_date(2021, 9, 21))
			return -1;
		if (!my_classic_logger.log_message("Message from main", " "))
			return -1;
		if (!my_classic_logger.log_event("*****************"))
			return -1;

		// Write to stderr
		if (!cli_logger.log_event("*****************", "$!"))
			return -1;
		if (!cli_logger.log_error(LINE1_TXT, "!!"))
			return -1;
		if (!cli_logger.log_warning(LINE2_TXT, "$!"))
			return -1;
		if (!cli_logger.log_note(LINE3_TXT))
			return -1;
		if (!cli_logger.write(LINE4_TXT))
			return -1;
		if (!cli_logger.write_date(2021, 9, 21))
			return -1;
		if (!cli_logger.log_message("Message from main", " "))
			return -1;
		if (!cli_logger.log_event("*****************"))
			return -1;
	}

	my_classic_logger.close_file();
	fprintf_s(stderr, "It took %.4f s to complete with C logger\n", my_timer.elapsed());

	fprintf_s(stderr, "\nDone\n");
	return 0;
}


