/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/09 13:19:52 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Check if arguments are valid

int	check_valid_args(char **argv)
{
	int		val;
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(&argv[i][0]))
			return (printf("Error: non-numeric argument!\n"), 1);
		val = ft_atoi(argv[i]);
		if (val <= 0)
			return (printf("Error: invalid argument value!\n"), 1);
		if (i == 1 && val > PHILO_MAX)
			return (printf("Error: too many philosophers (max 200)!\n"), 1);
		i++;
	}
	return (0);
}

// Initialize forks and philosophers

void	init_input(t_philo *philos, char **argv)
{
	philos->num_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = (size_t)ft_atoi(argv[2]);
	philos->time_to_eat = (size_t)ft_atoi(argv[3]);
	philos->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argv[5])
		philos->num_times_to_eat = ft_atoi(argv[5]);
	else
		philos->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		init_input(&philos[i], argv);
		philos[i].dead = &program->dead_flag;
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[i].num_of_philos];
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
}

void	init_forks(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	program->forks = forks;
}
