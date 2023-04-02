/**
 * @file visibility_control.h
 * @author Eren Naci Odabasi (enaciodabasi@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SR80_HARDWARE_INTERFACE__VISIBILITY_CONTROL_H_
#define SR80_HARDWARE_INTERFACE__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define SR80_HARDWARE_EXPORT __attribute__((dllexport))
#define SR80_HARDWARE_IMPORT __attribute__((dllimport))
#else
#define SR80_HARDWARE_EXPORT __declspec(dllexport)
#define SR80_HARDWARE_IMPORT __declspec(dllimport)
#endif
#ifdef SR80_HARDWARE_BUILDING_DLL
#define SR80_HARDWARE_PUBLIC SR80_HARDWARE_EXPORT
#else
#define SR80_HARDWARE_PUBLIC SR80_HARDWARE_IMPORT
#endif
#define SR80_HARDWARE_PUBLIC_TYPE SR80_HARDWARE_PUBLIC
#define SR80_HARDWARE_LOCAL
#else
#define SR80_HARDWARE_EXPORT __attribute__((visibility("default")))
#define SR80_HARDWARE_IMPORT
#if __GNUC__ >= 4
#define SR80_HARDWARE_PUBLIC __attribute__((visibility("default")))
#define SR80_HARDWARE_LOCAL __attribute__((visibility("hidden")))
#else
#define SR80_HARDWARE_PUBLIC
#define SR80_HARDWARE_LOCAL
#endif
#define SR80_HARDWARE_PUBLIC_TYPE
#endif

#endif // SR80_HARDWARE_INTERFACE__VISIBILITY_CONTROL_H_