/*
 * MapGenerator.cpp
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#include "MapGenerator.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

#include "../Console/Console.h"

namespace NS_NaviCommon
{
  bool
  MapGenerator::lock (int fd)
  {
    if (flock (fd, LOCK_EX) < 0)
    {
      return false;
    }
    return true;
  }

  bool
  MapGenerator::unlock (int fd)
  {
    if (flock (fd, LOCK_UN) < 0)
    {
      return false;
    }
    return true;
  }

  bool
  MapGenerator::saveMapInPGM (std::vector<char> map_data, int height, int width, std::string pgm_file)
  {
    int pgm_fd = open (pgm_file.c_str (), O_RDWR | O_CREAT);
    if (pgm_fd < 0)
    {
      console.debug ("Open file %s fail!", pgm_file.c_str ());
      return false;
    }
    
    if (!lock (pgm_fd))
    {
      console.debug ("Lock file %s fail!", pgm_file.c_str ());
      return false;
    }

    int resize_width = width;
    int resize_height = height;
    int pix255 = 255;
    int pix000 = 000;
    int pix099 = 99;
    int pix205 = 205;

    while ((resize_width % 4) != 0)
    {
      resize_width++;
    }

    while ((resize_height % 4) != 0)
    {
      resize_height++;
    }

    char meta_line[128] = {0};
    sprintf (meta_line, "P5\n%d %d\n255\n", resize_width, resize_height);
    write (pgm_fd, meta_line, sizeof (meta_line));

    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        int i = x + (height - y - 1) * width;
        if (map_data[i] == 0)
        { //occ [0,0.1)
          write (pgm_fd, &pix255, 1);
        }
        else if (map_data[i] == +100)
        { //occ (0.65,1]
          write (pgm_fd,&pix000, 1);
        }
        else if (map_data[i] == 99)
        {
          write (pgm_fd,&pix099, 1);
        }
        else
        { //occ [0.1,0.65]
          write (pgm_fd,&pix205, 1);
        }
      }
      for (int k = 0; k < (resize_width - width); k++)
      {
        write (pgm_fd, &pix000, 1);
      }
    }
    for (int y = 0; y < resize_height-height; y++)
    {
      for (int x = 0; x < resize_width; x++)
      {
        write (pgm_fd, &pix000, 1);
      }
    }

    unlock (pgm_fd);

    close (pgm_fd);

    return true;

  }
  
  bool
  MapGenerator::readMapFromPGM (std::string pgm_file, std::vector<char>& map_data, int& height, int& width)
  {
    int pgm_fd = open (pgm_file.c_str (), O_RDWR);
    if (pgm_fd < 0)
    {
      console.debug ("Open file %s fail!", pgm_file.c_str ());
      return false;
    }

    if (!lock (pgm_fd))
    {
      console.debug ("Lock file %s fail!", pgm_file.c_str ());
      return false;
    }

    char line[70] = {0};
    int max_val = 0;
    bool binary;
    int num_read = 0;
    int test, temp;

    while (read (pgm_fd, line, sizeof (line)) == 0)
      continue;

    while (line[0] == '#' || line[0] == '\n' || read (pgm_fd, line, sizeof (line)) == 0)
    {
      continue;
    }

    if ((line[0] == 'P') && (line[1] == '5'))
    {
      binary = true;
    }

    console.debug ("format: %c  %c", line[0], line[1]);


    while (read (pgm_fd, line, sizeof(line)) == 0)
      continue;

    sscanf (line, "%d %d", &width, &height);

    console.debug ("width:%d  height:%d", width, height);


    while (read (pgm_fd, line, sizeof(line))==0)
      continue;

    sscanf (line, "%d", &max_val);

    console.debug ("max value: %d", max_val);

    if (width < 1 || height < 1 || max_val < 0 || max_val > 256)
    {
      console.debug ("error picture!");
      return false;
    }
    else if (width > 2048 || height > 2048)
    {
      console.debug ("map is too large!");
      return false;
    }

    int size = width * height;

    map_data.resize (size);

    if (binary)
    {
      for (int i = 0; i < size; i++)
      {
        int flag = read (pgm_fd, &map_data[i], 1);
        if (flag == 0 || flag == -1)
          break;
      }
    }
    else
    {
      console.debug ("error format %d", binary);
      return false;
    }


    unlock (pgm_fd);

    close (pgm_fd);

    return true;

  }

  bool
  MapGenerator::addRobotPoseInMap (std::vector<char>& map_data, int map_height, int map_width, int robot_pose_x, int robot_pose_y)
  {
    for (int y = 0; y < map_height; y++)
    {
      for (int x = 0; x < map_width; x++)
      {
        int  k = x + (map_height - y - 1) * map_width;
        if(x == robot_pose_x && y == robot_pose_y)
        {
          map_data[k] = 99;
          return true;
        }
      }
    }
    return false;
  }

} /* namespace NS_NaviCommon */
