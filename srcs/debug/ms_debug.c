#include "minishell.h"
#include "lexer.h"
#include "conf.h"
#include <stdint.h>

char *CMD_to_str(t_command_type type)
{
	static char *cmd[] = {"CMD_PIPE", "CMD_REDIR_IN", "CMD_REDIR_OUT", "CMD_APPEND",
	"CMD_HEREDOC", "CMD_SEMICOLON", "CMD_AND_IF", "CMD_AND",
	"CMD_OR", "CMD_QUOTE", "CMD_PARENTHESIS", "CMD_EXPAND",
	"CMD_EXPAND_QUOTE", "CMD_TEXT", "CMD_JOIN", "CMD_JOIN_NO_PRINT", "CMD_EMPTY",
	"CMD_WILDCARD"};
	return (cmd[type]);
}

void print_indent(int indent)
{
	int i = 0;
	while (i < indent)
	{
		printf("\t");
		i++;
	}
}
void command_to_json(int indent, t_array *array)
{
	printf("[\n");
	while (array->size > 0)
	{
		t_command *command = (t_command *)array->data[0];
		print_indent(indent);
		printf("\t{\n");
		print_indent(indent);
		printf("\t\ttype : `%d-%s`,\n", command->type, CMD_to_str(command->type));
		if (!(command->type == CMD_WILDCARD || command->type == CMD_EMPTY))
		print_indent(indent);
		if (command->type == CMD_TEXT || command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
			printf("\t\tcontent : `%s`\n", command->content.str);
		else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
			(void)"tkt frere";
		else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
			printf("\t\tcontent : %d\n", command->content.fd);
		else if(command->content.array != NULL)
		{
			printf("\t\tcontent : ");
			command_to_json(indent + 2, command->content.array);
		}

		print_indent(indent);
		printf("\t},\n");

		// ft_arr_free((void *)command->content.array, 0);
		ft_arr_shift(array);
	}
	print_indent(indent);
	printf("]\n");
}

void command_map(t_array *array, void *(*f)(void *))
{
	ft_arr_map(array, (void *)f, 0);
}

void *print_json(t_command *command)
{

	printf("{");
	printf("type:`%d-%s`,", command->type, CMD_to_str(command->type));
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND || command->type == CMD_EXPAND_QUOTE)
		printf("content:`%s`", command->content.str);
	else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
		(void)"tkt frere";
	else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN || command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
		printf("content:%d", command->content.fd);
	else if(command->content.array != NULL)
	{
		printf("content:[");
		command_map(command->content.array, (void *)print_json);
		printf("],");
	}

	printf("},");
	return (command);
}

int ms_debug(t_shell *shell)
{
    printf(C_RED"%s\n"C_RESET, shell->prompt);
    printf(C_GREEN"FD: %d\n"C_RESET, shell->heredoc_size/2);
    printf("--------------------\n"C_GREEN"[");
    command_map(shell->commands, (void *)print_json);
    printf("]"C_RESET"\n--------------------\n");
    command_to_json(0, shell->commands);
    // print list heredoc
    int i = 0;
    while (shell->heredoc_size > 0 && i <= shell->heredoc_size/2)
    {
        printf(C_BLUE"- FD: %d | %d\n"C_RESET, (int)(intptr_t)shell->heredoc_fd->data[i], (int)(intptr_t)shell->heredoc_fd->data[i+1]);
        i+=2;
    }
    i = 0;
    while (shell->heredoc_size > 0 && i < shell->heredoc_size)
    {
        char *buffer = ft_calloc(sizeof(char), 100);
        ft_strcpy(buffer, "test");
        read((int)(intptr_t)shell->heredoc_fd->data[i], buffer, 100);
        printf(C_BLUE"%s\n"C_RESET, buffer);
        free(buffer);
        i += 2;
    }
    printf("\n--------------------\n");
    return (0);
}