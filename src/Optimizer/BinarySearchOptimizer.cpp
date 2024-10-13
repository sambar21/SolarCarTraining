#include "BinarySearchOptimizer.h"
#include "src/RaceRunner/RaceRunner.h"  // Include RaceRunner for race time calculation
#include <limits>
#include <optional>
#include <iostream>

BinarySearchOptimizer::BinarySearchOptimizer(
    const SolarCar& car, const Weather& weather, const Route& route, const RaceSchedule& schedule)
    : car(car), weather(weather), route(route), schedule(schedule) {}

std::optional<Optimizer::OptimizationOutput> BinarySearchOptimizer::optimize_race() const {
    double left = minimum_speed;
    double right = maximum_speed;
    OptimizationOutput best_output{};

    while (right - left > precision) {
        double mid_speed = (left + right) / 2.0;

        std::optional<double> race_time = RaceRunner::calculate_racetime(car, route, weather, schedule, mid_speed);

        if (!race_time.has_value()) {
            right = mid_speed;  // If we run out of energy, reduce speed
            continue;
        }

        best_output.speed = mid_speed;
        best_output.racetime = race_time.value();

        if (race_time.value() < best_output.racetime) {
            right = mid_speed;  // Try to find a faster race time at a lower speed
        } else {
            left = mid_speed;
        }
    }

    return best_output;
}
