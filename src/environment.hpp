#include "levels/arena.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class Environment
{

    int maxEpisodeSteps{10000};
    int currentStep{0};

public:
    Environment();

    py::tuple step(py::array_t<float> action);
    py::array_t<float> reset();

private:
    levels::Arena arena;
    levels::LevelType fakeLevel{levels::LevelType::ARENA};
};