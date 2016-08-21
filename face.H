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

# ifndef FACE_H
# define FACE_H

# include <QWidget>
# include <QPainter>

# define SIZE 40

enum class Status
{
  Happy,
  Sad,
  Glasses,
  Num_Status
};

class Face : public QWidget
{
  Q_OBJECT

  static QString face_images[int(Status::Num_Status)];

  void normal();

  Status status;

public:
  explicit Face(QWidget *parent = 0);

  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);

public slots:
  void sad();

  void happy();

signals:
  void face_clicked();
};

# endif // FACE_H
