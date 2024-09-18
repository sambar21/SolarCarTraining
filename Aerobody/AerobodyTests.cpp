#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <numbers>

#include "Aerobody.h"
#include "VelocityVector.hpp"

constexpr double EPSILON = 0.001; // %

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

TEST_CASE("VelocityVector Constructors: from_cartesian_components", "[VelocityVector]") {
	SECTION("North-South Construction") {
		// North Construction with different magnitudes
		const VelocityVector v1 = VelocityVector::from_cartesian_components(1, 0);
		REQUIRE_THAT(v1.get_north_south(), WithinRel(1, EPSILON));
		REQUIRE_THAT(v1.get_east_west(), WithinAbs(0, EPSILON));

		const VelocityVector v2 = VelocityVector::from_cartesian_components(10, 0);
		REQUIRE_THAT(v2.get_north_south(), WithinRel(10, EPSILON));
		REQUIRE_THAT(v2.get_east_west(), WithinAbs(0, EPSILON));
		const VelocityVector v3 = VelocityVector::from_cartesian_components(std::numbers::pi, 0);
		REQUIRE_THAT(v3.get_north_south(), WithinRel(std::numbers::pi, EPSILON));
		REQUIRE_THAT(v3.get_east_west(), WithinAbs(0, EPSILON));
		// South Construction with different magnitudes
		const VelocityVector v4 = VelocityVector::from_cartesian_components(-1, 0);
		REQUIRE_THAT(v4.get_north_south(), WithinRel(-1, EPSILON));
		REQUIRE_THAT(v4.get_east_west(), WithinAbs(0, EPSILON));

		const VelocityVector v5 = VelocityVector::from_cartesian_components(-10, 0);
		REQUIRE_THAT(v5.get_north_south(), WithinRel(-10, EPSILON));
		REQUIRE_THAT(v5.get_east_west(), WithinAbs(0, EPSILON));
		const VelocityVector v6 = VelocityVector::from_cartesian_components(-std::numbers::pi, 0);
		REQUIRE_THAT(v6.get_north_south(), WithinRel(-std::numbers::pi, EPSILON));
		REQUIRE_THAT(v6.get_east_west(), WithinAbs(0, EPSILON));
	}

	SECTION("East-West Construction") {
		// East Construction with different magnitudes
		const VelocityVector v1 = VelocityVector::from_cartesian_components(0, 1);
		REQUIRE_THAT(v1.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v1.get_east_west(), WithinRel(1, EPSILON));

		const VelocityVector v2 = VelocityVector::from_cartesian_components(0, 10);
		REQUIRE_THAT(v2.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v2.get_east_west(), WithinRel(10, EPSILON));
		const VelocityVector v3 = VelocityVector::from_cartesian_components(0, std::numbers::pi);
		REQUIRE_THAT(v3.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v3.get_east_west(), WithinRel(std::numbers::pi, EPSILON));
		// West Construction with different magnitudes
		const VelocityVector v4 = VelocityVector::from_cartesian_components(0, -1);
		REQUIRE_THAT(v4.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v4.get_east_west(), WithinRel(-1, EPSILON));

		const VelocityVector v5 = VelocityVector::from_cartesian_components(0, -10);
		REQUIRE_THAT(v5.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v5.get_east_west(), WithinRel(-10, EPSILON));
		const VelocityVector v6 = VelocityVector::from_cartesian_components(0, -std::numbers::pi);
		REQUIRE_THAT(v6.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v6.get_east_west(), WithinRel(-std::numbers::pi, EPSILON));
	}

	SECTION("Random Test 0") {
		const VelocityVector v = VelocityVector::from_cartesian_components(-26.1639, 29.8484);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-26.1639, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(29.8484, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector v = VelocityVector::from_cartesian_components(-58.9708, -33.4579);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-58.9708, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(-33.4579, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector v = VelocityVector::from_cartesian_components(80.6333, 12.0257);
		REQUIRE_THAT(v.get_north_south(), WithinRel(80.6333, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(12.0257, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector v = VelocityVector::from_cartesian_components(89.4748, 34.8631);
		REQUIRE_THAT(v.get_north_south(), WithinRel(89.4748, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(34.8631, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector v = VelocityVector::from_cartesian_components(25.8735, 94.3014);
		REQUIRE_THAT(v.get_north_south(), WithinRel(25.8735, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(94.3014, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector v = VelocityVector::from_cartesian_components(8.03837, -89.5614);
		REQUIRE_THAT(v.get_north_south(), WithinRel(8.03837, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(-89.5614, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector v = VelocityVector::from_cartesian_components(-71.866, 76.9131);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-71.866, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(76.9131, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector v = VelocityVector::from_cartesian_components(-63.744, -68.9692);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-63.744, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(-68.9692, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector v = VelocityVector::from_cartesian_components(41.0399, 34.4856);
		REQUIRE_THAT(v.get_north_south(), WithinRel(41.0399, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(34.4856, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector v = VelocityVector::from_cartesian_components(-43.3483, 72.853);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-43.3483, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(72.853, EPSILON));
	}

}

TEST_CASE("VelocityVector Constructors: from_polar_components", "[VelocityVector]") {
	SECTION("North-South Construction") {
		// North Construction with different magnitudes
		const VelocityVector v1 = VelocityVector::from_polar_components(1, 0);
		REQUIRE_THAT(v1.get_north_south(), WithinRel(1, EPSILON));
		REQUIRE_THAT(v1.get_east_west(), WithinAbs(0, EPSILON));

		const VelocityVector v2 = VelocityVector::from_polar_components(10, 0);
		REQUIRE_THAT(v2.get_north_south(), WithinRel(10, EPSILON));
		REQUIRE_THAT(v2.get_east_west(), WithinAbs(0, EPSILON));
		const VelocityVector v3 = VelocityVector::from_polar_components(std::numbers::pi, 0);
		REQUIRE_THAT(v3.get_north_south(), WithinRel(std::numbers::pi, EPSILON));
		REQUIRE_THAT(v3.get_east_west(), WithinAbs(0, EPSILON));
		// South Construction with different magnitudes
		const VelocityVector v4 = VelocityVector::from_polar_components(1, std::numbers::pi);
		REQUIRE_THAT(v4.get_north_south(), WithinRel(-1, EPSILON));
		REQUIRE_THAT(v4.get_east_west(), WithinAbs(0, EPSILON));

		const VelocityVector v5 = VelocityVector::from_polar_components(10, std::numbers::pi);
		REQUIRE_THAT(v5.get_north_south(), WithinRel(-10, EPSILON));
		REQUIRE_THAT(v5.get_east_west(), WithinAbs(0, EPSILON));
		const VelocityVector v6 = VelocityVector::from_polar_components(std::numbers::pi, std::numbers::pi);
		REQUIRE_THAT(v6.get_north_south(), WithinRel(-std::numbers::pi, EPSILON));
		REQUIRE_THAT(v6.get_east_west(), WithinAbs(0, EPSILON));
	}

	SECTION("East-West Construction") {
		// East Construction with different magnitudes
		const VelocityVector v1 = VelocityVector::from_polar_components(1, std::numbers::pi / 2);
		REQUIRE_THAT(v1.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v1.get_east_west(), WithinRel(1, EPSILON));

		const VelocityVector v2 = VelocityVector::from_polar_components(10, std::numbers::pi / 2);
		REQUIRE_THAT(v2.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v2.get_east_west(), WithinRel(10, EPSILON));
		const VelocityVector v3 = VelocityVector::from_polar_components(std::numbers::pi, std::numbers::pi / 2);
		REQUIRE_THAT(v3.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v3.get_east_west(), WithinRel(std::numbers::pi, EPSILON));
		// West Construction with different magnitudes
		const VelocityVector v4 = VelocityVector::from_polar_components(1, -std::numbers::pi / 2);
		REQUIRE_THAT(v4.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v4.get_east_west(), WithinRel(-1, EPSILON));

		const VelocityVector v5 = VelocityVector::from_polar_components(10, -std::numbers::pi / 2);
		REQUIRE_THAT(v5.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v5.get_east_west(), WithinRel(-10, EPSILON));
		const VelocityVector v6 = VelocityVector::from_polar_components(std::numbers::pi, -std::numbers::pi / 2);
		REQUIRE_THAT(v6.get_north_south(), WithinAbs(0, EPSILON));
		REQUIRE_THAT(v6.get_east_west(), WithinRel(-std::numbers::pi, EPSILON));
	}

	SECTION("Random Test 0") {
		const VelocityVector v = VelocityVector::from_polar_components(26.6498, 0.763922);
		REQUIRE_THAT(v.get_north_south(), WithinRel(19.2445, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(18.4352, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector v = VelocityVector::from_polar_components(69.1455, 0.31096);
		REQUIRE_THAT(v.get_north_south(), WithinRel(65.8293, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(21.1566, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector v = VelocityVector::from_polar_components(64.9869, 1.50552);
		REQUIRE_THAT(v.get_north_south(), WithinRel(4.23919, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(64.8485, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector v = VelocityVector::from_polar_components(55.7889, 2.84883);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-53.4151, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(16.1007, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector v = VelocityVector::from_polar_components(47.0201, -1.90729);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-15.5249, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(-44.3831, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector v = VelocityVector::from_polar_components(17.8782, 2.0835);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-8.76986, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(15.5794, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector v = VelocityVector::from_polar_components(29.3844, -1.47739);
		REQUIRE_THAT(v.get_north_south(), WithinRel(2.74076, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(-29.2563, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector v = VelocityVector::from_polar_components(47.3163, 1.40899);
		REQUIRE_THAT(v.get_north_south(), WithinRel(7.62282, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(46.6982, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector v = VelocityVector::from_polar_components(84.8723, 0.729054);
		REQUIRE_THAT(v.get_north_south(), WithinRel(63.2982, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(56.5389, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector v = VelocityVector::from_polar_components(15.2031, 2.14534);
		REQUIRE_THAT(v.get_north_south(), WithinRel(-8.26223, EPSILON));
		REQUIRE_THAT(v.get_east_west(), WithinRel(12.7621, EPSILON));
	}

}

TEST_CASE("VelocityVector Utilities: get_magnitude", "[VelocityVector]") {
	SECTION("Standard Tests") {
		const VelocityVector v1 = VelocityVector::from_cartesian_components(1, 0);
		REQUIRE_THAT(v1.get_magnitude(), WithinRel(1, EPSILON));
		const VelocityVector v2 = VelocityVector::from_cartesian_components(0, 1);
		REQUIRE_THAT(v2.get_magnitude(), WithinRel(1, EPSILON));
		const VelocityVector v3 = VelocityVector::from_cartesian_components(1, 1);
		REQUIRE_THAT(v3.get_magnitude(), WithinRel(std::sqrt(2), EPSILON));
		const VelocityVector v4 = VelocityVector::from_cartesian_components(3, 4);
		REQUIRE_THAT(v4.get_magnitude(), WithinRel(5, EPSILON));
		const VelocityVector v5 = VelocityVector::from_cartesian_components(5, 12);
		REQUIRE_THAT(v5.get_magnitude(), WithinRel(13, EPSILON));
	}

	SECTION("Random Test 0") {
		const VelocityVector v = VelocityVector::from_polar_components(79.4764, -1.27795);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(79.4764, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector v = VelocityVector::from_polar_components(12.1855, -2.27872);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(12.1855, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector v = VelocityVector::from_polar_components(0.355971, 0.508908);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(0.355971, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector v = VelocityVector::from_polar_components(34.6342, 1.75283);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(34.6342, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector v = VelocityVector::from_polar_components(38.5828, 2.56544);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(38.5828, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector v = VelocityVector::from_polar_components(60.9348, 1.66282);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(60.9348, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector v = VelocityVector::from_polar_components(44.2422, 2.87879);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(44.2422, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector v = VelocityVector::from_polar_components(24.8423, 2.69103);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(24.8423, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector v = VelocityVector::from_polar_components(37.0243, -0.0538984);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(37.0243, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector v = VelocityVector::from_polar_components(43.0171, 2.11605);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(43.0171, EPSILON));
	}

	SECTION("Random Test 10") {
		const VelocityVector v = VelocityVector::from_polar_components(13.0726, 0.0321963);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(13.0726, EPSILON));
	}

	SECTION("Random Test 11") {
		const VelocityVector v = VelocityVector::from_polar_components(15.2646, 2.02142);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(15.2646, EPSILON));
	}

	SECTION("Random Test 12") {
		const VelocityVector v = VelocityVector::from_polar_components(48.3812, 2.05039);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(48.3812, EPSILON));
	}

	SECTION("Random Test 13") {
		const VelocityVector v = VelocityVector::from_polar_components(89.0853, 2.58935);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(89.0853, EPSILON));
	}

	SECTION("Random Test 14") {
		const VelocityVector v = VelocityVector::from_polar_components(86.7713, 2.71193);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(86.7713, EPSILON));
	}

	SECTION("Random Test 15") {
		const VelocityVector v = VelocityVector::from_polar_components(88.1316, 1.99044);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(88.1316, EPSILON));
	}

	SECTION("Random Test 16") {
		const VelocityVector v = VelocityVector::from_polar_components(69.3072, -1.63678);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(69.3072, EPSILON));
	}

	SECTION("Random Test 17") {
		const VelocityVector v = VelocityVector::from_polar_components(1.73341, -1.82765);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(1.73341, EPSILON));
	}

	SECTION("Random Test 18") {
		const VelocityVector v = VelocityVector::from_polar_components(12.1883, 0.4959);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(12.1883, EPSILON));
	}

	SECTION("Random Test 19") {
		const VelocityVector v = VelocityVector::from_polar_components(33.2521, -1.04513);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(33.2521, EPSILON));
	}

	SECTION("Random Test 20") {
		const VelocityVector v = VelocityVector::from_polar_components(46.6628, -2.98402);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(46.6628, EPSILON));
	}

	SECTION("Random Test 21") {
		const VelocityVector v = VelocityVector::from_polar_components(38.8694, 0.512494);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(38.8694, EPSILON));
	}

	SECTION("Random Test 22") {
		const VelocityVector v = VelocityVector::from_polar_components(74.8845, 0.331945);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(74.8845, EPSILON));
	}

	SECTION("Random Test 23") {
		const VelocityVector v = VelocityVector::from_polar_components(53.6162, 0.0464611);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(53.6162, EPSILON));
	}

	SECTION("Random Test 24") {
		const VelocityVector v = VelocityVector::from_polar_components(89.469, -1.17109);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(89.469, EPSILON));
	}

	SECTION("Random Test 25") {
		const VelocityVector v = VelocityVector::from_polar_components(0.162497, -2.63319);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(0.162497, EPSILON));
	}

	SECTION("Random Test 26") {
		const VelocityVector v = VelocityVector::from_polar_components(89.2641, 2.0383);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(89.2641, EPSILON));
	}

	SECTION("Random Test 27") {
		const VelocityVector v = VelocityVector::from_polar_components(41.2025, 1.21075);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(41.2025, EPSILON));
	}

	SECTION("Random Test 28") {
		const VelocityVector v = VelocityVector::from_polar_components(74.8633, 2.24749);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(74.8633, EPSILON));
	}

	SECTION("Random Test 29") {
		const VelocityVector v = VelocityVector::from_polar_components(86.5231, 2.85409);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(86.5231, EPSILON));
	}

	SECTION("Random Test 30") {
		const VelocityVector v = VelocityVector::from_polar_components(3.61884, -0.489445);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(3.61884, EPSILON));
	}

	SECTION("Random Test 31") {
		const VelocityVector v = VelocityVector::from_polar_components(67.9829, -0.155573);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(67.9829, EPSILON));
	}

	SECTION("Random Test 32") {
		const VelocityVector v = VelocityVector::from_polar_components(47.4226, 0.486903);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(47.4226, EPSILON));
	}

	SECTION("Random Test 33") {
		const VelocityVector v = VelocityVector::from_polar_components(7.5577, -1.96181);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(7.5577, EPSILON));
	}

	SECTION("Random Test 34") {
		const VelocityVector v = VelocityVector::from_polar_components(76.8382, 2.1342);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(76.8382, EPSILON));
	}

	SECTION("Random Test 35") {
		const VelocityVector v = VelocityVector::from_polar_components(93.3783, -1.64006);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(93.3783, EPSILON));
	}

	SECTION("Random Test 36") {
		const VelocityVector v = VelocityVector::from_polar_components(71.6045, 1.69391);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(71.6045, EPSILON));
	}

	SECTION("Random Test 37") {
		const VelocityVector v = VelocityVector::from_polar_components(69.8343, 1.98384);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(69.8343, EPSILON));
	}

	SECTION("Random Test 38") {
		const VelocityVector v = VelocityVector::from_polar_components(92.7979, -1.22859);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(92.7979, EPSILON));
	}

	SECTION("Random Test 39") {
		const VelocityVector v = VelocityVector::from_polar_components(6.83783, -2.40385);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(6.83783, EPSILON));
	}

	SECTION("Random Test 40") {
		const VelocityVector v = VelocityVector::from_polar_components(14.4971, -2.50572);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(14.4971, EPSILON));
	}

	SECTION("Random Test 41") {
		const VelocityVector v = VelocityVector::from_polar_components(88.7179, 2.50309);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(88.7179, EPSILON));
	}

	SECTION("Random Test 42") {
		const VelocityVector v = VelocityVector::from_polar_components(24.9874, -0.486913);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(24.9874, EPSILON));
	}

	SECTION("Random Test 43") {
		const VelocityVector v = VelocityVector::from_polar_components(26.0813, 0.0418629);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(26.0813, EPSILON));
	}

	SECTION("Random Test 44") {
		const VelocityVector v = VelocityVector::from_polar_components(80.2624, 1.77803);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(80.2624, EPSILON));
	}

	SECTION("Random Test 45") {
		const VelocityVector v = VelocityVector::from_polar_components(59.1571, -2.71241);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(59.1571, EPSILON));
	}

	SECTION("Random Test 46") {
		const VelocityVector v = VelocityVector::from_polar_components(15.0902, -0.132526);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(15.0902, EPSILON));
	}

	SECTION("Random Test 47") {
		const VelocityVector v = VelocityVector::from_polar_components(17.7769, 1.13281);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(17.7769, EPSILON));
	}

	SECTION("Random Test 48") {
		const VelocityVector v = VelocityVector::from_polar_components(28.401, -1.33898);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(28.401, EPSILON));
	}

	SECTION("Random Test 49") {
		const VelocityVector v = VelocityVector::from_polar_components(12.9715, -1.04664);
		REQUIRE_THAT(v.get_magnitude(), WithinRel(12.9715, EPSILON));
	}

}

TEST_CASE("VelocityVector Utilities: get_heading", "[VelocityVector]") {
	SECTION("Random Test 0") {
		const VelocityVector v = VelocityVector::from_polar_components(96.3821, 0.255917);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.31488, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector v = VelocityVector::from_polar_components(83.494, -1.42067);
		REQUIRE_THAT(v.get_heading(), WithinRel(9.27465, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector v = VelocityVector::from_polar_components(98.5278, -3.03769);
		REQUIRE_THAT(v.get_heading(), WithinRel(4.60849, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector v = VelocityVector::from_polar_components(95.7767, 1.73804);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.16724, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector v = VelocityVector::from_polar_components(2.2662, 1.52108);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.0497179, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector v = VelocityVector::from_polar_components(60.7383, 2.66384);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.09304, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector v = VelocityVector::from_polar_components(50.8208, -0.73758);
		REQUIRE_THAT(v.get_heading(), WithinRel(8.59156, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector v = VelocityVector::from_polar_components(97.8738, -0.602357);
		REQUIRE_THAT(v.get_heading(), WithinRel(8.45634, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector v = VelocityVector::from_polar_components(88.8503, -2.32946);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.90026, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector v = VelocityVector::from_polar_components(61.179, 2.45474);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.883946, EPSILON));
	}

	SECTION("Random Test 10") {
		const VelocityVector v = VelocityVector::from_polar_components(64.3601, -1.20669);
		REQUIRE_THAT(v.get_heading(), WithinRel(9.06067, EPSILON));
	}

	SECTION("Random Test 11") {
		const VelocityVector v = VelocityVector::from_polar_components(56.7987, 0.79436);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.776436, EPSILON));
	}

	SECTION("Random Test 12") {
		const VelocityVector v = VelocityVector::from_polar_components(12.5803, -0.475616);
		REQUIRE_THAT(v.get_heading(), WithinRel(8.3296, EPSILON));
	}

	SECTION("Random Test 13") {
		const VelocityVector v = VelocityVector::from_polar_components(42.7183, 1.39015);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.180644, EPSILON));
	}

	SECTION("Random Test 14") {
		const VelocityVector v = VelocityVector::from_polar_components(68.3367, 3.04957);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.47877, EPSILON));
	}

	SECTION("Random Test 15") {
		const VelocityVector v = VelocityVector::from_polar_components(23.2089, 0.0435028);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.52729, EPSILON));
	}

	SECTION("Random Test 16") {
		const VelocityVector v = VelocityVector::from_polar_components(59.7599, -2.31819);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.88899, EPSILON));
	}

	SECTION("Random Test 17") {
		const VelocityVector v = VelocityVector::from_polar_components(20.6223, 0.858955);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.711841, EPSILON));
	}

	SECTION("Random Test 18") {
		const VelocityVector v = VelocityVector::from_polar_components(90.0914, -2.03286);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.60366, EPSILON));
	}

	SECTION("Random Test 19") {
		const VelocityVector v = VelocityVector::from_polar_components(61.0018, -1.7338);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.30459, EPSILON));
	}

	SECTION("Random Test 20") {
		const VelocityVector v = VelocityVector::from_polar_components(8.3356, 2.70238);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.13159, EPSILON));
	}

	SECTION("Random Test 21") {
		const VelocityVector v = VelocityVector::from_polar_components(27.3667, 1.16829);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.402506, EPSILON));
	}

	SECTION("Random Test 22") {
		const VelocityVector v = VelocityVector::from_polar_components(66.1036, -1.46204);
		REQUIRE_THAT(v.get_heading(), WithinRel(9.31602, EPSILON));
	}

	SECTION("Random Test 23") {
		const VelocityVector v = VelocityVector::from_polar_components(33.8187, 0.942283);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.628513, EPSILON));
	}

	SECTION("Random Test 24") {
		const VelocityVector v = VelocityVector::from_polar_components(33.4869, 0.153244);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.41755, EPSILON));
	}

	SECTION("Random Test 25") {
		const VelocityVector v = VelocityVector::from_polar_components(27.3259, 2.1989);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.628107, EPSILON));
	}

	SECTION("Random Test 26") {
		const VelocityVector v = VelocityVector::from_polar_components(97.6424, -1.55423);
		REQUIRE_THAT(v.get_heading(), WithinRel(9.40821, EPSILON));
	}

	SECTION("Random Test 27") {
		const VelocityVector v = VelocityVector::from_polar_components(94.3981, -0.357523);
		REQUIRE_THAT(v.get_heading(), WithinRel(8.2115, EPSILON));
	}

	SECTION("Random Test 28") {
		const VelocityVector v = VelocityVector::from_polar_components(66.7534, -0.117025);
		REQUIRE_THAT(v.get_heading(), WithinRel(7.97101, EPSILON));
	}

	SECTION("Random Test 29") {
		const VelocityVector v = VelocityVector::from_polar_components(65.5281, -1.00302);
		REQUIRE_THAT(v.get_heading(), WithinRel(8.857, EPSILON));
	}

	SECTION("Random Test 30") {
		const VelocityVector v = VelocityVector::from_polar_components(19.3833, 0.0124423);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.55835, EPSILON));
	}

	SECTION("Random Test 31") {
		const VelocityVector v = VelocityVector::from_polar_components(76.1357, 2.68693);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.11613, EPSILON));
	}

	SECTION("Random Test 32") {
		const VelocityVector v = VelocityVector::from_polar_components(50.3093, 2.9002);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.3294, EPSILON));
	}

	SECTION("Random Test 33") {
		const VelocityVector v = VelocityVector::from_polar_components(76.5864, 0.191504);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.37929, EPSILON));
	}

	SECTION("Random Test 34") {
		const VelocityVector v = VelocityVector::from_polar_components(23.0614, 2.73297);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.16217, EPSILON));
	}

	SECTION("Random Test 35") {
		const VelocityVector v = VelocityVector::from_polar_components(97.519, 0.480647);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.09015, EPSILON));
	}

	SECTION("Random Test 36") {
		const VelocityVector v = VelocityVector::from_polar_components(40.6603, -2.06329);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.63409, EPSILON));
	}

	SECTION("Random Test 37") {
		const VelocityVector v = VelocityVector::from_polar_components(54.0296, 0.483118);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.08768, EPSILON));
	}

	SECTION("Random Test 38") {
		const VelocityVector v = VelocityVector::from_polar_components(92.2722, 0.554212);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.01658, EPSILON));
	}

	SECTION("Random Test 39") {
		const VelocityVector v = VelocityVector::from_polar_components(84.7253, 2.27058);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.699788, EPSILON));
	}

	SECTION("Random Test 40") {
		const VelocityVector v = VelocityVector::from_polar_components(49.019, 3.06927);
		REQUIRE_THAT(v.get_heading(), WithinRel(-1.49848, EPSILON));
	}

	SECTION("Random Test 41") {
		const VelocityVector v = VelocityVector::from_polar_components(1.27071, 2.16826);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.597467, EPSILON));
	}

	SECTION("Random Test 42") {
		const VelocityVector v = VelocityVector::from_polar_components(80.6396, -1.27496);
		REQUIRE_THAT(v.get_heading(), WithinRel(9.12894, EPSILON));
	}

	SECTION("Random Test 43") {
		const VelocityVector v = VelocityVector::from_polar_components(96.9122, 2.14171);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.570917, EPSILON));
	}

	SECTION("Random Test 44") {
		const VelocityVector v = VelocityVector::from_polar_components(5.93936, 1.28897);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.281824, EPSILON));
	}

	SECTION("Random Test 45") {
		const VelocityVector v = VelocityVector::from_polar_components(42.2982, 1.28961);
		REQUIRE_THAT(v.get_heading(), WithinRel(0.28119, EPSILON));
	}

	SECTION("Random Test 46") {
		const VelocityVector v = VelocityVector::from_polar_components(72.1935, 2.43673);
		REQUIRE_THAT(v.get_heading(), WithinRel(-0.865935, EPSILON));
	}

	SECTION("Random Test 47") {
		const VelocityVector v = VelocityVector::from_polar_components(17.9144, -2.08996);
		REQUIRE_THAT(v.get_heading(), WithinRel(3.66076, EPSILON));
	}

	SECTION("Random Test 48") {
		const VelocityVector v = VelocityVector::from_polar_components(50.5066, 0.131029);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.43977, EPSILON));
	}

	SECTION("Random Test 49") {
		const VelocityVector v = VelocityVector::from_polar_components(60.5165, 0.446666);
		REQUIRE_THAT(v.get_heading(), WithinRel(1.12413, EPSILON));
	}

}

