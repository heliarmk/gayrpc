// Generated by github.com/IronsDu/protoc-gen-gayrpc
// Coding by github.com/liuhan907
// DO NOT EDIT!!!

#ifndef _ECHO_SERVICE_H
#define _ECHO_SERVICE_H

#include <string>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <future>

#include <google/protobuf/util/json_util.h>

#include "meta.pb.h"
#include "echo_service.pb.h"

#include "GayRpcCore.h"
#include "GayRpcError.h"
#include "GayRpcTypeHandler.h"
#include "GayRpcClient.h"
#include "GayRpcService.h"
#include "GayRpcReply.h"

namespace dodo {
namespace test {

namespace echo_service
{
    using namespace gayrpc::core;
    using namespace google::protobuf::util;
    
    
    enum class EchoServerMsgID:uint64_t
    {
        echo = 2333,
        login = 3333,
        
    };

    class EchoServerClient : public BaseClient
    {
    public:
        typedef std::shared_ptr<EchoServerClient> PTR;

        typedef std::function<void(const dodo::test::EchoResponse&,
            const gayrpc::core::RpcError&)> EchoHandle;
        typedef std::function<void(const dodo::test::LoginResponse&,
            const gayrpc::core::RpcError&)> LoginHandle;
        

    public:
        void echo(const dodo::test::EchoRequest& request,
            const EchoHandle& handle = nullptr)
        {
            call<dodo::test::EchoResponse>(request, static_cast<uint64_t>(EchoServerMsgID::echo), handle);
        }
        void login(const dodo::test::LoginRequest& request,
            const LoginHandle& handle = nullptr)
        {
            call<dodo::test::LoginResponse>(request, static_cast<uint64_t>(EchoServerMsgID::login), handle);
        }
        

         dodo::test::EchoResponse sync_echo(const dodo::test::EchoRequest& request,
            gayrpc::core::RpcError& error)
        {
                auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
                auto responsePromise = std::make_shared<std::promise<dodo::test::EchoResponse>>();

                echo(request, [responsePromise, errorPromise](const dodo::test::EchoResponse& response,
                    const gayrpc::core::RpcError& error) {
                    errorPromise->set_value(error);
                    responsePromise->set_value(response);
                });

                error = errorPromise->get_future().get();
                return responsePromise->get_future().get();
        }
         dodo::test::LoginResponse sync_login(const dodo::test::LoginRequest& request,
            gayrpc::core::RpcError& error)
        {
                auto errorPromise = std::make_shared<std::promise<gayrpc::core::RpcError>>();
                auto responsePromise = std::make_shared<std::promise<dodo::test::LoginResponse>>();

                login(request, [responsePromise, errorPromise](const dodo::test::LoginResponse& response,
                    const gayrpc::core::RpcError& error) {
                    errorPromise->set_value(error);
                    responsePromise->set_value(response);
                });

                error = errorPromise->get_future().get();
                return responsePromise->get_future().get();
        }
        

    public:
        static PTR Create(const RpcTypeHandleManager::PTR& rpcHandlerManager,
            const UnaryServerInterceptor& outboundInterceptor,
            const UnaryServerInterceptor& inboundInterceptor)
        {
            struct make_shared_enabler : public EchoServerClient
            {
            public:
                make_shared_enabler(const UnaryServerInterceptor& outboundInterceptor,
                    const UnaryServerInterceptor& inboundInterceptor)
                    : 
                    EchoServerClient(outboundInterceptor, inboundInterceptor) {}
            };

            auto client = PTR(new make_shared_enabler(outboundInterceptor, inboundInterceptor));
            client->installResponseStub(rpcHandlerManager);

            return client;
        }

    private:
        using BaseClient::BaseClient;
    };

    typedef TemplateReply<dodo::test::EchoResponse> EchoReply;
    typedef TemplateReply<dodo::test::LoginResponse> LoginReply;
    

    class EchoServerService : public BaseService
    {
    public:
        typedef std::shared_ptr<EchoServerService> PTR;
        virtual ~EchoServerService()
        {
        }

        virtual void onClose() {}

    private:
        virtual bool echo(const dodo::test::EchoRequest& request, 
            const EchoReply::PTR& replyObj) = 0;
        virtual bool login(const dodo::test::LoginRequest& request, 
            const LoginReply::PTR& replyObj) = 0;
        

    private:
        friend  void registerEchoServerService(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor);

