/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef GAME_FRAME_H
# define GAME_FRAME_H

# include <QLabel>
# include <QIcon>
# include <QVBoxLayout>
# include <QHBoxLayout>
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
