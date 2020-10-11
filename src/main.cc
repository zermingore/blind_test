#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>



int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "BlindTest");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);


  sf::Color bgColor;

  float color[3] = { 0.f, 0.f, 0.f };

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

    ImGui::SFML::Update(window, deltaClock.restart());


    // Dear ImGUi
    ImGui::Begin("Sample window");

    // Background color edit
    if (ImGui::ColorEdit3("Background color", color))
    {
      bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
      bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
      bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
    }

    ImGui::End();

    window.clear(bgColor); // fill background with color
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
}
