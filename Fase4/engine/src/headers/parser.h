#ifndef __PARSER_H__
#define __PARSER_H__

#include "tinyxml2.h"
#include "group.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace tinyxml2;

void readFile(string, vector<Point*>*);
int readXML(string, vector<Group*>*);


#endif