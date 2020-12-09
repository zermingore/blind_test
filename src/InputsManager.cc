/**
 * \file
 * \date October 31, 2020
 * \author JP
 * \brief InputsManager class definition
 */

#include <future>

#include <InputsManager.hh>



// Static members definition
std::multimap<const sf::Keyboard::Key, const e_key> InputsManager::_keys_mapping;
std::map<const e_key, const e_input> InputsManager::_events_mapping;
std::queue<e_input> InputsManager::_active_inputs; /// \warning NOT thread-safe
std::mutex InputsManager::_lock;
std::condition_variable InputsManager::_cv_new_frame;


void InputsManager::listen(const std::atomic_bool& stop_events_listen)
{
  // Debug::setThisThreadName("InputsListener");
  InputsManager::Initialize();

  // Launch the events processor in its own thread
  auto inputs = std::async(std::launch::async, InputsManager::process);

  // Listen for events until the window close event is found
  while (!stop_events_listen)
  {
    // Listen to input, convert them into events and push them in the fifo
    sf::Event event{};
    // while (graphics::GraphicsEngine::pollEvent(event)) /// \todo
    {
      // Close window: exit request
      if (event.type == sf::Event::Closed)
      {
        return;
      }

      // Skipping any non-relevant event
      if (event.type != sf::Event::KeyPressed)
      {
        continue;
      }

      // Push e_key matching the sf::Event
      InputsManager::pushEvent(event.key.code);
    }
  }
}



void InputsManager::process()
{
  // Debug::setThisThreadName("EventsProcessor");

  for (;;)
  {
    // Wait to access an event
    // auto input(InputsManager::popEvent());

    // Waiting for the new frame, signaled by the Graphics Engine
    std::unique_lock<std::mutex> lock(_lock);
    _cv_new_frame.wait(lock);

    // process events queue
    // if (!processInput(input))
    {
      // PRINTF("Event not processed");
    }
  }
}



void InputsManager::Initialize()
{
  // keyboard: user; e_key: binary
  // _keys_mapping: keyboard -> e_key ('z' and '8' can be used for LEFT key)
  // e_key -> keyboard (allow duplicated keys)

  _keys_mapping.insert({sf::Keyboard::Left,   e_key::LEFT});
  _keys_mapping.insert({sf::Keyboard::Right,  e_key::RIGHT});
  _keys_mapping.insert({sf::Keyboard::Up,     e_key::UP});
  _keys_mapping.insert({sf::Keyboard::Down,   e_key::DOWN});

  _keys_mapping.insert({sf::Keyboard::Space,  e_key::SELECTION});
  _keys_mapping.insert({sf::Keyboard::Escape, e_key::EXIT});


  // This event mapping is populated here but will then be read only
  // These are the mapping key (dissociated from the keyboard) -> event
  _events_mapping.insert({e_key::LEFT,         e_input::MOVE_LEFT   });
  _events_mapping.insert({e_key::RIGHT,        e_input::MOVE_RIGHT  });
  _events_mapping.insert({e_key::UP,           e_input::MOVE_UP     });
  _events_mapping.insert({e_key::DOWN,         e_input::MOVE_DOWN   });
  _events_mapping.insert({e_key::SELECTION,    e_input::SELECTION   });
  _events_mapping.insert({e_key::EXIT,         e_input::EXIT        });
}



void InputsManager::pushEvent(const sf::Keyboard::Key& key)
{
  // getting the logical key
  auto logical_key_it(_keys_mapping.find(key));
  if (logical_key_it == _keys_mapping.end())
  {
    return;
  }

  _active_inputs.push(_events_mapping[logical_key_it->second]);
}



void InputsManager::pushKey(const e_key& key)
{
  _active_inputs.push(_events_mapping.at(key));
}



e_input InputsManager::popEvent()
{
  while (_active_inputs.empty())
  {
  }

  const auto elt{_active_inputs.front()};
  _active_inputs.pop();
  return elt;
}
