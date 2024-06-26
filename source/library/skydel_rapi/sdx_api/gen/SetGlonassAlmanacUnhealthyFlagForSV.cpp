
#include "SetGlonassAlmanacUnhealthyFlagForSV.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of SetGlonassAlmanacUnhealthyFlagForSV
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const SetGlonassAlmanacUnhealthyFlagForSV::CmdName = "SetGlonassAlmanacUnhealthyFlagForSV";
    const char* const SetGlonassAlmanacUnhealthyFlagForSV::Documentation = "Set GLONASS satellite Almanac Unhealthy Flag Cn\n"
      "\n"
      "Name   Type Description\n"
      "------ ---- ----------------------------------------------------------\n"
      "SvId   int  The satellite's SV ID 1..24\n"
      "Health bool Status, false = Non-operability, true = Operability (Good)";
    const char* const SetGlonassAlmanacUnhealthyFlagForSV::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(SetGlonassAlmanacUnhealthyFlagForSV);
    REGISTER_COMMAND_TO_FACTORY_IMPL(SetGlonassAlmanacUnhealthyFlagForSV);


    SetGlonassAlmanacUnhealthyFlagForSV::SetGlonassAlmanacUnhealthyFlagForSV()
      : CommandBase(CmdName, TargetId)
    {}

    SetGlonassAlmanacUnhealthyFlagForSV::SetGlonassAlmanacUnhealthyFlagForSV(int svId, bool health)
      : CommandBase(CmdName, TargetId)
    {

      setSvId(svId);
      setHealth(health);
    }

    SetGlonassAlmanacUnhealthyFlagForSVPtr SetGlonassAlmanacUnhealthyFlagForSV::create(int svId, bool health)
    {
      return std::make_shared<SetGlonassAlmanacUnhealthyFlagForSV>(svId, health);
    }

    SetGlonassAlmanacUnhealthyFlagForSVPtr SetGlonassAlmanacUnhealthyFlagForSV::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<SetGlonassAlmanacUnhealthyFlagForSV>(ptr);
    }

    bool SetGlonassAlmanacUnhealthyFlagForSV::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<bool>::is_valid(m_values["Health"])
        ;

    }

    std::string SetGlonassAlmanacUnhealthyFlagForSV::documentation() const { return Documentation; }

    const std::vector<std::string>& SetGlonassAlmanacUnhealthyFlagForSV::fieldNames() const 
    { 
      static const std::vector<std::string> names {"SvId", "Health"}; 
      return names; 
    }


    int SetGlonassAlmanacUnhealthyFlagForSV::executePermission() const
    {
      return EXECUTE_IF_SIMULATING | EXECUTE_IF_IDLE;
    }


    int SetGlonassAlmanacUnhealthyFlagForSV::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void SetGlonassAlmanacUnhealthyFlagForSV::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    bool SetGlonassAlmanacUnhealthyFlagForSV::health() const
    {
      return parse_json<bool>::parse(m_values["Health"]);
    }

    void SetGlonassAlmanacUnhealthyFlagForSV::setHealth(bool health)
    {
      m_values.AddMember("Health", parse_json<bool>::format(health, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
