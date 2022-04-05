#pragma once

#include <cstdio>
#include <array>

class Error {
public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        kNoEnoughMemory,
        kIndexOutOfRange,
        kHostControllerNotHalted,
        kInvalidSlotID,
        kPortNotConnected,
        kInvalidEndpointNumber,
        kTransferRingNotSet,
        kAlreadyAllocated,
        kNotImplemented,
        kInvalidDescriptor,
        kBufferTooSmall,
        kUnknownDevice,
        kNoCorrespondingSetupStage,
        kTransferFailed,
        kInvalidPhase,
        kUnknownXHCISpeedID,
        kNoWaiter,
        kNoPCIMSI,
        kLastOfCode,
    };

    Error(Code code, const char* file, int line) : m_code{code}, m_line{line}, m_file{file} {}

    Code Cause() const {
        return this->m_code;
    }

    operator bool() const {
        return this->m_code != kSuccess;
    }

    const char* Name() const {
        return CODE_NAMES[static_cast<int>(this->m_code)];
    }

    const char* File() const {
        return this->m_file;
    }

    int Line() const {
        return this->m_line;
    }

private:
    static constexpr std::array CODE_NAMES{
        "kSuccess",
        "kFull",
        "kEmpty",
        "kNoEnoughMemory",
        "kIndexOutOfRange",
        "kHostControllerNotHalted",
        "kInvalidSlotID",
        "kPortNotConnected",
        "kInvalidEndpointNumber",
        "kTransferRingNotSet",
        "kAlreadyAllocated",
        "kNotImplemented",
        "kInvalidDescriptor",
        "kBufferTooSmall",
        "kUnknownDevice",
        "kNoCorrespondingSetupStage",
        "kTransferFailed",
        "kInvalidPhase",
        "kUnknownXHCISpeedID",
        "kNoWaiter",
        "kNoPCIMSI"
    };
    static_assert(Error::Code::kLastOfCode == CODE_NAMES.size());

    Code m_code;
    int m_line;
    const char* m_file;
};

#define MAKE_ERROR(code) Error((code), __FILE__, __LINE__)

template <class T>
struct WithError {
    T value;
    Error error;
};