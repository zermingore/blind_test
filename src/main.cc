#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>



int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "BlindTest");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);

  sf::CircleShape focusPoint;
  focusPoint.setRadius(30.f);
  focusPoint.setFillColor({255, 0, 0});
  focusPoint.setPosition(30.f, 30.f);


  sf::Color bgColor = { 0, 255, 0 };
  sf::Color focusPointColor = { 255, 0, 0 };

  float color[3] = { 0.f, 1.f, 0.f };
  float colorPoint[3] = { 1.f, 0.f, 0.f };

  sf::Clock deltaClock;
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    focusPoint.setFillColor(focusPointColor);
    focusPoint.setPosition((static_cast<int> (focusPoint.getPosition().y) + 1) % window.getSize().x,
                           (static_cast<int> (focusPoint.getPosition().y) + 1) % window.getSize().y);

    ImGui::SFML::Update(window, deltaClock.restart());


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

    ImGui::End();

    window.clear(bgColor); // fill background with color

    window.draw(focusPoint);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
