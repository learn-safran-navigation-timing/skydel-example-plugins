#pragma once

#include <memory>
#include "command_base.h"

#include <optional>
#include <string>
#include <vector>

namespace Sdx
{
  namespace Cmd
  {
    ///
    /// Please note the command SetBeiDouEphemerisDoubleParams is deprecated since 21.3. You may use SetBeiDouEphDoubleParamForEachSV.
    /// 
    /// Please note the command SetBeiDouEphDoubleParamForEachSV is deprecated since 23.11. You may use SetConstellationParameterForSV.
    /// 
    /// Set BeiDou ephemeris parameter value for all satellites
    ///
    /// Name        Type            Description
    /// ----------- --------------- --------------------------------------------------------------------------------------------------
    /// ParamName   string          Refer to SetBeiDouEphDoubleParamForSV for accepted names
    /// Val         array double    Parameter value for each satellite. Zero based index (index 0 => SV ID 1, index 1 => SV ID 2, etc)
    /// DataSetName optional string Optional name of the data set to use. If no value is provided, the active data set is used.
    ///

    class SetBeiDouEphemerisDoubleParams;
    typedef std::shared_ptr<SetBeiDouEphemerisDoubleParams> SetBeiDouEphemerisDoubleParamsPtr;
    
    
    class SetBeiDouEphemerisDoubleParams : public CommandBase
    {
    public:
      static const char* const CmdName;
      static const char* const Documentation;
      static const char* const TargetId;

      static const char* const Deprecated;


      SetBeiDouEphemerisDoubleParams();

      SetBeiDouEphemerisDoubleParams(const std::string& paramName, const std::vector<double>& val, const std::optional<std::string>& dataSetName = {});

      static SetBeiDouEphemerisDoubleParamsPtr create(const std::string& paramName, const std::vector<double>& val, const std::optional<std::string>& dataSetName = {});
      static SetBeiDouEphemerisDoubleParamsPtr dynamicCast(CommandBasePtr ptr);
      virtual bool isValid() const override;
      virtual std::string documentation() const override;
      virtual const std::vector<std::string>& fieldNames() const override;

      virtual std::optional<std::string> deprecated() const override;

      virtual int executePermission() const override;


      // **** paramName ****
      std::string paramName() const;
      void setParamName(const std::string& paramName);


      // **** val ****
      std::vector<double> val() const;
      void setVal(const std::vector<double>& val);


      // **** dataSetName ****
      std::optional<std::string> dataSetName() const;
      void setDataSetName(const std::optional<std::string>& dataSetName);
    };
    
  }
}

