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
# ifndef GAME_PANEL_H
# define GAME_PANEL_H

# include <QWidget>
# include <QPainter>
# include <matrix.H>
# include <QMouseEvent>

# define SCALE 20

class Game_Panel : public QWidget
{
  Q_OBJECT

  Matrix * matrix;

  std::mt19937 rng;

  bool finished;

  static QString images_names[Num_Matrix_Values - 1];

public:
  explicit Game_Panel(const size_t &,
                      const size_t &,
                      const size_t &,
                      QWidget *parent = 0);

  ~Game_Panel();

  const size_t & get_matrix_mines() const;

  const size_t & get_matrix_flags() const;

  void reinit(const size_t &, const size_t &, const size_t &);

  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);

signals:
  void lost();

  void win();

  void flags_changed();
};

# endif // GAME_PANEL_H
