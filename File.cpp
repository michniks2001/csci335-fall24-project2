#include "File.hpp"

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
File::File(const std::string& filename, const std::string& contents, int* icon) : filename_{""}, contents_{contents}, icon_{icon} {
   if (filename.empty()) { filename_ = "NewFile.txt"; return; }
   // Validate filename
   auto dot_position = filename.end();

   for (auto itr = filename.begin(); itr != filename.end(); ++itr) {
      const char& c = *itr;
      
      if (dot_position == filename.end() && c == '.') {
         // If the dot_position has not been set (ie. equals the end) and we encounter a period
         dot_position = itr;
      } else if (!std::isalnum(c)) {
         // We have found a non-alphanumeric character (including possibly *another* period by failing the first if-clause)
         throw InvalidFormatException("Invalid file name: " + filename);
      }
   }

   filename_ = std::string(filename.begin(), dot_position);
   
   if (filename.end() - dot_position <= 1) {
      // No period specified / no extension characters
      filename_ += ".txt";
   } else {
      filename_ += std::string(dot_position, filename.end());
   }   
}
      
/**

   * @brief Get the value stored in name_
   * 
   * @return std::string 
   */
std::string File::getName() const {
   return filename_;
}

/**
   * @brief Calculates and returns the size of the File Object (in bytes)
   *    by summing the size of the file's content member using sizeOf()
   * @note How does this relate to the string's length?
   */
size_t File::getSize() const {
   return contents_.size(); 
}

/**
   * @brief Get the value of contents_
   */
std::string File::getContents() const {
   return contents_;
}


/**
* @brief Gets the value of the icon_ member
*/
int* File::getIcon() const {
   return icon_;
}


/**
   * @brief Sets the value of icon_ to the given parameter. De-allocates the prevous array if necessary.
   * @param new_icon A pointer to an integer array of length ICON_DIM
   */
void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

/**
 * @brief Destroy the File object
 */
File::~File() {
   if (icon_) { delete[] icon_; }
}

/**
* @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
*/
File::File(const File& rhs) : filename_{rhs.getName()}, contents_{rhs.getContents()}, icon_{nullptr} {
   if (rhs.getIcon() == nullptr) { return; }
   
   // Create a deep copy of the icon array
   icon_ = new int[ICON_DIM];
   for (size_t pixel = 0; pixel < ICON_DIM; pixel++) {
      icon_[pixel] = rhs.icon_[pixel];
   }
}

/**
   * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File
   * @param rhs The File object to be copied
*/
File& File::operator=(const File& rhs) {
   // Check for self-assignment (otherwise we delete the icon and try to copy it. No bueno!)
   if (this == &rhs) { return *this; }

   filename_ = rhs.getName();
   contents_ = rhs.getContents();
   
   // Since we don't validate unique icons, we may unintentionally 
   // assign the same icon (via setter). Maybe (as pure hypothetical)
   // we have all of them as some default icon and need not create multiple copies
   if (icon_ == rhs.icon_) { return *this; }
   
   // If we can delete our icon, do so
   if (icon_) { 
      delete[] icon_; 
      icon_ = nullptr;
   }

   // If the to-be-copied object has an icon, make a deep copy (otherwise, we terminate now)
   if (rhs.getIcon() == nullptr) { return *this; }
   icon_ = new int[ICON_DIM];
   for (size_t pixel = 0; pixel < ICON_DIM; pixel++) {
      icon_[pixel] = rhs.icon_[pixel];
   }

   return *this;
}

/**
   * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
   * @param rhs The File whose data is moved
   * @post The rhs File object is left in a valid, but unspecified state ready to be deleted
   */
File::File(File&& rhs) : filename_{ std::move(rhs.filename_) }, contents_{ std::move(rhs.contents_) }, icon_{rhs.icon_} {
   rhs.icon_ = nullptr;
}

/**
   * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
   * 
   * @param rhs The File whose data is moved
   * @return File& A reference to the current object
   * @post The rhs File object is left in a valid, but unspecified state ready to be deleted
*/
File& File::operator=(File&& rhs) {
   // Check for self-assignment (otherwise errors occur when setting the icon member)
   if (this == &rhs) { return *this; }
   
   filename_ = std::move(rhs.filename_);
   contents_ = std::move(rhs.contents_);

   // Note! This is an edge case, but since we do not check for uniqueness when assigning a new icon
   // we may point two files to the same icon bitmap. So if we delete one, we delete both (no good!).

   if (icon_ && icon_ != rhs.icon_) {
      delete[] icon_;
      icon_ = nullptr;
   }
   
   icon_ = rhs.icon_;
   rhs.icon_ = nullptr;

   return *this;
}

/**
 * @brief For your convenience. Allows us to call 
 * std::cout << MyFileObject();
 * 
 * @param os An ostream to direct out contents to
 * @param target The target file whose contents are to be piped
 * @return std::ostream& A reference to the updated stream
 */
std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

/**
 * @brief Compaeres files based on their names, lexicographically
 */
bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}