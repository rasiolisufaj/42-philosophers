/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/09/29 21:44:55 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];	
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	// Parsing
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}

/*#include "../includes/philo.h"

int	main(int argc, char **argv)
{
    t_program		program;
    t_philo			philos[PHILO_MAX];	
    pthread_mutex_t	forks[PHILO_MAX];

    if (argc != 5 && argc != 6)
    {
        write(2, "Error: Usage: ./philo number_of_philosophers time_to_die "
            "time_to_eat time_to_sleep [number_of_meals]\n", 95);
        return (1);
    }
    if (check_valid_args(argv))
        return (1);
    memset(&program, 0, sizeof(t_program));
    memset(philos, 0, sizeof(t_philo) * PHILO_MAX);
    memset(forks, 0, sizeof(pthread_mutex_t) * PHILO_MAX);
    if (init_program(&program, philos) != 0)
        return (1);
    if (init_forks(philos, &program, forks, argv) != 0)
    {
        destroy_all(NULL, &program, forks);
        return (1);
    }
    if (thread_create(&program, forks) != 0)
    {
        destroy_all(NULL, &program, forks);
        return (1);
    }
    destroy_all(NULL, &program, forks);
    return (0);
}
*/