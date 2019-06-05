#ifndef __PARSER_H__
#define __PARSER_H__

#include "tinyxml2.h"
#include "../../../src/headers/Point.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace tinyxml2;
using namespace std;

void readFile(string, vector<Point*>*);
void readXML(string, vector<Point*>*);


#endif