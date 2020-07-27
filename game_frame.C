/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <game_frame.H>

Game_Frame::Game_Frame(QWidget *parent) :
    QWidget(parent), panel(8, 8, 10)/*panel(30, 16, 99)*/, width(30), height(16), num_mines(99)
{
  init_gui();
  change_mines_info();
  setFixedSize(625, 420);
  setWindowTitle("Buscaminas");
  setWindowIcon(QIcon(":/game/mines"));
  connect(&panel, SIGNAL(win()), &face, SLOT(happy()));
  connect(&panel, SIGNAL(lost()), &face, SLOT(sad()));
  connect(&face, SIGNAL(face_clicked()), this, SLOT(reinit_game()));
  connect(&panel, SIGNAL(flags_changed()), this, SLOT(change_mines_info()));
}

void Game_Frame::init_gui()
{
  QVBoxLayout * vlayout = new QVBoxLayout;
  QHBoxLayout * hlayout1 = new QHBoxLayout;
  hlayout1->addWidget(&face);
  vlayout->addLayout(hlayout1);
  QHBoxLayout * hlayout2 = new QHBoxLayout;
  hlayout2->addWidget(&panel);
  vlayout->addLayout(hlayout2, 1);
  lbl_flags.setFixedSize(100, 20);
  QHBoxLayout * hlayout3 = new QHBoxLayout;
  hlayout3->addWidget(&lbl_flags, 1);
  vlayout->addLayout(hlayout3, Qt::AlignCenter);
  setLayout(vlayout);
}

void Game_Frame::reinit_game()
{
  panel.reinit(width, height, num_mines);
  change_mines_info();
}

void Game_Frame::change_mines_info()
{
  lbl_flags.setText(QString("Minas: " +
                            QString::number(panel.get_matrix_flags())) +
                    QString(" / ") +
                    QString::number(panel.get_matrix_mines()));
}
