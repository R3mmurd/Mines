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

# ifndef GAME_FRAME_H
# define GAME_FRAME_H

# include <QtGui>
# include <game_panel.H>
# include <face.H>

class Game_Frame : public QWidget
{
  Q_OBJECT

  Game_Panel panel;

  Face face;

  QLabel lbl_flags;

  size_t width;
  size_t height;
  size_t num_mines;

  void init_menu();

  void init_gui();

public:
  explicit Game_Frame(QWidget * parent = 0);

public slots:
  void reinit_game();

  void change_mines_info();

};

#endif // GAME_FRAME_H
