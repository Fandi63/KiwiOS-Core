#include <efi.h>
#include <efilib.h>

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
   InitializeLib(ImageHandle, SystemTable);
   Print(L"===========\n");
   Print(L"K I W I O S\n");
   Print(L"-----------\n");
   Print(L"Core version 1.0\n");

   return EFI_SUCCESS;
}
