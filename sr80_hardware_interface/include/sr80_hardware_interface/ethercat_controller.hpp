/**
 * @file ethercat_controller.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SR80_HARDWARE_INTERFACE__ETHERCAT_CONTROLLER_HPP
#define SR80_HARDWARE_INTERFACE__ETHERCAT_CONTROLLER_HPP

// TODO: Replace all EtherCAT-Interface includes with a single header file.
#include "master.hpp"
#include "domain.hpp"
#include "slave.hpp"

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <optional>
#include <atomic>

#include <pthread.h>


#ifdef ENABLE_DC

extern "C"
{
    #include "dc_sync.h"
}

#endif 

namespace sr80_hardware
{
    struct PdoData
    {
        
    };

    class DataHandler
    {
        public:

        Data();

        void writeToROS(const PdoData& data_to_write);

        std::optional<PdoData> readFromROS();

        void writeToHardware(const PdoData& data_to_write);

        std::optional<PdoData> readFromHardware();

        private:
        
        std::queue<PdoData> m_HardwareDataQueue;

        std::queue<PdoData> m_RosDataQueue;

        std::shared_mutex m_RosDataMutex;

        std::shared_mutex m_HardwareDataMutex;

    };
    
    namespace ethercat
    {   
        class Controller
        {
            public: 

            Controller();

            DataHandler m_DataHandler;

            inline void changeThreadParams(
                int thread_policy,
                int thread_priority
            )
            {
                m_ThreadInfo.m_ThreadPolicy = thread_policy;
                m_ThreadInfo.m_ThreadPriority = thread_priority;
                m_ThreadInfo.m_SchedParam.sched_priority = m_ThreadInfo.m_ThreadPriority;
            }

            private:

            // Information about the cyclic task thread.
            std::thread m_CyclikTaskThread;
            struct
            {
                sched_param m_SchedParam;
                int m_ThreadPolicy = SCHED_FIFO;
                int m_ThreadPriority = 19;
            }m_ThreadInfo;

            bool setCyclicTaskRT();

        };
    }
}

#endif // SR80_HARDWARE_INTERFACE__ETHERCAT_CONTROLLER_HPP