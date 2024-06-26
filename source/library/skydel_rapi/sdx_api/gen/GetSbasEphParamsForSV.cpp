
#include "GetSbasEphParamsForSV.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetSbasEphParamsForSV
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetSbasEphParamsForSV::CmdName = "GetSbasEphParamsForSV";
    const char* const GetSbasEphParamsForSV::Documentation = "Get parameters for a SBAS satellite ephemeris (runtime modification only available for health parameter)\n"
      "\n"
      "Name       Type         Description\n"
      "---------- ------------ ----------------------------------------------------------------------------\n"
      "SvId       int          The satellite's SV ID\n"
      "ParamArray array string An array of params.\n"
      "                        Accepted values are: \"ClockBias\", \"RelativeFrequencyBias\", \"X\", \"Y\", \"Z\",\n"
      "                                             \"VelocityX\", \"VelocityY\", \"VelocityZ\", \"AccelerationX\",\n"
      "                                             \"AccelerationY\", \"AccelerationZ\", \"Health\", \"URA\" and\n"
      "                                             \"UraIndex\"";
    const char* const GetSbasEphParamsForSV::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(GetSbasEphParamsForSV);
    REGISTER_COMMAND_TO_FACTORY_IMPL(GetSbasEphParamsForSV);


    GetSbasEphParamsForSV::GetSbasEphParamsForSV()
      : CommandBase(CmdName, TargetId)
    {}

    GetSbasEphParamsForSV::GetSbasEphParamsForSV(int svId, const std::vector<std::string>& paramArray)
      : CommandBase(CmdName, TargetId)
    {

      setSvId(svId);
      setParamArray(paramArray);
    }

    GetSbasEphParamsForSVPtr GetSbasEphParamsForSV::create(int svId, const std::vector<std::string>& paramArray)
    {
      return std::make_shared<GetSbasEphParamsForSV>(svId, paramArray);
    }

    GetSbasEphParamsForSVPtr GetSbasEphParamsForSV::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetSbasEphParamsForSV>(ptr);
    }

    bool GetSbasEphParamsForSV::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<std::vector<std::string>>::is_valid(m_values["ParamArray"])
        ;

    }

    std::string GetSbasEphParamsForSV::documentation() const { return Documentation; }

    const std::vector<std::string>& GetSbasEphParamsForSV::fieldNames() const 
    { 
      static const std::vector<std::string> names {"SvId", "ParamArray"}; 
      return names; 
    }


    int GetSbasEphParamsForSV::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    int GetSbasEphParamsForSV::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void GetSbasEphParamsForSV::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::vector<std::string> GetSbasEphParamsForSV::paramArray() const
    {
      return parse_json<std::vector<std::string>>::parse(m_values["ParamArray"]);
    }

    void GetSbasEphParamsForSV::setParamArray(const std::vector<std::string>& paramArray)
    {
      m_values.AddMember("ParamArray", parse_json<std::vector<std::string>>::format(paramArray, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
