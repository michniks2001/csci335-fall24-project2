#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cstdint>
#include "InvalidFormatException.hpp"

class File {
   private:
      std::string filename_;
      std::string contents_;
      int* icon_;

      static const size_t ICON_DIM = 256; // Representing a 16 x 16 bitmap

   public: 
      /**
      * @brief Constructs a new File object.
      * 
      * @param filename A string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
      *    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
      *    - If no extension is provided (eg. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
      *    - Default value of "NewFile.txt" if none provided or if filename is empty 
      * @param contents A string representing the contents of the file.
      * @param icon A poointer to an integer array with length ICON_DIM
      * @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
      */
      File(const std::string& filename = "NewFile.txt", const std::string& contents = "", int* icon = nullptr);

      /**
       * @brief Enables printing the object via std::cout
       */
      friend std::ostream& operator<< (std::ostream& os, const File& target);

      /**
       * @brief Overloads the less than comparison operator. 
       * @return True if the name of the File alphabetically precedes the name of the rhs. False otherwise.
       */
      bool operator<(const File& rhs) const;

      /**
       * @brief Get the value stored in name_
       * 
       * @return std::string 
       */
      std::string getName() const;
      
      /**
       * @brief Get the value of contents_
       */
      std::string getContents() const;

      /**
      * @brief Calculates and returns the size of the File Object (in bytes)
      *    by summing the size of the file's content member using sizeOf()
      * @note How does this relate to the string's length?
      */
      size_t getSize() const;

      /**
       * @brief Gets the value of the icon_ member
       */
      int* getIcon() const;

      /**
       * @brief Sets the value of icon_ to the given parameter. De-allocates the prevous array if necessary.
       * @param new_icon A pointer to a length 256 (ie. ICON_DIM) array of unsigned 8 bit integers
       */
      void setIcon(int* new_icon); 


      /**
       * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
       */
      File(const File& rhs);

      /**
       * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
       * 
       * @param rhs The File object to be copied
       * @note If copy assignment operator is invoked upon itself, do nothing.
       */
      File& operator=(const File& rhs);

      /**
       * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
       * @param rhs The File whose data is moved
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are moved.
       *    - ALl pointers are set to nullptr
       */
      File(File&& rhs);

      /**
       * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
       * 
       * @param rhs The File whose data is moved
       * @return File& A reference to the current object
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are moved.
       *    - ALl pointers are set to nullptr
       * @note If move assignment operator is invoked upon itself, do nothing.
       */
      File& operator=(File&& rhs);

      // Destructor
      ~File();
};