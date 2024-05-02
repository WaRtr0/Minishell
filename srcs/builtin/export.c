/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:19:19 by gcros             #+#    #+#             */
/*   Updated: 2024/05/01 04:08:16 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "stdio.h"

int	append_to_env(char *var, t_env **envp);
int	print_export(t_env *envp);

int	export(char **av, t_env **envp)
{
	char	**arg_p;
	int		ret;

	ret = 0;
	if (*av == NULL)
		return (print_export(*envp));
	arg_p = av;
	while (*++arg_p)
		ret |= append_to_env(*arg_p, envp);
	return (ret);
}

int	append_to_env(char *var, t_env **envp)
{
	t_env	*e;
	char	*s;

	if (ms_parse_env_node(var, &e) == 1)
	{
		get_key(var, &s);
		printf("bash: export: `%s`: not a valid identifier\n", s);
		return (1);
	}
	if (!(e->value == NULL && ms_env_exist(*envp, e->key)))
		ms_env_add(envp, e);
	else
		ms_env_collapse(&e);
	return (0);
}

int	print_export(t_env *envp)
{
	if (envp == NULL)
		return (1);
	print_export(envp->left);
	if (envp->value == NULL)
		printf("export %s\n", envp->key);
	else
		printf("export %s=\"%s\"\n", envp->key, envp->value);
	print_export(envp->right);
	return (0);
}