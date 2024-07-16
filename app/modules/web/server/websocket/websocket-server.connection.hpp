#ifndef _WEBSOCKET_SERVER_CONNECTION_HPP_
#define _WEBSOCKET_SERVER_CONNECTION_HPP_

#include <oatpp/oatpp-websocket/AsyncWebSocket.hpp>
#include <oatpp/core/async/Executor.hpp>
#include <oatpp/core/async/Lock.hpp>
#include <oatpp/core/macro/component.hpp>
#include <core/elements/uuid.element.hpp>
#include <utils/logger/console.logger.hpp>
namespace Wasp
{
    class WSServerApplication; // FWD

    class WSServerConnection : public oatpp::websocket::AsyncWebSocket::Listener, public Wasp::UUIDElement
    {
    private:
        /**
         * Buffer for messages. Needed for multi-frame messages.
         */
        oatpp::data::stream::BufferOutputStream m_messageBuffer;

        /**
         * Lock for synchronization of writes to the web socket.
         */
        oatpp::async::Lock m_writeLock;

    private:
        std::shared_ptr<AsyncWebSocket> m_socket;
        std::shared_ptr<WSServerApplication> m_application;
        oatpp::String m_name;
        v_int32 m_connectionId;

    private:
        /**
         * Inject async executor object.
         */
        OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, m_asyncExecutor);

    public:
        WSServerConnection(const std::shared_ptr<AsyncWebSocket> &socket,
                           const std::shared_ptr<WSServerApplication> &application,
                           const oatpp::String &name,
                           v_int32 connectionId)
            : m_socket(socket), m_application(application), m_name(name), m_connectionId(connectionId)
        {
        }

        /**
         * Send message to peer (to user).
         * @param message
         */
        void sendMessage(const oatpp::String &message)
        {
            class SendMessageCoroutine : public oatpp::async::Coroutine<SendMessageCoroutine>
            {
            private:
                oatpp::async::Lock *m_lock;
                std::shared_ptr<AsyncWebSocket> m_websocket;
                oatpp::String m_message;

            public:
                SendMessageCoroutine(oatpp::async::Lock *lock,
                                     const std::shared_ptr<AsyncWebSocket> &websocket,
                                     const oatpp::String &message)
                    : m_lock(lock), m_websocket(websocket), m_message(message)
                {
                }

                Action act() override
                {
                    return oatpp::async::synchronize(m_lock, m_websocket->sendOneFrameTextAsync(m_message)).next(finish());
                }
            };

            m_asyncExecutor->execute<SendMessageCoroutine>(&m_writeLock, m_socket, message);
        };

        /**
         * Get room of the peer.
         * @return
         */
        std::shared_ptr<WSServerApplication> getApplication()
        {
            return m_application;
        };

        /**
         * Get peer nickname.
         * @return
         */
        oatpp::String getName()
        {
            return m_name;
        };

        /**
         * Get peer userId.
         * @return
         */
        v_int32 getConnectionId()
        {
            return m_connectionId;
        };

    public: // WebSocket Listener methods
        CoroutineStarter onPing(const std::shared_ptr<AsyncWebSocket> &socket, const oatpp::String &message) override
        {
            return oatpp::async::synchronize(&m_writeLock, socket->sendPongAsync(message));
        };
        CoroutineStarter onPong(const std::shared_ptr<AsyncWebSocket> &socket, const oatpp::String &message) override
        {
            return nullptr; // do nothing
        };
        CoroutineStarter onClose(const std::shared_ptr<AsyncWebSocket> &socket, v_uint16 code, const oatpp::String &message) override
        {
            return nullptr; // do nothing
        };
        CoroutineStarter readMessage(const std::shared_ptr<AsyncWebSocket> &socket, v_uint8 opcode, p_char8 data, oatpp::v_io_size size) override
        {
            if (size == 0)
            { // message transfer finished

                auto wholeMessage = m_messageBuffer.toString();
                m_messageBuffer.setCurrentPosition(0);
                Wasp::Logger::ConsoleLogger::STATIC_LOG(("Message Received From [" + *m_name.get() + "]: " + *wholeMessage.get()).c_str());
                this->sendMessage("Message " + wholeMessage + " Received!");
                // m_application->sendMessage(m_name + ": " + wholeMessage);
            }
            else if (size > 0)
            { // message frame received
                m_messageBuffer.writeSimple(data, size);
            }

            return nullptr; // do nothing
        };
    };
};

#endif // !_WEBSOCKET_CONNECTION_HPP_
