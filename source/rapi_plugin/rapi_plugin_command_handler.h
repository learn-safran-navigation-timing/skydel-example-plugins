#pragma once

#include "gen/GetVisibleSV.h"
#include "gen/GetVisibleSVResult.h"
#include "gen/SetLeapSecond.h"
#include "gen/SetStartTimeOffset.h"
#include "skydel_plug_ins/skydel_command_handler.h"
#include "skydel_plug_ins/skydel_notifier_interface.h"

using SetterCommand = Sdx::Cmd::SetLeapSecond;
using ActionCommand = Sdx::Cmd::SetStartTimeOffset;
using GetterCommand = Sdx::Cmd::GetVisibleSV;
using GetterCommandResult = Sdx::Cmd::GetVisibleSVResult;

class SkydelNotifierInterface;

class RapiPluginCommandHandler : public SkydelCommandHandler<RapiPluginCommandHandler>
{
public:
  RapiPluginCommandHandler(SkydelCommandExecutor& commandExecutor);

  void setNotifier(SkydelNotifierInterface* notifier) { m_notifier = notifier; };

  void execute(const SetterCommand&);
  CommandExecution::UndoHandler getUndo(const SetterCommand&);

  void execute(const ActionCommand&);

  Sdx::CommandResultPtr execute(const GetterCommand&) const;

private:
  int m_leapSecond {0};
  SkydelNotifierInterface* m_notifier;
};
