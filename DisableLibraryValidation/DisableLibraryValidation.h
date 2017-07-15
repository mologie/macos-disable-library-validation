//
//  DisableLibraryValidation.h
//  DisableLibraryValidation
//
//  Created by Oliver Kuckertz on 15.07.17.
//  Copyright © 2017 Oliver Kuckertz. All rights reserved.
//

#pragma once

#include <IOKit/IOService.h>

class com_mologie_DisableLibraryValidation : public IOService
{
    OSDeclareDefaultStructors(com_mologie_DisableLibraryValidation)
};
