/**
 * \file
 * \date November 02, 2020
 * \author JP
 * \brief GraphicsEngine class definition
 */

#include <GraphicsEngine.hh>

#include <cmath>
#include <imgui.hh>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>



namespace graphics {

// Static Variables definition
std::unique_ptr<sf::RenderWindow> GraphicsEngine::_window;
bool GraphicsEngine::_exit;



void GraphicsEngine::run()
{
  sf::VideoMode video_mode(800, 600, 32);
  if (!video_mode.isValid())
  {
    // ERROR("Unsupported Video Mode, falling back");
    video_mode = sf::VideoMode::getDesktopMode(); // falling back mode
    if (!video_mode.isValid()) {
      std::exit(-1);
    }
  }

  _window = std::make_unique<sf::RenderWindow> (video_mode, "Blind Test");
  _window->setFramerateLimit(60);
  _window->setKeyRepeatEnabled(false);
  _window->setVerticalSyncEnabled(true);
  ImGui::SFML::Init(*_window);
  _window->setActive();

  _exit = false;
  while (_window->isOpen() && !_exit)
  {
    auto graphics_start(std::chrono::steady_clock::now());
    //drawBackground();
    drawScene();

    // update the window
    _window->display();

    // EventsProcessor::notifyFrame();
  }

  // WARNING("Quitting Blind Test");
}



void GraphicsEngine::drawScene()
{
  sf::CircleShape focusPoint;
  focusPoint.setRadius(30.f);
  focusPoint.setFillColor({255, 0, 0});
  focusPoint.setPosition(30.f, 30.f);


  sf::Color bgColor = { 0, 255, 0 };
  sf::Color focusPointColor = { 255, 0, 0 };

  float color[3] = { 0.f, 1.f, 0.f };
  float colorPoint[3] = { 1.f, 0.f, 0.f };
  float pointSize = 30.f;
  float pointSpeed = 1.f;

  sf::Clock deltaClock;
  while (_window->isOpen())
  {
    sf::Event event;
    while (_window->pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed)
      {
        _window->close();
        exitRequest();
      }

      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          _window->close();
          exitRequest();
        }
      }
    }

    focusPoint.setFillColor(focusPointColor);
    focusPoint.setPosition(
      static_cast<float> (std::fmod(
        focusPoint.getPosition().y + pointSpeed, _window->getSize().x)),
      static_cast<float> (std::fmod(
        focusPoint.getPosition().y + pointSpeed, _window->getSize().y)));
    focusPoint.setRadius(pointSize);


    ImGui::SFML::Update(*_window, deltaClock.restart());


    // Dear ImGUi
    ImGui::Begin("Settings");

    // Background color edit
    if (ImGui::ColorEdit3("Background color", color))
    {
      bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
      bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
      bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
    }

    if (ImGui::ColorEdit3("Point color", colorPoint))
    {
      focusPointColor.r = static_cast<sf::Uint8>(colorPoint[0] * 255.f);
      focusPointColor.g = static_cast<sf::Uint8>(colorPoint[1] * 255.f);
      focusPointColor.b = static_cast<sf::Uint8>(colorPoint[2] * 255.f);
    }

    ImGui::SliderFloat("Point size", &pointSize, 1.f, 30.f);
    ImGui::SliderFloat("Point speed", &pointSpeed, 1.f, 10.f);

    ImGui::End();

    _window->clear(bgColor); // fill background with color

    _window->draw(focusPoint);
    ImGui::SFML::Render(*_window);
    _window->display();
  }

  ImGui::SFML::Shutdown();
}



void GraphicsEngine::drawBackground()
{
  _window->clear();
}



void GraphicsEngine::exitRequest()
{
  _exit = true; // Terminate the 'DrawScene' thread

  // NOT closing the window in order to prevent the event thread from crashing

  // Terminate the main thread; Nothing will try to catch it
  throw std::runtime_error("Exiting Blind Test...");
}



} // namespace graphics
