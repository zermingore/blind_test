/**
 * \file
 * \date December 3, 2020
 * \author JP
 * \brief Random class definition
 */

#include <tools/Random.hh>
#include <tools/Debug.hh>


long unsigned int Random::_randomSeed;
std::unique_ptr<std::mt19937> Random::_generator;



void Random::init()
{
/// \todo Cross-platform warning ignore
# pragma GCC diagnostic push // random_device and mt19937 are 5k on my machine
# pragma GCC diagnostic ignored "-Wlarger-than="
  std::random_device rd;
  if (_randomSeed == 0u)
  {
    _randomSeed = rd();
  }
  NOTICE("Using random seed:", _randomSeed);
  _generator = std::make_unique<std::mt19937> (_randomSeed);
# pragma GCC diagnostic pop
}



int Random::randInt(int min, int max)
{
  std::uniform_int_distribution<> rand(min, max);
  return rand(*_generator);
}
