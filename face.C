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

# include <face.H>

QString Face::face_images [] =
{
  ":/images/face/happy",
  ":/images/face/sad",
  ":/images/face/glasses"
};

Face::Face(QWidget *parent) :
    QWidget(parent)
{
  normal();
  setFixedSize(SIZE, SIZE);
}

void Face::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawPixmap(0, 0, SIZE, SIZE, face_images[int(status)]);
}

void Face::mousePressEvent(QMouseEvent *)
{
  normal();
  emit face_clicked();
}

void Face::sad()
{
  status = Status::Sad;
  repaint();
}

void Face::happy()
{
  status = Status::Happy;
  repaint();
}

void Face::normal()
{
  status = Status::Glasses;
  repaint();
}
