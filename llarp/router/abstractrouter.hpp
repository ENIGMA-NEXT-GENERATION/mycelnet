#ifndef LLARP_ABSTRACT_ROUTER_HPP
#define LLARP_ABSTRACT_ROUTER_HPP

#include <util/types.hpp>

#include <vector>

struct llarp_buffer_t;
struct llarp_dht_context;
struct llarp_ev_loop;
struct llarp_nodedb;
struct llarp_threadpool;

namespace llarp
{
  struct Crypto;
  class Logic;
  struct RouterContact;
  struct RouterID;
  struct ILinkMessage;
  struct ILinkSession;
  struct PathID_t;
  struct Profiling;
  struct SecretKey;
  struct Signature;

  namespace exit
  {
    struct Context;
  }

  namespace path
  {
    struct PathContext;
  }

  namespace routing
  {
    struct IMessageHandler;
  }

  struct AbstractRouter
  {
    virtual ~AbstractRouter() = 0;

    virtual void
    OnSessionEstablished(RouterContact rc) = 0;

    virtual bool
    HandleRecvLinkMessageBuffer(ILinkSession *from,
                                const llarp_buffer_t &msg) = 0;

    virtual Logic *
    logic() const = 0;

    virtual llarp_dht_context *
    dht() const = 0;

    virtual Crypto *
    crypto() const = 0;

    virtual llarp_nodedb *
    nodedb() const = 0;

    virtual const path::PathContext &
    pathContext() const = 0;

    virtual path::PathContext &
    pathContext() = 0;

    virtual const RouterContact &
    rc() const = 0;

    virtual exit::Context &
    exitContext() = 0;

    virtual const SecretKey &
    identity() const = 0;

    virtual const SecretKey &
    encryption() const = 0;

    virtual Profiling &
    routerProfiling() = 0;

    virtual llarp_ev_loop *
    netloop() const = 0;

    virtual llarp_threadpool *
    threadpool() = 0;

    virtual llarp_threadpool *
    diskworker() = 0;

    virtual bool
    Sign(Signature &sig, const llarp_buffer_t &buf) const = 0;

    virtual const byte_t *
    pubkey() const = 0;

    virtual void
    OnConnectTimeout(ILinkSession *session) = 0;

    /// called by link when a remote session has no more sessions open
    virtual void
    SessionClosed(RouterID remote) = 0;

    virtual llarp_time_t
    Now() const = 0;

    virtual bool
    GetRandomGoodRouter(RouterID &r) = 0;

    virtual bool
    SendToOrQueue(const RouterID &remote, const ILinkMessage *msg) = 0;

    virtual void
    PersistSessionUntil(const RouterID &remote, llarp_time_t until) = 0;

    virtual bool
    ParseRoutingMessageBuffer(const llarp_buffer_t &buf,
                              routing::IMessageHandler *h,
                              const PathID_t &rxid) = 0;

    virtual size_t
    NumberOfConnectedRouters() const = 0;

    virtual bool
    GetRandomConnectedRouter(RouterContact &result) const = 0;

    virtual void
    HandleDHTLookupForExplore(RouterID remote,
                              const std::vector< RouterContact > &results) = 0;

    /// check if newRc matches oldRC and update local rc for this remote contact
    /// if valid
    /// returns true on valid and updated
    /// returns false otherwise
    virtual bool
    CheckRenegotiateValid(RouterContact newRc, RouterContact oldRC) = 0;
  };
}  // namespace llarp

#endif
