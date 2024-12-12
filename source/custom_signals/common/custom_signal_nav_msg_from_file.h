#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <string>

class INavMessageBlock
{
public:
  virtual ~INavMessageBlock() = default;
  virtual bool getBit(int64_t elapsed, uint32_t prn) const = 0;
  virtual uint64_t getSvCount() const = 0;
  virtual bool isValid(uint32_t prn) const = 0;
  virtual int64_t timestamp(uint32_t prn) const = 0;
  virtual void update(int64_t elapsed, uint32_t prn, const std::string& bits) = 0;
  virtual uint64_t firstPrn() const = 0;
};

template<uint64_t SvCount, uint64_t FirstPrn, uint64_t BitCount, uint64_t MessageDurationMs>
class NavMessageBlock : public INavMessageBlock
{
public:
  using SetBitsFunc = std::function<void(std::array<bool, BitCount>&, const std::string&)>;

  NavMessageBlock(SetBitsFunc setBitsFunc) : m_setBitFunc(std::move(setBitsFunc)) {}

  bool getBit(int64_t elapsed, uint32_t prn) const override
  {
    const auto& msg = m_msgs.at(idx(prn));
    return msg.bits[(elapsed - msg.timestamp) * BitCount / MessageDurationMs];
  }

  uint64_t getSvCount() const override { return SvCount; }
  bool isValid(uint32_t prn) const override { return m_msgs.at(idx(prn)).isValid; }
  int64_t timestamp(uint32_t prn) const override { return m_msgs.at(idx(prn)).timestamp; }

  void update(int64_t elapsed, uint32_t prn, const std::string& bits) override
  {
    auto& msg = m_msgs.at(idx(prn));
    msg.isValid = true;
    msg.timestamp = elapsed;
    m_setBitFunc(msg.bits, bits);
  }

  uint64_t firstPrn() const override { return FirstPrn; };

  uint32_t idx(uint32_t prn) const { return prn - FirstPrn; }

private:
  struct Msg
  {
    bool isValid {false};
    int64_t timestamp;
    std::array<bool, BitCount> bits;
  };

  std::array<Msg, SvCount> m_msgs;
  SetBitsFunc m_setBitFunc;
};

class CustomSignalNavMsgFromFile
{
public:
  explicit CustomSignalNavMsgFromFile(const std::string& filename,
                                      std::unique_ptr<INavMessageBlock> navMsgBlock,
                                      size_t downlinkNavMessageIdx = 7);

  void prepare(int64_t elapsed, uint32_t prn);
  bool getBit(int64_t elapsed, uint32_t prn);

private:
  void parseBlock();

  size_t m_downlinkNavMsgIdx;
  std::ifstream m_file;
  std::string m_lastLine;
  std::unique_ptr<INavMessageBlock> m_navMsgBlock;
};
