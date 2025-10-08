/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/08 14:08:22 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_args_and_allocate(t_program *program, t_philo **philos,
		pthread_mutex_t **forks, char **argv)
{
	if (check_valid_args(argv))
		return (1);
	memset(program, 0, sizeof(t_program));
	*philos = malloc(sizeof(t_philo) * PHILO_MAX);
	*forks = malloc(sizeof(pthread_mutex_t) * PHILO_MAX);
	if (!philos || !forks)
		return (printf("Error: malloc failed!\n"), 1);
	memset(*philos, 0, sizeof(t_philo) * PHILO_MAX);
	memset(*forks, 0, sizeof(pthread_mutex_t) * PHILO_MAX);
	return (0);
}

static int	run_simulation(t_program *program, t_philo *philos,
		pthread_mutex_t *forks, char **argv)
{
	init_program(program, philos);
	init_forks(program, forks);
	init_input(philos, argv);
	init_philos(philos, program, forks, argv);
	if (thread_create(program) != 0)
	{
		destroy_all(program, forks, "Thread creation failed");
		return (1);
	}
	destroy_all(program, forks, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (printf("Error: invalid number of arguments!\n"), 1);
	if (check_args_and_allocate(&program, &philos, &forks, argv))
		return (1);
	if (run_simulation(&program, philos, forks, argv))
	{
		free(philos);
		free(forks);
		return (1);
	}
	free(philos);
	free(forks);
	return (0);
}
