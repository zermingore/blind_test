/**
 * \file
 * \date November 02, 2020
 * \author JP
 * \namespace graphics
 * \brief GraphicsEngine class declaration
 */

#ifndef GRAPHICS_ENGINE_HH_
# define GRAPHICS_ENGINE_HH_

# include <memory>
# include <mutex>

# include <SFML/Graphics/RenderWindow.hpp>
# include <SFML/Window/Event.hpp>



namespace graphics {



/**
 * \class GraphicsEngine
 * \brief Manages the display of the scene
 */
class GraphicsEngine
{
public:
  /**
   * \brief Initializes the SFML window and Dear ImGUi
   * \note Looping until exit request
   */
  static void run();

  /**
   * \brief Draws the whole scene. Updates the window
   * \note Drawing while the window is not closed
   */
  static void drawScene();

  /**
   * \brief Close the window on request; exiting the main loop
   * \note does not return
   */
  [[ noreturn ]] static void exitRequest();

  /**
   * \brief Return the next event on the window if any
   */
  static auto pollEvent(sf::Event& event) {
    return _window->pollEvent(event);
  }


private:
  /**
   * \brief Clear the window with the background color
   */
  void drawBackground();


  static std::unique_ptr<sf::RenderWindow> _window; ///< graphics window
  static bool _exit;           ///< true: got request to quit
};


} // namespace graphics

#endif /* !GRAPHICS_ENGINE_HH_ */
