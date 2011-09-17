#include "parser.h"

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'a':
      arguments->interactive = 1;
      break;
	 case 'c':
	   arguments->columns = 1;
	   break;
	 case 'i':
	   arguments->input_file = arg; 
	   break;
         case 'o':
           arguments->output_file = arg;
           break;
         case 'v':
           arguments->verbose = 1;
           break;
     
         case ARGP_KEY_ARG:
           if (state->arg_num >= 2)
             /* Too many arguments. */
             argp_usage (state);
     
           arguments->args[state->arg_num] = arg;
     
           break;
     
         case ARGP_KEY_END:
           if (state->arg_num < 2)
             /* Not enough arguments. */
             argp_usage (state);
           break;
     
         default:
           return ARGP_ERR_UNKNOWN;
         }
  return 0;
}
     
