#ifndef HOOKS
    #define HOOKS

    namespace GameHook
    {
        extern "C"
        {
            INSTRUCTIONSET ItemChallengeInjectCode();
        }

        bool CreateItemChallengeHook();
        void CreateGameHooks();
    }
#endif