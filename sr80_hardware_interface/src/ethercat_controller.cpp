/**
 * @file ethercat_controller.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "sr80_hardware_interface/ethercat_controller.hpp"

namespace sr80_hardware
{
    namespace ethercat
    {
        Controller::Controller()
        {

        }

        bool Controller::setCyclicTaskRT()
        {
            if(pthread_setschedparam(m_CyclikTaskThread.native_handle(), m_ThreadInfo.m_ThreadPolicy, &m_ThreadInfo.m_SchedParam))
            {
                return false;
            }

            return true;
        }
    }
}