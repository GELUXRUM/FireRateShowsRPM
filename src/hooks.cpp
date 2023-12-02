#include "hooks.h"
#include "detourxs/detourxs.h"

namespace HookLineAndSinker
{
	typedef __m128(CombatFormulas_GetWeaponDisplayRateOfFireSig)(RE::TESObjectWEAP*, RE::TESObjectWEAP::InstanceData*);
	REL::Relocation<CombatFormulas_GetWeaponDisplayRateOfFireSig> OriginalFunction;
	DetourXS hook;

	__m128 HookedCombatFormulas_GetWeaponDisplayRateOfFire(RE::TESObjectWEAP* a_weapon, RE::TESObjectWEAP::InstanceData* a_instanceData)
	{
		float shotsPerSecond{ a_weapon->GetShotsPerSecond(a_instanceData) * 60.0f };

		return _mm_set_ps1(shotsPerSecond);
	}

	void RegisterHook()
	{
		REL::Relocation<CombatFormulas_GetWeaponDisplayRateOfFireSig> funcLocation{ REL::ID(1403591) };
		if (hook.Create(reinterpret_cast<LPVOID>(funcLocation.address()), &HookedCombatFormulas_GetWeaponDisplayRateOfFire)) {
			OriginalFunction = reinterpret_cast<std::uintptr_t>(hook.GetTrampoline());
		} else {
			logger::warn("Failed to create hook");
		}
	}
}
