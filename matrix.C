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

# include <matrix.H>

Matrix::Matrix(const size_t & _h,
               const size_t & _w,
               const size_t & _mines,
               gsl_rng * r)
  : w(_w), h(_h), mines(_mines), flags(0), uncovered_boxes(0)
{

  matrix = new Box *[h];
  for (size_t i = 0; i < h; ++i)
    matrix[i] = new Box[w];

  for (size_t i = 0; i < mines; ++i)
    {
      while (true)
        {
          const size_t c = gsl_rng_uniform_int(r, w);
          const size_t f = gsl_rng_uniform_int(r, h);
          if (matrix[f][c].object != Bomb)
            {
              matrix[f][c].object = Bomb;
              inc_mines_around(f, c);
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

void Matrix::flag(const size_t & i, const size_t & j)
{
  Matrix_Values & s = matrix[i][j].status;
  if (s == Uncovered)
    return;

  if (s == Flag)
    {
      s = Covered;
      --flags;
    }
  else
    {
      if (flags == mines)
        return;
      s = Flag;
      ++flags;
    }
}

void Matrix::discover(const size_t & i, const size_t & j)
{
  if (i >= h or j >= w)
    return;
  Matrix_Values & s = matrix[i][j].status;
  if (s == Uncovered or s == Flag or matrix[i][j].object == Bomb)
    return;

  ++uncovered_boxes;
  s = Uncovered;
  if (matrix[i][j].object == Zero)
    {
      discover(i - 1, j - 1);
      discover(i - 1, j);
      discover(i - 1, j + 1);
      discover(i, j + 1);
      discover(i + 1, j + 1);
      discover(i + 1, j);
      discover(i + 1, j - 1);
      discover(i, j - 1);
    }
}

void Matrix::discover_all_mines()
{
  for (size_t i = 0; i < h; ++i)
    for (size_t j = 0; j < w; ++j)
      if (matrix[i][j].object == Bomb and matrix[i][j].status != Flag)
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
                        ((matrix[i - 1][j].object == Bomb) ? 0 : 1));
      if (j > 0)
        matrix[i - 1][j - 1].object =
            Matrix_Values(int(matrix[i - 1][j - 1].object) +
                          ((matrix[i - 1][j - 1].object == Bomb) ? 0 : 1));
      if (j < w - 1)
        matrix[i - 1][j + 1].object =
            Matrix_Values(int(matrix[i - 1][j + 1].object) +
                          ((matrix[i - 1][j + 1].object == Bomb) ? 0 : 1));
    }
  if (i < h - 1)
    {
      matrix[i + 1][j].object =
          Matrix_Values(int(matrix[i + 1][j].object) +
                        ((matrix[i + 1][j].object == Bomb) ? 0 : 1));
      if (j > 0)
        matrix[i + 1][j - 1].object =
            Matrix_Values(int(matrix[i + 1][j - 1].object) +
                          ((matrix[i + 1][j - 1].object == Bomb) ? 0 : 1));
      if (j < w - 1)
        matrix[i + 1][j + 1].object =
            Matrix_Values(int(matrix[i + 1][j + 1].object) +
                          ((matrix[i + 1][j + 1].object == Bomb) ? 0 : 1));
    }
  if (j > 0)
    matrix[i][j - 1].object =
        Matrix_Values(int(matrix[i][j - 1].object) +
                      ((matrix[i][j - 1].object == Bomb) ? 0 : 1));
  if (j < w - 1)
    matrix[i][j + 1].object =
        Matrix_Values(int(matrix[i][j + 1].object) +
                      ((matrix[i][j + 1].object == Bomb) ? 0 : 1));
}
