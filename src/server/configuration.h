#ifndef __batyr_configuration_h__
#define __batyr_configuration_h__

#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace Batyr
{
    
    struct Layer
    {
        std::string name;
        std::string dataSource;

        typedef std::shared_ptr<Layer> Ptr;
    };


    class ConfigurationError : public std::runtime_error 
    {
        public:
            ConfigurationError(const std::string & message) 
                    : std::runtime_error(message)
            {
            };
    };


    class Configuration
    {
        public:
            Configuration(const std::string & configFile);

            /**
             * get a layer by its name.
             * throws ConfigurationError if it does not exist
             */
            Layer::Ptr getLayer(const std::string &) const;

            unsigned int getHttpPort() const
            {
                return http_port;
            }

            unsigned int getNumWorkerThreads() const
            {
                return num_worker_threads;
            }

            unsigned int getLayerCount() const
            {
                return layers.size();
            }

            typedef std::shared_ptr<Configuration> Ptr;

        private:
            std::unordered_map<std::string, Layer::Ptr> layers;

            /* default settings */
            unsigned int http_port = 9090;
            unsigned int num_worker_threads = 2;

            void parse(const std::string & configFile);
    };

};

#endif // __batyr_configuration_h__