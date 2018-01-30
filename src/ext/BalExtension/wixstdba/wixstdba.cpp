// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

#include "precomp.h"

static HINSTANCE vhInstance = NULL;

extern "C" BOOL WINAPI DllMain(
    IN HINSTANCE hInstance,
    IN DWORD dwReason,
    IN LPVOID /* pvReserved */
    )
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        ::DisableThreadLibraryCalls(hInstance);
        vhInstance = hInstance;
        break;

    case DLL_PROCESS_DETACH:
        vhInstance = NULL;
        break;
    }

    return TRUE;
}


extern "C" HRESULT WINAPI BootstrapperApplicationCreate(
    __in IBootstrapperEngine* pEngine,
    __in const BOOTSTRAPPER_COMMAND* pCommand,
    __out IBootstrapperApplication** ppApplication
    )
{
    HRESULT hr = S_OK;

    BalInitialize(pEngine);

    hr = CreateBootstrapperApplication(vhInstance, FALSE, S_OK, pEngine, pCommand, ppApplication);
    BalExitOnFailure(hr, "Failed to create bootstrapper application interface.");

LExit:
    return hr;
}


extern "C" void WINAPI BootstrapperApplicationDestroy()
{
    BalUninitialize();
}


extern "C" HRESULT WINAPI MbaPrereqBootstrapperApplicationCreate(
    __in HRESULT hrHostInitialization,
    __in IBootstrapperEngine* pEngine,
    __in const BOOTSTRAPPER_COMMAND* pCommand,
    __out IBootstrapperApplication** ppApplication
    )
{
    HRESULT hr = S_OK;

    BalInitialize(pEngine);

    hr = CreateBootstrapperApplication(vhInstance, TRUE, hrHostInitialization, pEngine, pCommand, ppApplication);
    BalExitOnFailure(hr, "Failed to create managed prerequisite bootstrapper application interface.");

LExit:
    return hr;
}


extern "C" void WINAPI MbaPrereqBootstrapperApplicationDestroy()
{
    BalUninitialize();
}


#include "../balcondition.cpp"
#include "../balinfo.cpp"
#include "../balretry.cpp"
#include "../balutil.cpp"

#include "../strutil.cpp"
#include "../locutil.cpp"
#include "../apputil.cpp"
#include "../dictutil.cpp"
#include "../thmutil.cpp"
#include "../xmlutil.cpp"
#include "../memutil.cpp"
#include "../fileutil.cpp"
#include "../dirutil.cpp"
#include "../pathutil.cpp"
#include "../uriutil.cpp"
#include "../regutil.cpp"
#include "../shelutil.cpp"
#include "../resrutil.cpp"
#include "../dutil.cpp"
#include "../gdiputil.cpp"
