#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>
#include <array>

const std::string ENGINE_ON = "EngineOn";
const std::string ENGINE_OFF = "EngineOff";
const std::string INFO = "Info";
const std::string SET_GEAR = "SetGear";
const std::string SET_SPEED = "SetSpeed";

const std::string FORWARD_DIRECTION = "forward";
const std::string BACKWARD_DIRECTION = "backward";
const std::string STANDING_DIRECTION = "standing still";

const std::string INFO_ENGINE = "Engine: ";
const std::string INFO_DIRECTION = "Direction: ";
const std::string INFO_SPEED = "Speed: ";
const std::string INFO_GEAR = "Gear: ";
const std::string INFO_ON = "on";
const std::string INFO_OFF = "off";

const std::string UNKNOWN_COMMAND = "Unknown command\n";
const std::string INVALID_COMMAND_ARGUMENT = "Invalid command argument\n";
const std::string INVALID_TURNOFF_ENGUINE = "Car must be stopped and in neutral gear\n";
const std::string INVALID_GEAR = "Invalid gear\n";
const std::string TURN_IF_NOT_RUNNING_ENGUINE = "Cannot set gear while engine is off\n";
const std::string UNSUITABLE_CURRENT_SPEED = "Unsuitable current speed\n";
const std::string CANT_REVERSE_WHILE_MOVING = "Cannot reverse while moving\n";
const std::string SPEED_CANT_BE_NEGATIVE = "Speed cannot be negative\n";
const std::string CANT_SET_SPEED_ENGUINE_OFF = "Cannot set speed while engine is off\n";
const std::string CANT_ACCELERATE_ON_NETURAL = "Cannot accelerate on neutral\n";
const std::string SPEED_OUT_OF_RANGE = "Speed is out of gear range\n";

enum Broadcast
{
  BACK = -1,
  ZERO,
  FIRST,
  SECOND,
  THIRD,
  FOURTH,
  FIFTH
};

const std::unordered_map<Broadcast, std::array<int, 2>> BROADCASTS = {
    {BACK, {0, 20}},
    {ZERO, {0, 0}},
    {FIRST, {0, 30}},
    {SECOND, {20, 50}},
    {THIRD, {30, 60}},
    {FOURTH, {40, 90}},
    {FIFTH, {50, 150}},
};

enum class COMMANDS
{
  ENGINE_ON_E = 0,
  ENGINE_OFF_E,
  INFO_E,
  SET_GEAR_E,
  SET_SPEED_E
};

const std::unordered_map<std::string, COMMANDS> commandHandlers = {
    {ENGINE_ON, COMMANDS::ENGINE_ON_E},
    {ENGINE_OFF, COMMANDS::ENGINE_OFF_E},
    {INFO, COMMANDS::INFO_E},
    {SET_GEAR, COMMANDS::SET_GEAR_E},
    {SET_SPEED, COMMANDS::SET_SPEED_E}};

#endif
