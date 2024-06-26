
#include "EnableIntTxTrajectorySmoothing.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of EnableIntTxTrajectorySmoothing
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const EnableIntTxTrajectorySmoothing::CmdName = "EnableIntTxTrajectorySmoothing";
    const char* const EnableIntTxTrajectorySmoothing::Documentation = "Set trajectory smoothing for interference Track enabled or disabled\n"
      "\n"
      "Name    Type   Description\n"
      "------- ------ -------------------------------------------------------------------\n"
      "Enabled bool   If true, interference trajectory will be smoothed during simulation\n"
      "Id      string Transmitter unique identifier.";
    const char* const EnableIntTxTrajectorySmoothing::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(EnableIntTxTrajectorySmoothing);
    REGISTER_COMMAND_TO_FACTORY_IMPL(EnableIntTxTrajectorySmoothing);


    EnableIntTxTrajectorySmoothing::EnableIntTxTrajectorySmoothing()
      : CommandBase(CmdName, TargetId)
    {}

    EnableIntTxTrajectorySmoothing::EnableIntTxTrajectorySmoothing(bool enabled, const std::string& id)
      : CommandBase(CmdName, TargetId)
    {

      setEnabled(enabled);
      setId(id);
    }

    EnableIntTxTrajectorySmoothingPtr EnableIntTxTrajectorySmoothing::create(bool enabled, const std::string& id)
    {
      return std::make_shared<EnableIntTxTrajectorySmoothing>(enabled, id);
    }

    EnableIntTxTrajectorySmoothingPtr EnableIntTxTrajectorySmoothing::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<EnableIntTxTrajectorySmoothing>(ptr);
    }

    bool EnableIntTxTrajectorySmoothing::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<bool>::is_valid(m_values["Enabled"])
          && parse_json<std::string>::is_valid(m_values["Id"])
        ;

    }

    std::string EnableIntTxTrajectorySmoothing::documentation() const { return Documentation; }

    const std::vector<std::string>& EnableIntTxTrajectorySmoothing::fieldNames() const 
    { 
      static const std::vector<std::string> names {"Enabled", "Id"}; 
      return names; 
    }


    int EnableIntTxTrajectorySmoothing::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    bool EnableIntTxTrajectorySmoothing::enabled() const
    {
      return parse_json<bool>::parse(m_values["Enabled"]);
    }

    void EnableIntTxTrajectorySmoothing::setEnabled(bool enabled)
    {
      m_values.AddMember("Enabled", parse_json<bool>::format(enabled, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string EnableIntTxTrajectorySmoothing::id() const
    {
      return parse_json<std::string>::parse(m_values["Id"]);
    }

    void EnableIntTxTrajectorySmoothing::setId(const std::string& id)
    {
      m_values.AddMember("Id", parse_json<std::string>::format(id, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
