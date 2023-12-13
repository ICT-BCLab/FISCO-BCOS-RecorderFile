#include "RecorderFile.h"

// namespace dev
// {
//     namespace recorderfile
//     {

void RecorderFile::CreateLog()
{
    string cmd="mkdir -p " + Workdir;
    system(cmd.c_str());
}

// 交易池输入通量
void RecorderFile::TransactionPoolInputThroughputInit()
{
    string path =Workdir+"/transaction_pool_input_throughput.csv";
    TransactionPoolInputThroughputF.open(path, ios::out | ios::app);
    if (!TransactionPoolInputThroughputF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("transaction_pool_input_throughput open failed");
    }
    try
    {
        string str = "measure_time,tx_hash,source\n";
        TransactionPoolInputThroughputF << str;
        TransactionPoolInputThroughputF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[transaction_pool_input_throughput] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[transaction_pool_input_throughput] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 交易排队延迟
void RecorderFile::TxQueueDelayInit()
{
    string path =Workdir+"/tx_queue_delay.csv";
    TxQueueDelayF.open(path, ios::out | ios::app);
    if (!TxQueueDelayF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("tx_queue_delay open failed");
    }
    try
    {
        string str = "measure_time,tx_hash,in/outFlag\n";
        TxQueueDelayF << str;
        TxQueueDelayF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[tx_queue_delay] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[tx_queue_delay] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 交易延迟
void RecorderFile::TxDelayStartInit()
{
    string path =Workdir+"/tx_delay_start.csv";
    TxDelayStartF.open(path, ios::out | ios::app);
    if (!TxDelayStartF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("tx_delay_start open failed");
    }
    try
    {
        string str = "measure_time,tx_hash\n";
        TxDelayStartF << str;
        TxDelayStartF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[tx_delay_start] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[tx_delay_start] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 合约执行时间
void RecorderFile::ContractTimeInit()
{
    string path =Workdir+"/contract_time.csv";
    ContractTimeF.open(path, ios::out | ios::app);
    if (!ContractTimeF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("contract_time open failed");
    }
    try
    {
        string str = "tx_hash,contract_address,start_time,end_time,exec_time,type\n";
        ContractTimeF << str;
        ContractTimeF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[contract_time] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[contract_time] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 块内交易冲突率
void RecorderFile::BlockTxConflictRateInit()
{
    string path =Workdir+"/block_tx_conflict_rate.csv";
    BlockTxConflictRateF.open(path, ios::out | ios::app);
    if (!BlockTxConflictRateF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("block_tx_conflict_rate open failed");
    }
    try
    {
        string str = "measure_time,block_height,block_tx_count,conflict_count\n";
        BlockTxConflictRateF << str;
        BlockTxConflictRateF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[block_tx_conflict_rate] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[block_tx_conflict_rate] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 数据库写入速率db_state_write_rate
void RecorderFile::DbStateWriteRateInit()
{
    string path =Workdir+"/db_state_write_rate.csv";
    DbStateWriteRateF.open(path, ios::out | ios::app);
    if (!DbStateWriteRateF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("db_state_write_rate open failed");
    }
    try
    {
        string str = "start_time,end_time,block_height,block_hash,write_duration\n";
        DbStateWriteRateF << str;
        DbStateWriteRateF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[db_state_write_rate] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[db_state_write_rate] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 出块耗时[区块落库时刻]
void RecorderFile::BlockCommitDurationEndInit()
{
    string path =Workdir+"/block_commit_duration_end.csv";
    BlockCommitDurationEndF.open(path, ios::out | ios::app);
    if (!BlockCommitDurationEndF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("block_commit_duration_end open failed");
    }
    try
    {
        string str = "measure_time,block_height,block_hash,block_tx_count,block_txsroot\n";
        BlockCommitDurationEndF << str;
        BlockCommitDurationEndF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[block_commit_duration_end] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[block_commit_duration_end] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 交易延迟[区块落库时刻]
void RecorderFile::TxDelayEndInit()
{
    string path =Workdir+"/tx_delay_end.csv";
    TxDelayEndF.open(path, ios::out | ios::app);
    if (!TxDelayEndF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("tx_delay_end open failed");
    }
    try
    {
        string str = "measure_time,block_height,tx_hash\n";
        TxDelayEndF << str;
        TxDelayEndF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[tx_delay_end] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[tx_delay_end] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 出块耗时[区块打包完成时刻]
void RecorderFile::BlockCommitDurationStartInit()
{
    string path =Workdir+"/block_commit_duration_start.csv";
    BlockCommitDurationStartF.open(path, ios::out | ios::app);
    if (!BlockCommitDurationStartF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("block_commit_duration_start open failed");
    }
    try
    {
        string str = "measure_time,block_height\n";
        BlockCommitDurationStartF << str;
        BlockCommitDurationStartF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[block_commit_duration_start] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[block_commit_duration_start] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 块内交易吞吐量[区块打包完成时刻]
void RecorderFile::TxinBlockTpsInit()
{
    string path =Workdir+"/tx_in_block_tps.csv";
    TxinBlockTpsF.open(path, ios::out | ios::app);
    if (!TxinBlockTpsF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("tx_in_block_tps open failed");
    }
    try
    {
        string str = "measure_time,block_height,block_txsroot,block_tx_count\n";
        TxinBlockTpsF << str;
        TxinBlockTpsF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[tx_in_block_tps] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[tx_in_block_tps] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 数据读取速率
void RecorderFile::DbStateReadRateInit()
{
    string path =Workdir+"/db_state_read_rate.csv";
    DbStateReadRateF.open(path, ios::out | ios::app);
    if (!DbStateReadRateF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("db_state_read_rate open failed");
    }
    try
    {
        string str = "measure_time,block_hash,read_duration,type\n";
        DbStateReadRateF << str;
        DbStateReadRateF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[db_state_read_rate] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[db_state_read_rate] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 每轮pbft共识耗时
void RecorderFile::ConsensusPBFTCostInit()
{
    string path =Workdir+"/consensus_pbft_cost.csv";
    ConsensusPBFTCostF.open(path, ios::out | ios::app);
    if (!ConsensusPBFTCostF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("consensus_pbft_cost open failed");
    }
    try
    {
        string str = "block_height,pbft_start,pbft_end,pbft_cost,type\n";
        ConsensusPBFTCostF << str;
        ConsensusPBFTCostF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[consensus_pbft_cost] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[consensus_pbft_cost] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 每轮raft共识耗时
void RecorderFile::ConsensusRaftCostInit()
{
    string path =Workdir+"/consensus_raft_cost.csv";
    ConsensusRaftCostF.open(path, ios::out | ios::app);
    if (!ConsensusRaftCostF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("consensus_raft_cost open failed");
    }
    try
    {
        string str = "block_height,raft_start,raft_end,raft_cost\n";
        ConsensusRaftCostF << str;
        ConsensusRaftCostF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[consensus_raft_cost] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[consensus_raft_cost] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}

// 区块验证耗时
void RecorderFile::BlockValidationEfficiencyInit()
{
    string path =Workdir+"/block_validation_efficiency.csv";
    BlockValidationEfficiencyF.open(path, ios::out | ios::app);
    if (!BlockValidationEfficiencyF)
    {
        RECORDEFILE_LOG(ERROR) << LOG_DESC("block_validation_efficiency open failed");
    }
    try
    {
        string str = "start_time,end_time,cost_time,block_height,block_tx_count\n";
        BlockValidationEfficiencyF << str;
        BlockValidationEfficiencyF.close();
        RECORDEFILE_LOG(INFO) << LOG_DESC("[block_validation_efficiency] init succeed");
    }
    catch (std::exception const& e)
    {
        RECORDEFILE_LOG(WARNING) << LOG_DESC("[block_validation_efficiency] init failed")
                            << LOG_KV("errorInfo", boost::diagnostic_information(e));
    }
}


void RecorderFile::ConfigInit() 
{
    CreateLog();
    TransactionPoolInputThroughputInit();
    TxQueueDelayInit();
    TxDelayStartInit();
    ContractTimeInit();
    BlockTxConflictRateInit();
    DbStateWriteRateInit();
    BlockCommitDurationEndInit();
    TxDelayEndInit();
    BlockCommitDurationStartInit();
    TxinBlockTpsInit();
    DbStateReadRateInit();
    ConsensusPBFTCostInit();
    ConsensusRaftCostInit();
    BlockValidationEfficiencyInit();
}

int RecorderFile::Start(uint16_t port)
{
    return int(port);
}

void RecorderFile::Record(string data, string filename) 
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
