// ======================================================================
// \title  TcpClient/test/ut/Tester.hpp
// \author mstarch
// \brief  hpp file for ByteStreamDriverModel test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "TcpClientGTestBase.hpp"
#include "Drv/TcpClient/TcpClientComponentImpl.hpp"
#include "Drv/Ip/TcpServerSocket.hpp"

#define SEND_DATA_BUFFER_SIZE 1024

namespace Drv {

  class TcpClientTester :
    public TcpClientGTestBase
  {
      // Maximum size of histories storing events, telemetry, and port outputs
      static const NATIVE_INT_TYPE MAX_HISTORY_SIZE = 1000;
      // Instance ID supplied to the component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_ID = 0;
      // Queue depth supplied to component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_QUEUE_DEPTH = 100;

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object TcpClientTester
      //!
      TcpClientTester();

      //! Destroy object TcpClientTester
      //!
      ~TcpClientTester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      void setup_helper(Drv::TcpServerSocket& server, Drv::SocketDescriptor& server_fd, bool recv_thread, bool reconnect);

      void test_basic_messaging();

      void test_multiple_messaging();

      void test_receive_thread();

      void test_advanced_reconnect();

      void test_no_automatic_send_connection();

      void test_no_automatic_recv_connection();

      void test_with_loop(U32 iterations, bool recv_thread=false);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_recv
      //!
      void from_recv_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &recvBuffer,
          const RecvStatus &recvStatus
      );

      //! Handler for from_ready
      //!
      void from_ready_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler for from_allocate
      //!
      Fw::Buffer from_allocate_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U32 size
      );

      //! Handler for from_deallocate
      //!
      void from_deallocate_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer &fwBuffer
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      bool wait_on_change(Drv::IpSocket &socket, bool open, U32 iterations);

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      TcpClientComponentImpl component;
      Fw::Buffer m_data_buffer;
      Fw::Buffer m_data_buffer2;
      U8 m_data_storage[SEND_DATA_BUFFER_SIZE];
      std::atomic<bool> m_spinner;

  };

} // end namespace Drv

#endif
