#ifndef __random__
#define __random__

#include <random>

struct PRNG
{
  std::mt19937_64 engine{std::random_device{}()};
};

class Random
{
public:
  Random() : generator()
  {
  }
  int random_integer(int min = 0, int max = UINT16_MAX)
  {
    using uid = std::uniform_int_distribution<int>;
    thread_local static auto dist = uid{};
    return dist(generator.engine, uid::param_type{min, max});
  }

  double random_normal(double standard_deviation)
  {
    using nd = std::normal_distribution<double>;
    thread_local static auto dist = nd{};
    return dist(generator.engine, nd::param_type{0.0, standard_deviation});
  }

  double random_real(double min, double max = UINT64_MAX)
  {
    using urd = std::uniform_real_distribution<double>;
    thread_local static auto dist = urd{};
    return dist(generator.engine, urd::param_type{min, max});
  }

private:
  PRNG generator;
};

#endif