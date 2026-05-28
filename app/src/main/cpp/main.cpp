#include "raymob.h"
#include "Sim/Application.h"

int main() {
  auto *app = Application::get();

  app->run();

  delete app;
}
