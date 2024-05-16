#include "arr.h"
#include "char.h"
#include "conf.h"
#include "parser.h"
#include "str.h"
// #include "num.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "exec.h"
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>


int	ms_syntax_error(t_error error, char *msg, t_shell *shell)
{
	if (!shell->prompt_listen)
		return (0);
	if (error == E_SYNTAX_UPD_TOK)
	{
		printf(ERR_SYNTAX_UPD_TOK, msg);
		free(msg);
	}
	else if (error == E_SYNTAX_UPD_EOF)
		printf(ERR_SYNTAX_UPD_EOF);
	else if (error == E_SYNTAX_UPD_NLN)
		printf(ERR_SYNTAX_UPD_NLN);
	shell->prompt_listen = 0;
	return (0);
}