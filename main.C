/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QApplication>
# include <game_frame.H>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  Game_Frame f;
  f.show();
  return app.exec();
}
