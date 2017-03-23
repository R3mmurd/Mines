/*
  This file is part of mines game
  Copyright (C) 2011 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to 

  Alejandro Mujica

  aledrums@gmail.com
*/

# include <utility>

# include <QStack>

# include <matrix.H>

Matrix::Matrix(const size_t & _h,
               const size_t & _w,
               const size_t & _mines,
               std::mt19937 & rng)
  : w(_w), h(_h), mines(_mines), flags(0), uncovered_boxes(0)
{

  using unif_dist_t = std::uniform_int_distribution<int>;

  unif_dist_t col_dist {0, int(w) - 1};
  unif_dist_t row_dist {0, int(h) - 1};

  matrix = new Box *[h];
  for (size_t i = 0; i < h; ++i)
    matrix[i] = new Box[w];

  for (size_t i = 0; i < mines; ++i)
    {
      while (true)
        {
          const size_t col = col_dist(rng);
          const size_t row = row_dist(rng);
          if (matrix[row][col].object != Mine)
            {
              matrix[row][col].object = Mine;
              inc_mines_around(row, col);
              break;
            }
        }
    }
}

Matrix::~Matrix()
{
  for (size_t i = 0; i < h; ++i)
    delete []matrix[i];
  delete []matrix;
}

const size_t & Matrix::rows() const
{
  return h;
}

const size_t & Matrix::cols() const
{
  return w;
}

const Matrix_Values & Matrix::object_of(const size_t & i, const size_t & j)
{
  return matrix[i][j].object;
}

const Matrix_Values & Matrix::status_of(const size_t & i, const size_t & j)
{
  return matrix[i][j].status;
}

bool Matrix::flag(const size_t & i, const size_t & j)
{
  Matrix_Values & s = matrix[i][j].status;
  if (s == Uncovered)
    return false;

  if (s == Flag)
    {
      s = Covered;
      --flags;
    }
  else
    {
      if (flags == mines)
        return false;
      s = Flag;
      ++flags;
    }

  return true;
}

void Matrix::discover(const size_t & _i, const size_t & _j)
{
  using Pos = std::pair<size_t, size_t>;

  QStack<Pos> stack;

  stack.push(std::make_pair(_i, _j));

  while (not stack.empty())
    {
      Pos p = stack.pop();

      const size_t & i = p.first;
      const size_t & j = p.second;

      if (i >= h or j >= w)
        continue;

      Matrix_Values & s = matrix[i][j].status;

      if (s == Uncovered or s == Flag or matrix[i][j].object == Mine)
        continue;

      ++uncovered_boxes;
      s = Uncovered;
      if (matrix[i][j].object == Zero)
        {
          stack.push(std::make_pair(i - 1, j - 1));
          stack.push(std::make_pair(i - 1, j));
          stack.push(std::make_pair(i - 1, j + 1));
          stack.push(std::make_pair(i, j + 1));
          stack.push(std::make_pair(i + 1, j + 1));
          stack.push(std::make_pair(i + 1, j));
          stack.push(std::make_pair(i + 1, j - 1));
          stack.push(std::make_pair(i, j - 1));
        }
    }
}

void Matrix::discover_all_mines()
{
  for (size_t i = 0; i < h; ++i)
    for (size_t j = 0; j < w; ++j)
      if (matrix[i][j].object == Mine and matrix[i][j].status != Flag)
        matrix[i][j].status = Uncovered;
}

const size_t & Matrix::get_flags() const
{
  return flags;
}

const size_t & Matrix::get_mines() const
{
  return mines;
}

bool Matrix::are_uncovered_all() const
{
  return uncovered_boxes == w * h - mines;
}

void Matrix::inc_mines_around(const size_t & i, const size_t & j)
{
  if (i > 0)
    {
      matrix[i - 1][j].object =
          Matrix_Values(int(matrix[i - 1][j].object) +
                        ((matrix[i - 1][j].object == Mine) ? 0 : 1));
      if (j > 0)
        matrix[i - 1][j - 1].object =
            Matrix_Values(int(matrix[i - 1][j - 1].object) +
                          ((matrix[i - 1][j - 1].object == Mine) ? 0 : 1));
      if (j < w - 1)
        matrix[i - 1][j + 1].object =
            Matrix_Values(int(matrix[i - 1][j + 1].object) +
                          ((matrix[i - 1][j + 1].object == Mine) ? 0 : 1));
    }
  if (i < h - 1)
    {
      matrix[i + 1][j].object =
          Matrix_Values(int(matrix[i + 1][j].object) +
                        ((matrix[i + 1][j].object == Mine) ? 0 : 1));
      if (j > 0)
        matrix[i + 1][j - 1].object =
            Matrix_Values(int(matrix[i + 1][j - 1].object) +
                          ((matrix[i + 1][j - 1].object == Mine) ? 0 : 1));
      if (j < w - 1)
        matrix[i + 1][j + 1].object =
            Matrix_Values(int(matrix[i + 1][j + 1].object) +
                          ((matrix[i + 1][j + 1].object == Mine) ? 0 : 1));
    }
  if (j > 0)
    matrix[i][j - 1].object =
        Matrix_Values(int(matrix[i][j - 1].object) +
                      ((matrix[i][j - 1].object == Mine) ? 0 : 1));
  if (j < w - 1)
    matrix[i][j + 1].object =
        Matrix_Values(int(matrix[i][j + 1].object) +
                      ((matrix[i][j + 1].object == Mine) ? 0 : 1));
}
