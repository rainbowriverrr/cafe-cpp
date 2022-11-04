/*

    Author : River Wang
    Date   : 2022/10/27

*/

#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <string>

class Page {
   public:
    Page(std::string path);
    ~Page();
    void render();

   private:
    std::string path;
};

#endif