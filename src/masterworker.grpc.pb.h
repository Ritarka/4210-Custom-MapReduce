// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: masterworker.proto
#ifndef GRPC_masterworker_2eproto__INCLUDED
#define GRPC_masterworker_2eproto__INCLUDED

#include "masterworker.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace masterworker {

// To communicate between master and worker node, we will use gRPC
class MasterWorker final {
 public:
  static constexpr char const* service_full_name() {
    return "masterworker.MasterWorker";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // for map
    virtual ::grpc::Status AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::masterworker::TaskCompletion* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>> AsyncAssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>>(AsyncAssignMapTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>> PrepareAsyncAssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>>(PrepareAsyncAssignMapTaskRaw(context, request, cq));
    }
    // for reduce
    virtual ::grpc::Status AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::masterworker::TaskCompletion* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>> AsyncAssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>>(AsyncAssignReduceTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>> PrepareAsyncAssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>>(PrepareAsyncAssignReduceTaskRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // for map
      virtual void AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response, std::function<void(::grpc::Status)>) = 0;
      virtual void AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // for reduce
      virtual void AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response, std::function<void(::grpc::Status)>) = 0;
      virtual void AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>* AsyncAssignMapTaskRaw(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>* PrepareAsyncAssignMapTaskRaw(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>* AsyncAssignReduceTaskRaw(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::masterworker::TaskCompletion>* PrepareAsyncAssignReduceTaskRaw(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::masterworker::TaskCompletion* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>> AsyncAssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>>(AsyncAssignMapTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>> PrepareAsyncAssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>>(PrepareAsyncAssignMapTaskRaw(context, request, cq));
    }
    ::grpc::Status AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::masterworker::TaskCompletion* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>> AsyncAssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>>(AsyncAssignReduceTaskRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>> PrepareAsyncAssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>>(PrepareAsyncAssignReduceTaskRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response, std::function<void(::grpc::Status)>) override;
      void AssignMapTask(::grpc::ClientContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response, ::grpc::ClientUnaryReactor* reactor) override;
      void AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response, std::function<void(::grpc::Status)>) override;
      void AssignReduceTask(::grpc::ClientContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>* AsyncAssignMapTaskRaw(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>* PrepareAsyncAssignMapTaskRaw(::grpc::ClientContext* context, const ::masterworker::MapTask& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>* AsyncAssignReduceTaskRaw(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::masterworker::TaskCompletion>* PrepareAsyncAssignReduceTaskRaw(::grpc::ClientContext* context, const ::masterworker::ReduceTask& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_AssignMapTask_;
    const ::grpc::internal::RpcMethod rpcmethod_AssignReduceTask_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // for map
    virtual ::grpc::Status AssignMapTask(::grpc::ServerContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response);
    // for reduce
    virtual ::grpc::Status AssignReduceTask(::grpc::ServerContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssignMapTask(::grpc::ServerContext* context, ::masterworker::MapTask* request, ::grpc::ServerAsyncResponseWriter< ::masterworker::TaskCompletion>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssignReduceTask(::grpc::ServerContext* context, ::masterworker::ReduceTask* request, ::grpc::ServerAsyncResponseWriter< ::masterworker::TaskCompletion>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_AssignMapTask<WithAsyncMethod_AssignReduceTask<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::masterworker::MapTask, ::masterworker::TaskCompletion>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::masterworker::MapTask* request, ::masterworker::TaskCompletion* response) { return this->AssignMapTask(context, request, response); }));}
    void SetMessageAllocatorFor_AssignMapTask(
        ::grpc::MessageAllocator< ::masterworker::MapTask, ::masterworker::TaskCompletion>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::masterworker::MapTask, ::masterworker::TaskCompletion>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AssignMapTask(
      ::grpc::CallbackServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::masterworker::ReduceTask, ::masterworker::TaskCompletion>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::masterworker::ReduceTask* request, ::masterworker::TaskCompletion* response) { return this->AssignReduceTask(context, request, response); }));}
    void SetMessageAllocatorFor_AssignReduceTask(
        ::grpc::MessageAllocator< ::masterworker::ReduceTask, ::masterworker::TaskCompletion>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::masterworker::ReduceTask, ::masterworker::TaskCompletion>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AssignReduceTask(
      ::grpc::CallbackServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_AssignMapTask<WithCallbackMethod_AssignReduceTask<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssignMapTask(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAssignReduceTask(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->AssignMapTask(context, request, response); }));
    }
    ~WithRawCallbackMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AssignMapTask(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->AssignReduceTask(context, request, response); }));
    }
    ~WithRawCallbackMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AssignReduceTask(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_AssignMapTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_AssignMapTask() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::masterworker::MapTask, ::masterworker::TaskCompletion>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::masterworker::MapTask, ::masterworker::TaskCompletion>* streamer) {
                       return this->StreamedAssignMapTask(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_AssignMapTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status AssignMapTask(::grpc::ServerContext* /*context*/, const ::masterworker::MapTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAssignMapTask(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::masterworker::MapTask,::masterworker::TaskCompletion>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_AssignReduceTask : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_AssignReduceTask() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::masterworker::ReduceTask, ::masterworker::TaskCompletion>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::masterworker::ReduceTask, ::masterworker::TaskCompletion>* streamer) {
                       return this->StreamedAssignReduceTask(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_AssignReduceTask() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status AssignReduceTask(::grpc::ServerContext* /*context*/, const ::masterworker::ReduceTask* /*request*/, ::masterworker::TaskCompletion* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAssignReduceTask(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::masterworker::ReduceTask,::masterworker::TaskCompletion>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_AssignMapTask<WithStreamedUnaryMethod_AssignReduceTask<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_AssignMapTask<WithStreamedUnaryMethod_AssignReduceTask<Service > > StreamedService;
};

}  // namespace masterworker


#endif  // GRPC_masterworker_2eproto__INCLUDED