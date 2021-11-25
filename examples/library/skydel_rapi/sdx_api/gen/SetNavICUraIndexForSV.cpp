#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of SetNavICUraIndexForSV
///
#include "gen/SetNavICUraIndexForSV.h"

namespace Sdx
{
  namespace Cmd
  {
    const char* const SetNavICUraIndexForSV::CmdName = "SetNavICUraIndexForSV";
    const char* const SetNavICUraIndexForSV::Documentation = "Please note the command SetNavICUraIndex is deprecated since 21.3. You may use SetNavICUraIndexForSV.\n\nSet the URA index of a NavIC satellite";

    REGISTER_COMMAND_FACTORY(SetNavICUraIndexForSV);


    SetNavICUraIndexForSV::SetNavICUraIndexForSV()
      : CommandBase(CmdName)
    {}

    SetNavICUraIndexForSV::SetNavICUraIndexForSV(int svId, int urai)
      : CommandBase(CmdName)
    {

      setSvId(svId);
      setUrai(urai);
    }


    SetNavICUraIndexForSVPtr SetNavICUraIndexForSV::create(int svId, int urai)
    {
      return SetNavICUraIndexForSVPtr(new SetNavICUraIndexForSV(svId, urai));
    }

    SetNavICUraIndexForSVPtr SetNavICUraIndexForSV::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<SetNavICUraIndexForSV>(ptr);
    }

    bool SetNavICUraIndexForSV::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<int>::is_valid(m_values["SvId"])
          && parse_json<int>::is_valid(m_values["Urai"])
        ;

    }

    std::string SetNavICUraIndexForSV::documentation() const { return Documentation; }


    int SetNavICUraIndexForSV::executePermission() const
    {
      return EXECUTE_IF_IDLE | EXECUTE_IF_SIMULATING;
    }


    int SetNavICUraIndexForSV::svId() const
    {
      return parse_json<int>::parse(m_values["SvId"]);
    }

    void SetNavICUraIndexForSV::setSvId(int svId)
    {
      m_values.AddMember("SvId", parse_json<int>::format(svId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    int SetNavICUraIndexForSV::urai() const
    {
      return parse_json<int>::parse(m_values["Urai"]);
    }

    void SetNavICUraIndexForSV::setUrai(int urai)
    {
      m_values.AddMember("Urai", parse_json<int>::format(urai, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}