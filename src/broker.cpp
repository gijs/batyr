#include "broker.h"

#include <thread>
#include <functional>


using namespace GeoPoll;


Broker::Broker() 
    : logger(Poco::Logger::get("Broker"))
{
    poco_information(logger, "Setting up the broker");
    //logger = Poco::Logger::get("Broker");
}


Broker::~Broker()
{
    stop();
}


void
Broker::addListener(std::shared_ptr<Geopoll::BaseListener> listener_ptr)
{
    listeners.push_back(listener_ptr);
}


void
Broker::run()
{
    // start all listeners
    for(auto ilistener = listeners.begin(); ilistener != listeners.end() ; ++ilistener) {
        // TODO: run listeners in seperate threads
        // http://stackoverflow.com/questions/10673585/start-thread-with-member-function
        std::thread lThread(
            std::bind(&Geopoll::BaseListener::run, (*ilistener))
            );
        lThread.detach();
        //(*ilistener)->run();
    }
}


void
Broker::stop()
{
    // stopping all listeners
    /*
    for(auto ilistener = listeners.begin(); ilistener != listeners.end() ; ++ilistener) {
        (*ilistener)->stop();
    }
    */
}
