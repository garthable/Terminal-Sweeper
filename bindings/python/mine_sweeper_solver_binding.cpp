#include "pybind11/pybind11.h"
#include "mine_sweeper_solver.hpp"
#include "mine_sweeper_solver_functions.hpp"

namespace py = pybind11;

slvr::MineSweeperSolver createSolver(const mswp::MineSweeper& mineSweeper)
{
    return slvr::MineSweeperSolver(mineSweeper);
}

PYBIND11_MODULE(MineSweeperSolver, m)
{
    py::class_<slvr::MineSweeperSolver> mineSweeperSolver(m);

    mineSweeperSolver
        .def(py::init<>(&createSolver))
        .def("update", &slvr::MineSweeperSolver::update)
        .def("width", &slvr::MineSweeperSolver::width)
        .def("size", &slvr::MineSweeperSolver::size);
    
    py::class_<slvr::ActionArray> actionArray(m);

    actionArray
        .def("reset", &slvr::ActionArray::reset);

    m.def("use_action_arrays", slvr::useActionArrays);
    m.def("lazy_solve", slvr::lazySolve);
    m.def("intersection_solve", slvr::intersectionSolver);
}