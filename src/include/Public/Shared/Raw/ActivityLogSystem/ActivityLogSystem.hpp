#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw::ActivityLogSystem
{
	using Lock = util::OffsetPtr<0x58, Red::SharedSpinLock>;
	using Logs = util::OffsetPtr<0x60, Red::DynArray<Red::CString>>;
}