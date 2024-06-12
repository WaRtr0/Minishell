/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_command_to_json.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:42:31 by mmorot            #+#    #+#             */
/*   Updated: 2024/06/12 14:41:21 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_indent(int indent)
{
	int	i;

	i = 0;
	while (i < indent)
	{
		printf("\t");
		i++;
	}
}

static void	print_conditional(int indent, t_array *array)

{
	t_command	*command;

	command = (t_command *)array->data[0];
	printf("\t\ttype : `%d-%s`,\n", command->type,
		ms_debug_cmd_to_str(command->type));
	if (!(command->type == CMD_WILDCARD || command->type == CMD_EMPTY))
		print_indent(indent);
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND
		|| command->type == CMD_EXPAND_QUOTE)
		printf("\t\tcontent : `%s`\n", command->content.str);
	else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
		(void)"void";
	else if (command->type == CMD_HEREDOC || command->type == CMD_REDIR_IN
		|| command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
		printf("\t\tcontent : %d\n", command->content.fd);
	else if (command->content.array != NULL)
	{
		printf("\t\tcontent : ");
		ms_debug_command_to_json(indent + 2, command->content.array);
	}
}

void	ms_debug_command_to_json(int indent, t_array *array)
{
	printf("[\n");
	while (array->size > 0)
	{
		print_indent(indent);
		printf("\t{\n");
		print_indent(indent);
		print_conditional(indent, array);
		print_indent(indent);
		printf("\t},\n");
		ft_arr_shift(array);
	}
	print_indent(indent);
	printf("]\n");
}

static void	print_conditional_exec(int indent, t_array *array )

{
	t_command	*command;

	command = (t_command *)array->data[0];
	printf("\t\ttype : `%d-%s`,\n", command->type,
		ms_debug_cmd_to_str(command->type));
	if (!(command->type == CMD_WILDCARD || command->type == CMD_EMPTY))
		print_indent(indent);
	if (command->type == CMD_TEXT || command->type == CMD_EXPAND
		|| command->type == CMD_EXPAND_QUOTE || command->type == CMD_REDIR_IN
		|| command->type == CMD_REDIR_OUT || command->type == CMD_APPEND)
		printf("\t\tcontent : `%s`\n", command->content.str);
	else if (command->type == CMD_WILDCARD || command->type == CMD_EMPTY)
		(void)"void";
	else if (command->type == CMD_HEREDOC)
		printf("\t\tcontent : %d\n", command->content.fd);
	else if (command->content.array != NULL)
	{
		printf("\t\tcontent : ");
		ms_debug_command_to_json_exec(indent + 2, command->content.array);
	}
}

void	ms_debug_command_to_json_exec(int indent, t_array *array)
{
	printf("[\n");
	while (array->size > 0)
	{
		print_indent(indent);
		printf("\t{\n");
		print_indent(indent);
		print_conditional_exec(indent, array);
		print_indent(indent);
		printf("\t},\n");
		ft_arr_shift(array);
	}
	print_indent(indent);
	printf("]\n");
}