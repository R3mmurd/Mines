/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <chrono>

# include <game_panel.H>

QString Game_Panel::images_names [] =
{
  ":/images/matrix/square",
  ":/images/matrix/flag",
  ":/images/matrix/0",
  ":/images/matrix/1",
  ":/images/matrix/2",
  ":/images/matrix/3",
  ":/images/matrix/4",
  ":/images/matrix/5",
  ":/images/matrix/6",
  ":/images/matrix/7",
  ":/images/matrix/8",
  ":/images/matrix/mine"
};

Game_Panel::Game_Panel(const size_t & w,
                       const size_t & h,
                       const size_t & m,
                       QWidget * parent) :
  QWidget(parent), finished(false)
{
  unsigned long seed =
    std::chrono::high_resolution_clock::now().time_since_epoch().count() %
    std::mt19937::max();

  rng.seed(seed);

  matrix = new Matrix(h, w, m, rng);
  resize(matrix->cols() * SCALE, matrix->rows() * SCALE);

  win_sound = new QSound(":/audio/win_sound", this);
  lost_sound = new QSound(":/audio/lost_sound", this);
  explosion_sound = new QSound(":/audio/explosion_sound", this);
  click_sound = new QSound(":/audio/click_sound", this);
  flag_sound = new QSound(":/audio/flag_sound", this);
}

void Game_Panel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  for(size_t i = 0; i < matrix->rows(); ++i)
    for (size_t j = 0; j < matrix->cols(); ++j)
      {
        switch(matrix->status_of(i, j))
          {
          case Covered:
          case Flag:
            painter.drawPixmap(j * SCALE, i * SCALE, SCALE, SCALE,
                               images_names[matrix->status_of(i, j) - 1]);
            break;
          default:
            painter.drawPixmap(j * SCALE, i * SCALE, SCALE, SCALE,
                               images_names[matrix->object_of(i, j) - 1]);
          }
      }
}

void Game_Panel::mousePressEvent(QMouseEvent * evt)
{
  if (finished)
    return;

  QPoint p = evt->pos();

  const size_t j = int (p.x() / SCALE);
  const size_t i = int (p.y() / SCALE);

  if (evt->button() == Qt::RightButton)
    {
      if (matrix->flag(i, j))
        {
          flag_sound->play();
          emit flags_changed();
        }
    }
  else if (evt->button() == Qt::LeftButton)
    {
      if (matrix->object_of(i, j) == Mine and matrix->status_of(i, j) != Flag)
        {
          matrix->discover_all_mines();
          finished = true;
          emit lost();
          explosion_sound->play();
          lost_sound->play();
        }
      else
        {
          click_sound->play();
          matrix->discover(i, j);
          finished = matrix->are_uncovered_all();
          if (finished)
            {
              win_sound->play();
              emit win();
            }
        }
    }
  repaint();
}

void Game_Panel::reinit(const size_t & w, const size_t & h, const size_t & m)
{
  delete matrix;
  matrix = new Matrix(h, w, m, rng);
  finished = false;
  repaint();
}

Game_Panel::~Game_Panel()
{
  delete matrix;
}

const size_t & Game_Panel::get_matrix_mines() const
{
  return matrix->get_mines();
}

const size_t & Game_Panel::get_matrix_flags() const
{
  return matrix->get_flags();
}
