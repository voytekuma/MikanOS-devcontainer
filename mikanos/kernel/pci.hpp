/**
 * @file pci.hpp
 * 
 * PCIバス制御プログラム
 */

#pragma once

#include <cstdint>
#include <array>

#include "error.hpp"

namespace pci {

/** CONFIG_ADDRESS レジスタの IO ポートアドレス */
const uint16_t kConfigAddress = 0x0cf8;
/** CONFIG_DATA レジスタの IO ポートアドレス */
const uint16_t kConfigData = 0x0cfc;

/** PCI デバイスのクラスコード */
struct ClassCode {
    uint8_t base, sub, interface;

    /** ベースクラスが等しい場合に真を返す */
    bool Match(uint8_t b) { return b == base; }
    /** ベースクラスとサブクラスが等しい場合に真を返す */
    bool Match(uint8_t b, uint8_t s) { return Match(b) && s == sub; }
    /** ベース・サブ・インターフェースが等しい場合に真を返す */
    bool Match(uint8_t b, uint8_t s, uint8_t i) {
        return Match(b, s) && i == interface;
    }
};

/** PCI デバイスを操作するための基礎データを格納する */
struct Device {
    uint8_t bus, device, function, header_type;
    ClassCode class_code;
};

/** CONFIG_ADDRESS に指定された整数を書き込む */
void WriteAddress(uint32_t address);
/** CONFIG_DATA に指定された整数を書き込む */
void WriteData(uint32_t value);
/** CONFIG_DATA から 32 ビット整数を読み込む*/
uint32_t ReadData();

/** ベンダ ID レジスタを読み取る（全ヘッダタイプ共通）*/
uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
/** デバイス ID レジスタを読み取る（全ヘッダタイプ共通）*/
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
/** ヘッダタイプレジスタを読み取る（全ヘッダタイプ共通）*/
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
/** クラスコードレジスタを読み取る */
ClassCode ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
/** バス番号レジスタを読み取る */
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

inline uint16_t ReadVendorId(const Device& dev) {
    return ReadVendorId(dev.bus, dev.device, dev.function);
}

/** 指定された PCI デバイスの 32 ビットレジスタを読み取る */
uint32_t ReadConfReg(const Device& dev, uint8_t reg_addr);
/** 指定された PCI デバイスの 32 ビットレジスタに書き込む */
void WriteConfReg(const Device& dev, uint8_t reg_addr, uint32_t value);

/** 単一ファンクションの場合に真を返す */
bool IsSingleFunctionDevice(uint8_t header_type);

/** ScanAllBus() により発見された PCI デバイスの一覧 */
inline std::array<Device, 32> devices;
/** devices の有効な要素の数 */
inline int num_device;

/** PCI デバイスをすべて探索し device に格納する */
Error ScanAllBus();

constexpr uint8_t CalcBarAddress(unsigned int bar_index) {
    return 0x10 + 4 * bar_index;
}

WithError<uint64_t> ReadBar(Device& device, unsigned int bar_index);

/** PCI ケーパビリティレジスタの共通ヘッダ */
union CapabilityHeader {
    uint32_t data;
    struct {
        uint32_t cap_id : 8;
        uint32_t next_ptr : 8;
        uint32_t cap : 16;
    } __attribute__((packed)) bits;
} __attribute__((packed));

const uint8_t kCapabilityMSI = 0x05;
const uint8_t kCapabilityMSIX = 0x11;

/** 指定された PCI デバイスの指定されたケーパビリティレジスタを読み込む */
CapabilityHeader ReadCapabilityHeader(const Device& dev, uint8_t addr);

/** MSI ケーパビリティ構造 */
struct MSICapability {
    union {
        uint32_t data;
        struct {
            uint32_t cap_id : 8;
            uint32_t next_ptr : 8;
            uint32_t msi_enable : 1;
            uint32_t multi_msg_capable : 3;
            uint32_t multi_msg_enable : 3;
            uint32_t addr_64_capable : 1;
            uint32_t per_vector_mask_capable : 1;
            uint32_t : 7;
        } __attribute__((packed)) bits;
    } __attribute__((packed)) header;

    uint32_t msg_addr;
    uint32_t msg_upper_addr;
    uint32_t msg_data;
    uint32_t mask_bits;
    uint32_t pending_bits;
} __attribute__((packed));

/** MSI または MSI-X 割り込みを設定する*/
Error ConfigureMSI(const Device& dev, uint32_t msg_addr, uint32_t msg_data, unsigned int num_vector_exponent);

enum class MSITriggerMode {
    kEdge = 0,
    kLevel = 1,
};

enum class MSIDeliveryMode {
    kFixed          = 0b000,
    kLowestPriority = 0b001,
    kSMI            = 0b010,
    KNMI            = 0b100,
    KINIT           = 0b101,
    kExtINT         = 0b111,
};

Error ConfigureMSIFixedDestination(
    const Device& dev, uint8_t apic_id,
    MSITriggerMode trigger_mode, MSIDeliveryMode delivery_mode,
    uint8_t vector, unsigned int num_vector_exponent);

}