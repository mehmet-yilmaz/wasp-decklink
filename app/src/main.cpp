#include <app.module.hpp>

int main(int argc, char *argv[])
{

    Wasp::Bootstrap::App->init();
    Wasp::Bootstrap::App->run();
    return 0;
};