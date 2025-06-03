#include "philos.h"

static void	ph_think(t_philo *philo);
static void	ph_take_forks_and_eat(t_philo *philo);
static void	ph_release_forks(t_philo *philo);
static void	ph_sleep(t_philo *philo);

void	run_routine(void *arg)
{
	t_philo	*philo = arg;

	while (1)
	{
		if (philo->data->dead)
			break;
		ph_think(philo);
		ph_take_forks_and_eat(philo);
		ph_release_forks(philo);
		printf("ID: %zu, Eaten: %zu, Must eat: %zu\n", philo->index, philo->meals_eaten, philo->data->must_eat);
		if (philo->meals_eaten == philo->data->must_eat)
			break ;
		ph_sleep(philo);
	}
}

static void	ph_think(t_philo *philo)
{
	t_data *data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu is thinking\n", ph_time_to_ms() - data->start_ms, philo->index);
	pthread_mutex_unlock(&data->print_lock);
}

static void	ph_take_forks_and_eat(t_philo *philo)
{
	t_data *data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu has taken a fork\n", ph_time_to_ms() - data->start_ms, philo->index);
	pthread_mutex_unlock(&data->print_lock);

	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu has taken a fork\n", ph_time_to_ms() - data->start_ms, philo->index);
	pthread_mutex_unlock(&data->print_lock);

	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu is eating\n", ph_time_to_ms() - data->start_ms, philo->index);
	pthread_mutex_unlock(&data->print_lock);
	philo->last_meal = ph_time_to_ms();
	philo->meals_eaten++;
	usleep(data->eat_ms * 1000);
}

static void	ph_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	ph_sleep(t_philo *philo)
{
	t_data *data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu is sleeping\n", ph_time_to_ms() - data->start_ms, philo->index);
	pthread_mutex_unlock(&data->print_lock);
	usleep(data->sleep_ms * 1000);
}
