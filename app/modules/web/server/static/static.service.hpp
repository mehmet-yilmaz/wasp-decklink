#ifndef ___WASP_WEB_STATIC_SERVICE_HPP___
#define ___WASP_WEB_STATIC_SERVICE_HPP___

#include <core/materials/service.hpp>
#include <shared.hpp>
#include <utils/controller/file.controller.hpp>

namespace Wasp
{
    class StaticService : public Wasp::Service
    {
    private:
        const std::string m_basePath;

    public:
        StaticService(const Wasp::Types::TName &name) : Wasp::Service(name), m_basePath("static"){};
        virtual ~StaticService() override{};

        virtual void init() override
        {
            this->m_initialized = true;
        };

        virtual void run() override
        {
            this->m_running = true;
        };

        std::pair<std::string, std::string> getFile(const std::string &path)
        {
            std::pair<std::string, std::string> response;
            std::string filename = this->m_basePath + "/" + path;
            if (!Wasp::Controllers::FileController::isExist(filename))
            {
                filename = this->m_basePath + "/index.html";
            }
            auto extention = Wasp::Controllers::FileController::getExtention(filename);
            auto contentType = Wasp::Controllers::FileController::getContentType(*extention);
            return std::make_pair(filename, contentType->second);
        };

        std::pair<std::string, std::string> getWildFile(const std::string &path = "index")
        {
            std::pair<std::string, std::string> response;
            std::string filename = this->m_basePath + "/index.html";
            auto extention = Wasp::Controllers::FileController::getExtention(filename);

            if (Wasp::Controllers::FileController::isExist(this->m_basePath + "/" + path))
            {
                filename = this->m_basePath + "/" + path;
            }
            else
            {
                extention = Wasp::Controllers::FileController::getExtention(path);
                if (extention != nullptr)
                {
                    if (Wasp::Controllers::FileController::isExist(this->m_basePath + path.substr(path.find_last_of("/"))))
                    {
                        filename = this->m_basePath + path.substr(path.find_last_of("/"));
                    }
                    else
                    {
                        auto pathArray = Wasp::Controllers::FileController::splitString(path, '/');
                        std::string fname;
                        for (int i = 0; i < pathArray.size(); i++)
                        {
                            if (Wasp::Controllers::FileController::isExist(this->m_basePath + "/" + pathArray[i]))
                            {
                                fname = this->m_basePath + "/" + pathArray[i];
                                for (int j = i + 1; j < pathArray.size(); j++)
                                {
                                    fname += "/" + pathArray[j];
                                }
                                break;
                            }
                        }
                        if (Wasp::Controllers::FileController::isExist(fname))
                        {
                            filename = fname;
                        }
                    }
                }
            }
            extention = Wasp::Controllers::FileController::getExtention(filename);
            auto contentType = Wasp::Controllers::FileController::getContentType(*extention);
            return std::make_pair(filename, contentType->second);
        };
    };
    namespace Bootstrap
    {
        const auto staticService = std::make_shared<Wasp::StaticService>("StaticService");
    };
}

#endif // !___WASP_WEB_STATIC_SERVICE_HPP____