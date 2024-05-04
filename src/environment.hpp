#include "levels/arena.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class Environment
{

    int maxEpisodeSteps;
    int videoRecordInterval;
    int frameSkip;

    int currentStep{0};
    int currentEpsiode{0};

public:
    Environment(int maxEpisodeSteps, int videoRecordInterval, int frameSkip);

    py::tuple step(py::array_t<float> actions);
    py::tuple reset();

    void initHumanRender();
    void draw();

private:
    levels::Arena arena;
    levels::LevelType fakeLevel{levels::LevelType::ARENA};
};