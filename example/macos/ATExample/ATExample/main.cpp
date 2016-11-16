//
//  main.cpp
//  ATExample
//
//  Created by Slowhand0309
//  Copyright © 2016年 Slowhand0309. All rights reserved.
//
#include "ATlib/log/ATlibLogger.h"
#include "ATlib/log/ATlibFilePrinter.h"
#include "ATgae/engine/ATgaeEngineCreator.h"

/**
 * Call when main loop.
 */
void onCallback()
{
}

int main(int argc, char *argv[])
{
    // Create Window info.
    ATWindowInfo info;
    info.setWidth(640);
    info.setHeight(480);
    info.setWindowTitle(_T("AKATSUKI"));

    // Create engine and run.
    ATEngine *pEngine = ATEngineCreator::getEngine();
    if (pEngine->initialize(argc, argv) != AT_OK) {
        fprintf(stderr, "ATEngine initialize error.");
        return -1;
    }
    pEngine->setCallback(onCallback);
    pEngine->setWindowInfo(info);

    // main loop...
    pEngine->run();

    ATEngineCreator::releaseEngine();
    return 0;
}
