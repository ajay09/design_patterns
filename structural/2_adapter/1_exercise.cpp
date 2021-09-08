struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{
private:
  Square s;
public:
  SquareToRectangleAdapter(const Square& square) : s{square}
  {
  }

  int width() const override { return s.side; }
  int height() const override { return s.side; }

};

