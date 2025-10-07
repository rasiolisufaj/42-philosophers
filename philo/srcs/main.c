/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/07 13:35:47 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (printf("Error: invalid number of arguments!\n"), 1);
	if (check_valid_args(argv) == 1)
		return (1);
	memset(&program, 0, sizeof(t_program));
	memset(philos, 0, sizeof(t_philo) * PHILO_MAX);
	memset(forks, 0, sizeof(pthread_mutex_t) * PHILO_MAX);
	init_program(&program, philos);
	init_forks(&program, forks);
	init_input(philos, argv);
	init_philos(philos, &program, forks, argv);
	if (thread_create(&program) != 0)
		return (destroy_all(&program, forks, "Thread creation failed"), 1);
	destroy_all(&program, forks, NULL);
	return (0);
}
