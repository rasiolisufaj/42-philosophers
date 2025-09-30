/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/09/30 12:49:38 by raisufaj         ###   ########.fr       */
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
	init_forks(&program, forks, argv);
	init_philos(philos, &program, forks, argv);
	int num = ft_atoi(argv[1]);
    for (int i = 0; i < num; i++)
    {
        printf("Philo %d:\n", philos[i].id);
        printf("  num_of_philos: %d\n", philos[i].num_of_philos);
        printf("  time_to_die: %zu\n", philos[i].time_to_die);
        printf("  time_to_eat: %zu\n", philos[i].time_to_eat);
        printf("  time_to_sleep: %zu\n", philos[i].time_to_sleep);
        printf("  num_times_to_eat: %d\n", philos[i].num_times_to_eat);
        printf("  meals_eaten: %d\n", philos[i].meals_eaten);
        printf("  eating: %d\n", philos[i].eating);
        printf("  start_time: %zu\n", philos[i].start_time);
        printf("  last_meal: %zu\n", philos[i].last_meal);
    }
	destroy_all(NULL, &program, forks);
	return (0);
}
