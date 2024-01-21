#pragma once
#include "W4Framework.h"

struct FSM{
    enum class Events{
        Initialize,
        Win,
        Fail,
        Next
    };
    struct States{
        struct Preloading       : w4::fsm::FuncState<Events>{};
        struct Game             : w4::fsm::FuncState<Events>{};
        struct WinMenu          : w4::fsm::FuncState<Events>{};
        struct FailMenu         : w4::fsm::FuncState<Events>{};
    };
    using Type = w4::fsm::FSM<
            w4::fsm::Transition<Events::Initialize, States::Preloading, States::Game>,
            w4::fsm::Transition<Events::Win,        States::Game,           States::WinMenu>,
            w4::fsm::Transition<Events::Fail,       States::Game,           States::FailMenu>,
            w4::fsm::Transition<Events::Next,       States::WinMenu,        States::Game>,
            w4::fsm::Transition<Events::Next,       States::FailMenu,       States::Game>
    >;
};