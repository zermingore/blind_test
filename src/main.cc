#include <future>

#include <tools/Debug.hh>
#include <InputsManager.hh>
#include <GraphicsEngine.hh>
#include <tools/OptionsParser.hh>



int main(int ac, const char **av)
{
  Debug::init();

  // Options parsing
  OptionsParser opt(ac, av);
  try
  {
    opt.parse();
  }
  catch (const ArgumentsHelpVersionException&)
  {
    return EXIT_SUCCESS;
  }
  catch (const ArgumentsException& e)
  {
    ERROR("Invalid arguments:\n", e.what());
    return EXIT_FAILURE;
  }

  std::atomic_bool stop_events_listener{false};
  auto inputs = std::async(
    std::launch::async,
    InputsManager::listen,
    std::ref(stop_events_listener)
  );

  graphics::GraphicsEngine::run();
}
