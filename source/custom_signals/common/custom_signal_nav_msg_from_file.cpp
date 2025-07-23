#include "custom_signal_nav_msg_from_file.h"

#include <filesystem>
#include <sstream>

namespace
{
constexpr int32_t DOWNLINK_ELAPSED_MS_INDEX = 0;
constexpr int32_t DOWNLINK_SV_ID_INDEX = 1;

inline std::vector<std::string> split(const std::string& str, const std::string& delim)
{
  std::vector<std::string> sent;
  std::string::size_type pos = 0;

  while (true)
  {
    std::string::size_type delimPos = str.find(delim, pos);
    sent.push_back(str.substr(pos, delimPos - pos));
    if (delimPos == std::string::npos)
      break;
    pos = delimPos + delim.size();
  }
  return sent;
}

inline int64_t toInt64(const std::string& str)
{
  int64_t sent = 0;
  std::istringstream iss(str);
  iss >> sent;
  return sent;
}

inline bool parseLine(const std::string& line,
                      int64_t& out_timestamp,
                      int64_t& out_svID,
                      std::string& out_bits,
                      size_t navMsgIdx)
{
  std::vector<std::string> values = split(line, ",");

  if (values.size() < navMsgIdx + 1)
    return false;

  out_timestamp = toInt64(values[DOWNLINK_ELAPSED_MS_INDEX]);
  out_svID = toInt64(values[DOWNLINK_SV_ID_INDEX]);
  out_bits = values[navMsgIdx];

  return true;
}

template<typename... TArgs>
std::string buildString(TArgs&&... args)
{
  std::ostringstream oss;

  (oss << ... << args);
  return oss.str();
}

} // namespace

CustomSignalNavMsgFromFile::CustomSignalNavMsgFromFile(const std::string& filename,
                                                       std::unique_ptr<INavMessageBlock> navMsgBlock,
                                                       size_t downlinkNavMessageIdx) :
  m_downlinkNavMsgIdx(downlinkNavMessageIdx),
  m_file(std::filesystem::path(filename)),
  m_navMsgBlock(std::move(navMsgBlock))
{
  if (!m_file)
    throw std::runtime_error {"Couldn't open file " + filename};

  // skip header
  std::string headerLine;
  std::getline(m_file, headerLine);

  // get the first line
  std::getline(m_file, m_lastLine);

  parseBlock();
}

void CustomSignalNavMsgFromFile::prepare(int64_t elapsed, uint32_t svID)
{
  if (!m_navMsgBlock->isValid(svID))
    throw std::runtime_error(buildString("Downlink file is missing SV ID ", svID, "."));

  if (elapsed <= 0 && m_navMsgBlock->timestamp(svID) != elapsed)
    throw std::runtime_error("Downlink file start time is incorrect for this simulation.");

  while (m_file && m_navMsgBlock->timestamp(svID) < elapsed)
    parseBlock();

  if (!m_file && m_navMsgBlock->timestamp(svID) != elapsed)
    throw std::runtime_error(buildString("Downlink file end reached, can't get block for elapsed ms ", elapsed, "."));
}

bool CustomSignalNavMsgFromFile::getBit(int64_t elapsed, uint32_t svID)
{
  return m_navMsgBlock->getBit(elapsed, svID);
}

void CustomSignalNavMsgFromFile::parseBlock()
{
  int64_t timestamp;
  int64_t firstTimestamp;
  int64_t svID;
  std::string bits;

  if (!parseLine(m_lastLine, timestamp, svID, bits, m_downlinkNavMsgIdx))
    return;

  firstTimestamp = timestamp;

  do
  {
    if (svID < 1 || svID > static_cast<int64_t>(m_navMsgBlock->getSvCount()))
      throw std::runtime_error(buildString("Invalid SV ID ", svID, " in downlink file."));

    m_navMsgBlock->update(timestamp, static_cast<uint32_t>(svID), bits);
  } while (std::getline(m_file, m_lastLine) && parseLine(m_lastLine, timestamp, svID, bits, m_downlinkNavMsgIdx) &&
           timestamp == firstTimestamp);
}
