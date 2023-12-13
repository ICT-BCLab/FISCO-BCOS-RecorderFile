#ifndef RECORDERFILE
#define RECORDERFILE
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <sstream>

#include <libdevcore/Common.h>
#include <libdevcore/Exceptions.h>

using namespace std;


#define RECORDEFILE_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("RECORDERFILE")

class RecorderFile
{
    public:   
        map<string, string> registerInfo;
        const string Workdir = "./log_record";


        void CreateLog();
        void TransactionPoolInputThroughputInit();
        void TxQueueDelayInit();
        void TxDelayStartInit();
        void ContractTimeInit();
        void BlockTxConflictRateInit();
        void DbStateWriteRateInit();
        void BlockCommitDurationEndInit();
        void TxDelayEndInit();
        void BlockCommitDurationStartInit();
        void TxinBlockTpsInit();
        void DbStateReadRateInit();
        void ConsensusPBFTCostInit();
        void ConsensusRaftCostInit();
        void BlockValidationEfficiencyInit();

        void ConfigInit();
        int Start(uint16_t port);

        void Record(string data, string filename);
    private:
        ofstream TransactionPoolInputThroughputF;
        ofstream TxQueueDelayF;
        ofstream TxDelayStartF;
        ofstream ContractTimeF;
        ofstream BlockTxConflictRateF;
        ofstream DbStateWriteRateF;
        ofstream BlockCommitDurationEndF;
        ofstream TxDelayEndF;
        ofstream BlockCommitDurationStartF;
        ofstream TxinBlockTpsF;
        ofstream DbStateReadRateF;
        ofstream ConsensusPBFTCostF;
        ofstream ConsensusRaftCostF;
        ofstream BlockValidationEfficiencyF;
};
#endif