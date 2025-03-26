#pragma once

#include <juce_core/juce_core.h>

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#define PARAMS_FILENAME ("params.bin")

// PARAMS OBJECT

struct Params
{
  // ** always update the serialize function when changing this struct! **

  struct Tesira
  {
    std::string remoteAddress;
    std::string localAddress;
    int port = 23;
  } tesira;

  struct Osc
  {
    int port = 57820;
  } osc;
};

// --------------------------------------

class ParamsFile : private juce::Thread
{
  struct SerialParams
  {
    Params params;

    // PARAMS SERIALIZATION
    template <class Archive>
    void serialize(Archive &ar, const unsigned int)
    {
      ar & params.tesira.remoteAddress;
      ar & params.tesira.localAddress;
      ar & params.tesira.port;
      ar & params.osc.port;
    }
  };

public:
  ParamsFile() : juce::Thread("ParamsFile"), params()
  {
    // get file path
    auto dir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory);
    dir = dir.getChildFile(PRODUCT_NAME_WITHOUT_VERSION);
    if (!dir.exists())
      dir.createDirectory();
    dir = dir.getChildFile(PARAMS_FILENAME);

    filepath = dir.getFullPathName().toStdString();

    // initial file load
    loadFile();
  }
  ~ParamsFile() override
  {
    stopThread(100);
  }

  // manipulation

  /** get params object */
  const Params &get() { return params; }
  /** update the parameters object */
  void set(std::function<void(Params &)> updater)
  {
    updater(params);
    saveFile();
  }

private:
  // members

  Params params;
  std::string filepath;

  // serialization functions

  void saveFile()
  {
    if (!isThreadRunning())
      startThread();
    juce::Thread::launch([this]() { //
      waitForThreadToExit(1000);
      startThread();
    });
  }
  void run() override
  { // SAVE FILE
    try
    {
      SerialParams sp{};
      sp.params = params;

      std::ofstream file(filepath);
      boost::archive::binary_oarchive archive(file);
      archive << sp;
    }
    catch (const std::exception &e)
    {
      juce::MessageManager::callAsync([e]() { //
        DBG("ERROR SAVING FILE " << e.what());
      });
    }
  }

  void loadFile()
  {
    try
    {
      SerialParams sp{};
      std::ifstream file(filepath);
      boost::archive::binary_iarchive archive(file);
      archive >> sp;
      params = sp.params;
    }
    catch (const std::exception &)
    {
    }
  }
};
