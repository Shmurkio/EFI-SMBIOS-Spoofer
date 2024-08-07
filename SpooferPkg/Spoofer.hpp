#pragma once

extern "C"
{
    #include <Uefi.h>
    #include <Library/UefiLib.h>
    #include <Library/UefiBootServicesTableLib.h>
    #include <Library/UefiApplicationEntryPoint.h>
    #include <Library/UefiRuntimeServicesTableLib.h>
    #include <stdio.h>
    #include <Library/ShellCEntryLib.h>
    #include <Library/BaseMemoryLib.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <Guid/SmBios.h>
    #include <Protocol/Smbios.h>
}

#include "LibCpp/defs.hpp"

/* SMBIOS structures */
#pragma pack(push, 1)

struct SMBIOS_ENTRY_POINT_STRUCTURE_32
{
    uint8_t AnchorString[4];
    uint8_t EntryPointChecksum;
    uint8_t EntryPointLength;
    uint8_t SmbiosMajorVersion;
    uint8_t SmbiosMinorVersion;
    uint16_t SmbiosStructureMaximumSize;
    uint8_t EntryPointRevision;
    uint8_t FormattedArea[5];
    uint8_t IntermediateAnchorString[5];
    uint8_t IntermediateChecksum;
    uint16_t StructureTableLength;
    uint32_t StructureTableAddress;
    uint16_t NumberOfStructures;
    uint8_t BcdRevision;
};

struct SMBIOS_ENTRY_POINT_STRUCTURE_64
{
    uint8_t AnchorString[5];
    uint8_t EntryPointChecksum;
    uint8_t EntryPointLength;
    uint8_t SmbiosMajorVersion;
    uint8_t SmbiosMinorVersion;
    uint8_t SmbiosDocrev;
    uint8_t EntryPointRevision;
    uint8_t Reserved;
    uint32_t StructureTableMaximumSize;
    uint64_t StructureTableAddress;
};

#pragma pack(pop)

void Clr();
void Color(uint64_t Attribute);
EFI_STATUS GetEntryPointStructure(OUT EFI_SMBIOS_TABLE_HEADER **EntryPointStructure);
bool IsX64(EFI_SMBIOS_TABLE_HEADER *EntryPointStructure);