        static bool echo_stub(const RpcMeta& meta,
            const std::string& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            dodo::test::EchoRequest request;
            
            switch (meta.encoding())
            {
            case RpcMeta::BINARY:
                if (!request.ParseFromString(data))
                {
                    std::cerr << "parse binary EchoRequst error " << std::endl;
                    return false;
                }
                break;
            case RpcMeta::JSON:
                {
                    auto s = JsonStringToMessage(data, &request);
                    if (!s.ok())
                    {
                        throw std::runtime_error("parse json EchoRequst failed:" +
                            s.error_message().as_string());
                    }
                }
                break;
            default:
                std::cerr << "parse EchoRequst of unspported encoding type:" << meta.encoding() << std::endl;
                return false;
            }

            inboundInterceptor(meta,
                request,
                [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message) {
                auto replyObject = std::make_shared<EchoReply>(meta, outboundInterceptor);
                service->echo(request, replyObject);
            });
            return true;
        }
        static bool login_stub(const RpcMeta& meta,
            const std::string& data,
            const EchoServerService::PTR& service,
            const UnaryServerInterceptor& inboundInterceptor,
            const UnaryServerInterceptor& outboundInterceptor)
        {
            dodo::test::LoginRequest request;
            
            switch (meta.encoding())
            {
            case RpcMeta::BINARY:
                if (!request.ParseFromString(data))
                {
                    std::cerr << "parse binary LoginRequst error " << std::endl;
                    return false;
                }
                break;
            case RpcMeta::JSON:
                {
                    auto s = JsonStringToMessage(data, &request);
                    if (!s.ok())
                    {
                        throw std::runtime_error("parse json LoginRequst failed:" +
                            s.error_message().as_string());
                    }
                }
                break;
            default:
                std::cerr << "parse LoginRequst of unspported encoding type:" << meta.encoding() << std::endl;
                return false;
            }

            inboundInterceptor(meta,
                request,
                [service,
                outboundInterceptor,
                &request](const RpcMeta& meta, const google::protobuf::Message& message) {
                auto replyObject = std::make_shared<LoginReply>(meta, outboundInterceptor);
                service->login(request, replyObject);
            });
            return true;
        }
        
    };

    inline void registerEchoServerService(gayrpc::core::RpcTypeHandleManager::PTR rpcTypeHandleManager,
        const EchoServerService::PTR& service,
        const UnaryServerInterceptor& inboundInterceptor,
        const UnaryServerInterceptor& outboundInterceptor)
    {
        typedef std::function<bool(const RpcMeta&,
            const std::string& data,
            const EchoServerService::PTR&,
            const UnaryServerInterceptor&,
            const UnaryServerInterceptor&)> EchoServerServiceRequestHandler;

        typedef std::unordered_map<uint64_t, EchoServerServiceRequestHandler> EchoServerServiceHandlerMapById;
        typedef std::unordered_map<std::string, EchoServerServiceRequestHandler> EchoServerServiceHandlerMapByStr;

        // TODO::这里不应该每一次注册都构造一个单独的map,应该此服务的所有服务对象共享这两个map
        auto serviceHandlerMapById = std::make_shared<EchoServerServiceHandlerMapById>();
        auto serviceHandlerMapByStr = std::make_shared<EchoServerServiceHandlerMapByStr>();

        std::string namespaceStr = "dodo.test.";

        // TODO::避免method.MethodName默认为小写开头，而是需要和proto里定义的函数名称完全一致
        (*serviceHandlerMapById)[static_cast<uint64_t>(EchoServerMsgID::echo)] = EchoServerService::echo_stub;
        (*serviceHandlerMapById)[static_cast<uint64_t>(EchoServerMsgID::login)] = EchoServerService::login_stub;
        
        (*serviceHandlerMapByStr)[namespaceStr+"EchoServer.echo"] = EchoServerService::echo_stub;
        (*serviceHandlerMapByStr)[namespaceStr+"EchoServer.login"] = EchoServerService::login_stub;
        

        auto requestStub = [service,
            serviceHandlerMapById,
            serviceHandlerMapByStr,
            inboundInterceptor,
            outboundInterceptor](const RpcMeta& meta, const std::string& data) {
            
            if (meta.type() != RpcMeta::REQUEST)
            {
                return false;
            }
            
            EchoServerServiceRequestHandler handler;

            if (!meta.request_info().strmethod().empty())
            {
                auto it = serviceHandlerMapByStr->find(meta.request_info().strmethod());
                if (it == serviceHandlerMapByStr->end())
                {
                    std::cerr << "not found handle, method:" << meta.request_info().strmethod();
                    return false;
                }
                handler = (*it).second;
            }
            else
            {
                auto it = serviceHandlerMapById->find(meta.request_info().intmethod());
                if (it == serviceHandlerMapById->end())
                {
                    std::cerr << "not found handle, method:" << meta.request_info().intmethod();
                    return false;
                }
                handler = (*it).second;
            }

            return handler(meta,
                data,
                service,
                inboundInterceptor,
                outboundInterceptor);
        };
        rpcTypeHandleManager->registerTypeHandle(RpcMeta::REQUEST, requestStub);
    }
    
}

}
}

#endif

