#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

# define THINKING "is thinking"

# define EATING "is eating"

# define FORKING "has taken a fork"

# define SLEEPING "is sleeping"

# define USAGE "usage: ./philos [number of philos] \
[time to die] [time to eat] [time to sleep] \
(optional)[number of time each philo must eat]\n"	

# define INVALID_NUMBER "usage: input values must be \
positive and only include numbers.\n"

# define OVER_INTMAX "usage: input value must be greater \
than 0 and cannot exceed value of INT_MAX (2147483647)\n"

# define PH_COUNT "philo count cannot exceed 50!\n"

# define MALLOC_FAIL "memory allocation failed!\n"

# define THREAD_FAIL "thread creation failed!\n"

# define INIT_PRINT_LOCK "failed to init print_lock\n"

# define INIT_INDEX_LOCK "failed to init index_lock\n"

# define INIT_FORK_MUTEX "failed to init fork mutex\n"

# define INIT_MEAL_LOCK "failed to init meal mutex\n"

# define PHILO_MAX 500

#endif