TEST_CASE("VelocityVector Utilities: angle_between", "[VelocityVector]") {
	SECTION("Standard Tests") {
		const VelocityVector v0 = VelocityVector::from_cartesian_components(0, 0);
		const VelocityVector v1 = VelocityVector::from_cartesian_components(1, 0);
		REQUIRE(v1.angle_between(v0) == 0);
		REQUIRE(v0.angle_between(v1) == 0);
		const VelocityVector v2 = VelocityVector::from_cartesian_components(0, 1);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-std::numbers::pi / 2, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(std::numbers::pi / 2, EPSILON));
		const VelocityVector v3 = VelocityVector::from_cartesian_components(1, 1);
		REQUIRE_THAT(v1.angle_between(v3), WithinRel(-std::numbers::pi / 4, EPSILON));
		REQUIRE_THAT(v3.angle_between(v1), WithinRel(std::numbers::pi / 4, EPSILON));
		REQUIRE_THAT(v2.angle_between(v3), WithinRel(std::numbers::pi / 4, EPSILON));
		REQUIRE_THAT(v3.angle_between(v2), WithinRel(-std::numbers::pi / 4, EPSILON));
	}

	SECTION("Random Test 0") {
		const VelocityVector v1 = VelocityVector::from_polar_components(49.4584, 1.1706);
		const VelocityVector v2 = VelocityVector::from_polar_components(69.6924, 3.02748);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.85688, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.85688, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector v1 = VelocityVector::from_polar_components(51.4128, 1.87821);
		const VelocityVector v2 = VelocityVector::from_polar_components(87.9204, -0.239364);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(2.11758, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-2.11758, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector v1 = VelocityVector::from_polar_components(86.0769, -2.98754);
		const VelocityVector v2 = VelocityVector::from_polar_components(97.6672, 1.5022);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.79344, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.79344, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector v1 = VelocityVector::from_polar_components(27.0585, -2.01479);
		const VelocityVector v2 = VelocityVector::from_polar_components(29.7484, 0.255343);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.27013, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.27013, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector v1 = VelocityVector::from_polar_components(43.2694, 2.22576);
		const VelocityVector v2 = VelocityVector::from_polar_components(10.7028, -2.22249);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.83493, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.83493, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector v1 = VelocityVector::from_polar_components(70.9345, -2.38306);
		const VelocityVector v2 = VelocityVector::from_polar_components(23.2513, 0.599379);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.98244, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.98244, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector v1 = VelocityVector::from_polar_components(49.4479, -1.67268);
		const VelocityVector v2 = VelocityVector::from_polar_components(1.21493, 1.32882);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-3.0015, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(3.0015, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector v1 = VelocityVector::from_polar_components(78.4735, -1.43353);
		const VelocityVector v2 = VelocityVector::from_polar_components(89.842, -2.23416);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.800632, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.800632, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector v1 = VelocityVector::from_polar_components(41.7159, -0.460825);
		const VelocityVector v2 = VelocityVector::from_polar_components(94.9682, 1.00221);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.46303, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.46303, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector v1 = VelocityVector::from_polar_components(84.0556, 1.83285);
		const VelocityVector v2 = VelocityVector::from_polar_components(78.6217, -0.20951);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(2.04236, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-2.04236, EPSILON));
	}

	SECTION("Random Test 10") {
		const VelocityVector v1 = VelocityVector::from_polar_components(83.426, -2.8696);
		const VelocityVector v2 = VelocityVector::from_polar_components(23.1464, -1.26514);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.60446, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.60446, EPSILON));
	}

	SECTION("Random Test 11") {
		const VelocityVector v1 = VelocityVector::from_polar_components(47.9382, -2.08878);
		const VelocityVector v2 = VelocityVector::from_polar_components(48.9682, 1.67298);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(2.52142, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-2.52142, EPSILON));
	}

	SECTION("Random Test 12") {
		const VelocityVector v1 = VelocityVector::from_polar_components(15.2664, 2.41161);
		const VelocityVector v2 = VelocityVector::from_polar_components(20.5207, -2.72381);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.14777, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.14777, EPSILON));
	}

	SECTION("Random Test 13") {
		const VelocityVector v1 = VelocityVector::from_polar_components(90.4251, -0.346844);
		const VelocityVector v2 = VelocityVector::from_polar_components(68.4809, -0.397534);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.0506907, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.0506907, EPSILON));
	}

	SECTION("Random Test 14") {
		const VelocityVector v1 = VelocityVector::from_polar_components(78.9933, 1.82388);
		const VelocityVector v2 = VelocityVector::from_polar_components(88.4836, 2.8083);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.984418, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.984418, EPSILON));
	}

	SECTION("Random Test 15") {
		const VelocityVector v1 = VelocityVector::from_polar_components(18.8659, -1.40039);
		const VelocityVector v2 = VelocityVector::from_polar_components(88.901, -2.50308);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.1027, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.1027, EPSILON));
	}

	SECTION("Random Test 16") {
		const VelocityVector v1 = VelocityVector::from_polar_components(84.5019, -0.0454057);
		const VelocityVector v2 = VelocityVector::from_polar_components(13.3898, 1.99292);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.03833, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.03833, EPSILON));
	}

	SECTION("Random Test 17") {
		const VelocityVector v1 = VelocityVector::from_polar_components(1.26052, -2.79037);
		const VelocityVector v2 = VelocityVector::from_polar_components(89.6186, 1.76815);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.72467, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.72467, EPSILON));
	}

	SECTION("Random Test 18") {
		const VelocityVector v1 = VelocityVector::from_polar_components(9.84227, 0.570379);
		const VelocityVector v2 = VelocityVector::from_polar_components(27.2548, -1.01134);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.58172, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.58172, EPSILON));
	}

	SECTION("Random Test 19") {
		const VelocityVector v1 = VelocityVector::from_polar_components(78.9325, 2.01731);
		const VelocityVector v2 = VelocityVector::from_polar_components(40.3578, 2.23597);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.21866, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.21866, EPSILON));
	}

	SECTION("Random Test 20") {
		const VelocityVector v1 = VelocityVector::from_polar_components(82.2877, -0.0892948);
		const VelocityVector v2 = VelocityVector::from_polar_components(61.9334, -2.42301);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(2.33371, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-2.33371, EPSILON));
	}

	SECTION("Random Test 21") {
		const VelocityVector v1 = VelocityVector::from_polar_components(15.7669, -1.34381);
		const VelocityVector v2 = VelocityVector::from_polar_components(88.1064, -2.09046);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.746651, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.746651, EPSILON));
	}

	SECTION("Random Test 22") {
		const VelocityVector v1 = VelocityVector::from_polar_components(47.685, 1.44031);
		const VelocityVector v2 = VelocityVector::from_polar_components(69.1583, -1.87692);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.96595, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.96595, EPSILON));
	}

	SECTION("Random Test 23") {
		const VelocityVector v1 = VelocityVector::from_polar_components(81.2123, 1.20961);
		const VelocityVector v2 = VelocityVector::from_polar_components(77.6032, 0.641101);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.568513, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.568513, EPSILON));
	}

	SECTION("Random Test 24") {
		const VelocityVector v1 = VelocityVector::from_polar_components(69.0193, 0.431584);
		const VelocityVector v2 = VelocityVector::from_polar_components(83.8571, 1.17029);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.738702, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.738702, EPSILON));
	}

	SECTION("Random Test 25") {
		const VelocityVector v1 = VelocityVector::from_polar_components(71.2791, 2.23993);
		const VelocityVector v2 = VelocityVector::from_polar_components(20.9834, -1.91868);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.12458, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.12458, EPSILON));
	}

	SECTION("Random Test 26") {
		const VelocityVector v1 = VelocityVector::from_polar_components(10.8842, 1.47805);
		const VelocityVector v2 = VelocityVector::from_polar_components(49.0451, -0.106336);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.58438, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.58438, EPSILON));
	}

	SECTION("Random Test 27") {
		const VelocityVector v1 = VelocityVector::from_polar_components(20.7843, -0.885272);
		const VelocityVector v2 = VelocityVector::from_polar_components(61.983, -0.30768);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.577592, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.577592, EPSILON));
	}

	SECTION("Random Test 28") {
		const VelocityVector v1 = VelocityVector::from_polar_components(4.67845, 2.74883);
		const VelocityVector v2 = VelocityVector::from_polar_components(29.6541, 0.256521);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(2.49231, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-2.49231, EPSILON));
	}

	SECTION("Random Test 29") {
		const VelocityVector v1 = VelocityVector::from_polar_components(27.191, 2.22583);
		const VelocityVector v2 = VelocityVector::from_polar_components(60.5689, 1.98715);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.238686, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.238686, EPSILON));
	}

	SECTION("Random Test 30") {
		const VelocityVector v1 = VelocityVector::from_polar_components(53.1189, 2.64696);
		const VelocityVector v2 = VelocityVector::from_polar_components(34.8264, -2.60198);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.03425, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.03425, EPSILON));
	}

	SECTION("Random Test 31") {
		const VelocityVector v1 = VelocityVector::from_polar_components(86.8652, -0.156494);
		const VelocityVector v2 = VelocityVector::from_polar_components(24.9812, -2.06221);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.90571, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.90571, EPSILON));
	}

	SECTION("Random Test 32") {
		const VelocityVector v1 = VelocityVector::from_polar_components(39.4701, 0.629265);
		const VelocityVector v2 = VelocityVector::from_polar_components(1.43636, -2.4127);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(3.04197, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-3.04197, EPSILON));
	}

	SECTION("Random Test 33") {
		const VelocityVector v1 = VelocityVector::from_polar_components(66.2605, 1.03554);
		const VelocityVector v2 = VelocityVector::from_polar_components(4.34053, 3.06299);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.02745, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.02745, EPSILON));
	}

	SECTION("Random Test 34") {
		const VelocityVector v1 = VelocityVector::from_polar_components(65.9873, 2.77075);
		const VelocityVector v2 = VelocityVector::from_polar_components(44.7157, 2.06799);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.70276, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.70276, EPSILON));
	}

	SECTION("Random Test 35") {
		const VelocityVector v1 = VelocityVector::from_polar_components(14.4133, 0.727076);
		const VelocityVector v2 = VelocityVector::from_polar_components(89.7777, -2.67254);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.88357, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.88357, EPSILON));
	}

	SECTION("Random Test 36") {
		const VelocityVector v1 = VelocityVector::from_polar_components(80.4763, -0.872129);
		const VelocityVector v2 = VelocityVector::from_polar_components(44.8186, -0.659394);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.212735, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.212735, EPSILON));
	}

	SECTION("Random Test 37") {
		const VelocityVector v1 = VelocityVector::from_polar_components(75.6923, -1.04652);
		const VelocityVector v2 = VelocityVector::from_polar_components(13.1006, -0.217781);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.828742, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.828742, EPSILON));
	}

	SECTION("Random Test 38") {
		const VelocityVector v1 = VelocityVector::from_polar_components(18.9141, 1.00177);
		const VelocityVector v2 = VelocityVector::from_polar_components(37.7014, 0.703635);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.298135, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.298135, EPSILON));
	}

	SECTION("Random Test 39") {
		const VelocityVector v1 = VelocityVector::from_polar_components(54.5552, 1.39393);
		const VelocityVector v2 = VelocityVector::from_polar_components(39.5692, 0.954264);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(0.439667, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-0.439667, EPSILON));
	}

	SECTION("Random Test 40") {
		const VelocityVector v1 = VelocityVector::from_polar_components(41.6709, -2.5035);
		const VelocityVector v2 = VelocityVector::from_polar_components(18.6501, 2.71286);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(1.06682, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(-1.06682, EPSILON));
	}

	SECTION("Random Test 41") {
		const VelocityVector v1 = VelocityVector::from_polar_components(19.0516, 2.64347);
		const VelocityVector v2 = VelocityVector::from_polar_components(25.1091, -3.08367);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.556052, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.556052, EPSILON));
	}

	SECTION("Random Test 42") {
		const VelocityVector v1 = VelocityVector::from_polar_components(59.6253, -2.58795);
		const VelocityVector v2 = VelocityVector::from_polar_components(27.3216, -0.670474);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.91747, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.91747, EPSILON));
	}

	SECTION("Random Test 43") {
		const VelocityVector v1 = VelocityVector::from_polar_components(22.8969, 1.91323);
		const VelocityVector v2 = VelocityVector::from_polar_components(56.4786, -2.87834);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.49162, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.49162, EPSILON));
	}

	SECTION("Random Test 44") {
		const VelocityVector v1 = VelocityVector::from_polar_components(10.2777, -2.1721);
		const VelocityVector v2 = VelocityVector::from_polar_components(45.4488, -1.4062);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.7659, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.7659, EPSILON));
	}

	SECTION("Random Test 45") {
		const VelocityVector v1 = VelocityVector::from_polar_components(25.408, -1.41176);
		const VelocityVector v2 = VelocityVector::from_polar_components(30.5999, 1.29965);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.71141, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.71141, EPSILON));
	}

	SECTION("Random Test 46") {
		const VelocityVector v1 = VelocityVector::from_polar_components(1.62522, 3.07352);
		const VelocityVector v2 = VelocityVector::from_polar_components(65.5687, -3.04564);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-0.164019, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(0.164019, EPSILON));
	}

	SECTION("Random Test 47") {
		const VelocityVector v1 = VelocityVector::from_polar_components(68.961, 0.681068);
		const VelocityVector v2 = VelocityVector::from_polar_components(97.1899, 1.95318);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.27211, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.27211, EPSILON));
	}

	SECTION("Random Test 48") {
		const VelocityVector v1 = VelocityVector::from_polar_components(23.4281, -1.77164);
		const VelocityVector v2 = VelocityVector::from_polar_components(73.6617, 0.0425024);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-1.81414, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(1.81414, EPSILON));
	}

	SECTION("Random Test 49") {
		const VelocityVector v1 = VelocityVector::from_polar_components(21.0947, -0.803852);
		const VelocityVector v2 = VelocityVector::from_polar_components(44.2027, 1.41307);
		REQUIRE_THAT(v1.angle_between(v2), WithinRel(-2.21692, EPSILON));
		REQUIRE_THAT(v2.angle_between(v1), WithinRel(2.21692, EPSILON));
	}

}

