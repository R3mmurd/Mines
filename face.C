/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
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
