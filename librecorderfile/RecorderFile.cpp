#include "RecorderFile.h"

std::map<std::string,bool> accessConfig {
        {"All",true},
        {"consensus_raft_cost", true},
        {"block_commit_duration_end", true},
        {"block_commit_duration_start", true},
        {"block_tx_conflict_rate", true},
        {"block_validation_efficiency", true},
        {"consensus_pbft_cost", true},
        {"contract_time", true},
        {"db_state_read_rate", true},
        {"db_state_write_rate", true},
        {"net_p2p_transmission_latency",true},
        {"peer_message_throughput", true},
        {"transaction_pool_input_throughput", true},
        {"tx_delay_end", true},
        {"tx_delay_start", true},
        {"tx_in_block_tps", true},
        {"tx_queue_delay", true}
};

void RecorderFile::CreateLogDir()
{
    string cmd="mkdir -p " + Workdir;
    system(cmd.c_str());
}

void RecorderFile::MetricsInit()
{
    const std::vector<RecorderFile::PerformanceMetric> metrics = {
        {"block_commit_duration_end", "measure_time,block_height,block_hash,block_tx_count,block_txsroot"},
        {"block_commit_duration_start", "measure_time,block_height"},
        {"block_tx_conflict_rate", "measure_time,block_height,block_tx_count,conflict_count"},
        {"block_validation_efficiency", "start_time,end_time,cost_time,block_height,block_tx_count"},
        {"consensus_pbft_cost", "block_height,pbft_start,pbft_end,pbft_cost,type"},
        {"consensus_raft_cost", "block_height,raft_start,raft_end,raft_cost"},
        {"contract_time", "tx_hash,contract_address,start_time,end_time,exec_time,type"},
        {"db_state_read_rate", "measure_time,block_hash,read_duration,type"},
        {"db_state_write_rate", "start_time,end_time,block_height,block_hash,write_duration"},
        {"net_p2p_transmission_latency", "send_time,send_id,receive_time,receive_id,duration"},
        {"peer_message_throughput", "measure_time,action_type,message_type,message_size"},
        {"transaction_pool_input_throughput", "measure_time,tx_hash,source"},
        {"tx_delay_start", "measure_time,tx_hash"},
        {"tx_in_block_tps", "measure_time,block_height,block_txsroot,block_tx_count"},
        {"tx_queue_delay", "measure_time,tx_hash,in/outFlag"},
    };
}

void RecorderFile::ConfigInit() 
{
    CreateLogDir();
    MetricsInit();

    for (const auto& metric : metrics)
    {
        string path = Workdir + "/" + metric.name + ".csv";
        MetricF.open(path, ios::out | ios::app);
        if (!MetricF)
        {
            RECORDEFILE_LOG(ERROR) << LOG_DESC("Metric file open failed")
                                << LOG_KV("metricName", metric.name);
            continue;
        }
        try
        {
            string str = metric.parameters + "\n";
            MetricF << str;
            MetricF.close();
            RECORDEFILE_LOG(INFO) << LOG_DESC("Metric initialization succeeded")
                            << LOG_KV("metricName", metric.name);
        }
        catch (std::exception const& e)
        {
            RECORDEFILE_LOG(WARNING) << LOG_DESC("Metric initialization failed")
                                << LOG_KV("metricName", metric.name)
                                << LOG_KV("errorInfo", boost::diagnostic_information(e));
        }
    }
}

void RecorderFile::RunServer(int port)
{
    RECORDEFILE_LOG(INFO) << LOG_DESC("[ConfigServer] start init");
    // 初始化 oatpp 环境
    oatpp::base::Environment::init();

    // 为 HTTP 请求创建路由器
    auto router = oatpp::web::server::HttpRouter::createShared();

    // 路由请求到处理程序
    router->route("GET", "/config/accessconfig", std::make_shared<Handler_getAccessconfig>());
    router->route("PUT", "/config/accessconfig", std::make_shared<Handler_updateAccessconfig>());

    // 创建 HTTP 连接处理程序
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // 创建 TCP 连接提供者
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", uint16_t(port), oatpp::network::Address::IP_4});

    // 创建服务器，它接受提供的 TCP 连接并将其传递给 HTTP 连接处理程序
    oatpp::network::Server server(connectionProvider, connectionHandler);

    RECORDEFILE_LOG(INFO) << LOG_DESC("[config server] is running")
                            << LOG_KV("port", uint16_t(port));
    // 运行服务器
    server.run();

    // 销毁 oatpp 环境
    oatpp::base::Environment::destroy();
}

void RecorderFile::Start(int port)
{
    ConfigInit();
    RunServer(port);
}

void RecorderFile::Record(string data, string filename) 
{

    // RECORDEFILE_LOG(INFO) << LOG_DESC("[Check yaml]")
    //                         << LOG_KV("All", accessConfig["All"])
    //                         << LOG_KV("consensus_raft_cost", accessConfig["consensus_raft_cost"])
    //                         << LOG_KV("block_commit_duration_end", accessConfig["block_commit_duration_end"])
    //                         << LOG_KV("block_commit_duration_start", accessConfig["block_commit_duration_start"])
    //                         << LOG_KV("block_tx_conflict_rate", accessConfig["block_tx_conflict_rate"])
    //                         << LOG_KV("block_validation_efficiency", accessConfig["block_validation_efficiency"])
    //                         << LOG_KV("consensus_pbft_cost", accessConfig["consensus_pbft_cost"])
    //                         << LOG_KV("contract_time", accessConfig["contract_time"])
    //                         << LOG_KV("db_state_read_rate", accessConfig["db_state_read_rate"])
    //                         << LOG_KV("db_state_write_rate", accessConfig["db_state_write_rate"])
    //                         << LOG_KV("peer_message_throughput", accessConfig["peer_message_throughput"])
    //                         << LOG_KV("transaction_pool_input_throughput", accessConfig["transaction_pool_input_throughput"])
    //                         << LOG_KV("tx_delay_end", accessConfig["tx_delay_end"])
    //                         << LOG_KV("tx_delay_start", accessConfig["tx_delay_start"])
    //                         << LOG_KV("tx_in_block_tps", accessConfig["tx_in_block_tps"])
    //                         << LOG_KV("tx_queue_delay", accessConfig["tx_queue_delay"])
    //                         ;

    if(accessConfig["All"] && accessConfig[filename])
    {
        string path = Workdir + "/" + filename + ".csv";
        ofstream file(path, ios::out | ios::app);
        if (!file) 
        {
            RECORDEFILE_LOG(ERROR) << LOG_DESC(path + " open failed");
        }
        try
        {
            file << data;
            file.close();
            RECORDEFILE_LOG(INFO) << LOG_DESC("[" + path +"] record succeed");
        }
        catch (std::exception const& e)
        {
            RECORDEFILE_LOG(ERROR) << LOG_DESC("[" + path +"] record missed")
                                << LOG_KV("errorInfo", boost::diagnostic_information(e));
        }
    }
}
