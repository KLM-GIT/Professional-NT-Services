#include <windows.h>

int main()
{
   HDESK hdesk = NULL;
   HWINSTA hwinsta = NULL;
   SECURITY_DESCRIPTOR sd;
   SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;

   __try
   {
      // Open the window station and desktop
      hwinsta = OpenWindowStation("winsta0", FALSE, WRITE_DAC);
      if (hwinsta == NULL)
         __leave;

      hdesk = OpenDesktop("default", 0, FALSE,
                      WRITE_DAC | DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS);
      if (hdesk == NULL)
         __leave;

      // Create a security descriptor with a NULL DACL
      if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
         __leave;

      if(!SetSecurityDescriptorDacl(&sd, TRUE, (PACL)NULL, FALSE))
         __leave;

      // Set the security descriptors on the winstation and desktop
      //  to the new one you just created
      if(!SetUserObjectSecurity(hwinsta, &si, &sd))
         __leave;

      if(!SetUserObjectSecurity(hdesk, &si, &sd))
         __leave;
   }
   __finally                  // Close the handles on error or as normal flow
   {
      if(hdesk != NULL)
         CloseDesktop(hdesk);

      if(hwinsta != NULL)
         CloseWindowStation(hwinsta);
   }
   return 0;
}
