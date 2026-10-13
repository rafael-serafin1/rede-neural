#pragma once

enum class logic_gates: unsigned char {
    AND  = 0,
    OR   = 1,
    XOR  = 2,
    NAND = 3,
    NOR  = 4,
    NXOR = 5
};

const char* convert_logic_gate(logic_gates gate) {
    char* resultado;

    switch (gate) {
        case logic_gates::AND:
            resultado = "AND";
        case logic_gates::NAND:
            resultado = "NAND";
        case logic_gates::OR:
            resultado = "OR";
        case logic_gates::NOR:
            resultado = "NOR";
        case logic_gates::XOR:
            resultado = "XOR";
        case logic_gates::NXOR:
            resultado = "NXOR";
    }

    return (const char*) resultado;
}

class logic {
public:
    static bool And(bool first, bool second) {
        if (first and second)
            return true;

        return false;
    }

    static bool Or(bool first, bool second) {
        if (!first and !second) 
            return false;
        return true;
    }

    static bool Xor(bool first, bool second) {
        if (first == second)
            return false;
        return true;
    }

    static bool Not(bool first) {
        return !first;
    }

    static bool Nand(bool first, bool second) {
        return !(first and second);
    }

    static bool Nor(bool first, bool second) {
        return !(first or second);
    }

    static bool Nxor(bool first, bool second) {
        return !(first != second);
    }
};