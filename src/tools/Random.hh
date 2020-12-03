/**
 * \file
 * \date December 3, 2020
 * \author JP
 * \brief Random generation class declaration
 */

#ifndef RANDOM_HH_
# define RANDOM_HH_

# include <random>
# include <memory>


/**
 * \class Random
 * \brief Random generator class
 * \note Static class
 */
class Random
{
public:
  /**
   * \brief Random generator initialization
   */
  static void init();

  static auto seed() { return _randomSeed; }

  /**
   * \brief Random int generation
   * \param min Inclusive minimal value
   * \param max Inclusive maximal value
   * \return Value between min and max
   */
  static int randInt(int min, int max);

  /**
   * \brief Templated random value generation
   * \param min Inclusive minimal value
   * \param max Inclusive maximal value
   * \return Value between min and max
   */
  template<typename T>
  static T randVal(T min, T max)
  {
    std::uniform_int_distribution<T> rand(min, max);
    return static_cast<T> (rand(*_generator));
  }

  /**
   * \brief Random bool generation
   * \return Random boolean
   */
  static bool randBool();


private:
  static long unsigned int _randomSeed; ///< Random generator seed
  static std::unique_ptr<std::mt19937> _generator;
};


#endif /* !RANDOM_HH_ */
