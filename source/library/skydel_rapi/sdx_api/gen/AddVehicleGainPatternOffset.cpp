
#include "gen/AddVehicleGainPatternOffset.h"

#include "command_factory.h"
#include "command_result_factory.h"
#include "parse_json.hpp"

///
/// Definition of AddVehicleGainPatternOffset
///

namespace Sdx
{
  namespace Cmd
  {
    const char* const AddVehicleGainPatternOffset::CmdName = "AddVehicleGainPatternOffset";
    const char* const AddVehicleGainPatternOffset::Documentation = "Add an offset (in db) for all values of the pattern.";

    REGISTER_COMMAND_FACTORY(AddVehicleGainPatternOffset);


    AddVehicleGainPatternOffset::AddVehicleGainPatternOffset()
      : CommandBase(CmdName)
    {}

    AddVehicleGainPatternOffset::AddVehicleGainPatternOffset(const Sdx::GNSSBand& band, double offset, const Sdx::optional<std::string>& antennaName)
      : CommandBase(CmdName)
    {

      setBand(band);
      setOffset(offset);
      setAntennaName(antennaName);
    }

    AddVehicleGainPatternOffsetPtr AddVehicleGainPatternOffset::create(const Sdx::GNSSBand& band, double offset, const Sdx::optional<std::string>& antennaName)
    {
      return std::make_shared<AddVehicleGainPatternOffset>(band, offset, antennaName);
    }

    AddVehicleGainPatternOffsetPtr AddVehicleGainPatternOffset::dynamicCast(CommandBasePtr ptr)
    {
      return std::dynamic_pointer_cast<AddVehicleGainPatternOffset>(ptr);
    }

    bool AddVehicleGainPatternOffset::isValid() const
    {
      
        return m_values.IsObject()
          && parse_json<Sdx::GNSSBand>::is_valid(m_values["Band"])
          && parse_json<double>::is_valid(m_values["Offset"])
          && parse_json<Sdx::optional<std::string>>::is_valid(m_values["AntennaName"])
        ;

    }

    std::string AddVehicleGainPatternOffset::documentation() const { return Documentation; }


    int AddVehicleGainPatternOffset::executePermission() const
    {
      return EXECUTE_IF_IDLE;
    }


    Sdx::GNSSBand AddVehicleGainPatternOffset::band() const
    {
      return parse_json<Sdx::GNSSBand>::parse(m_values["Band"]);
    }

    void AddVehicleGainPatternOffset::setBand(const Sdx::GNSSBand& band)
    {
      m_values.AddMember("Band", parse_json<Sdx::GNSSBand>::format(band, m_values.GetAllocator()), m_values.GetAllocator());
    }



    double AddVehicleGainPatternOffset::offset() const
    {
      return parse_json<double>::parse(m_values["Offset"]);
    }

    void AddVehicleGainPatternOffset::setOffset(double offset)
    {
      m_values.AddMember("Offset", parse_json<double>::format(offset, m_values.GetAllocator()), m_values.GetAllocator());
    }



    Sdx::optional<std::string> AddVehicleGainPatternOffset::antennaName() const
    {
      return parse_json<Sdx::optional<std::string>>::parse(m_values["AntennaName"]);
    }

    void AddVehicleGainPatternOffset::setAntennaName(const Sdx::optional<std::string>& antennaName)
    {
      m_values.AddMember("AntennaName", parse_json<Sdx::optional<std::string>>::format(antennaName, m_values.GetAllocator()), m_values.GetAllocator());
    }


  }
}
