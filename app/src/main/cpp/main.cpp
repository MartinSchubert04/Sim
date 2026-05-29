#include "raymob.h"
#include "Sim/Application.h"

int main() {
  auto *app = createApplication();

  app->run();

  delete app;
}
