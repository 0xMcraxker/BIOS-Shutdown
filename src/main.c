#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_FLAG_PLANNED))
    {
        DWORD errorCode = GetLastError();
        LPSTR errorMessage = NULL;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorMessage, 0, NULL);

        if (errorMessage)
        {
            MessageBoxA(NULL, errorMessage, TEXT("Error"), MB_OK | MB_ICONERROR);
            printf("Failed to shutdown: %s\n", errorMessage);
            LocalFree(errorMessage);
        }
        else
        {
            char errorMessage[256];
            snprintf(errorMessage, sizeof(errorMessage), "%ld", errorCode);

            LPCSTR lpErrorMessage = errorMessage;

            MessageBoxA(NULL, lpErrorMessage, TEXT("Exit Status"), MB_OK | MB_ICONERROR);
        }

        return EXIT_FAILURE;
    }

    printf("Shutdown initiated successfully.\n");
    return EXIT_SUCCESS;
}
