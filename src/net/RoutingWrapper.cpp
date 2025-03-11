#include "RoutingWrapper.h"

RoutingWrapper::RoutingWrapper(MainComponent *ui_, RouteMap routes_)
    : ui{ui_}, routes{routes_}
{
}

void RoutingWrapper::handleMessage(juce::String msg)
{
  auto obj = juce::JSON::parse(msg);
  auto type_v = obj.getProperty("type", JSNIL);
  if (!type_v.isString())
    return;
  auto type = type_v.toString().toStdString();
  auto data = obj.getProperty("data", JSNIL);

  if (routes.find(type) != routes.end())
  {
    routes[type](data);
  }
}
