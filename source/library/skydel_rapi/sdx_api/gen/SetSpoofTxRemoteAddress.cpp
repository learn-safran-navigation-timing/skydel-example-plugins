
#include "SetSpoofTxRemoteAddress.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of SetSpoofTxRemoteAddress
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const SetSpoofTxRemoteAddress::CmdName = "SetSpoofTxRemoteAddress";
    const char* const SetSpoofTxRemoteAddress::Documentation = "Set the address of the spoofer instance that will\n"
      "generate the signal for this spoofer transmitter.\n"
      "\n"
      "Name       Type   Description\n"
      "---------- ------ ------------------------------\n"
      "Address    string Remote instance IP address.\n"
      "InstanceId int    Remote instance ID.\n"
      "Id         string Transmitter unique identifier.";
    const char* const SetSpoofTxRemoteAddress::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(SetSpoofTxRemoteAddress);
    REGISTER_COMMAND_TO_FACTORY_IMPL(SetSpoofTxRemoteAddress);


    SetSpoofTxRemoteAddress::SetSpoofTxRemoteAddress()
      : CommandBase(CmdName, TargetId)
    {}

    SetSpoofTxRemoteAddress::SetSpoofTxRemoteAddress(const std::string& address, int instanceId, const std::string& id)
      : CommandBase(CmdName, TargetId)
    {

      setAddress(address);
      setInstanceId(instanceId);
      setId(id);
    }

    SetSpoofTxRemoteAddressPtr SetSpoofTxRemoteAddress::create(const std::string& address, int instanceId, const std::string& id)
    {
      return std::make_shared<SetSpoofTxRemoteAddress>(address, instanceId, id);
    }

    SetSpoofTxRemoteAddressPtr SetSpoofTxRemoteAddress::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<SetSpoofTxRemoteAddress>(ptr);
    }

    bool SetSpoofTxRemoteAddress::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<std::string>::is_valid(m_values["Address"])
          && parse_json<int>::is_valid(m_values["InstanceId"])
          && parse_json<std::string>::is_valid(m_values["Id"])
        ;

    }

    std::string SetSpoofTxRemoteAddress::documentation() const { return Documentation; }

    const std::vector<std::string>& SetSpoofTxRemoteAddress::fieldNames() const 
    { 
      static const std::vector<std::string> names {"Address", "InstanceId", "Id"}; 
      return names; 
    }


    int SetSpoofTxRemoteAddress::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    std::string SetSpoofTxRemoteAddress::address() const
    {
      return parse_json<std::string>::parse(m_values["Address"]);
    }

    void SetSpoofTxRemoteAddress::setAddress(const std::string& address)
    {
      m_values.AddMember("Address", parse_json<std::string>::format(address, m_values.GetAllocator()), m_values.GetAllocator());
    }



    int SetSpoofTxRemoteAddress::instanceId() const
    {
      return parse_json<int>::parse(m_values["InstanceId"]);
    }

    void SetSpoofTxRemoteAddress::setInstanceId(int instanceId)
    {
      m_values.AddMember("InstanceId", parse_json<int>::format(instanceId, m_values.GetAllocator()), m_values.GetAllocator());
    }



    std::string SetSpoofTxRemoteAddress::id() const
    {
      return parse_json<std::string>::parse(m_values["Id"]);
    }

    void SetSpoofTxRemoteAddress::setId(const std::string& id)
    {
      m_values.AddMember("Id", parse_json<std::string>::format(id, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
