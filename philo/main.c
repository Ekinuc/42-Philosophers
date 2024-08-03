/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euc <euc@student.42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:47:33 by euc               #+#    #+#             */
/*   Updated: 2024/08/02 14:24:54 by euc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_control(t_philo *philo)
{
	pthread_mutex_lock(philo->data->die_check);
	philo->control = philo->data->is_dead;
	pthread_mutex_unlock(philo->data->die_check);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right_fork);
	prts(philo, get_time() - philo->data->start_time, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	printf("%lld %d died\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static void	ft_thread(t_data *data)
{
	long long	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		init_philo(data, i);
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->n_philo];
	}
	i = -1;
	while (++i < data->n_philo)
	{
		data->err = pthread_create(&data->philos[i].philo, NULL, routine,
				&data->philos[i]);
		if (data->err)
			return ;
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philos[i].philo, NULL);
	while (--i > -1)
		pthread_mutex_destroy(&data->forks[i]);
}

static int	argc_checker(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(ft_isdigit(argv[i])))
			return (free(data->die_check), free(data->print), free(data), 0);
		i++;
	}
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (free(data->die_check), free(data->print), free(data), 0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (free(data->philos), free(data->die_check),
			free(data->print), free(data), 0);
	return (pthread_mutex_init(data->die_check, NULL),
		pthread_mutex_init(data->print, NULL), 1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Error ARG : %s\n", "Wrong number of arguments"), 0);
	data = malloc(sizeof(t_data));
	if (!data || !init_data(data) || !argc_checker(data, argv, argc))
		return (0);
	if (data->n_philo > 1)
		ft_thread(data);
	else
	{
		pthread_mutex_init(&data->forks[0], NULL);
		init_philo(data, 0);
		data->philos[0].right_fork = &data->forks[0];
		data->err = pthread_create(&data->philos[0].philo, NULL,
				one_philo, &data->philos[0]);
		if (data->err)
			return (0);
		pthread_join(data->philos[0].philo, NULL);
		pthread_mutex_destroy(&data->forks[0]);
	}
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->forks);
	return (free(data->die_check), free(data->print),
		free(data->forks), free(data->philos), free(data), 0);
}
