/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorot <mmorot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:30:58 by mmorot            #+#    #+#             */
/*   Updated: 2024/04/12 03:58:56 by mmorot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ms_prompt.c
 * @brief Fichier qui contient la fonction qui va lancer le prompt
 *
 */
#include "arr.h"
#include "char.h"
#include "conf.h"
#include "minishell.h"
#include "prompt.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

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

int	ft_include(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*select_str(char *str, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	get_operator(char *str)
{
	if (!ft_strncmp(str, S_OR, ft_strlen(S_OR)))
		return (E_OR);
	if (!ft_strncmp(str, S_AND_IF, ft_strlen(S_AND_IF)))
		return (E_AND_IF);
	return (-1);
}


int	get_metachar(char *str)
{
	if (!ft_strncmp(str, S_AND, ft_strlen(S_AND)))
		return (E_AND);
	if (!ft_strncmp(str, S_PIPE, ft_strlen(S_PIPE)))
		return (E_PIPE);
	if (!ft_strncmp(str, S_SEMICOLON, ft_strlen(S_SEMICOLON)))
		return (E_SEMICOLON);
	return (-1);
}

int	pass_blank(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_include(BLANK, str[i]))
		i++;
	return (i);
}

int	pass_word(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_include(NO_WORD, str[i]))
		i++;
	return (i);
}

int	pass_name(const char *str)
{
	size_t	i;

	i = 1;
	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i]) || ft_include("_", str[i])))
		i++;
	return (i);
}



t_type	get_type(char *str)
{
	if (!ft_include(NO_WORD, str[0]))
		return (E_WORD);
	if (ft_include(BLANK, str[0]))
		return (E_EMPTY);
	if (ft_include(PARENTHESIS, str[0]))
		return (E_PARENTHESIS);
	if (get_operator(str) != -1)
		return (E_OPERATOR);
	if (get_metachar(str) != -1)
		return (E_METACHAR);
	if (!ft_strncmp(str, S_DQUOTE, ft_strlen(S_DQUOTE)))
		return (E_DQUOTE);
	if (!ft_strncmp(str, S_SQUOTE, ft_strlen(S_SQUOTE)))
		return (E_SQUOTE);
	if (!ft_strncmp(str, S_HEREDOC, ft_strlen(S_HEREDOC)))
		return (E_HEREDOC);
	if (!ft_strncmp(str, S_APPEND, ft_strlen(S_APPEND)))
		return (E_APPEND);
	if (!ft_strncmp(str, S_REDIR_OUT, ft_strlen(S_REDIR_OUT)))
		return (E_REDIR_OUT);
	if (!ft_strncmp(str, S_REDIR_IN, ft_strlen(S_REDIR_IN)))
		return (E_REDIR_IN);
	if (!ft_strncmp(str, S_COMMENT, ft_strlen(S_COMMENT)))
		return (E_COMMENT);
	if (!ft_strncmp(str, S_WILDCARD, ft_strlen(S_WILDCARD)))
		return (E_WILDCARD);
	if (!ft_strncmp(str, S_NEWLINE, ft_strlen(S_NEWLINE)))
		return (E_NEWLINE);
	if (!ft_strncmp(str, S_DOLLAR, ft_strlen(S_DOLLAR)))
		return (E_NAME);
	return (E_EOF);
}

int	next_indent(t_type value, char *str)
{
	if (value >= E_HEREDOC && value <= E_OPERATOR)
		return (2);
	if (value >= E_PARENTHESIS && value <= E_COMMENT)
		return (1);
	if (value == E_WORD)
		return (pass_word(str));
	if (value == E_NAME)
		return (pass_name(str));
	if (value == E_EMPTY)
		return (pass_blank(str));
	return (-1);
}

int	ms_parser(char *line, t_prompt_status *status, t_shell *shell)
{
	size_t	i;
	size_t	len;
	size_t	verif;
	t_type	type;

	(void)status;
	(void)shell;
	i = 0;   
	verif = ft_strlen(line);
	if (verif <= 0)
		return (0);
	shell->prompt_listen = 1;
	while (line[i])
	{
		type = get_type(&line[i]);
		if (type == E_EOF)
			break ;
		len = next_indent(type, &line[i]);
		printf(YELLOW"type: %d | is: %s\n", type, select_str(&line[i], len));
		i += len;
		len = 0;
	}
	printf(BLUE"indent: "WHITE"%zu | %zu\n"RESET, i, verif);
	return (1);
}



/**
 * @brief Fonction qui va recupérer les commandes de l'utilisateur et les executer
 *
 * @param shell Structure principal du programme
 * @return int **0** si tout c'est bien passé sinon **1**
 */
int	ms_prompt(t_shell *shell)
{
	char			*line;
	t_prompt_status	status;

	status = (t_prompt_status){0};
	shell->line = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			ms_parser(line, &status, shell);
		}
		free(line);
	}
	return (0);
}