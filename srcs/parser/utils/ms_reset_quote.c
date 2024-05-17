#include "parser.h"

int ms_reset_quote(t_prompt_status *status)
{
	// printf("quote-A\n");
	if (status->squote + status->dquote > 1)
	{
		// printf("quote-B\n");
		status->squote = 0;
		status->dquote = 0;
		return (1);
	}
	return (0);
}