#include <framework.h>

namespace GameHook
{
    // Multi Skill Equip
    const SHORT bytePattern[] = { 0x48, 0x8B, 0x51, 0x08, 0x33, 0xC0, 0x48, 0x85, 0xD2, 0x74, 0x09, 0x8B, 0x4A, 0x34 };

    const SHORT patternLength = 14;

    const SHORT patternOffset = 11;

    // Name of the module in which to scan for byte patterns.
    const WCHAR moduleName[] = L"ShadowOfWar.exe";

    AOBScanner pScanner;

    // Injections and scanned addresses.
    extern "C"
    {
        UINT_PTR itemChallengeJmpAddr = 0;
        EXPORT BYTE* itemChallengeAddress = nullptr;
        INSTRUCTIONSET ItemChallengeInjectCode()
        {
            __asm__
            (
                "mov %ecx, 0x30(%rdx)\n\t"
                "cmp 0x30(%rdx), %ecx\n\t"
                "jmp *itemChallengeJmpAddr"
            );
        }
    }

    bool IsSkillHookEnabled = true;
    bool CreateItemChallengeHook()
    {
        itemChallengeAddress = pScanner.PerformModuleScan(bytePattern, patternLength, patternOffset, moduleName);
        itemChallengeJmpAddr = (UINT_PTR)(itemChallengeAddress + 6);
        return itemChallengeAddress != nullptr;
    }

    // Hook startup.
    void CreateGameHooks()
    {
        CreateItemChallengeHook();
        MH_CreateHook(itemChallengeAddress, (LPVOID)ItemChallengeInjectCode, nullptr);
        MH_EnableHook(MH_ALL_HOOKS);
    }
}