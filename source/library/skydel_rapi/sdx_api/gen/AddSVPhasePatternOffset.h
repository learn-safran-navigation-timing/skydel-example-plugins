#pragma once

#include <memory>
#include "command_base.h"

#include "gen/GNSSBand.h"
#include <optional>
#include <string>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Add an offset (in rad) for all values of the phase pattern.
    ///
    /// Name        Type            Description
    /// ----------- --------------- ------------------------------------------------------------------------------------
    /// Band        GNSSBand        Offset will be apply to this band.
    /// System      string          "GPS", "GLONASS", "Galileo", "BeiDou", "SBAS", "QZSS", "NavIC" or "PULSAR"
    /// Offset      double          Phase offset (in rad)
    /// AntennaName optional string Vehicle antenna name. If no name is specified, apply the offset to the Basic Antenna
    ///

    class AddSVPhasePatternOffset;
    typedef std::shared_ptr<AddSVPhasePatternOffset> AddSVPhasePatternOffsetPtr;
    
    
    class AddSVPhasePatternOffset : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;
      static const char* const TargetId;


      AddSVPhasePatternOffset();

      AddSVPhasePatternOffset(const Sdx::GNSSBand& band, const std::string& system, double offset, const std::optional<std::string>& antennaName = {});

      static AddSVPhasePatternOffsetPtr create(const Sdx::GNSSBand& band, const std::string& system, double offset, const std::optional<std::string>& antennaName = {});
      static AddSVPhasePatternOffsetPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;
      virtual const std::vector<std::string>& fieldNames() const override;

      virtual int executePermission() const override;


      // **** band ****
      Sdx::GNSSBand band() const;
      void setBand(const Sdx::GNSSBand& band);


      // **** system ****
      std::string system() const;
      void setSystem(const std::string& system);


      // **** offset ****
      double offset() const;
      void setOffset(double offset);


      // **** antennaName ****
      std::optional<std::string> antennaName() const;
      void setAntennaName(const std::optional<std::string>& antennaName);
    };
    
  }
}

