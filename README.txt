CS 3307
Group Project Stage 3

Group 8:
 *  Julian Koksal (jkoksal)
 *  Daniel Christopher McGarr (dmcgarr)
 *  Alex Mihas (amihas)
 *  Sharon Nikritin (snikriti)
 *  River Wang (twang666)

2022-11-08

---
How to build
---

Assuming that the Wt library is installed to the default path.

To build all:
  make

To build the web server:
  make main

To build the DBHelper test:
  make tests

---
How to run
---

To run the web server:
  ./Main --docroot . --http-listen localhost:8080

To run the DBHelper test:
  ./TestDBHelper

