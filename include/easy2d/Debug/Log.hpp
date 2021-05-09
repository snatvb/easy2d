#pragma once
#include <string>
#include <spdlog/spdlog.h>

namespace easy2d
{
#define INFO(...) spdlog::info(__VA_ARGS__)
#define CRIT(...) spdlog::critical(__VA_ARGS__)

#ifdef NDEBUG
#define DEBUG(...)
#define ERR(...)
#define WARN(...)
#else
#define DEBUG(...) spdlog::info(__VA_ARGS__)
#define ERR(...) spdlog::error(__VA_ARGS__)
#define WARN(...) spdlog::warn(__VA_ARGS__)
#endif
} // -- easy2d
