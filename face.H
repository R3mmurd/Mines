/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
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
