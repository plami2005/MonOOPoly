#pragma once
#include "Color.h"

inline const char* getColorAnsiCode(Color color) {
    switch (color) {
    case Color::Brown: return "\033[38;5;94m";
    case Color::LightBlue: return "\033[38;5;81m";
    case Color::Pink: return "\033[38;5;206m";
    case Color::Orange: return "\033[38;5;214m";
    case Color::Red: return "\033[38;5;196m";
    case Color::Yellow: return "\033[38;5;226m";
    case Color::Green: return "\033[38;5;46m";
    case Color::DarkBlue: return "\033[38;5;21m";
    case Color::Railroad: return "\033[38;5;250m";
    case Color::Utility: return "\033[38;5;250m";
    case Color::Tax: return "\033[38;5;244m";
    default: return "\033[0m";
    }
}
