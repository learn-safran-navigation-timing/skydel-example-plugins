
#include "GetIntTxAntennaResult.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetIntTxAntennaResult
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetIntTxAntennaResult::CmdName = "GetIntTxAntennaResult";
    const char* const GetIntTxAntennaResult::Documentation = "Result of GetIntTxAntenna.\n"
      "\n"
      "Name Type               Description\n"
      "---- ------------------ -------------------------------------------------------------------------------------------------------------------------\n"
      "Gain array array double Gain matrix (dB). The first dimension will be mapped to elevation [-90, 90] and the second dimension to azimuth [0, 360[.\n"
      "Type AntennaPatternType Pattern type\n"
      "Id   string             Transmitter unique identifier.";
    const char* const GetIntTxAntennaResult::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_IMPL(GetIntTxAntennaResult);


    GetIntTxAntennaResult::GetIntTxAntennaResult()
      : CommandResult(CmdName, TargetId)
    {}

    GetIntTxAntennaResult::GetIntTxAntennaResult(const std::vector<std::vector<double>>& gain, const Sdx::AntennaPatternType& type, const std::string& id)
      : CommandResult(CmdName, TargetId)
    {

      setGain(gain);
      setType(type);
      setId(id);
    }

    GetIntTxAntennaResult::GetIntTxAntennaResult(CommandBasePtr relatedCommand, const std::vector<std::vector<double>>& gain, const Sdx::AntennaPatternType& type, const std::string& id)
      : CommandResult(CmdName, TargetId, relatedCommand)
    {

      setGain(gain);
      setType(type);
      setId(id);
    }


    GetIntTxAntennaResultPtr GetIntTxAntennaResult::create(const std::vector<std::vector<double>>& gain, const Sdx::AntennaPatternType& type, const std::string& id)
    {
      return std::make_shared<GetIntTxAntennaResult>(gain, type, id);
    }

    GetIntTxAntennaResultPtr GetIntTxAntennaResult::create(CommandBasePtr relatedCommand, const std::vector<std::vector<double>>& gain, const Sdx::AntennaPatternType& type, const std::string& id)
    {
      return std::make_shared<GetIntTxAntennaResult>(relatedCommand, gain, type, id);
    }

    GetIntTxAntennaResultPtr GetIntTxAntennaResult::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetIntTxAntennaResult>(ptr);
    }

    bool GetIntTxAntennaResult::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<std::vector<std::vector<double>>>::is_valid(m_values["Gain"])
          && parse_json<Sdx::AntennaPatternType>::is_valid(m_values["Type"])
          && parse_json<std::string>::is_valid(m_values["Id"])
        ;

    }

    std::string GetIntTxAntennaResult::documentation() const { return Documentation; }

    const std::vector<std::string>& GetIntTxAntennaResult::fieldNames() const 
    { 
      static const std::vector<std::string> names {"Gain", "Type", "Id"}; 
      return names; 
    }


    std::vector<std::vector<double>> GetIntTxAntennaResult::gain() const
    {
      return parse_json<std::vector<std::vector<double>>>::parse(m_values["Gain"]);
    }

    void GetIntTxAntennaResult::setGain(const std::vector<std::vector<double>>& gain)
    {
      m_values.AddMember("Gain", parse_json<std::vector<std::vector<double>>>::format(gain, m_values.GetAllocator()), m_values.GetAllocator());
    }



    Sdx::AntennaPatternType GetIntTxAntennaResult::type() const
    {
      return parse_json<Sdx::AntennaPatternType>::parse(m_values["Type"]);
    }

    void GetIntTxAntennaResult::setType(const Sdx::AntennaPatternType& type)
    {
      m_values.AddMember("Type", parse_json<Sdx::AntennaPatternType>::format(type, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string GetIntTxAntennaResult::id() const
    {
      return parse_json<std::string>::parse(m_values["Id"]);
    }

    void GetIntTxAntennaResult::setId(const std::string& id)
    {
      m_values.AddMember("Id", parse_json<std::string>::format(id, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
