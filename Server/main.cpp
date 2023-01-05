#include "Application.h"

int main(int argc, char *argv[]) {
    Application::getInstance().run(argc, argv);
    return 0;
}