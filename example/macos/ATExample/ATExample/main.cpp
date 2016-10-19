//
//  main.cpp
//  ATExample
//
//  Created by Slowhand0309
//  Copyright © 2016年 Slowhand0309. All rights reserved.
//
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibSysPrinter.h"
#include "ATgae/engine/ATgaeEngineCreator.h"


int main(int argc, char *argv[])
{
    ATLogger<ATSysPrinter> logger;
    
    TString message = _T("Hello AKATSUKI\n");
    logger.log(LOG_LEVEL_INFO, message);
    
    ATEngine *pEngine = ATEngineCreator::getEngine();
    pEngine->initialize(argc, argv);
    
    return 0;
}
