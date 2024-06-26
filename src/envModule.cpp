#include <pybind11/pybind11.h>

#include "environment.hpp"

namespace py = pybind11;

PYBIND11_MODULE(Starships, m)
{
    py::class_<Environment>(m, "Starships")
        .def(py::init<int, int, int>())
        .def("step", &Environment::step)
        .def("reset", &Environment::reset)
        .def("init_rendering", &Environment::initHumanRender)
        .def("draw", &Environment::draw);
}
