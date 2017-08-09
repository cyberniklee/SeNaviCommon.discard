/*
 * MapGenerator.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef _MAPGENERATOR_H_
#define _MAPGENERATOR_H_

#include <vector>
#include <string>

namespace NS_NaviCommon
{
  
  class MapGenerator
  {
  public:
    static bool saveMapInPGM (std::vector<char> map_data, int height, int width, std::string pgm_file);
    static bool readMapFromPGM (std::string pgm_file, std::vector<char>& map_data, int& height, int& width);

    static bool addRobotPoseInMap (std::vector<char>& map_data, int map_height, int map_width, int robot_pose_x, int robot_pose_y);

  private:
    static bool lock (int fd);
    static bool unlock (int fd);
  };

} /* namespace NS_NaviCommon */

#endif /* MAPGENERATOR_MAPGENERATOR_H_ */
