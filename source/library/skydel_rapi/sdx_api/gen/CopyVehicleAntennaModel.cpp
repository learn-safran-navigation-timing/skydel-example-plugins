
#include "CopyVehicleAntennaModel.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of CopyVehicleAntennaModel
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const CopyVehicleAntennaModel::CmdName = "CopyVehicleAntennaModel";
    const char* const CopyVehicleAntennaModel::Documentation = "Copy a vehicle antenna model.\n"
      "\n"
      "Name     Type   Description\n"
      "-------- ------ ------------------------------------\n"
      "Name     string Reference vehicle antenna model name\n"
      "CopyName string Copy vehicle antenna model name";
    const char* const CopyVehicleAntennaModel::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(CopyVehicleAntennaModel);
    REGISTER_COMMAND_TO_FACTORY_IMPL(CopyVehicleAntennaModel);


    CopyVehicleAntennaModel::CopyVehicleAntennaModel()
      : CommandBase(CmdName, TargetId)
    {}

    CopyVehicleAntennaModel::CopyVehicleAntennaModel(const std::string& name, const std::string& copyName)
      : CommandBase(CmdName, TargetId)
    {

      setName(name);
      setCopyName(copyName);
    }

    CopyVehicleAntennaModelPtr CopyVehicleAntennaModel::create(const std::string& name, const std::string& copyName)
    {
      return std::make_shared<CopyVehicleAntennaModel>(name, copyName);
    }

    CopyVehicleAntennaModelPtr CopyVehicleAntennaModel::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<CopyVehicleAntennaModel>(ptr);
    }

    bool CopyVehicleAntennaModel::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<std::string>::is_valid(m_values["Name"])
          && parse_json<std::string>::is_valid(m_values["CopyName"])
        ;

    }

    std::string CopyVehicleAntennaModel::documentation() const { return Documentation; }

    const std::vector<std::string>& CopyVehicleAntennaModel::fieldNames() const 
    { 
      static const std::vector<std::string> names {"Name", "CopyName"}; 
      return names; 
    }


    int CopyVehicleAntennaModel::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    std::string CopyVehicleAntennaModel::name() const
    {
      return parse_json<std::string>::parse(m_values["Name"]);
    }

    void CopyVehicleAntennaModel::setName(const std::string& name)
    {
      m_values.AddMember("Name", parse_json<std::string>::format(name, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string CopyVehicleAntennaModel::copyName() const
    {
      return parse_json<std::string>::parse(m_values["CopyName"]);
    }

    void CopyVehicleAntennaModel::setCopyName(const std::string& copyName)
    {
      m_values.AddMember("CopyName", parse_json<std::string>::format(copyName, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
