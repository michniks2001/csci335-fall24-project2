#pragma once

#include <iostream>
#include <stdexcept> 

class InvalidFormatException : public std::runtime_error {    
   public: 
         InvalidFormatException() : runtime_error("Something bad happened.") {} 
         InvalidFormatException(const std::string& error_message) : runtime_error(error_message) {} 
}; 