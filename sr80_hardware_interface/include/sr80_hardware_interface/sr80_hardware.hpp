/**
 * @file sr80_hardware.hpp
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SR80_HARDWARE_INTERFACE__SR80_HARDWARE_HPP
#define SR80_HARDWARE_INTERFACE__SR80_HARDWARE_HPP

#include <hardware_interface/handle.hpp>
#include <hardware_interface/hardware_info.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <hardware_interface/system_interface.hpp>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/state.hpp>
#include <class_list_macros.hpp>

#include <vector>

#include "sr80_hardware_interface/visibility_control.h"

namespace sr80_hardware
{

    struct JointValues
    {
        double position{0.0};
        double velocity{0.0};
        double effort{0.0};
        double acceleration{0.0};
    };

    struct Joint
    {
        std::string name;
        JointValues states{};
        JointValues commands{};
    };

    class SR80Hardware : public hardware_interface::SystemInterface
    {
        public:

        RCLCPP_SHARED_PTR_DEFINITIONS(SR80Hardware);

        SR80_HARDWARE_PUBLIC
        hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo& info) override;

        SR80_HARDWARE_PUBLIC
        std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

        SR80_HARDWARE_PUBLIC
        std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

        SR80_HARDWARE_PUBLIC
        hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State& previous_state) override;

        SR80_HARDWARE_PUBLIC
        hardware_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State& previous_state) override;

        SR80_HARDWARE_PUBLIC
        hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State& previous_state) override;

        //SR80_HARDWARE_PUBLIC
        //hardware_interface::CallbackReturn on_error(const rclcpp_lifecycle::State& previous_state) override;
        
        SR80_HARDWARE_PUBLIC
        hardware_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State& previous_state) override;

        SR80_HARDWARE_PUBLIC
        hardware_interface::return_type read(const rclcpp::Time& time, const rclcpp::Duration& period) override;

        SR80_HARDWARE_PUBLIC
        hardware_interface::return_type write(const rclcpp::Time& time, const rclcpp::Duration& period) override; 

        private:

        std::vector<Joint> m_Joints;

    };

} // End of namespace sr80_hardware


#endif // SR80_HARDWARE_INTERFACE__SR80_HARDWARE_HPP