/**
 * \file
 * \date October 31, 2020
 * \author JP
 * \brief InputsManager class declaration and enum e_input definition
 */

#ifndef INPUTS_MANAGER_HH_
# define INPUTS_MANAGER_HH_

# include <map>
# include <memory>
# include <functional>
# include <queue>

# include <SFML/Window/Event.hpp>

enum class e_input; // definition follows
enum class e_key;   // definition follows



/**
 * \class InputsManager
 * \brief Listen to and process SFML events.
 */
class InputsManager
{
public:
  /**
   * \brief Polls events until the exit event was found
   * \param stop_events_listen stop thread condition
   * \note Loop polling events, populating the events queue
   * \note Initialize the keys handling
   */
  static void listen(const std::atomic_bool& stop_events_listen);

  /**
   * \brief Process events from the events queue
   * \note does not return
   */
  [[ noreturn ]] static void process();


  /**
   * \brief Initialize the mappings keyboard_inputs -> keys
   *   and keys -> high_level_inputs
   */
  static void Initialize();

  /**
   * \brief Push the event matching the given input into the events queue
   * \param key Key used to fetch the Event to push in the queue
   */
  static void pushEvent(const sf::Keyboard::Key& key);

  /**
   * \brief Push the logical key into the events queue
   * \param key Logical event
   * \warning Throws if the key is not mapped
   */
  static void pushKey(const e_key& key);

  /**
   * \brief Retrieve the oldest event from the events queue
   * \return The poped event
   * \note Blocks until an event is found in the queue
   */
  static e_input popEvent();

  /**
   * \brief Associates a callback to an event identified by key.
   * \param input event to link with the callback.
   * \param cb callback to associate to the event.
   */
  void registerEvent(const e_input input, const std::function<void()> cb) {
    _callbacks[input] = cb;
  }


private:
  /// Callbacks / events association
  std::map<e_input, std::function<void()>> _callbacks;

  /// Hardware / logical keys mapping
  static std::multimap<const sf::Keyboard::Key, const e_key> _keys_mapping;

  /// Events mapping
  static std::map<const e_key, const e_input> _events_mapping;

  /// Current inputs (high level keys)
  static std::queue<e_input> _active_inputs; // NOT thread-safe

  ///< Lock between frames
  static std::mutex _lock;

  ///< New frame notification
  static std::condition_variable _cv_new_frame;
};



/**
 * \enum e_input
 * \brief Logical input names
 * \warning New inputs should be added at the end of the list
 *   (as tests may rely on the values)
 */
enum class e_input
{
  // Motion keys
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,

  // Action keys
  SELECTION,

  // Exit requests
  EXIT,

  NB_KEYS
};



/**
 * \enum e_key
 * \brief Keys indexes allowing key repeating
 * \warning New inputs should be added at the end of the list
 *   (as tests may rely on the values)
 */
enum class e_key
{
  UP = 0,
  DOWN,
  LEFT,
  RIGHT,

  // action keys
  SELECTION,

  // exit requests
  EXIT,

  NB_KEYS
};


#endif /* !INPUTS_MANAGER_HH_ */
