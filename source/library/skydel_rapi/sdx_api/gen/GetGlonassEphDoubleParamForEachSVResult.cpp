#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetGlonassEphDoubleParamForEachSVResult
///
#include "gen/GetGlonassEphDoubleParamForEachSVResult.h"

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetGlonassEphDoubleParamForEachSVResult::CmdName = "GetGlonassEphDoubleParamForEachSVResult";
    const char* const GetGlonassEphDoubleParamForEachSVResult::Documentation = "Result of GetGlonassEphDoubleParamForEachSV.";

    REGISTER_COMMAND_RESULT_FACTORY(GetGlonassEphDoubleParamForEachSVResult);


    GetGlonassEphDoubleParamForEachSVResult::GetGlonassEphDoubleParamForEachSVResult()
      : CommandResult(CmdName)
    {}

    GetGlonassEphDoubleParamForEachSVResult::GetGlonassEphDoubleParamForEachSVResult(CommandBasePtr relatedCommand, const std::string& paramName, const std::vector<double>& val)
      : CommandResult(CmdName, relatedCommand)
    {

      setParamName(paramName);
      setVal(val);
    }


    GetGlonassEphDoubleParamForEachSVResultPtr GetGlonassEphDoubleParamForEachSVResult::create(CommandBasePtr relatedCommand, const std::string& paramName, const std::vector<double>& val)
    {
      return GetGlonassEphDoubleParamForEachSVResultPtr(new GetGlonassEphDoubleParamForEachSVResult(relatedCommand, paramName, val));
    }

    GetGlonassEphDoubleParamForEachSVResultPtr GetGlonassEphDoubleParamForEachSVResult::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetGlonassEphDoubleParamForEachSVResult>(ptr);
    }

    bool GetGlonassEphDoubleParamForEachSVResult::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<std::string>::is_valid(m_values["ParamName"])
          && parse_json<std::vector<double>>::is_valid(m_values["Val"])
        ;

    }

    std::string GetGlonassEphDoubleParamForEachSVResult::documentation() const { return Documentation; }


    std::string GetGlonassEphDoubleParamForEachSVResult::paramName() const
    {
      return parse_json<std::string>::parse(m_values["ParamName"]);
    }

    void GetGlonassEphDoubleParamForEachSVResult::setParamName(const std::string& paramName)
    {
      m_values.AddMember("ParamName", parse_json<std::string>::format(paramName, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::vector<double> GetGlonassEphDoubleParamForEachSVResult::val() const
    {
      return parse_json<std::vector<double>>::parse(m_values["Val"]);
    }

    void GetGlonassEphDoubleParamForEachSVResult::setVal(const std::vector<double>& val)
    {
      m_values.AddMember("Val", parse_json<std::vector<double>>::format(val, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
