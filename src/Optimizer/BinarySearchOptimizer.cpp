#include "BinarySearchOptimizer.h"
#include "RaceRunner/RaceRunner.h"
#include <limits> 
#include <algorithm> 

BinarySearchOptimizer::BinarySearchOptimizer(
    const SolarCar& car, const Weather& weather, const Route& route, const RaceSchedule& schedule)
    : car(car), weather(weather), route(route), schedule(schedule) {}

std::optional<Optimizer::OptimizationOutput> BinarySearchOptimizer::optimize_race() const {
    double low = minimum_speed;
    double high = maximum_speed;
    OptimizationOutput best_output{};
    best_output.racetime = std::numeric_limits<double>::max();
    bool found_any_valid_speed = false;

    while (high - low > precision) {
        double mid = (low + high) / 2;
        auto race_time = RaceRunner::calculate_racetime(car, route, weather, schedule, mid);

        if (race_time.has_value()) {
            
            found_any_valid_speed = true;
            if (race_time.value() < best_output.racetime) {
                best_output.speed = mid;
                best_output.racetime = race_time.value();
            }
            low = mid; 
        } else {
            
            high = mid;
        }
    }

    if (!found_any_valid_speed) {
        return std::nullopt;
    }

    if (best_output.racetime == std::numeric_limits<double>::max()) {
        best_output.speed = low;
        best_output.racetime = RaceRunner::calculate_racetime(car, route, weather, schedule, low).value_or(std::numeric_limits<double>::max());
    }

    return best_output;
}
