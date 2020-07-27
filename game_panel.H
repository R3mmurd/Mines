/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef GAME_PANEL_H
# define GAME_PANEL_H

# include <QWidget>
# include <QPainter>
# include <matrix.H>
# include <QMouseEvent>
# include <QSound>

# define SCALE 20

class Game_Panel : public QWidget
{
  Q_OBJECT

  Matrix * matrix;

  std::mt19937 rng;

  bool finished;

  QSound * win_sound;
  QSound * lost_sound;
  QSound * explosion_sound;
  QSound * click_sound;
  QSound * flag_sound;

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
