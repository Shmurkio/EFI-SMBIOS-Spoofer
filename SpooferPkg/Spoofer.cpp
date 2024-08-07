#include "Spoofer.hpp"

void Clr()
{
    gST->ConOut->ClearScreen(gST->ConOut);
}

void Color(uint64_t Attribute)
{
    gST->ConOut->SetAttribute(gST->ConOut, Attribute);
}

EFI_STATUS GetEntryPointStructure(OUT EFI_SMBIOS_TABLE_HEADER **EntryPointStructure)
{
    /* SMBIOS Table GUID */
    for (int i = 0; i < gST->NumberOfTableEntries; i++)
    {
        if (CompareGuid(&gST->ConfigurationTable[i].VendorGuid, &gEfiSmbiosTableGuid))
        {
            *EntryPointStructure = reinterpret_cast<EFI_SMBIOS_TABLE_HEADER *>(gST->ConfigurationTable[i].VendorTable);
            return EFI_SUCCESS;
        }
    }

    /* SMBIOS 3 Table GUID */
    for (int i = 0; i < gST->NumberOfTableEntries; i++)
    {
        if (CompareGuid(&gST->ConfigurationTable[i].VendorGuid, &gEfiSmbios3TableGuid))
        {
            *EntryPointStructure = reinterpret_cast<EFI_SMBIOS_TABLE_HEADER *>(gST->ConfigurationTable[i].VendorTable);
            return EFI_SUCCESS;
        }
    }

    return EFI_NOT_FOUND;
}

bool IsX64(EFI_SMBIOS_TABLE_HEADER *EntryPointStructure)
{
    if (*(reinterpret_cast<unsigned char *>(EntryPointStructure + 3)) == 0x33) // _SM3_ = 64-Bit
    {
        return true;
    }

    return false;
}