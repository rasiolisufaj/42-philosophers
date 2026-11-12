/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/02 15:42:17 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Print message
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

// Check if the philosopher died
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Flag the death and print it under write_lock so nothing prints after it
int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos[i].write_lock);
			pthread_mutex_lock(philos[i].dead_lock);
			*(philos[i].dead) = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			printf("%zu %d died\n", get_current_time() - philos[i].start_time,
				philos[i].id);
			pthread_mutex_unlock(philos[i].write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Check if all the philos ate enough
int	check_meals(t_philo *philos)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten < philos[i].num_times_to_eat)
			all_ate = 0;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(philos->dead_lock);
		*(philos->dead) = 1;
		pthread_mutex_unlock(philos->dead_lock);
		return (1);
	}
	return (0);
}

// Monitor thread function
void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	pthread_mutex_lock(philos->write_lock);
	pthread_mutex_unlock(philos->write_lock);
	while (1)
	{
		if (check_if_dead(philos))
			break ;
		if (check_meals(philos))
			break ;
		usleep(100);
	}
	return (NULL);
}
