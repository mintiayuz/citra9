// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <map>
#include <memory>
#include <dynarmic/dynarmic.h>
#include "common/common_types.h"
#include "core/arm/arm_interface.h"
#include "core/arm/skyeye_common/armstate.h"

namespace Memory {
struct PageTable;
} // namespace Memory

class ARM_Dynarmic final : public ARM_Interface {
public:
    ARM_Dynarmic(PrivilegeMode initial_mode);

    void SetPC(u32 pc) override;
    u32 GetPC() const override;
    u32 GetReg(int index) const override;
    void SetReg(int index, u32 value) override;
    u32 GetVFPReg(int index) const override;
    void SetVFPReg(int index, u32 value) override;
    u32 GetVFPSystemReg(VFPSystemRegister reg) const override;
    void SetVFPSystemReg(VFPSystemRegister reg, u32 value) override;
    u32 GetCPSR() const override;
    void SetCPSR(u32 cpsr) override;
    u32 GetCP15Register(CP15Register reg) override;
    void SetCP15Register(CP15Register reg, u32 value) override;

    void SaveContext(ThreadContext& ctx) override;
    void LoadContext(const ThreadContext& ctx) override;

    void PrepareReschedule() override;
    void ExecuteInstructions(int num_instructions) override;

    void ClearInstructionCache() override;
    void PageTableChanged() override;

private:
    Dynarmic::Jit* jit = nullptr;
    Memory::PageTable* current_page_table = nullptr;
    std::map<Memory::PageTable*, std::unique_ptr<Dynarmic::Jit>> jits;
    std::shared_ptr<ARMul_State> interpreter_state;
};
