#pragma once

#include <array>

class Error {
public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        kLastOfCode,
    };

    Error(Code code) : m_code{code} {}

    operator bool() const {
        return this->m_code != kSuccess;
    }

    const char* Name() const {
        return CODE_NAMES[static_cast<int>(this->m_code)];
    }

private:
    static constexpr std::array<const char*, 3> CODE_NAMES = {
        "kSuccess",
        "kFull",
        "kEmpty",
    };

    Code m_code;
};