//
//  DisableLibraryValidation.cpp
//  DisableLibraryValidation
//
//  Created by Oliver Kuckertz on 15.07.17.
//  Copyright © 2017 Oliver Kuckertz. All rights reserved.
//

#include <IOKit/IOLib.h>
#include "DisableLibraryValidation.h"

OSDefineMetaClassAndStructors(com_mologie_DisableLibraryValidation, IOService)

// This service does not implement any methods. Its sole purpose is to have IOKit load our driver on boot.
