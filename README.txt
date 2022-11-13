--------------------------------
            CS 3307
 Group Project Final Submission
--------------------------------

Group 8:
 *  Julian Koksal (jkoksal)
 *  Daniel Christopher McGarr (dmcgarr)
 *  Alex Mihas (amihas)
 *  Sharon Nikritin (snikriti)
 *  River Wang (twang666)

2022-11-29

---------------
 How to build:
---------------

3rd party libraries required:
 * Wt
 * SQLite3

If these libraries are not installed in the default path, you may need to
add the g++ "-L" option to the variable "LDLIBS" in the Makefile.


To build the web server:
  make


To build the DBHelper test:
  make tests

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

