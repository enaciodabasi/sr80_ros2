/**
 * @file sr80_hardware.cpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "sr80_hardware_interface/sr80_hardware.hpp"

namespace sr80_hardware
{
    hardware_interface::CallbackReturn SR80Hardware::on_init(const hardware_interface::HardwareInfo& info)
    {
        RCLCPP_INFO(rclcpp::get_logger("SR80HardwareInterface"), "Configuring SR80 hardware interface.");

        if(hardware_interface::SystemInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS)
        {
            return hardware_interface::CallbackReturn::ERROR;
        }

        m_Joints.resize(
            info_.joints.size(),
            Joint()
        );

        for(std::size_t i = 0; i < info_.joints.size(); i++)
        {
            m_Joints[i].name = info_.joints[i].name;

            m_Joints[i].states.position = std::numeric_limits<double>::quiet_NaN();
            m_Joints[i].states.velocity = std::numeric_limits<double>::quiet_NaN();
            m_Joints[i].states.effort = std::numeric_limits<double>::quiet_NaN();

            m_Joints[i].commands.position = std::numeric_limits<double>::quiet_NaN();
            m_Joints[i].commands.velocity = std::numeric_limits<double>::quiet_NaN();
            m_Joints[i].commands.effort = std::numeric_limits<double>::quiet_NaN();
            m_Joints[i].commands.acceleration = std::numeric_limits<double>::quiet_NaN();

        }

        return hardware_interface::CallbackReturn::SUCCESS;
    }

    std::vector<hardware_interface::StateInterface> SR80Hardware::export_state_interfaces()
    {
        RCLCPP_INFO_ONCE(rclcpp::get_logger("SR80HardwareInterface"), "Exporting state interfaces.");

        std::vector<hardware_interface::StateInterface> stateInterfaces;

        for(std::size_t i = 0; i < info_.joints.size(); i++)
        {
            stateInterfaces.emplace_back(
                hardware_interface::StateInterface{
                    info_.joints[i].name,
                    hardware_interface::HW_IF_POSITION,
                    &m_Joints[i].states.position
                }
            );          

            stateInterfaces.emplace_back(
                hardware_interface::StateInterface{
                    info_.joints[i].name,
                    hardware_interface::HW_IF_VELOCITY,
                    &m_Joints[i].states.velocity
                }
            );

            stateInterfaces.emplace_back(
                hardware_interface::StateInterface{
                    info_.joints[i].name,
                    hardware_interface::HW_IF_EFFORT,
                    &m_Joints[i].states.effort
                }
            );
        }   

        return stateInterfaces;
    }

    std::vector<hardware_interface::CommandInterface> SR80Hardware::export_command_interfaces()
    {
        std::vector<hardware_interface::CommandInterface> commandInterfaces;

        for(std::size_t i = 0; i < info_.joints.size(); i++)
        {
            commandInterfaces.emplace_back(
                hardware_interface::CommandInterface(
                    info_.joints[i].name, hardware_interface::HW_IF_POSITION, &m_Joints[i].commands.position
                )
            );

            commandInterfaces.emplace_back(
                hardware_interface::CommandInterface(
                    info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &m_Joints[i].commands.velocity
                )
            );

            commandInterfaces.emplace_back(
                hardware_interface::CommandInterface(
                    info_.joints[i].name, hardware_interface::HW_IF_EFFORT, &m_Joints[i].commands.effort
                )
            );

            commandInterfaces.emplace_back(
                hardware_interface::CommandInterface(
                    info_.joints[i].name, hardware_interface::HW_IF_ACCELERATION, &m_Joints[i].commands.acceleration
                )
            );
        }

        return commandInterfaces;
    }

    // Definition of the rclcpp_lifecycle state functions:

    hardware_interface::CallbackReturn SR80Hardware::on_configure(const rclcpp_lifecycle::State& previous_state)
    {
        // Configure EtherCAT controller.

        return hardware_interface::CallbackReturn::SUCCESS;
    }

    hardware_interface::CallbackReturn SR80Hardware::on_activate(const rclcpp_lifecycle::State& previous_state)
    {
        for(std::size_t i = 0; i < m_Joints.size(); i++)
        {
            auto& joint = m_Joints[i];

            if(std::isnan(joint.states.position))
            {
                joint.states.position = 0.0;
            }
            if(std::isnan(joint.states.velocity))
            {
                joint.states.velocity = 0.0;
            }
            if(std::isnan(joint.states.effort))
            {
                joint.states.effort = 0.0;
            }

            if(std::isnan(joint.commands.position))
            {
                joint.commands.position = 0.0;
            }
            if(std::isnan(joint.commands.velocity))
            {
                joint.commands.velocity = 0.0;
            }
            if(std::isnan(joint.commands.effort))
            {
                joint.commands.effort = 0.0;
            }
            if(std::isnan(joint.commands.acceleration))
            {
                joint.commands.acceleration = 0.0;
            }
            
        }

        // Activate EtherCAT master.

        return hardware_interface::CallbackReturn::SUCCESS;
    }

    hardware_interface::CallbackReturn SR80Hardware::on_deactivate(const rclcpp_lifecycle::State& previous_state)
    {
        return hardware_interface::CallbackReturn::SUCCESS;
    }

    hardware_interface::CallbackReturn SR80Hardware::on_shutdown(const rclcpp_lifecycle::State& previous_state)
    {
        return hardware_interface::CallbackReturn::SUCCESS;
    }

    
}

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(sr80_hardware::SR80Hardware, hardware_interface::SystemInterface)