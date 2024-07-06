#include <cinttypes>
#include <exceptions.hpp>
#include <vector>

class Matrix
{
public:
  /* Constructors and Destructor */
  explicit Matrix();
  explicit Matrix(size_t);
  explicit Matrix(size_t, size_t);
  explicit Matrix(size_t, size_t, double *const);
  explicit Matrix(size_t, size_t, std::initializer_list<double>);
  explicit Matrix(size_t, size_t, std::vector<double>);
  Matrix(Matrix const &other);
  Matrix(Matrix &&other);
  ~Matrix();

  // assignment
  Matrix &operator=(const Matrix &);
  Matrix &operator=(Matrix &&other);

  void swap(Matrix &) noexcept;
  friend void swap(Matrix &, Matrix &);

  /* Getters and Setters*/
  size_t rows() const
  {
    return rows_;
  }
  size_t cols() const
  {
    return cols_;
  }

  double const *data() const
  {
    return data_;
  }

  int id() const
  {
    return id_;
  }

  void set_rows(size_t height)
  {
    throw new NotImplementedException(__FUNCTION__, "Stub message");
    // rows_ = height;
  }
  void set_cols(size_t width)
  {
    throw new NotImplementedException(__FUNCTION__, "Stub message");
    // cols_ = width;
  }

  /** IO operations */
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

  friend std::istream &operator>>(std::istream &is, Matrix &matrix);

  /* Operations */
private:
  uint8_t rows_;
  uint8_t cols_;
  static int id_counter_;
  int const id_;

  double *data_;
};
