#include "Spoofer.hpp"

int main()
{
    Clr();
    Color(EFI_MAGENTA | EFI_BACKGROUND_BLACK);
    printf("EFI Spoofer by Shmurkio - https://github.com/Shmurkio/EFI-SMBIOS-Spoofer\n\n");

    /* Get the SMBIOS Entry Point Structure */
    EFI_SMBIOS_TABLE_HEADER *EntryPointStructure = nullptr;

    EFI_STATUS Status = GetEntryPointStructure(&EntryPointStructure);

    if (EFI_ERROR(Status))
    {
        Color(EFI_RED | EFI_BACKGROUND_BLACK);
        printf("Spoofing failed: Entry Point Structure not found.\n");
        Color(EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK);
        return static_cast<int>(Status);
    }

    /* Overwrite the Entry Point Structure depending on its architecture  */
    if (IsX64(EntryPointStructure))
    {
        SMBIOS_ENTRY_POINT_STRUCTURE_64 *Eps64 = reinterpret_cast<SMBIOS_ENTRY_POINT_STRUCTURE_64 *>(EntryPointStructure);
        SetMem(Eps64, Eps64->EntryPointLength, 0xFF);
    }
    else
    {
        SMBIOS_ENTRY_POINT_STRUCTURE_32 *Eps32 = reinterpret_cast<SMBIOS_ENTRY_POINT_STRUCTURE_32 *>(EntryPointStructure);
        SetMem(Eps32, Eps32->EntryPointLength, 0xFF);
    }

    Color(EFI_GREEN | EFI_BACKGROUND_BLACK);
    printf("Spoofing successful.\n");
    Color(EFI_LIGHTGRAY | EFI_BACKGROUND_BLACK);

    return 0;
}