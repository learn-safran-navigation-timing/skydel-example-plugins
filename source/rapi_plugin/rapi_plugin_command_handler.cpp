#include "rapi_plugin_command_handler.h"

#include <QString>

#include "skydel_plug_ins/skydel_notifier_interface.h"

RapiPluginCommandHandler::RapiPluginCommandHandler(SkydelCommandExecutor& commandExecutor) :
  SkydelCommandHandler<RapiPluginCommandHandler>(commandExecutor)
{
  registerCommandWithUndo<SetterCommand>();
  registerCommand<ActionCommand>();
  registerNonMutableCommand<GetterCommand>();
}

void RapiPluginCommandHandler::execute(const SetterCommand& cmd)
{
  if (cmd.leapSecond() < 0 || cmd.leapSecond() > 10)
    throw std::runtime_error("Inavalid value, must be between 0 and 10.");

  m_notifier->notify(QString("SetterCommand::execute %1").arg(cmd.leapSecond()).toStdString(),
                     SkydelNotifierInterface::WARNING);
  m_leapSecond = cmd.leapSecond();
}

CommandExecution::UndoHandler RapiPluginCommandHandler::getUndo(const SetterCommand&)
{
  return [this, value = m_leapSecond]() {
    m_notifier->notify(QString("SetterCommand::undo %1").arg(value).toStdString(), SkydelNotifierInterface::WARNING);
    m_leapSecond = value;
  };
}

void RapiPluginCommandHandler::execute(const ActionCommand& cmd)
{
  if (cmd.offset() < 10 || cmd.offset() > 20)
    throw std::runtime_error("Inavalid value, must be between 10 and 20.");

  m_notifier->notify(QString("ActionCommand::execute %1").arg(cmd.offset()).toStdString(),
                     SkydelNotifierInterface::WARNING);
}

Sdx::CommandResultPtr RapiPluginCommandHandler::execute(const GetterCommand& cmd) const
{
  if (cmd.system() != "Test")
    throw std::runtime_error("Inavalid system value, must be Test.");

  m_notifier->notify("GetterCommand::execute", SkydelNotifierInterface::WARNING);

  return GetterCommandResult::create(cmd.system(), {1, 2, 3, 4});
}
