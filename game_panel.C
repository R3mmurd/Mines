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

# include <chrono>

# include <game_panel.H>

QString Game_Panel::images_names [] =
{
  ":/matrix/square",
  ":/matrix/flag",
  ":/matrix/0",
  ":/matrix/1",
  ":/matrix/2",
  ":/matrix/3",
  ":/matrix/4",
  ":/matrix/5",
  ":/matrix/6",
  ":/matrix/7",
  ":/matrix/8",
  ":/matrix/mine"
};

Game_Panel::Game_Panel(const size_t & w,
                       const size_t & h,
                       const size_t & m,
                       QWidget * parent) :
  QWidget(parent), finished(false)
{
  unsigned long seed =
    std::chrono::high_resolution_clock::now().time_since_epoch().count() %
    std::mt19937::max();

  rng.seed(seed);

  matrix = new Matrix(h, w, m, rng);
  resize(matrix->cols() * SCALE, matrix->rows() * SCALE);
}
# include <iostream>
void Game_Panel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  for(size_t i = 0; i < matrix->rows(); ++i)
    for (size_t j = 0; j < matrix->cols(); ++j)
      {
        switch(matrix->status_of(i, j))
          {
          case Covered:
          case Flag:
            painter.drawPixmap(j * SCALE, i * SCALE, SCALE, SCALE,
                               images_names[matrix->status_of(i, j) - 1]);
            break;
          default:
            painter.drawPixmap(j * SCALE, i * SCALE, SCALE, SCALE,
                               images_names[matrix->object_of(i, j) - 1]);
          }
      }
}

void Game_Panel::mousePressEvent(QMouseEvent * evt)
{
  if (finished)
    return;

  QPoint p = evt->pos();

  const size_t j = int (p.x() / SCALE);
  const size_t i = int (p.y() / SCALE);

  if (evt->button() == Qt::RightButton)
    {
      matrix->flag(i, j);
      emit flags_changed();
    }
  else if (evt->button() == Qt::LeftButton)
    {
      if (matrix->object_of(i, j) == Bomb and matrix->status_of(i, j) != Flag)
        {
          matrix->discover_all_mines();
          finished = true;
          emit lost();
        }
      else
        {
          matrix->discover(i, j);
          finished = matrix->are_uncovered_all();
          if (finished)
            emit win();
        }
    }
  repaint();
}

void Game_Panel::reinit(const size_t & w, const size_t & h, const size_t & m)
{
  delete matrix;
  matrix = new Matrix(h, w, m, rng);
  finished = false;
  repaint();
}

Game_Panel::~Game_Panel()
{
  delete matrix;
}

const size_t & Game_Panel::get_matrix_mines() const
{
  return matrix->get_mines();
}

const size_t & Game_Panel::get_matrix_flags() const
{
  return matrix->get_flags();
}
