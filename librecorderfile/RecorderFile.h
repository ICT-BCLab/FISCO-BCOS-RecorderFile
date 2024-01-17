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

#include <yaml-cpp/yaml.h>

#include <oatpp/network/Server.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/network/Server.hpp>

#define O_UNUSERD(x) (void)x;

using namespace std;

#define RECORDEFILE_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("RECORDERFILE")

extern map<string,bool> accessConfig;
class RecorderFile
{
    public:   
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
        void PeerMessageThroughputInit();
        void BlockValidationEfficiencyInit();
        void NetP2PTransmissionLatencyInit();
        
        void ConfigInit();
        void RunServer(int port);
        void Start(int port);

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
        ofstream PeerMessageThroughputF;
        ofstream BlockValidationEfficiencyF;
        ofstream NetP2PTransmissionLatencyF;
};

class Handler_getAccessconfig: public oatpp::web::server::HttpRequestHandler 
{
public:
    shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest>& request) override{
        O_UNUSERD(request);
        YAML::Node file=YAML::LoadFile("./accessconfig.yml"); // 读取文件
        for (YAML::const_iterator it = file.begin(); it != file.end(); ++it) {
            // 获取kv
            const string& key = it->first.as<string>();
            bool value = it->second.as<bool>();
            // 添加到map
            accessConfig[key] = value;
        }
        string respStr = YAML::Dump(file); // 转成字符串
        return ResponseFactory::createResponse(Status::CODE_200, respStr);
    }
};

class Handler_updateAccessconfig : public oatpp::web::server::HttpRequestHandler 
{
public:
    shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest>& request) override{
        string reqStr=request->readBodyToString();
        YAML::Node newfile=YAML::Load(reqStr); // 接收传过来的更新配置
        
        for (YAML::const_iterator it = newfile.begin(); it != newfile.end(); ++it) {
            // 获取kv
            const string& key = it->first.as<string>();
            bool value = it->second.as<bool>();
            // 添加到map
            accessConfig[key] = value;
        }

        std::ofstream fout("./accessconfig.yml");
        fout << newfile; // 写入文件
        fout.close();
        
        string respStr = YAML::Dump(newfile); // 转成字符串
        return ResponseFactory::createResponse(Status::CODE_200, respStr);
    }
};

#endif