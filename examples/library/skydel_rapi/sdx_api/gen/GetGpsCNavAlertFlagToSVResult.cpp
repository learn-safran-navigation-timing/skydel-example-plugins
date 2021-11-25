#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetGpsCNavAlertFlagToSVResult
///
#include "gen/GetGpsCNavAlertFlagToSVResult.h"

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetGpsCNavAlertFlagToSVResult::CmdName = "GetGpsCNavAlertFlagToSVResult";
    const char* const GetGpsCNavAlertFlagToSVResult::Documentation = "Result of GetGpsCNavAlertFlagToSV.";

    REGISTER_COMMAND_RESULT_FACTORY(GetGpsCNavAlertFlagToSVResult);


    GetGpsCNavAlertFlagToSVResult::GetGpsCNavAlertFlagToSVResult()
      : CommandResult(CmdName)
    {}

    GetGpsCNavAlertFlagToSVResult::GetGpsCNavAlertFlagToSVResult(CommandBasePtr relatedCommand, int svId, bool alert)
      : CommandResult(CmdName, relatedCommand)
    {

      setSvId(svId);
      setAlert(alert);
    }


    GetGpsCNavAlertFlagToSVResultPtr GetGpsCNavAlertFlagToSVResult::create(CommandBasePtr relatedCommand, int svId, bool alert)
    {
      return GetGpsCNavAlertFlagToSVResultPtr(new GetGpsCNavAlertFlagToSVResult(relatedCommand, svId, alert));
    }

    GetGpsCNavAlertFlagToSVResultPtr GetGpsCNavAlertFlagToSVResult::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetGpsCNavAlertFlagToSVResult>(ptr);
    }

    bool GetGpsCNavAlertFlagToSVResult::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<bool>::is_valid(m_values["Alert"])
        ;

    }

    std::string GetGpsCNavAlertFlagToSVResult::documentation() const { return Documentation; }


    int GetGpsCNavAlertFlagToSVResult::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void GetGpsCNavAlertFlagToSVResult::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    bool GetGpsCNavAlertFlagToSVResult::alert() const
    {
      return parse_json<bool>::parse(m_values["Alert"]);
    }

    void GetGpsCNavAlertFlagToSVResult::setAlert(bool alert)
    {
      m_values.AddMember("Alert", parse_json<bool>::format(alert, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}