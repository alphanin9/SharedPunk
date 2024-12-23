#pragma once
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include <RED4ext/Scripting/Natives/Generated/game/ui/CharacterCustomizationSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/CharacterCustomizationState.hpp>

#include <Impl/Detail/Hashes.hpp>
#include <Shared/Util/Core.hpp>

namespace shared::raw::CharacterCustomizationSystem
{
	using Lock = util::OffsetPtr<0x70, Red::SharedSpinLock>;
	using State = util::OffsetPtr<0x78, Red::Handle<Red::game::ui::CharacterCustomizationState>>;

	// RDX is probably CC state handle but it doesn't matter since we grab it anyway
	constexpr auto OnNewGame =
        util::RawFunc<detail::Hashes::CharacterCustomizationSystem_OnNewGame,
                      void (*)(Red::game::ui::CharacterCustomizationSystem* aThis, void* aRdx)>();
    }