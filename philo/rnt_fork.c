/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rnt_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:42:09 by euc               #+#    #+#             */
/*   Updated: 2024/08/01 20:49:17 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prts(t_philo *philo, long long time, char *status)
{
	check_control(philo);
	pthread_mutex_lock(philo->data->print);
	if (philo->control != 1)
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(philo->data->print);
}
