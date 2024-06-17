/*
** EPITECH PROJECT, 2024
** DFMY-Zappy
** File description:
** Arguments tests
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include "types/world/chrono.h"

Test(chrono_tests, simple_init)
{
    chrono_t chrono = { 0 };

    chrono_init(&chrono, 10);
    cr_assert_eq(chrono.frequency, 10);
    cr_assert_eq(chrono.started_at.tv_sec, 0);
    cr_assert_eq(chrono.started_at.tv_usec, 0);
    cr_assert_eq(chrono.stopped_at.tv_sec, 0);
    cr_assert_eq(chrono.stopped_at.tv_usec, 0);
}

Test(chrono_tests, simple_start)
{
    // Arrange
    chrono_t chrono = { 0 };
    struct timeval tv = { 0 };

    chrono_init(&chrono, 10);
    gettimeofday(&tv, NULL);

    // Act
    chrono_start(&chrono);

    // Assert
    cr_assert_eq(chrono.started_at.tv_sec, tv.tv_sec);
    cr_assert(
        chrono.started_at.tv_usec >= tv.tv_usec + 2 ||
        chrono.started_at.tv_usec <= tv.tv_usec + 2
    );
}

Test(chrono_tests, simple_stop)
{
    // Arrange
    chrono_t chrono = { 0 };
    struct timeval tv = { 0 };

    chrono_init(&chrono, 10);
    chrono_start(&chrono);
    usleep(1000);
    gettimeofday(&tv, NULL);

    // Act
    chrono_stop(&chrono);

    // Assert
    cr_assert_eq(chrono.stopped_at.tv_sec, tv.tv_sec);
    cr_assert(
        chrono.stopped_at.tv_usec >= tv.tv_usec + 2 ||
        chrono.stopped_at.tv_usec <= tv.tv_usec + 2
    );
}

Test(chrono_tests, get_elapsed_unit_in_1_sec)
{
    // Arrange
    chrono_t chrono = { 0 };
    struct timeval tv = { 0 };

    chrono_init(&chrono, 1);
    chrono_start(&chrono);
    sleep(1);
    gettimeofday(&tv, NULL);
    chrono_stop(&chrono);

    // Act
    time_unit_t elapsed_time = chrono_get_elapsed_units(&chrono);

    // Assert
    cr_assert_float_eq(elapsed_time, 1, 1);
}

Test(chrono_tests, get_elapsed_unit_in_100ms)
{
    // Arrange
    chrono_t chrono = { 0 };

    chrono_init(&chrono, 10);
    chrono_start(&chrono);
    usleep(100000); // 100ms
    chrono_stop(&chrono);

    // Act
    time_unit_t elapsed_time = chrono_get_elapsed_units(&chrono);

    // Assert
    cr_assert_float_eq(elapsed_time, 1, 0.01);
}

Test(chrono_tests, get_elapsed_unit_in_10ms)
{
    // Arrange
    chrono_t chrono = { 0 };

    chrono_init(&chrono, 10);
    chrono_start(&chrono);
    usleep(10000); // 10ms
    chrono_stop(&chrono);

    // Act
    time_unit_t elapsed_time = chrono_get_elapsed_units(&chrono);

    // Assert
    cr_assert_float_eq(elapsed_time, 0.1, 0.01);
}

Test(chrono_tests, time_unit_to_timeval_with_freq_10)
{
    // Arrange
    chrono_t chrono = { 0 };
    timeval_t tv = { 0 };

    chrono_init(&chrono, 10);

    // Act
    chrono_units_to_timeval(&chrono, 1, &tv);

    // Assert
    cr_assert_eq(tv.tv_sec, 10);
}

Test(chrono_tests, time_unit_to_timeval_with_freq_1)
{
    // Arrange
    chrono_t chrono = { 0 };
    timeval_t tv = { 0 };

    chrono_init(&chrono, 1);

    // Act
    chrono_units_to_timeval(&chrono, 1, &tv);

    // Assert
    cr_assert_eq(tv.tv_sec, 1);
}
