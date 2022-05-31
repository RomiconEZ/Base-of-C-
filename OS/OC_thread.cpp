#include <iostream>
#include<thread>
#include<chrono>
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <mutex>
#include <vector>
#include <cstdint>


using namespace std;

//=============================================================================
//  Forward declarations:
BOOL GetProcessList(DWORD ProcessID);
BOOL ListProcessModules(DWORD dwPID, DWORD ProcessID);
BOOL ListProcessThreads(DWORD dwOwnerPID, DWORD ProcessID);
void printError(TCHAR* msg);
//=============================================================================
BOOL GetProcessList(DWORD ProcessID)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;
    //ProcessID = 0;
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, ProcessID);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        // printError("CreateToolhelp32Snapshot (of processes)");
        return(FALSE);
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        //printError(L"Process32First"); // show cause of failure
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return(FALSE);
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        if (pe32.th32ProcessID == ProcessID)
        {
            wprintf(TEXT("\n\n====================================================="));
            wprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
            wprintf(TEXT("\n-------------------------------------------------------"));

            // Retrieve the priority class.
            dwPriorityClass = 0;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL)

            {
                dwPriorityClass = GetPriorityClass(hProcess);
                if (!dwPriorityClass)
                    //   printError(L"GetPriorityClass");
                    CloseHandle(hProcess);
            }

            wprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
            wprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
            wprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
            wprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
            if (dwPriorityClass)
                wprintf(TEXT("\n  Priority class    = %d"), dwPriorityClass);

            // List the modules and threads associated with this process
            ListProcessModules(pe32.th32ProcessID, ProcessID);
            ListProcessThreads(pe32.th32ProcessID, ProcessID);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}


BOOL ListProcessModules(DWORD dwPID,DWORD ProcessID)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        //   printError(L("CreateToolhelp32Snapshot (of modules)"));
        return(FALSE);
    }

    // Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if (!Module32First(hModuleSnap, &me32))
    {
        //   printError(L("Module32First"));  // show cause of failure
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return(FALSE);
    }

    // Now walk the module list of the process,
    // and display information about each module
    do
    {
        _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        _tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
        _tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
        _tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
        _tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID,DWORD ProcessID)
{
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    // Take a snapshot of all running threads  
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, ProcessID);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
        return(FALSE);

    // Fill in the size of the structure before using it. 
    te32.dwSize = sizeof(THREADENTRY32);

    // Retrieve information about the first thread,
    // and exit if unsuccessful
    if (!Thread32First(hThreadSnap, &te32))
    {
        //    printError(("Thread32First")); // show cause of failure
        CloseHandle(hThreadSnap);          // clean the snapshot object
        return(FALSE);
    }

    // Now walk the thread list of the system,
    // and display information about each thread
    // associated with the specified process
    do
    {
        if (te32.th32OwnerProcessID == dwOwnerPID)
        {
            _tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
            _tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri);
            _tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri);
            _tprintf(TEXT("\n"));
        }
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return(TRUE);
}

void printError(TCHAR* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        sysMsg, 256, NULL);

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while ((*p > 31) || (*p == 9))
        ++p;
    do { *p-- = 0; } while ((p >= sysMsg) &&
        ((*p == '.') || (*p < 33)));

    // Display the message
    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}
//=============================================================================
  /*! set the affinity of a given thread */
void setAffinity(HANDLE thread, size_t affinity)
{
#if (_WIN32_WINNT >= 0x0601) // FIXME: use getProcAddress to activate this feature only if supported by Windows
    int groups = GetActiveProcessorGroupCount();
    int totalProcessors = 0, group = 0, number = 0;
    for (int i = 0; i < groups; i++) {
        int processors = GetActiveProcessorCount(i);
        if (totalProcessors + processors > affinity) {
            group = i;
            number = (int)affinity - totalProcessors;
            break;
        }
        totalProcessors += processors;
    }

    GROUP_AFFINITY groupAffinity;
    groupAffinity.Group = (WORD)group;
    groupAffinity.Mask = (KAFFINITY)(__int64(1) << number);
    groupAffinity.Reserved[0] = 0;
    groupAffinity.Reserved[1] = 0;
    groupAffinity.Reserved[2] = 0;
    //if (!SetThreadGroupAffinity(thread, &groupAffinity, NULL))
    //    THROW_RUNTIME_ERROR("cannot set thread group affinity");

    PROCESSOR_NUMBER processorNumber;
    processorNumber.Group = group;
    processorNumber.Number = number;
    processorNumber.Reserved = 0;
    //if (!SetThreadIdealProcessorEx(thread, &processorNumber, NULL))
    //    THROW_RUNTIME_ERROR("cannot set ideal processor");
#else
    if (!SetThreadAffinityMask(thread, DWORD_PTR(uint64(1) << affinity)))
        THROW_RUNTIME_ERROR("cannot set thread affinity mask");
    if (SetThreadIdealProcessor(thread, (DWORD)affinity) == (DWORD)-1)
        THROW_RUNTIME_ERROR("cannot set ideal processor");
#endif
}
//======================================================================
void work()
{
	for (int i = 0; i < 10; i++)
	{
		cout <<"ID потока "<< this_thread::get_id() <<" work "<< i << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	/*cout << "============= Work started =============" << endl;
	cout << "a + b = " << a + b << endl;
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "============= Work stopped =============" << endl;*/
}

int main()
{
    DWORD ProcessID = GetCurrentProcessId();
	setlocale(LC_ALL, "ru");
    thread th(work);
	//thread th(work,200,31);
	//thread th(work); //создание экземпляра потока // передаем указатель на функцию
	// th.detach(); //разрываем связь между объетом th и тем потоком, который мы начали выполнять 
	// к окончанию работы main завершится и поток th
	// this_thread::get_id(); //получить id потока
	// th.join();//дождаться выполнения задачи
	for (int i = 0; i < 10; i++)
	{
		cout << "ID потока " << this_thread::get_id() << " main " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	this_thread::sleep_for(chrono::milliseconds(5000)); //приостанавливает работу потока на определенный период времени
    cout << "==============================================================" << endl;
    GetProcessList(ProcessID);
	th.join();
    //cout << "=============================Thread_affinity=================================" << endl;
    //setAffinity(HANDLE thread, size_t affinity)
    //cout << "==============================================================" << endl;
	return 0;
}