TEST_CASE("Aerobody: get_wind", "[Aerobody]") {
	SECTION("Standard Test: Perpendicular") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(1, 0);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(0, 1);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(std::sqrt(2), EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(std::numbers::pi / 4, EPSILON));
	}

	SECTION("Standard Test: Parallel With Car") {
		const VelocityVector reported_wind = VelocityVector::from_polar_components(1, std::numbers::pi);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(1, 0);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinAbs(0, EPSILON));
		const VelocityVector reported_wind_2 = VelocityVector::from_polar_components(10, std::numbers::pi);
		const VelocityVector car_velocity_2 = VelocityVector::from_cartesian_components(1, 0);
		const ApparentWindVector wind_2 = Aerobody::get_wind(reported_wind_2, car_velocity_2);
		REQUIRE_THAT(wind_2.speed, WithinRel(9, EPSILON));
		REQUIRE_THAT(wind_2.yaw, WithinRel(std::numbers::pi, EPSILON) || WithinRel(-std::numbers::pi, EPSILON));
	}

	SECTION("Standard Test: Parallel Against Car") {
		const VelocityVector reported_wind = VelocityVector::from_polar_components(1, 0);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(1, 0);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(2, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinAbs(0, EPSILON));
		const VelocityVector reported_wind_2 = VelocityVector::from_polar_components(10, 0);
		const VelocityVector car_velocity_2 = VelocityVector::from_cartesian_components(1, 0);
		const ApparentWindVector wind_2 = Aerobody::get_wind(reported_wind_2, car_velocity_2);		REQUIRE_THAT(wind_2.speed, WithinRel(11, EPSILON));
		REQUIRE_THAT(wind_2.yaw, WithinAbs(0, EPSILON));
	}

	SECTION("Random Test 0") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(85.8089, -79.8073);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-72.0995, -49.6938);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(130.225, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.0728, EPSILON));
	}

	SECTION("Random Test 1") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-79.8678, -90.7703);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(29.833, -61.2338);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(160.027, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.77135, EPSILON));
	}

	SECTION("Random Test 2") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(13.085, 16.4514);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-35.8899, 68.67);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(88.1232, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.219835, EPSILON));
	}

	SECTION("Random Test 3") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(19.8615, 38.1111);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-30.1151, 50.9567);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(89.6561, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.419154, EPSILON));
	}

	SECTION("Random Test 4") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-11.9992, 13.5249);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(87.9108, -64.1759);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(91.2583, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.0421882, EPSILON));
	}

	SECTION("Random Test 5") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-47.747, 66.6627);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(8.06355, 13.9268);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(89.8301, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.982391, EPSILON));
	}

	SECTION("Random Test 6") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-52.3076, -60.0761);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-9.8889, 20.3953);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(73.7765, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.68722, EPSILON));
	}

	SECTION("Random Test 7") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(46.56, -15.0289);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-3.81953, 99.8133);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(94.9481, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.505176, EPSILON));
	}

	SECTION("Random Test 8") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(77.0535, 39.3809);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-24.6711, -21.4146);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(55.3779, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-2.75715, EPSILON));
	}

	SECTION("Random Test 9") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-90.058, 25.2272);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-38.6013, -20.5988);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(128.743, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.526147, EPSILON));
	}

	SECTION("Random Test 10") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-94.4767, -48.5826);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(74.3035, -22.867);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(74.2428, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(1.54742, EPSILON));
	}

	SECTION("Random Test 11") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(10.2191, 53.7664);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-79.4703, 68.4931);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(140.51, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.344083, EPSILON));
	}

	SECTION("Random Test 12") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(52.9451, 7.35949);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-38.5342, 61.088);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(69.9481, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.770267, EPSILON));
	}

	SECTION("Random Test 13") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(61.5614, -11.7103);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(64.9457, 84.2877);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(145.848, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.393431, EPSILON));
	}

	SECTION("Random Test 14") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(87.2115, -91.922);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(89.6318, 46.0514);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(182.695, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.728407, EPSILON));
	}

	SECTION("Random Test 15") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(55.5507, 89.9575);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-96.2634, 94.3036);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(188.705, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.578224, EPSILON));
	}

	SECTION("Random Test 16") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-58.0894, 10.604);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(11.5881, -57.4627);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(66.016, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.980564, EPSILON));
	}

	SECTION("Random Test 17") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(76.561, -37.7017);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(8.08642, -50.2237);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(122.049, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.606767, EPSILON));
	}

	SECTION("Random Test 18") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(86.0693, -4.16542);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-26.6589, -5.24923);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(60.1518, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-2.79002, EPSILON));
	}

	SECTION("Random Test 19") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-97.6624, 63.8701);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-85.4308, -44.7494);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(184.089, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.586567, EPSILON));
	}

	SECTION("Random Test 20") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-49.7319, -84.8772);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(0.668559, 86.8196);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(49.1018, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.53893, EPSILON));
	}

	SECTION("Random Test 21") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-90.4824, -33.3851);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(52.7221, -81.5762);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(121.004, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.891124, EPSILON));
	}

	SECTION("Random Test 22") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-39.6596, 12.4717);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-54.2246, 40.0168);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(107.561, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.125979, EPSILON));
	}

	SECTION("Random Test 23") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(51.557, -54.9361);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(18.8708, -45.343);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(122.54, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.217905, EPSILON));
	}

	SECTION("Random Test 24") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-21.891, 95.5338);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(56.9086, -58.1968);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(51.1888, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.61403, EPSILON));
	}

	SECTION("Random Test 25") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(8.46276, 77.6521);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(30.9589, 33.3335);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(117.779, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.407184, EPSILON));
	}

	SECTION("Random Test 26") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(47.7761, 51.2423);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(97.3929, -46.2323);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(145.255, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.4777, EPSILON));
	}

	SECTION("Random Test 27") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(69.6273, -71.7757);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-93.7847, -95.6942);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(169.203, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.63206, EPSILON));
	}

	SECTION("Random Test 28") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(50.8717, -14.7463);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(48.7886, 93.4781);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(127.007, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.421148, EPSILON));
	}

	SECTION("Random Test 29") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-92.2922, 30.555);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(93.0619, -85.4491);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(54.8995, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.813997, EPSILON));
	}

	SECTION("Random Test 30") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-94.9424, 0.688861);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(61.0065, -50.2748);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(60.0867, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(1.48171, EPSILON));
	}

	SECTION("Random Test 31") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-17.5477, -46.061);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(78.6953, 15.5343);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(68.344, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.657924, EPSILON));
	}

	SECTION("Random Test 32") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-8.67845, -14.3229);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-83.2096, 8.93439);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(92.0459, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.165537, EPSILON));
	}

	SECTION("Random Test 33") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-38.2782, -47.3316);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(76.7962, 42.0797);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(38.8744, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.636773, EPSILON));
	}

	SECTION("Random Test 34") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-8.70539, -44.259);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-53.7704, 70.4719);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(67.7521, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.521762, EPSILON));
	}

	SECTION("Random Test 35") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(43.9969, -52.2979);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-50.5816, -24.3183);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(76.8986, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.03691, EPSILON));
	}

	SECTION("Random Test 36") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(77.4593, 55.6364);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-44.0342, 0.409239);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(65.256, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(2.09926, EPSILON));
	}

	SECTION("Random Test 37") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-15.8019, -35.8768);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-72.1812, 87.5849);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(102.053, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.350185, EPSILON));
	}

	SECTION("Random Test 38") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-85.512, 49.9114);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-25.3205, 85.2391);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(174.784, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.398107, EPSILON));
	}

	SECTION("Random Test 39") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-89.7345, 75.1148);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(92.5409, -45.5493);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(29.6984, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-1.93355, EPSILON));
	}

	SECTION("Random Test 40") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(32.0048, -27.6959);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(72.9943, 15.9558);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(105.653, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.326554, EPSILON));
	}

	SECTION("Random Test 41") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(76.6982, -97.4257);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-69.0844, 50.7901);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(47.2531, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-2.36659, EPSILON));
	}

	SECTION("Random Test 42") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(95.7519, 23.4837);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(22.3372, -62.9302);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(124.503, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.90733, EPSILON));
	}

	SECTION("Random Test 43") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-9.97569, 75.9289);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(63.5926, 13.3394);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(104.133, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.823151, EPSILON));
	}

	SECTION("Random Test 44") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(65.3653, -95.9823);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(34.5934, 53.4979);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(108.612, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(1.39868, EPSILON));
	}

	SECTION("Random Test 45") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(6.16138, 20.0263);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-2.71391, -74.2438);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(54.327, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.100038, EPSILON));
	}

	SECTION("Random Test 46") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(10.6143, -80.2663);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-82.6054, 5.37607);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(103.881, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.870123, EPSILON));
	}

	SECTION("Random Test 47") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(5.97468, 67.1506);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(25.9081, 39.5165);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(111.33, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-0.289874, EPSILON));
	}

	SECTION("Random Test 48") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(-87.653, 96.5806);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(43.7161, -0.115064);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(106, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(-2.00082, EPSILON));
	}

	SECTION("Random Test 49") {
		const VelocityVector reported_wind = VelocityVector::from_cartesian_components(20.2528, 99.5117);
		const VelocityVector car_velocity = VelocityVector::from_cartesian_components(-97.9935, -5.43103);
		const ApparentWindVector wind = Aerobody::get_wind(reported_wind, car_velocity);
		REQUIRE_THAT(wind.speed, WithinRel(122.044, EPSILON));
		REQUIRE_THAT(wind.yaw, WithinRel(0.935578, EPSILON));
	}

}

