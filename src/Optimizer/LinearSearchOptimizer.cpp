#include "LinearSearchOptimizer.h"
#include "src/RaceRunner/RaceRunner.h"  
#include <limits>
#include <optional>
#include <iostream>

LinearSearchOptimizer::LinearSearchOptimizer(
    const SolarCar& car, const Weather& weather, const Route& route, const RaceSchedule& schedule)
    : car(car), weather(weather), route(route), schedule(schedule) {}

std::optional<Optimizer::OptimizationOutput> LinearSearchOptimizer::optimize_race() const {
    double best_speed = minimum_speed;
    double best_time = std::numeric_limits<double>::max();  
    OptimizationOutput best_output{};  // Initialize with default constructor

    for (double speed = best_speed; speed <= maximum_speed; speed += speed_step) {
        std::optional<double> race_time = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);

        if (!race_time.has_value()) {
            continue;
        }

        if (race_time.value() < best_time) {
            best_time = race_time.value();
            best_speed = speed;

            best_output.speed = speed;
            best_output.racetime = race_time.value();
        }
    }

    return best_output;
}
