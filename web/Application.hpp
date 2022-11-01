/*

    Author : River Wang
    Date   : 2022/10/27

*/

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class Application : public Wt::WApplication {
   public:
    Application(const Wt::WEnvironment &env);

   private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
};

#endif