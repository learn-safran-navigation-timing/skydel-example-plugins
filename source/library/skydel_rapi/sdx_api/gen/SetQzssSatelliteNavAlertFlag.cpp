
#include "gen/SetQzssSatelliteNavAlertFlag.h"

#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of SetQzssSatelliteNavAlertFlag
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const SetQzssSatelliteNavAlertFlag::CmdName = "SetQzssSatelliteNavAlertFlag";
    const char* const SetQzssSatelliteNavAlertFlag::Documentation = "Please note the command SetQzssSatelliteNavAlertFlag is deprecated since 21.3. You may use SetQzssNavAlertFlagForSV.\n\nSet QZSS NAV Alert Flag";

    REGISTER_COMMAND_FACTORY(SetQzssSatelliteNavAlertFlag);


    SetQzssSatelliteNavAlertFlag::SetQzssSatelliteNavAlertFlag()
      : CommandBase(CmdName)
    {}

    SetQzssSatelliteNavAlertFlag::SetQzssSatelliteNavAlertFlag(int svId, bool alert, const Sdx::optional<std::string>& dataSetName)
      : CommandBase(CmdName)
    {

      setSvId(svId);
      setAlert(alert);
      setDataSetName(dataSetName);
    }

    SetQzssSatelliteNavAlertFlagPtr SetQzssSatelliteNavAlertFlag::create(int svId, bool alert, const Sdx::optional<std::string>& dataSetName)
    {
      return std::make_shared<SetQzssSatelliteNavAlertFlag>(svId, alert, dataSetName);
    }

    SetQzssSatelliteNavAlertFlagPtr SetQzssSatelliteNavAlertFlag::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<SetQzssSatelliteNavAlertFlag>(ptr);
    }

    bool SetQzssSatelliteNavAlertFlag::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<bool>::is_valid(m_values["Alert"])
          && parse_json<Sdx::optional<std::string>>::is_valid(m_values["DataSetName"])
        ;

    }

    std::string SetQzssSatelliteNavAlertFlag::documentation() const { return Documentation; }


    int SetQzssSatelliteNavAlertFlag::executePermission() const
    {
      return EXECUTE_IF_SIMULATING | EXECUTE_IF_IDLE;
    }


    int SetQzssSatelliteNavAlertFlag::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void SetQzssSatelliteNavAlertFlag::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    bool SetQzssSatelliteNavAlertFlag::alert() const
    {
      return parse_json<bool>::parse(m_values["Alert"]);
    }

    void SetQzssSatelliteNavAlertFlag::setAlert(bool alert)
    {
      m_values.AddMember("Alert", parse_json<bool>::format(alert, m_values.GetAllocator()), m_values.GetAllocator());
    }



    Sdx::optional<std::string> SetQzssSatelliteNavAlertFlag::dataSetName() const
    {
      return parse_json<Sdx::optional<std::string>>::parse(m_values["DataSetName"]);
    }

    void SetQzssSatelliteNavAlertFlag::setDataSetName(const Sdx::optional<std::string>& dataSetName)
    {
      m_values.AddMember("DataSetName", parse_json<Sdx::optional<std::string>>::format(dataSetName, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
