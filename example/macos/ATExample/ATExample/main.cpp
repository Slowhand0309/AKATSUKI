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


void onCallback(ATEngine *pEngine)
{
    ATLogger<ATSysPrinter> logger;

    TString message = _T("Hello AKATSUKI");
    logger.log(LOG_LEVEL_INFO, message);
}

int main(int argc, char *argv[])
{
    // Create Window info.
    ATWindowInfo info;
    info.setDispWidth(640);
    info.setDispHeight(480);
    info.setWindowTitle(_T("AKATSUKI"));

    // Create engine and run.
    ATEngine *pEngine = ATEngineCreator::getEngine();
    pEngine->initialize(argc, argv);
    pEngine->setCallback(onCallback);
    pEngine->setWindowInfo(info);
    pEngine->run();
    pEngine->finalize();
    return 0;
}
