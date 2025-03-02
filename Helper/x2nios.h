//
//  Macros.h
//  ModMenu
//
//  Created by AHMED ALI on 4/2/19.
//  Copyright © 2019 Joey. All rights reserved.
//

#import "KittyMemory/writeData.hpp"
#import "KittyMemory/MemoryPatch.hpp"
#include <substrate.h>
#include <mach-o/dyld.h>
#include <dlfcn.h>
#include "oxorany/oxorany_include.h"
#include "encrypt.h"

#define Dobby(offset, ptr, orig) DobbyHook(reinterpret_cast<void*>(getRealOffset(offset)), reinterpret_cast<void*>(ptr), reinterpret_cast<void**>(&orig))

// thanks to shmoo for the usefull stuff under this comment.
#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^
#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)
#define HOOK_NO_ORIG(offset, ptr) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, NULL)
#define HOOKSYM(sym, ptr, org) MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, (void **)&org)
#define HOOKSYM_NO_ORIG(sym, ptr)  MSHookFunction((void*)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, NULL)
#define getSym(symName) dlsym((void *)RTLD_DEFAULT, symName)
uintptr_t base_addr = {};

uint64_t getRealOffset(uint64_t offset)
{
	return KittyMemory::getAbsoluteAddress(encrypt(oxorany("UnityFramework")), offset);
}

void patchOffset(uint64_t offset, std::string hexBytes) {
	MemoryPatch patch = MemoryPatch::createWithHex(encrypt(oxorany("UnityFramework")), offset, hexBytes);
	if(!patch.isValid()){
		
		return;
	}
	if(!patch.Modify()) {
      
    }
}

