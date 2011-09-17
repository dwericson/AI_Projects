#include <argp.h>

const char *argp_program_version =
       "attrib-count 1.0";
const char *argp_program_bug_address =
       "<john.downs@maine.edu>";

/* Program documentation. */
static char doc[] =
       "attrib-count -- a program to count attributes";
     
/* A description of the arguments we accept. */
static char args_doc[] = "[-i FILE] [-o FILE] [asv]";
     
/* The options we understand. */
static struct argp_option options[] = {
       {"interactive",  'a', 0,      0,  "Run in interactive mode" },
       {"verbose",      'v', 0,      0,  "Produce verbose output" },
       {"columns",      'c', 0,      0,  "Just print attribute columns" },
       {"output",       'o', "FILE", 0,
        "Output to FILE instead of standard output" },
       {"input",   'i', "FILE", 0,
        "Input from FILE instead of standard input" },
       { 0 }
};
     
/* Used by main to communicate with parse_opt. */
struct arguments
{
	int verbose       = 0;
	int columns       = 0;
	int interactive   = 0;
        char *output_file = "";
	char *input_file  = "";
};
     
/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state);
/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };
