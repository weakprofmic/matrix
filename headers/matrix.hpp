#include <cinttypes>

class Matrix {
  public:

  /* Constructors and Destructor */
    Matrix();
    Matrix(size_t);
    Matrix(size_t, size_t);
    ~Matrix();

  /* Getters and Setters*/
    size_t get_rows() const
    {
      return rows;
    }
    size_t get_cols() const
    {
      return cols;
    }

    
    void set_rows(size_t height)
    {
      rows = height;
    }
    void set_cols(size_t width)
    {
      cols = width;
    }
    
  /* Operations */
  private:
    uint8_t rows;
    uint8_t cols;

};
