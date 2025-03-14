#pragma once
#include <cstdint>

namespace mem
{
	template <typename Return, typename ... Args>
	constexpr Return Call(void* _this, const std::uintptr_t index, Args ... args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(_this))[index](_this, args...);
	}

	constexpr void* Get(void* _this, const std::uintptr_t index) noexcept
	{
		return (*static_cast<void***>(_this))[index];
	}
}

