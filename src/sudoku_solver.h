#ifndef SRC_SUDOKU_SOLVER_H_
#define SRC_SUDOKU_SOLVER_H_

#include <utility>
#include "../src/grid.h"
#include "../src/coord_utils.h"

namespace sudoku
{

    bool _solve(
        Grid *grid,
        Coord cell_coord = std::make_pair(0, 0))
    {
        auto next_coord = get_next_cell_coord(cell_coord);

        if (grid->coord_was_pre_filled(cell_coord))
        {
            if (cell_coord == std::make_pair(8, 8))
                return true;
            return _solve(grid, next_coord);
        }

        auto values = grid->get_possible_values_for_cell_at_coord(cell_coord);
        if (values.size() == 0)
            return false;

        for (auto value : values)
        {
            grid->update(cell_coord, value);
            if (cell_coord == std::make_pair(8, 8))
                return true;

            bool next_cell_is_solved = _solve(grid, next_coord);
            if (next_cell_is_solved)
                return true;

            grid->clear_values_starting_from_coord(cell_coord);
        }

        if (cell_coord == std::make_pair(0, 0))
            throw std::logic_error(
                "This puzzle doesn't have a solution!");

        return false;
    }

    void solve(Grid *grid)
    {

        _solve(grid);
    }

}

#endif