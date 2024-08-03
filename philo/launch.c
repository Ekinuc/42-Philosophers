/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:40:48 by euc               #+#    #+#             */
/*   Updated: 2024/08/01 20:50:12 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	static int	printtable = 1;

	pthread_mutex_lock(philo->data->print);
	if (philo->control == 0)
	{
		if (get_time() - philo->data->start_time - \
				philo->last_eat_time >= philo->data->time_to_die)
		{
			if (printtable)
			{
				printf("%lld %d died\n", get_time() - \
					philo->data->start_time, philo->id);
				printtable = 0;
			}
			pthread_mutex_lock(philo->data->die_check);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(philo->data->die_check);
			pthread_mutex_unlock(philo->data->print);
			return (0);
		}
	}
	pthread_mutex_unlock(philo->data->print);
	return (1);
}

static int	ft_sleep(t_philo *philo)
{
	prts(philo, get_time() - philo->data->start_time, "is sleeping");
	while (dead_check(philo) && philo->control != 1)
	{
		if (get_time() - philo->data->start_time - philo->last_eat_time == \
				philo->data->time_to_sleep && philo->control != 1)
			return (1);
		usleep(50);
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	prts(philo, time, "is eating");
	while (dead_check(philo) && philo->control != 1 && \
			philo->eat_count != philo->data->must_eat)
	{
		if (philo->data->time_to_eat == (get_time() - \
				philo->data->start_time - time) && philo->control != 1)
		{
			philo->last_eat_time = get_time() - philo->data->start_time;
			philo->eat_count++;
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	prnt_fork(t_philo *philo)
{
	check_control(philo);
	prts(philo, get_time() - philo->data->start_time, "has taken a fork");
	usleep(100);
	check_control(philo);
	prts(philo, get_time() - philo->data->start_time, "has taken a fork");
	ft_eat(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(15000);
	while (philo->control != 1 && philo->eat_count != philo->data->must_eat)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		prnt_fork(philo);
		check_control(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (philo->control == 1)
			break ;
		ft_sleep(philo);
		check_control(philo);
		if (philo->control == 1)
			break ;
		prts(philo, get_time() - philo->data->start_time, "is thinking");
		check_control(philo);
		if (philo->control == 1)
			break ;
	}
	return (0);
}
