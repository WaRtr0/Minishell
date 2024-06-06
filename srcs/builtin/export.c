/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:19:19 by gcros             #+#    #+#             */
/*   Updated: 2024/06/06 12:52:24 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "stdio.h"
#include "put.h"

int	append_to_env(char *var, t_env **envp);
int	print_export(t_env *envp);

int	export(char **av, t_env **envp)
{
	char	**arg_p;
	int		ret;

	ret = 0;
	if (*(av + 1) == NULL)
		return (print_export(*envp));
	arg_p = av;
	while (*++arg_p)
		ret |= append_to_env(*arg_p, envp);
	return (ret << 8);
}

int	append_to_env(char *var, t_env **envp)
{
	t_env	*e;
	char	*s;
	char	*err_msg;

	if (ms_parse_env_node(var, &e) == 1)
	{
		get_key(var, &s);
		err_msg = ft_strsjoin((char *[])
			{"mishell: export: `", s, "`: not a valid identifier", NULL});
		if (err_msg)
			ft_putendl_fd(err_msg, 2);
		free(err_msg);
		return (EXIT_FAILURE);
	}
	if (!(e->value == NULL && ms_env_exist(*envp, e->key)))
		ms_env_add(envp, e);
	else
		ms_env_collapse(&e);
	return (0);
}

int	print_export(t_env *envp)
{
	char	*prt_val;

	if (envp == NULL)
		return (EXIT_FAILURE << 8);
	print_export(envp->left);
	if (envp->value == NULL)
		prt_val = ft_strsjoin((char *[]){"export ", envp->key, NULL});
	else
		prt_val = ft_strsjoin((char *[])
			{"export ", envp->key, "=\"", envp->value, "\"", NULL});
	if (prt_val)
		ft_putendl_fd(prt_val, 1);
	free(prt_val);
	print_export(envp->right);
	return (0);
}
