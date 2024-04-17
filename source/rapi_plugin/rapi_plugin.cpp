#include "rapi_plugin.h"

#include "gen/GetSimulatorState.h"
#include "gen/SimulatorStateResult.h"
#include "rapi_plugin_view.h"

RapiPlugin::RapiPlugin() : SkydelRapiAccess(PLUGIN_IID), m_commandHandler(commandExecutor())
{
}

SkydelWidgets RapiPlugin::createUI()
{
  auto view = new RapiPluginView;

  connect(view, &RapiPluginView::buttonUpdateClicked, [this, view]() {
    post(Sdx::Cmd::GetSimulatorState::create(), [=](Sdx::CommandResultPtr result) {
      if (auto simulatorStateResult = Sdx::Cmd::SimulatorStateResult::dynamicCast(result))
        view->setSimulatorState(QString::fromStdString(simulatorStateResult->state()));
    });
  });

  connect(view, &RapiPluginView::buttonPostSetterCommandClicked, this, [this]() {
    auto cmd = SetterCommand::create(1);
    rapidjson::Value value {PLUGIN_IID};
    const std::string key = "CmdTargetId";
    cmd->setValue(key, value);
    post(cmd);
  });

  return {view};
}
