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

    DataHandler::DataHandler()
    {

    }

    void DataHandler::writeToROS(const PdoData& data_to_write)
    {
        std::unique_lock<std::shared_mutex> ulk(m_HardwareDataMutex);
        m_HardwareDataQueue.push(std::move(data_to_write));
        ulk.unlock();
    }

    std::optional<PdoData> DataHandler::readFromROS()
    {
        std::shared_lock<std::shared_mutex> slk(m_RosDataMutex);

        if(m_RosDataQueue.empty())
        {
            return std::nullopt;
        }

        const PdoData pdoData = m_RosDataQueue.front();
        m_RosDataQueue.pop();
        
        slk.unlock();

        return pdoData;
    }

    void DataHandler::writeToHardware(const PdoData& data_to_write)
    {
        std::unique_lock<std::shared_mutex> ulk(m_RosDataMutex);
        m_RosDataQueue.push(std::move(data_to_write));
        ulk.unlock();
    }

    std::optional<PdoData> DataHandler::readFromHardware()
    {
        std::shared_lock<std::shared_mutex> shl(m_HardwareDataMutex);

        if(m_HardwareDataQueue.empty())
        {
            return std::nullopt;
        }

        const PdoData pdoData = m_HardwareDataQueue.front(); // Get the first PDO data from the queue.
        m_HardwareDataQueue.pop(); // Pop the queue.

        shl.unlock();

        return pdoData;
    }


}