/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:44:12 by gcros             #+#    #+#             */
/*   Updated: 2024/05/03 00:01:47 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stddef.h>

typedef struct s_env	t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*left;
	t_env	*right;
};

void	ms_env_init(char *key, char *value, t_env *env);
t_env	*ms_env_new(char *key, char *value);
int		ms_env_add(t_env **head, t_env *e);
char	*ms_env_get(t_env *env, char *key);
int		ms_env_exist(t_env *env, char *key);
void	ms_env_remove(t_env	**head, char *key);
void	ms_env_collapse(t_env **head);
int		ms_env_gen(char **strs, t_env **env);
int		ms_parse_env_node(char *str, t_env **out);
int		ms_env_to_strs(t_env *env, char ***out);
int		ms_env_complete(t_env **env, char *exec_cmd);

#endif