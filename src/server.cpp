#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/Message.h>

#include "server.h"
#include "broker.h"

using namespace Geopoll;


int
Server::main(const std::vector<std::string> & args)
{
    initLogging();

    GeoPoll::Broker broker;

    auto httplistener_ptr = std::make_shared<Geopoll::HttpListener>();
    broker.addListener(httplistener_ptr);
    broker.run();

    waitForTerminationRequest();  // wait for CTRL-C or kill

    broker.stop();

    return Poco::Util::Application::EXIT_OK;
};


void
Server::initLogging()
{
    // initialize the logging system
    Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
    Poco::AutoPtr<Poco::PatternFormatter> pPF(new Poco::PatternFormatter);

    // formatting patterns 
    // see http://www.appinf.com/docs/poco/Poco.PatternFormatter.html
    pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S [%p] [%s] %t");
    Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pPF, pCons));
    Poco::Logger::root().setChannel(pFC);

#ifdef _DEBUG
    // allow logging on max. level in debug builds
    Poco::Logger::root().setLevel(Poco::Message::PRIO_DEBUG);
#else
    Poco::Logger::root().setLevel(Poco::Message::PRIO_INFORMATION);
#endif

}
