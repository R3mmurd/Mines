/*
  Minesweeper remake.

  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef MATRIX_H
# define MATRIX_H

# include <stdexcept>
# include <random>

enum Matrix_Values
{
  Uncovered,
  Covered,
  Flag,
  Zero,
  One,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Mine,
  Num_Matrix_Values
};

class Matrix
{
  struct Box
  {
    Matrix_Values object;
    Matrix_Values status;
    Box() : object(Zero), status(Covered)
    {
      // Empty
    }
  };

  Box ** matrix;

  size_t w;
  size_t h;

  size_t mines;
  size_t flags;

  size_t uncovered_boxes;

  void inc_mines_around(const size_t &, const size_t &);

public:
    Matrix(const size_t &, const size_t &, const size_t &, std::mt19937 &);

    ~Matrix();

    const size_t & rows() const;

    const size_t & cols() const;

    const Matrix_Values & object_of(const size_t &, const size_t &);

    const Matrix_Values & status_of(const size_t &, const size_t &);

    bool flag(const size_t &, const size_t &);

    void discover(const size_t &, const size_t &);

    void discover_all_mines();

    const size_t & get_flags() const;

    const size_t & get_mines() const;

    bool are_uncovered_all() const;
};

# endif // MATRIX_H
