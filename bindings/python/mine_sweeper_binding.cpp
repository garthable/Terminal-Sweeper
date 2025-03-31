#include "pybind11/pybind11.h"
#include "mine_sweeper.hpp"

namespace py = pybind11;

mswp::MineSweeper createMineSweeper(mswp::BoardWidth width, mswp::BoardHeight height, mswp::BombCount bombCount, mswp::BoardSeed boardSeed)
{
    return mswp::MineSweeper(width, height, bombCount, boardSeed);
}

PYBIND11_MODULE(MineSweeper, m)
{
    py::class_<mswp::MineSweeper> mineSweeper(m);

    py::enum_<mswp::MineSweeper::GameState>(mineSweeper, "GameState");

    mineSweeper
        .def(py::init<>(&createMineSweeper))
        .def("click", static_cast<bool (mswp::MineSweeper::*)(mswp::BoardIndex)>(&mswp::MineSweeper::click))
        .def("click", static_cast<bool (mswp::MineSweeper::*)(mswp::BoardXPos, mswp::BoardYPos)>(&mswp::MineSweeper::click))
        .def("flag", static_cast<bool (mswp::MineSweeper::*)(mswp::BoardIndex)>(&mswp::MineSweeper::flag))
        .def("flag", static_cast<bool (mswp::MineSweeper::*)(mswp::BoardXPos, mswp::BoardYPos)>(&mswp::MineSweeper::flag))
        .def("size", &mswp::MineSweeper::size)
        .def("remaining_tiles", &mswp::MineSweeper::remainingTile)
        .def("width", &mswp::MineSweeper::width)
        .def("game_state", &mswp::MineSweeper::gameState)
        .def("flags_remaining", &mswp::MineSweeper::flagsRemaining)
        .def("reset", &mswp::MineSweeper::reset);
}