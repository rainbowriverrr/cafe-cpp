--------------------------------
            CS 3307
 Group Project Final Submission
--------------------------------

Group 8:
 * Julian Koksal (jkoksal)
 * Daniel Christopher McGarr (dmcgarr)
 * Alex Mihas (amihas)
 * Sharon Nikritin (snikriti)
 * River Wang (twang666)

2022-11-29


---------------
 How to build:
---------------

3rd party libraries required:
 * Wt
 * SQLite3

If these libraries are not installed in the default path, you may need to
add the g++ "-L" option to the variable "LDLIBS" in the Makefile.

To make all:
  make all

To build the web server:
  make main

To build the tests:
  make tests

---------------------
 About the database:
---------------------

Building any of the targets above will also create the SQLite3 database and
create all of the tables.

This is the state in which the tests should be run.

The web server can be run in this state, but the pages will be empty
without any testing data.

So, before running the web server for the first time we recommend running
the Test Data Generator, which will fill the database with testing data.
This should only be run once, unless the database is reset.

To run the TestDataGenerator:
  ./TestDataGenerator


The database can be reset to its original state, where the tables have
been created but there is no test data.

To reset the database:
  make dbreset

-------------
 How to run:
-------------

To run the web server:
  ./Main --docroot . --http-listen localhost:8080

Navigate to localhost:8080 using your web browser of choice.

Note:
  The site may not function correctly with a very outdated browser.


To run the DBHelper test:
  ./TestDBHelper

To run the Authenticator test:
  ./TestAuthenticator

