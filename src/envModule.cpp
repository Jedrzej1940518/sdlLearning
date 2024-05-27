#include <pybind11/pybind11.h>

#include "environment.hpp"

namespace py = pybind11;

PYBIND11_MODULE(Starships, m)
{
    py::class_<Environment>(m, "Starships")
        .def(py::init<int, int, int, int, std::string>())
        .def("step", &Environment::step)
        .def("reset", &Environment::reset)
        .def("write_times", &Environment::writeTimerResults);
}
