#pragma once
#include <string>
#include <spdlog/spdlog.h>

namespace easy2d
{
#define INFO(...) spdlog::info(__VA_ARGS__)
#define CRIT(...) spdlog::critical(__VA_ARGS__)

#ifdef NDEBUG
#define LOG(...) spdlog::log(__VA_ARGS__)
#define DEBUG(...) spdlog::debug(__VA_ARGS__)
#define ERROR(...) spdlog::error(__VA_ARGS__)
#else
#define LOG(...)
#define DEBUG(...)
#define ERROR(...)
#endif
} // -- easy2d