TEST_CASE("Aerobody: aerodynamic_drag", "[Aerobody]") {
	SECTION("Standard Test: Perpendicular") {
		const double drag_coefficient = 0.005;
		const double frontal_area = 1;
		const double air_density = 1.225;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind_perp = { .speed = 1, .yaw = 0};
		const double drag = aero.aerodynamic_drag(wind_perp, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0030625, EPSILON));
		const ApparentWindVector wind_perp_2 = { .speed = 10, .yaw = 0};
		const double drag_2 = aero.aerodynamic_drag(wind_perp_2, air_density);
		REQUIRE_THAT(drag_2, WithinRel(0.30625, EPSILON));
	}

	SECTION("Standard Test: Parallel With Car") {
		const double drag_coefficient = 0.005;
		const double frontal_area = 1;
		const double air_density = 1.225;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind_par = { .speed = 1, .yaw = std::numbers::pi / 2};
		const double drag = aero.aerodynamic_drag(wind_par, air_density);
		REQUIRE_THAT(drag, WithinAbs(0, EPSILON / 100.0));
		const ApparentWindVector wind_par_2 = { .speed = 10, .yaw = std::numbers::pi / 2};
		const double drag_2 = aero.aerodynamic_drag(wind_par_2, air_density);
		REQUIRE_THAT(drag_2, WithinAbs(0, EPSILON / 100.0));
	}

	SECTION("Random Test 0") {
		const double drag_coefficient = 0.00701603;
		const double frontal_area = 3.97;
		const double air_density = 1.42449;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 20.6323, .yaw = 1.64452};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0458186, EPSILON));
	}

	SECTION("Random Test 1") {
		const double drag_coefficient = 0.00358346;
		const double frontal_area = 4.52422;
		const double air_density = 1.04368;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 89.7674, .yaw = 2.43967};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(39.752, EPSILON));
	}

	SECTION("Random Test 2") {
		const double drag_coefficient = 0.00883127;
		const double frontal_area = 7.19096;
		const double air_density = 1.18419;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 45.7031, .yaw = 0.915599};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(29.1594, EPSILON));
	}

	SECTION("Random Test 3") {
		const double drag_coefficient = 0.0062003;
		const double frontal_area = 7.39944;
		const double air_density = 1.19608;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 41.0166, .yaw = -0.500799};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(35.5186, EPSILON));
	}

	SECTION("Random Test 4") {
		const double drag_coefficient = 0.00445965;
		const double frontal_area = 5.4567;
		const double air_density = 1.34184;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 53.05, .yaw = -2.87301};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(42.7129, EPSILON));
	}

	SECTION("Random Test 5") {
		const double drag_coefficient = 0.00191034;
		const double frontal_area = 4.94166;
		const double air_density = 1.07975;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 26.3767, .yaw = -2.79095};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(3.12745, EPSILON));
	}

	SECTION("Random Test 6") {
		const double drag_coefficient = 0.00429404;
		const double frontal_area = 9.76066;
		const double air_density = 1.06606;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 86.0618, .yaw = 3.11194};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(165.325, EPSILON));
	}

	SECTION("Random Test 7") {
		const double drag_coefficient = 0.00606008;
		const double frontal_area = 9.22284;
		const double air_density = 1.33849;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 70.8944, .yaw = -0.533152};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(139.435, EPSILON));
	}

	SECTION("Random Test 8") {
		const double drag_coefficient = 0.00814794;
		const double frontal_area = 2.30766;
		const double air_density = 1.36364;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 12.2179, .yaw = 2.72317};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(1.59778, EPSILON));
	}

	SECTION("Random Test 9") {
		const double drag_coefficient = 0.0054803;
		const double frontal_area = 4.44687;
		const double air_density = 1.09157;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 44.1733, .yaw = 1.04946};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(6.43768, EPSILON));
	}

	SECTION("Random Test 10") {
		const double drag_coefficient = 0.00840197;
		const double frontal_area = 6.70259;
		const double air_density = 1.28814;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 11.9478, .yaw = -1.42618};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.107527, EPSILON));
	}

	SECTION("Random Test 11") {
		const double drag_coefficient = 0.00176457;
		const double frontal_area = 9.52572;
		const double air_density = 1.1162;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 87.5986, .yaw = -1.76198};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.59917, EPSILON));
	}

	SECTION("Random Test 12") {
		const double drag_coefficient = 0.000801252;
		const double frontal_area = 1.35436;
		const double air_density = 1.41398;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 35.4701, .yaw = 0.372882};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.837146, EPSILON));
	}

	SECTION("Random Test 13") {
		const double drag_coefficient = 0.00898297;
		const double frontal_area = 5.14869;
		const double air_density = 1.43301;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 6.67715, .yaw = 2.48648};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.929049, EPSILON));
	}

	SECTION("Random Test 14") {
		const double drag_coefficient = 0.00757117;
		const double frontal_area = 2.42962;
		const double air_density = 1.18913;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 91.1812, .yaw = 0.552662};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(65.872, EPSILON));
	}

	SECTION("Random Test 15") {
		const double drag_coefficient = 0.00202754;
		const double frontal_area = 8.91724;
		const double air_density = 1.0868;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 98.7323, .yaw = -2.12419};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(26.4554, EPSILON));
	}

	SECTION("Random Test 16") {
		const double drag_coefficient = 0.00737824;
		const double frontal_area = 7.3123;
		const double air_density = 1.27924;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 41.5721, .yaw = 0.419592};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(49.7415, EPSILON));
	}

	SECTION("Random Test 17") {
		const double drag_coefficient = 0.00937609;
		const double frontal_area = 7.77076;
		const double air_density = 1.13433;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 45.5793, .yaw = -1.5397};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0830034, EPSILON));
	}

	SECTION("Random Test 18") {
		const double drag_coefficient = 0.00983739;
		const double frontal_area = 9.84909;
		const double air_density = 1.30947;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 62.2652, .yaw = -1.43255};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(4.67065, EPSILON));
	}

	SECTION("Random Test 19") {
		const double drag_coefficient = 0.00508943;
		const double frontal_area = 4.01468;
		const double air_density = 1.34592;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 9.13226, .yaw = 0.303528};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(1.0443, EPSILON));
	}

	SECTION("Random Test 20") {
		const double drag_coefficient = 0.000310514;
		const double frontal_area = 8.88744;
		const double air_density = 1.42345;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 69.9333, .yaw = 0.47908};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(7.56476, EPSILON));
	}

	SECTION("Random Test 21") {
		const double drag_coefficient = 0.00222998;
		const double frontal_area = 7.65119;
		const double air_density = 1.43528;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 46.202, .yaw = 0.524466};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(19.5832, EPSILON));
	}

	SECTION("Random Test 22") {
		const double drag_coefficient = 0.00474162;
		const double frontal_area = 9.23246;
		const double air_density = 1.464;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 85.1306, .yaw = -2.85005};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(213.049, EPSILON));
	}

	SECTION("Random Test 23") {
		const double drag_coefficient = 0.000325036;
		const double frontal_area = 6.3201;
		const double air_density = 1.05602;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 93.1916, .yaw = 2.96694};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(9.13553, EPSILON));
	}

	SECTION("Random Test 24") {
		const double drag_coefficient = 0.00172511;
		const double frontal_area = 3.57936;
		const double air_density = 1.47035;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 91.2537, .yaw = -0.212154};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(36.1258, EPSILON));
	}

	SECTION("Random Test 25") {
		const double drag_coefficient = 0.00700303;
		const double frontal_area = 2.65206;
		const double air_density = 1.45066;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 40.1437, .yaw = 0.381444};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(18.7006, EPSILON));
	}

	SECTION("Random Test 26") {
		const double drag_coefficient = 0.00576029;
		const double frontal_area = 5.01213;
		const double air_density = 1.39916;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 75.9178, .yaw = -1.25931};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(10.9342, EPSILON));
	}

	SECTION("Random Test 27") {
		const double drag_coefficient = 0.00670754;
		const double frontal_area = 6.516;
		const double air_density = 1.01806;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 24.4712, .yaw = -0.503946};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(10.2162, EPSILON));
	}

	SECTION("Random Test 28") {
		const double drag_coefficient = 0.00211887;
		const double frontal_area = 9.1039;
		const double air_density = 1.12663;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 26.6486, .yaw = -1.25747};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.733099, EPSILON));
	}

	SECTION("Random Test 29") {
		const double drag_coefficient = 0.00839326;
		const double frontal_area = 2.84523;
		const double air_density = 1.38558;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 40.5239, .yaw = -3.03508};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(26.8619, EPSILON));
	}

	SECTION("Random Test 30") {
		const double drag_coefficient = 0.00524481;
		const double frontal_area = 5.34951;
		const double air_density = 1.36728;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 73.4826, .yaw = 1.45677};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(1.34089, EPSILON));
	}

	SECTION("Random Test 31") {
		const double drag_coefficient = 0.00217528;
		const double frontal_area = 7.82979;
		const double air_density = 1.13653;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 12.6525, .yaw = -1.59015};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.000580464, EPSILON));
	}

	SECTION("Random Test 32") {
		const double drag_coefficient = 0.00806864;
		const double frontal_area = 9.21229;
		const double air_density = 1.35826;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 6.1132, .yaw = 1.82795};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.122025, EPSILON));
	}

	SECTION("Random Test 33") {
		const double drag_coefficient = 0.00912579;
		const double frontal_area = 9.91225;
		const double air_density = 1.44966;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 96.282, .yaw = 0.222116};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(578.316, EPSILON));
	}

	SECTION("Random Test 34") {
		const double drag_coefficient = 0.00737859;
		const double frontal_area = 4.53362;
		const double air_density = 1.14431;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 92.0362, .yaw = -2.33932};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(78.3276, EPSILON));
	}

	SECTION("Random Test 35") {
		const double drag_coefficient = 0.00043732;
		const double frontal_area = 7.66381;
		const double air_density = 1.08587;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 99.2489, .yaw = 1.34319};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.912634, EPSILON));
	}

	SECTION("Random Test 36") {
		const double drag_coefficient = 0.00826577;
		const double frontal_area = 9.56429;
		const double air_density = 1.19201;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 4.4274, .yaw = -0.436317};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.758647, EPSILON));
	}

	SECTION("Random Test 37") {
		const double drag_coefficient = 0.000714324;
		const double frontal_area = 1.25077;
		const double air_density = 1.04133;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 60.2996, .yaw = -1.75749};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0582705, EPSILON));
	}

	SECTION("Random Test 38") {
		const double drag_coefficient = 0.00897262;
		const double frontal_area = 1.59649;
		const double air_density = 1.15144;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 5.79528, .yaw = 2.56121};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.193696, EPSILON));
	}

	SECTION("Random Test 39") {
		const double drag_coefficient = 0.00405085;
		const double frontal_area = 6.63086;
		const double air_density = 1.24241;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 44.7866, .yaw = -2.78995};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(29.4986, EPSILON));
	}

	SECTION("Random Test 40") {
		const double drag_coefficient = 0.00505733;
		const double frontal_area = 6.26639;
		const double air_density = 1.15267;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 29.3172, .yaw = -1.65316};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.106264, EPSILON));
	}

	SECTION("Random Test 41") {
		const double drag_coefficient = 0.00803774;
		const double frontal_area = 3.86797;
		const double air_density = 1.2317;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 44.1767, .yaw = 1.80332};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(1.98422, EPSILON));
	}

	SECTION("Random Test 42") {
		const double drag_coefficient = 0.00818658;
		const double frontal_area = 4.56429;
		const double air_density = 1.44828;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 15.6894, .yaw = -2.55671};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(4.63031, EPSILON));
	}

	SECTION("Random Test 43") {
		const double drag_coefficient = 0.0072808;
		const double frontal_area = 6.67368;
		const double air_density = 1.03358;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 74.2935, .yaw = 0.532677};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(102.854, EPSILON));
	}

	SECTION("Random Test 44") {
		const double drag_coefficient = 0.00414104;
		const double frontal_area = 1.90184;
		const double air_density = 1.44097;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 87.189, .yaw = -1.55302};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0136273, EPSILON));
	}

	SECTION("Random Test 45") {
		const double drag_coefficient = 0.00692663;
		const double frontal_area = 3.54391;
		const double air_density = 1.30913;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 3.83155, .yaw = 1.98352};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.037951, EPSILON));
	}

	SECTION("Random Test 46") {
		const double drag_coefficient = 0.0062708;
		const double frontal_area = 4.0906;
		const double air_density = 1.25758;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 22.0472, .yaw = 1.60821};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0109707, EPSILON));
	}

	SECTION("Random Test 47") {
		const double drag_coefficient = 0.00406449;
		const double frontal_area = 1.02042;
		const double air_density = 1.12896;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 41.261, .yaw = 2.85436};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(3.66586, EPSILON));
	}

	SECTION("Random Test 48") {
		const double drag_coefficient = 0.00165619;
		const double frontal_area = 3.13501;
		const double air_density = 1.17555;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 52.5314, .yaw = 0.918333};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(3.10446, EPSILON));
	}

	SECTION("Random Test 49") {
		const double drag_coefficient = 0.00636983;
		const double frontal_area = 5.12421;
		const double air_density = 1.11326;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 1.51547, .yaw = -0.55218};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0302461, EPSILON));
	}

	SECTION("Random Test 50") {
		const double drag_coefficient = 0.00367907;
		const double frontal_area = 1.52154;
		const double air_density = 1.25005;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 32.4886, .yaw = -0.561096};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.64735, EPSILON));
	}

	SECTION("Random Test 51") {
		const double drag_coefficient = 0.00891015;
		const double frontal_area = 7.24637;
		const double air_density = 1.18655;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 29.1178, .yaw = 0.490792};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(25.2624, EPSILON));
	}

	SECTION("Random Test 52") {
		const double drag_coefficient = 0.00593031;
		const double frontal_area = 1.25729;
		const double air_density = 1.23961;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 80.1848, .yaw = 2.27396};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(12.4242, EPSILON));
	}

	SECTION("Random Test 53") {
		const double drag_coefficient = 0.00969524;
		const double frontal_area = 2.14973;
		const double air_density = 1.01125;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 27.0227, .yaw = -0.476572};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(6.07597, EPSILON));
	}

	SECTION("Random Test 54") {
		const double drag_coefficient = 0.00648968;
		const double frontal_area = 6.6077;
		const double air_density = 1.46229;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 32.5089, .yaw = 0.020665};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(33.1205, EPSILON));
	}

	SECTION("Random Test 55") {
		const double drag_coefficient = 0.000659422;
		const double frontal_area = 6.33248;
		const double air_density = 1.34961;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 74.1151, .yaw = -2.13855};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(4.47585, EPSILON));
	}

	SECTION("Random Test 56") {
		const double drag_coefficient = 0.00486994;
		const double frontal_area = 1.64081;
		const double air_density = 1.40849;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 81.7352, .yaw = -0.336929};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(33.4857, EPSILON));
	}

	SECTION("Random Test 57") {
		const double drag_coefficient = 0.00681474;
		const double frontal_area = 4.19281;
		const double air_density = 1.08301;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 49.2856, .yaw = 2.90268};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(35.4786, EPSILON));
	}

	SECTION("Random Test 58") {
		const double drag_coefficient = 0.00767348;
		const double frontal_area = 1.80461;
		const double air_density = 1.06805;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 34.3243, .yaw = 1.67284};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0904108, EPSILON));
	}

	SECTION("Random Test 59") {
		const double drag_coefficient = 0.00478627;
		const double frontal_area = 8.4113;
		const double air_density = 1.4002;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 9.9211, .yaw = 2.88683};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.59801, EPSILON));
	}

	SECTION("Random Test 60") {
		const double drag_coefficient = 0.00865159;
		const double frontal_area = 2.58765;
		const double air_density = 1.14513;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 85.2116, .yaw = 2.94391};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(89.4829, EPSILON));
	}

	SECTION("Random Test 61") {
		const double drag_coefficient = 0.00595838;
		const double frontal_area = 4.05041;
		const double air_density = 1.41648;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 2.00443, .yaw = -2.34766};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0337505, EPSILON));
	}

	SECTION("Random Test 62") {
		const double drag_coefficient = 0.00237935;
		const double frontal_area = 9;
		const double air_density = 1.30006;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 46.7367, .yaw = 2.18801};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(10.1847, EPSILON));
	}

	SECTION("Random Test 63") {
		const double drag_coefficient = 0.001997;
		const double frontal_area = 4.22577;
		const double air_density = 1.05135;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 63.6893, .yaw = -0.697735};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(10.5665, EPSILON));
	}

	SECTION("Random Test 64") {
		const double drag_coefficient = 0.0045743;
		const double frontal_area = 6.90954;
		const double air_density = 1.36165;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 43.6156, .yaw = -0.210099};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(39.1544, EPSILON));
	}

	SECTION("Random Test 65") {
		const double drag_coefficient = 0.00785944;
		const double frontal_area = 7.40197;
		const double air_density = 1.28338;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 17.9086, .yaw = -1.06937};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.76626, EPSILON));
	}

	SECTION("Random Test 66") {
		const double drag_coefficient = 0.00304097;
		const double frontal_area = 7.45899;
		const double air_density = 1.39653;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 77.0198, .yaw = -1.16096};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(14.9173, EPSILON));
	}

	SECTION("Random Test 67") {
		const double drag_coefficient = 0.00662562;
		const double frontal_area = 3.14409;
		const double air_density = 1.13598;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 1.416, .yaw = -0.562241};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0169821, EPSILON));
	}

	SECTION("Random Test 68") {
		const double drag_coefficient = 0.00072156;
		const double frontal_area = 2.87024;
		const double air_density = 1.14903;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 41.6692, .yaw = 1.96484};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.304513, EPSILON));
	}

	SECTION("Random Test 69") {
		const double drag_coefficient = 0.00954132;
		const double frontal_area = 4.34973;
		const double air_density = 1.39924;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 79.5529, .yaw = -0.405409};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(155.175, EPSILON));
	}

	SECTION("Random Test 70") {
		const double drag_coefficient = 0.000190017;
		const double frontal_area = 9.72597;
		const double air_density = 1.42445;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 44.199, .yaw = -0.2652};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.39474, EPSILON));
	}

	SECTION("Random Test 71") {
		const double drag_coefficient = 0.00158732;
		const double frontal_area = 9.96849;
		const double air_density = 1.24808;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 55.6402, .yaw = -0.50171};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(23.4989, EPSILON));
	}

	SECTION("Random Test 72") {
		const double drag_coefficient = 0.00797408;
		const double frontal_area = 4.09225;
		const double air_density = 1.20481;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 37.568, .yaw = -2.62809};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(21.0491, EPSILON));
	}

	SECTION("Random Test 73") {
		const double drag_coefficient = 0.00142075;
		const double frontal_area = 2.88645;
		const double air_density = 1.14905;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 34.3269, .yaw = 2.72421};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.32005, EPSILON));
	}

	SECTION("Random Test 74") {
		const double drag_coefficient = 0.00025091;
		const double frontal_area = 3.95136;
		const double air_density = 1.28681;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 11.2223, .yaw = 0.353686};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.070699, EPSILON));
	}

	SECTION("Random Test 75") {
		const double drag_coefficient = 0.0097904;
		const double frontal_area = 9.50978;
		const double air_density = 1.02819;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 32.7751, .yaw = 2.44733};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(30.3682, EPSILON));
	}

	SECTION("Random Test 76") {
		const double drag_coefficient = 0.00616854;
		const double frontal_area = 8.36358;
		const double air_density = 1.27179;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 76.8952, .yaw = -1.15216};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(32.0568, EPSILON));
	}

	SECTION("Random Test 77") {
		const double drag_coefficient = 0.00114449;
		const double frontal_area = 6.57415;
		const double air_density = 1.49529;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 20.9335, .yaw = -1.41705};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0578149, EPSILON));
	}

	SECTION("Random Test 78") {
		const double drag_coefficient = 0.00539913;
		const double frontal_area = 3.1573;
		const double air_density = 1.20461;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 33.7865, .yaw = -0.510782};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(8.91943, EPSILON));
	}

	SECTION("Random Test 79") {
		const double drag_coefficient = 0.00947881;
		const double frontal_area = 7.75322;
		const double air_density = 1.48971;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 63.7342, .yaw = -1.05845};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(53.4365, EPSILON));
	}

	SECTION("Random Test 80") {
		const double drag_coefficient = 0.00915515;
		const double frontal_area = 1.54629;
		const double air_density = 1.48918;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 84.642, .yaw = 2.1658};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(23.7254, EPSILON));
	}

	SECTION("Random Test 81") {
		const double drag_coefficient = 0.00356525;
		const double frontal_area = 9.89252;
		const double air_density = 1.02776;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 60.3829, .yaw = 0.904325};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(25.2561, EPSILON));
	}

	SECTION("Random Test 82") {
		const double drag_coefficient = 0.00253428;
		const double frontal_area = 5.48861;
		const double air_density = 1.1112;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 4.16802, .yaw = -2.762};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.115824, EPSILON));
	}

	SECTION("Random Test 83") {
		const double drag_coefficient = 0.00120413;
		const double frontal_area = 9.42344;
		const double air_density = 1.14123;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 6.63064, .yaw = 1.62064};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.000706734, EPSILON));
	}

	SECTION("Random Test 84") {
		const double drag_coefficient = 0.00365768;
		const double frontal_area = 8.9892;
		const double air_density = 1.18198;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 81.0591, .yaw = -0.607403};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(86.0871, EPSILON));
	}

	SECTION("Random Test 85") {
		const double drag_coefficient = 0.00308906;
		const double frontal_area = 9.95502;
		const double air_density = 1.26842;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 76.274, .yaw = -0.217441};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(108.182, EPSILON));
	}

	SECTION("Random Test 86") {
		const double drag_coefficient = 0.00388216;
		const double frontal_area = 4.16019;
		const double air_density = 1.47648;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 44.6561, .yaw = -1.40115};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.677781, EPSILON));
	}

	SECTION("Random Test 87") {
		const double drag_coefficient = 0.00143218;
		const double frontal_area = 5.43954;
		const double air_density = 1.18076;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 58.3054, .yaw = 2.49907};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(10.0213, EPSILON));
	}

	SECTION("Random Test 88") {
		const double drag_coefficient = 0.00401889;
		const double frontal_area = 7.98333;
		const double air_density = 1.26728;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 30.6638, .yaw = -2.12822};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(5.34921, EPSILON));
	}

	SECTION("Random Test 89") {
		const double drag_coefficient = 0.00672105;
		const double frontal_area = 3.20624;
		const double air_density = 1.49539;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 18.2973, .yaw = -2.24936};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.1252, EPSILON));
	}

	SECTION("Random Test 90") {
		const double drag_coefficient = 0.00592231;
		const double frontal_area = 2.04828;
		const double air_density = 1.48902;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 97.327, .yaw = 1.52422};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.18543, EPSILON));
	}

	SECTION("Random Test 91") {
		const double drag_coefficient = 0.00917752;
		const double frontal_area = 2.44489;
		const double air_density = 1.35392;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 14.9193, .yaw = 2.71104};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.79201, EPSILON));
	}

	SECTION("Random Test 92") {
		const double drag_coefficient = 0.000959167;
		const double frontal_area = 7.50248;
		const double air_density = 1.28259;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 93.8784, .yaw = -2.88541};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(38.0602, EPSILON));
	}

	SECTION("Random Test 93") {
		const double drag_coefficient = 0.00494009;
		const double frontal_area = 3.02744;
		const double air_density = 1.22246;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 78.0503, .yaw = -1.48604};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.399097, EPSILON));
	}

	SECTION("Random Test 94") {
		const double drag_coefficient = 0.00382053;
		const double frontal_area = 2.76296;
		const double air_density = 1.34169;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 14.5214, .yaw = 1.67209};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.0152687, EPSILON));
	}

	SECTION("Random Test 95") {
		const double drag_coefficient = 0.00547034;
		const double frontal_area = 2.60695;
		const double air_density = 1.38688;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 1.36255, .yaw = 2.31682};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.00845756, EPSILON));
	}

	SECTION("Random Test 96") {
		const double drag_coefficient = 0.00116275;
		const double frontal_area = 4.35529;
		const double air_density = 1.23651;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 78.3162, .yaw = -2.01005};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(3.47291, EPSILON));
	}

	SECTION("Random Test 97") {
		const double drag_coefficient = 0.00517413;
		const double frontal_area = 9.03876;
		const double air_density = 1.42108;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 51.795, .yaw = -0.145773};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(87.2664, EPSILON));
	}

	SECTION("Random Test 98") {
		const double drag_coefficient = 0.00214707;
		const double frontal_area = 1.49612;
		const double air_density = 1.44876;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 78.3344, .yaw = 2.04267};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(2.95025, EPSILON));
	}

	SECTION("Random Test 99") {
		const double drag_coefficient = 0.00483444;
		const double frontal_area = 4.84252;
		const double air_density = 1.43364;
		const Aerobody aero = Aerobody(drag_coefficient, frontal_area);
		const ApparentWindVector wind = { .speed = 6.24055, .yaw = -2.45818};
		const double drag = aero.aerodynamic_drag(wind, air_density);
		REQUIRE_THAT(drag, WithinRel(0.392958, EPSILON));
	}

}

