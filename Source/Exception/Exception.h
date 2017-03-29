/*
 * Copyright (C) 2009, Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <stdexcept>
#include "../Parameter/XMLParser.h"

namespace NS_NaviCommon
{
  
  class Exception: public std::runtime_error
  {
  public:
    Exception (const std::string& what)
        : std::runtime_error (what)
    {
    }
  };
  
  class NullPointException
  {
  public:
    std::string message;
    void* point_;

    NullPointException (const std::string& what, void* point)
    {
      message = what;
      point_ = point;
    }
    ;

    NullPointException (NullPointException& exception)
    {
      this->message = exception.message;
      this->point_ = exception.point_;
    }
    ;
  };
  
  class FileException
  {
  public:
    std::string message;
    std::string filename_;

    FileException (const std::string& what, std::string& filename)
    {
      message = what;
      filename_ = filename;
    }
    ;

    FileException (FileException& exception)
    {
      this->message = exception.message;
      this->filename_ = exception.filename_;
    }
    ;
  };
  
  class XMLException
  {
  public:
    std::string message;
    XMLNode node_;

    XMLException (const std::string& what, XMLNode& node)
    {
      message = what;
      node_ = node;
    }
    ;

    XMLException (XMLException& exception)
    {
      this->message = exception.message;
      this->node_ = exception.node_;
    }
    ;
  };
  
  class DataException
  {
  public:
    std::string message;

    DataException ()
    {
    }
    ;

    DataException (const std::string& what)
    {
      message = what;
    }
    ;

    DataException (DataException& exception)
    {
      this->message = exception.message;
    }
    ;
    
  };
  
  class DataQueueException: public DataException
  {
    DataQueueException (const std::string& what)
        : DataException (what)
    {
      
    }
    ;
  };
  
  class DataDispitcherException: public DataException
  {
    DataDispitcherException (const std::string& what)
        : DataException (what)
    {
      
    }
    ;
  };

}

#endif

