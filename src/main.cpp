#include <exception>
#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#include "app/AppContainer.h"

namespace {

// Включает UTF-8 для ввода и вывода консоли Windows.
// На других системах ничего не делает.
void setupConsoleUtf8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

}  // namespace

int main() {
    setupConsoleUtf8();

    try {
        AppContainer container;
        container.run();
    } catch (const std::exception& error) {
        std::cerr << "Критическая ошибка: " << error.what() << "\n";
        return 1;
    }

    return 0;
}