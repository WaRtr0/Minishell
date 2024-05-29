/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:27:06 by gcros             #+#    #+#             */
/*   Updated: 2024/05/29 15:35:23 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ms_exit_status(int new_status, int save)
{
	static int	status;

	if (save)
		status = new_status;
	return (status);
}

int	ms_get_status(void)
{
	return (ms_exit_status(0, 0));
}

void	ms_set_status(int new_status)
{
	ms_exit_status(new_status, 1);
}
