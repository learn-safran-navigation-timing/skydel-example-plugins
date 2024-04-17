
#include "GetNmeaLoggerSentences.h"

#include "command_factory.h"
#include "parse_json.hpp"

///
/// Definition of GetNmeaLoggerSentences
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const GetNmeaLoggerSentences::CmdName = "GetNmeaLoggerSentences";
    const char* const GetNmeaLoggerSentences::Documentation = "Get the NMEA sentences that will be generated by the logger.";
    const char* const GetNmeaLoggerSentences::TargetId = "";

    REGISTER_COMMAND_TO_FACTORY_DECL(GetNmeaLoggerSentences);
    REGISTER_COMMAND_TO_FACTORY_IMPL(GetNmeaLoggerSentences);


    GetNmeaLoggerSentences::GetNmeaLoggerSentences()
      : CommandBase(CmdName, TargetId)
    {

    }

    GetNmeaLoggerSentencesPtr GetNmeaLoggerSentences::create()
    {
      return std::make_shared<GetNmeaLoggerSentences>();
    }

    GetNmeaLoggerSentencesPtr GetNmeaLoggerSentences::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<GetNmeaLoggerSentences>(ptr);
    }

    bool GetNmeaLoggerSentences::isValid() const
    {
      
        return m_values.IsObject()
        ;

    }

    std::string GetNmeaLoggerSentences::documentation() const { return Documentation; }

    const std::vector<std::string>& GetNmeaLoggerSentences::fieldNames() const 
    { 
      static const std::vector<std::string> names {}; 
      return names; 
    }


    int GetNmeaLoggerSentences::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }

  }
}
