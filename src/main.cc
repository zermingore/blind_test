#include <future>

#include <tools/Debug.hh>
#include <InputsManager.hh>
#include <GraphicsEngine.hh>


int main()
{
  Debug::init();

  std::atomic_bool stop_events_listener{false};
  auto inputs = std::async(
    std::launch::async,
    InputsManager::listen,
    std::ref(stop_events_listener)
  );

  graphics::GraphicsEngine::run();
}
